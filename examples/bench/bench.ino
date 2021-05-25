// демо бенчмарка
#define OS_BENCH    // дефайн до подключения либы
#include <GyverOS.h>
GyverOS<3> OS;	// указать макс. количество задач

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // подключаем задачи (порядковый номер, имя функции, период в мс)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 500);
  
  OS.enableLoad(2000);  // включить измерение загруженности за 2000 мс
  OS.attachLoopTime(0); // подключить счётчик времени выполнения задачи 0
}

void loop() {
  OS.tick();	// вызывать как можно чаще, задачи выполняются здесь
  
  // OS.getLeft() возвращает время в мс до ближайшей задачи
  // на это время можно усыпить МК, например при помощи narcoleptic или GyverPower
  // для примера просто поставим delay на это время
  delay(OS.getLeft());
}

// обработчики задач
void f1() {
  delay(66);  // имитация бурной деятельности
}

void f2() {
  // выводим загруженность МК в порт (16%)
  Serial.println(OS.getLoad());
}

void f3() {
  // выводит время выполнения задачи и мигает светодиодом на D13
  digitalWrite(13, !digitalRead(13));
  Serial.println(OS.getLoopTime());   // последнее измеренное время
  //Serial.println(OS.getMaxLoopTime());  // макс. время
}
