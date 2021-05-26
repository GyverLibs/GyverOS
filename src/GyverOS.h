/*
    Библиотека лёгкого диспетчера задач для Arduino
    Документация: 
    GitHub: https://github.com/GyverLibs/GyverOS
    Возможности:
    - Лёгкий вес
    - Статическое выбираемое количество задач
    - Возможность остановки, отключения и прямого вызова задач
    - Вычисление времени до ближайшей задачи (для сна на этот период)
    - Встроенный бенчмарк: время выполнения задачи и загруженность процессора
    - Алгоритм работает на системном таймере millis()
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/

#ifndef GyverOS_h
#define GyverOS_h

// раскомментировать для использования бенчмарка
//#define OS_BENCH

template < uint16_t _AMOUNT >
class GyverOS {
public:
    // тикер. Вызывать как можно чаще
    void tick() {    
        #ifdef OS_BENCH
        if (loadP > 0) {
            if (millis() - loadTmr >= loadP) {
                loadTmr += loadP;
                load = (loadSum / 10ul) / loadP;  // (loadSum / 1000) / loadP * 100
                loadSum = 0;
            }
            us = micros();
        }
        #endif

        bool flag = 0;    
        for (int i = 0; i < _AMOUNT; i++) {
            if (callbacks[i] && states[i]) {   
                uint32_t left = millis() - tmrs[i];
                if (prds[i] == 0 || left >= prds[i]) {					
                    if (prds[i] > 0) tmrs[i] += prds[i] * (left / prds[i]);
                    #ifdef OS_BENCH
                    if (loopTimeNum == i) loopTime = micros();
                    #endif
                    callbacks[i]();
                    #ifdef OS_BENCH
                    if (loopTimeNum == i) {
                        loopTime = micros() - loopTime;
                        if (loopTime > loopTimeMax) loopTimeMax = loopTime;
                    }
                    #endif
                    flag = 1;
                }
            }
        }
        #ifdef OS_BENCH
        if (loadP > 0 && flag) loadSum += micros() - us;
        #endif
    }
    
    // подключить функцию обработчик задачи
    void attach(int num, void (*handler)(), uint32_t prd = 0) {
        if (num >= _AMOUNT) return;
        callbacks[num] = *handler;    
        prds[num] = prd;
        start(num);
    }
    
    // отключить функцию обработчик задачи
    void detach(int num) {
        if (num >= _AMOUNT) return;
        callbacks[num] = NULL;
    }
    
    // установить период для задачи
    void setPeriod(int num, uint32_t prd) {
        if (num >= _AMOUNT) return;
        prds[num] = prd;
        tmrs[num] = millis();
    }
    
    // запустить задачу
    void start(int num) {
        if (num >= _AMOUNT) return;
        states[num] = 1;
        tmrs[num] = millis();
    }
    
    // перезапустить задачу
    void restart(int num) {
        start(num);
    }
    
    // остановить задачу
    void stop(int num) {
        if (num >= _AMOUNT) return;
        states[num] = 0;
    }
    
    // вызвать задачу
    void exec(int num) {
        if (num >= _AMOUNT) return;
        callbacks[num]();
    }
    
    // получить время до ближайшей задачи
    uint32_t getLeft() {
        uint32_t nearPrd = UINT32_MAX;
        uint32_t tm;
        for (int i = 0; i < _AMOUNT; i++) {
            if (callbacks[i] && states[i]) {
                uint32_t tm = prds[i] + tmrs[i] - millis();
                nearPrd = min(nearPrd, tm);     
            }
        }
        return nearPrd;
    }
    
    // ====== БЕНЧМАРК ======
    // подключить счётчик времени выполнения задачи и сбросить максимум
    void attachLoopTime(int num) {
        #ifdef OS_BENCH
        loopTimeNum = num;
        loopTimeMax = 0;
        #endif
    }
    
    // отключить счётчик времени выполнения задачи
    void detachLoopTime() {
        #ifdef OS_BENCH
        loopTimeNum = -1;
        #endif
    }
    
    // получить текущее время выполнения выбранной ранее задачи в мкс
    uint32_t getLoopTime() {
        #ifdef OS_BENCH
        return loopTime;
        #else
        return 0;
        #endif
    }
    
    // получить максимальное время выполнения выбранной ранее задачи в мкс
    uint32_t getMaxLoopTime() {
        #ifdef OS_BENCH
        return loopTimeMax;
        #else
        return 0;
        #endif
    }	
    
    // получить загруженность процессора в процентах
    int getLoad() {
        #ifdef OS_BENCH
        return load;
        #else
        return 0;
        #endif
    }
    
    // включить измерение загруженности процессора за указанный период в мс
    void enableLoad(uint32_t loadp = 1000) {
        #ifdef OS_BENCH
        loadP = loadp;
        loadTmr = millis();
        loadSum = 0;
        #endif
    }
    
    // отключить измерение загруженности процессора
    void disableLoad() {
        #ifdef OS_BENCH
        loadP = 0;
        #endif
    }

private:
    void (*callbacks[_AMOUNT])() = {};
    uint32_t tmrs[_AMOUNT], prds[_AMOUNT], loopTime = 0, loopTimeMax = 0;
    bool states[_AMOUNT];
#ifdef OS_BENCH
    uint32_t loadP = 0, us = 0, loadTmr = 0, loadSum = 0;
    int load = 0, loopTimeNum = -1;
#endif
};
#endif
