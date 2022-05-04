# GyverOS
Lightweight task manager library for Arduino
- A light weight
- Static selectable number of tasks
- Ability to stop, disable and directly call tasks
- Calculation of time to the nearest task (for sleep for this period)
- Built-in benchmark: task execution time and processor load
- The algorithm works on the millis() system timer

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverOS** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/GyverOS/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE %D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
GyverOS<5>OS; // specify max. number of tasks
```

<a id="usage"></a>
## Usage
```cpp
void setMicros(bool mode); // enable microsecond mode (true)
void tick(); // ticker. Call as often as possible
void attach(int num, void (*handler)(), uint32_t prd = 0); // connect the task handler function
void detach(int num); // disable the task handler function
void setPeriod(int num, uint32_tprd); // set the period for the task
void start(int num); // run task
void restart(int num); // restart task
void stop(int num); // stop task
void exec(int num); // call task
uint32_t getLeft(); // get the time until the next task

// ====== BENCHMARK ======
void attachLoopTime(int num); // connect the task execution time counter and reset the maximum
void detachLoopTime(); // disable the task execution time counter
uint32_t getLoopTime(); // get the current execution time of the previously selected task in µs
uint32_t getMaxLoopTime(); // get the maximum execution time of the previously selected task in µs
void enableLoad(uint32_tloadp); // enable measurement of processor load for the specified period in ms
void disableLoad(); // disable CPU utilization measurement
int getLoad(); // get CPU usage in percent

// === DEFINE SETTINGS ===
// declare BEFORE linking the library
#define OS_BENCH // connect the benchmark module (performance test)
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
// task manager demo

#include <GyverOS.h>
GyverOS<5>OS; // specify max. number of tasks

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // connect tasks (serial number, function name, period in ms)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 200);
  
  //OS.detach(0); // disable task 0
  //OS.setPeriod(0, 200); // change task period 0 to 200 ms
  //OS.start(0); // start task 0
  //OS.stop(0); // stop task 0
  //OS.exec(0); // do task 0 now
}

void loop() {
  OS.tick(); // call as often as possible, tasks are performed here
  
  // OS.getLeft() returns the time in ms to the nearest task
  // at this time, you can put the MK to sleep, for example, using narcoleptic or GyverPower
  // for example, just set delay for this time
  delay(OS.getLeft());
}

// task handlers
void f1() {
  // outputs its period to the port
  static uint32_tms;
  Serial.println(millis() - ms);
  ms = millis();
}

void f2() {
  static uint32_tms;
  // outputs its period to the port
  Serial.println(millis() - ms);
  ms = millis();
}

void f3() {
  // outputs its period to the port and blinks the LED on D13
  digitalWrite(13, !digitalRead(13));
  static uint32_tms;
  Serial.println(millis() - ms);
  ms = millis();
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - added microsecond mode
- v1.2 - added microsecond mode to the class

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!