# Pill-O-Matic: Real-Time Scheduled Automatic Pill Dispenser

- Arduino-based automatic pill dispenser with sensor-driven safety logic and stepper-controlled mechanical dispensing.

## Documentation

- [System Design and Implementation](Pill-O-Matic_System_Design_and_Implementation.md) 
- [Project Summary](Pill-O-Matic_Project_Summary.md) 

## Demonstration
[![Pill-O-Matic Demo](images_and_videos/Device_Demonstration/37.png)](https://github.com/user-attachments/assets/4b54a555-bc47-4cf3-90d2-f38e5f574e28)

## Project Overview

Pill-O-Matic is a real-time scheduled automatic pill dispenser designed to deliver single doses of medication at predefined times throughout the day. The system integrates sensing, timing, control logic, and mechanical actuation to ensure reliable and user-aware dispensing.

An Arduino Uno coordinates the system using a DS3231 real-time clock (RTC) module for accurate scheduling. At each scheduled time, the system verifies tray presence using an analog Hall effect sensor before actuating a stepper motor to rotate a compartmentalized pill wheel and dispense one dose. The system prevents incorrect operation through state-based logic, ensuring pills are only dispensed when appropriate conditions are met.

## Technical Highlights

- **Embedded firmware development:** Programmed Arduino control logic for RTC-based scheduling, Hall sensor tray detection, LED status feedback, and stepper motor actuation.
- **Electromechanical system integration:** Integrated sensing, timing, motor control, and mechanical dispensing into a coordinated automated medication system.
- **Sensor-based safety control:** Used tray-presence detection to prevent dispensing when the tray is missing and reduce the risk of duplicate or unsafe dispensing.
- **Real-time scheduled operation:** Implemented DS3231 RTC-based dose timing so dispensing events occur autonomously at predefined medication times.
- **Indexed stepper motor control:** Drove a 28BYJ-48 stepper motor through a ULN2003 driver to rotate the pill wheel by fixed increments for single-dose dispensing.
- **State-based control logic:** Structured system behavior around idle, tray-missing, dispensing, and pill-waiting states for predictable user interaction.
- **Power-conscious actuator design:** De-energized the stepper motor when idle to reduce heat, current draw, and unnecessary standby power use.
- **Rapid hardware prototyping:** Fabricated and tested a mixed-material prototype combining 3D-printed PLA mechanisms, embedded magnets, a plywood lid, and cardboard-mounted electronics.

## Key Features

- Real-time scheduled dispensing using RTC-based timing  
- Sensor-based tray detection using analog Hall effect sensor (SS49E)  
- Stepper motor-driven mechanical indexing (45° per dose)  
- State-based control logic to prevent missed or duplicate dispensing  
- User interaction detection via tray removal (no buttons required)  
- Energy-efficient motor control with zero idle current draw  

## System Architecture

- **Controller:** Arduino Uno  
- **Timing Module:** DS3231 Real-Time Clock (RTC)  
- **Sensor:** SS49E Analog Hall Effect Sensor  
- **Actuator:** 28BYJ-48 5V Stepper Motor + ULN2003 Driver  
- **User Feedback:** Red and Green LEDs  
- **Power:** External 5V supply for motor (shared ground with Arduino)  



## System Operation

1. The RTC continuously tracks real time  
2. The Arduino checks scheduled dispensing times  
3. The Hall sensor verifies tray presence  
4. If conditions are met, the stepper motor rotates 45° to dispense one dose  
5. The system waits for tray removal before allowing the next dispense  
6. If the tray is missing or a pill is still present, dispensing is blocked  



## Fabrication and Materials

- 3D-printed PLA pill wheel and tray for precise geometry  
- Plywood lid for enclosure support and accessibility  
- Solderless breadboard for circuit prototyping  
- Embedded magnets for tray detection  



## Key Design Decisions

- Selected Hall effect sensing over force-based detection due to low pill weight, improving reliability  
- Implemented state-based logic to handle missed doses and prevent unsafe operation  
- Disabled stepper motor holding current to reduce power consumption and prevent overheating  
- Designed mechanical clearances to ensure smooth motion without post-processing  
- Used a hybrid material approach (PLA + plywood) to balance precision and structural simplicity  

## Future Improvements

- Improve enclosure robustness and overall durability  
- Integrate user interface (LCD display or alert system)  
- Add battery power for standalone operation  
- Enable wireless connectivity for remote monitoring and notifications  
- Expand system with data logging and health tracking features  



## Outcome

This project demonstrates the successful design and integration of an electromechanical system combining hardware, firmware, and mechanical components. The final prototype reliably performs time-based dispensing with sensor-driven safety logic and efficient power management, showcasing practical engineering problem-solving and system-level thinking.
