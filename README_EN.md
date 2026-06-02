This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverOS.svg?color=brightgreen)](https://github.com/GyverLibs/GyverOS/releases/latest/download/GyverOS.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverOS.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverOS)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverOS?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

|в️в️в️<br>**A more powerful and interesting tool has appeared[Looper](https://github.com/GyverLibs/Looper)- also a task manager, but with much greater capabilities**<br>,️,️️|
| --- |

# GyverOS
Light Task Manager Library for Arduino
- Lightweight.
- Static number of tasks selected
- Ability to stop, disconnect and directly call tasks
- Calculating the time to the nearest task (to sleep for this period)
- Built-in benchmark: task execution time and processor load
- The algorithm runs on the system timer millis()

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverOS** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverOS/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
GyverOS<5> OS;	// indicate max. task
```

<a id="usage"></a>
## Use of use
```cpp
void setMicros(bool mode);          // Turn on the microsecond mode (true)
void tick();                        // ticker. Call as often as possible
void attach(int num, void (*handler)(), uint32_t prd = 0);  // connect the task handler function
void detach(int num);               // disable the task handler function
void setPeriod(int num, uint32_t prd);  // periodize
void start(int num);                // set up
void restart(int num);              // reset
void stop(int num);                 // stop
void exec(int num);                 // challenge
uint32_t getLeft();                 // Get time for the next task

// =============
void attachLoopTime(int num);       // connect the task time counter and reset the maximum
void detachLoopTime();              // turn off the task time counter
uint32_t getLoopTime();             // Get the current time of execution of the previously selected task in mx
uint32_t getMaxLoopTime();          // Get the maximum time to perform the previously selected task in mx
void enableLoad(uint32_t loadp);    // include the measurement of the processor load for the specified period in ms
void disableLoad();                 // disable processor load measurement
int getLoad();                      // Get processor load in percentage

// = === DEFINIONS OF ATTRUCTIONS ===
// declare before connecting the library
#define OS_BENCH    // connect the benchmark module (performance test)
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
// demo task manager

#include <GyverOS.h>
GyverOS<5> OS;	// indicate max. task

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // connect tasks (serial number, function name, period in ms)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 200);
  
  //OS.detach(0); // disable task 0
  //OS.setPeriod(0, 200) // change task period 0 to 200 ms
  //OS.start(0); // Launch task 0
  //OS.stop(0); // stop task 0
  //OS.exec(0) To complete task 0 now
}

void loop() {
  OS.tick();	// As often as possible, tasks are performed here.
  
  // OS.getLeft() returns time to MS to the nearest task
  // MK can be euthanized at this time, for example with narcoleptic or GyverPower.
  // For example, let’s put a delay on this time.
  delay(OS.getLeft());
}

// taskmaster
void f1() {
  // port out
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}

void f2() {
  static uint32_t ms;
  // port out
  Serial.println(millis() - ms);
  ms = millis();
}

void f3() {
  // takes its period to port and flashes LED on the D13
  digitalWrite(13, !digitalRead(13));
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - added microsecond mode
- v1.2 - introduced microsecond mode in the class
- v1.2.1 - increased stability

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
