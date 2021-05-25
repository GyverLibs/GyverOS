// демо диспетчера задач

#include <GyverOS.h>
GyverOS<5> OS;	// указать макс. количество задач

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // подключаем задачи (порядковый номер, имя функции, период в мс)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 200);
  
  //OS.detach(0);         // отключить задачу 0
  //OS.setPeriod(0, 200); // сменить период задачи 0 на 200 мс
  //OS.start(0);          // запустить задачу 0
  //OS.stop(0);           // остановить задачу 0
  //OS.exec(0);           // выполнить задачу 0 сейчас
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
  // выводит свой период в порт
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}

void f2() {
  static uint32_t ms;
  // выводит свой период в порт
  Serial.println(millis() - ms);
  ms = millis();
}

void f3() {
  // выводит свой период в порт и  мигает светодиодом на D13
  digitalWrite(13, !digitalRead(13));
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}
