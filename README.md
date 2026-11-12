# Arduino Projects

A collection of Arduino UNO projects with source sketches (`.ino`), pre-compiled Proteus binaries (`.ino.hex`), and lab manuals (`.pdf`).

## Projects

| Project | Description | Source Code | Proteus Binary | Lab Report / Manual |
| --- | --- | --- | --- | --- |
| **Smart Door Lock** | Password-based door lock using 4×3 Keypad, 16×2 LCD, and Servo motor | [`Smart_door_lock.ino`](Smart_door_lock/Smart_door_lock.ino) | [`Smart_door_lock.ino.hex`](Smart_door_lock/build/arduino.avr.uno/Smart_door_lock.ino.hex) | [`Password_Based_Smart_Door_Lock_Lab_Guide.pdf`](Smart_door_lock/Lab_report/Password_Based_Smart_Door_Lock_Lab_Guide.pdf) |
| **Smart Automatic Dustbin** | Touchless ultrasonic dustbin lid controller using Servo motor | [`Smart_Automatic_Dustbin.ino`](Smart_Automatic_Dustbin/Smart_Automatic_Dustbin.ino) | [`Smart_Automatic_Dustbin.ino.hex`](Smart_Automatic_Dustbin/build/arduino.avr.uno/Smart_Automatic_Dustbin.ino.hex) | [`Smart_Automatic_Dustbin_Proteus_Lab_Manual.pdf`](Smart_Automatic_Dustbin/Lab_report/Smart_Automatic_Dustbin_Proteus_Lab_Manual.pdf) |
| **Solar Monitoring System** | Solar panel voltage, current (ACS712), and power monitoring on 20×4 LCD | [`Solar_Monitoring_System_Lab_Manual_.ino`](Solar_Monitoring_System_Lab_Manual_/Solar_Monitoring_System_Lab_Manual_.ino) | [`Solar_Monitoring_System_Lab_Manual_.ino.hex`](Solar_Monitoring_System_Lab_Manual_/build/arduino.avr.uno/Solar_Monitoring_System_Lab_Manual_.ino.hex) | — |

## Running in Proteus (without compiling)

1. Open your Proteus schematic and double-click the **Arduino UNO** component.
2. In **Program File**, select the project's `.ino.hex` file from `build/arduino.avr.uno/`.
3. Set clock frequency to `16 MHz` (if available) and run the simulation.

## Compiling from Source

1. Open the project's `.ino` file in **Arduino IDE**.
2. Install any required libraries (e.g., `Keypad`, `LiquidCrystal`, `Servo`).
3. Select **Tools → Board → Arduino AVR Boards → Arduino Uno** and upload or use **Sketch → Export Compiled Binary**.
