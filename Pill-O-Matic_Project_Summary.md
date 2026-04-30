# Pill-O-Matic: Real-Time Scheduled Automatic Pill Dispenser

## Project Description

Designed and built a real-time clock-based automatic pill dispenser that delivers single doses at predefined times throughout the day. The system integrates sensing, control logic, and mechanical actuation to ensure reliable and user-aware dispensing.

An Arduino Uno coordinates the system using a DS3231 real-time clock (RTC) module for accurate scheduling. At each scheduled time, the system verifies tray presence using an analog Hall effect sensor before actuating a 28BYJ-48 stepper motor (via ULN2003 driver) to rotate a compartmentalized pill wheel and dispense one dose. Visual feedback is provided through LEDs to indicate system status and user interaction.

The system implements a state-based control logic to prevent incorrect operation, including blocking dispensing when the tray is absent and detecting tray removal as confirmation that the user has taken the medication. Additionally, the motor is actively de-energized after each movement to eliminate idle current draw and reduce thermal load.

## Key Contributions and Skills Demonstrated

- **Embedded Systems & Control Logic**
  - Developed real-time scheduling using RTC integration and Arduino firmware
  - Implemented state-machine logic for safe dispensing and user interaction tracking

- **Hardware Integration**
  - Integrated sensors, actuators, and driver circuits into a cohesive system
  - Designed and debugged full circuit on a solderless breadboard

- **Electromechanical System Design**
  - Designed and fabricated a rotating pill wheel and tray using 3D-printed PLA
  - Integrated motor-driven actuation with mechanical indexing (45° per dose)

- **Power Optimization**
  - Identified and resolved stepper motor idle current issue by implementing coil de-energization in software

- **System Reliability & Safety**
  - Implemented logic to prevent double dispensing and detect missed doses
  - Designed user-aware interactions using sensor feedback instead of manual inputs

## Fabrication and Materials

- 3D-printed PLA components for pill wheel and tray
- Plywood lid for structural support and accessibility
- Breadboard-based circuit for rapid prototyping and testing

## Outcome

Successfully developed a fully functional prototype demonstrating reliable time-based dispensing, accurate mechanical actuation, and robust sensor-driven control. The project highlights the ability to design and integrate hardware, firmware, and mechanical systems into a complete working device.

## Future Improvements

- Refine enclosure design for durability and manufacturability
- Add user interface (LCD display or alert system)
- Integrate battery power and wireless connectivity for standalone operation
