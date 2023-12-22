This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyveros
Little Library of Tasks for Arduino
- A light weight
- Static selected number of tasks
- the possibility of stopping, disconnecting and direct calling tasks
- Caluation of time to the nearest task (for sleeping for this period)
- Built -in benchmark: the time of the task and the processor workload
- the algorithm works on the system timer Millis ()

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyveros ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyveros/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Gyveros <5> OS;// indicate Max.The number of tasks
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID setmicros (Bool Mode);// Turn on the microsecond mode (True)
VOID Tick ();// ticker.Call
Void attach (int num, void (*handler) (), uint32_t PRD = 0);// Connect the task processor function
VOID Detach (int num);// Disable the function of the problem processor
VOID setperiod (int num, uint32_t PRD);// set the period for the task
VOID Start (int num);// Launch the task
VOID RESTART (int num);// restart the task
VOID Stop (int num);// Stop the task
VOID Exec (int num);// Call the task
uint32_t getleft ();// Get the time to the next task

// ====== Benchmark ========
Void attachlooptime (int num);// Connect the time of the time of the task and reset the maximum
VOID Detachlooptime ();// Disconnect the time of the task of the task
uint32_t getlooptime ();// get the current time of the previously selected task in the ISS
uint32_t getmaxlooptime ();// Get the maximum execution time of the selected ptasks in the ISS
VOID ENABLELOAD (Uint32_T Loadp);// Enable the measurement of the processor workshop for the specified period in MS
VOID DISABLELOAD ();// Disable the measurement of processor workload
int Getload ();// Get processor workload as a percentage

// === The defines of settings ====
// announce before connecting the library
#define os_bench // Connect the Benchmark module (performance test)
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
// Demo dispatcher of tasks

#include <gyveros.h>
Gyveros <5> OS;// indicate Max.The number of tasks

VOID setup () {
  Serial.Begin (9600);
  Pinmode (13, output);
  
  // We connect the tasks (serial number, function name, period in MS)
  OS.TTACH (0, F1, 400);
  OS.ATTACH (1, F2, 1000);
  OS.TTACH (2, F3, 200);
  
  //Os.detach (0);// Disable the task 0
  //Os.Setperiod (0, 200);// Change the period of problem 0 by 200 ms
  //Os.start(0);// Run the problem 0
  //Os.stop(0);// Stop the problem 0
  //OS.Exec(0);// Complete the problem 0 now
}

VOID loop () {
  OS.Tick ();// call as often as possible, the tasks are performed here
  
  // os.getleft () returns the time to the MS to the nearest task
  // At this time, you can sleep MK, for example, using Narcoleptic or Gyverpower
  // For example, just put DELAY for this time
  Delay (os.getleft ());
}

// Task handlers
VOID F1 () {
  // takes its period to the port
  static uint32_t ms;
  Serial.println (Millis () - MS);
  MS = Millis ();
}

VOID F2 () {
  static uint32_t ms;
  // takes its period to the port
  Serial.println (Millis () - MS);
  MS = Millis ();
}

VOID F3 () {
  // Bods its period to the port and flashes with LED on D13
  DigitalWrite (13,! DigitalRead (13));
  static uint32_t ms;
  Serial.println (Millis () - MS);
  MS = Millis ();
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - added a microsecond mode
- v1.2 - introduced a microsecond mode in class
- v1.2.1 - increased stability

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code