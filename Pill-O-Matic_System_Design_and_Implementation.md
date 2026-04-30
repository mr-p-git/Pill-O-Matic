# Pill-O-Matic: Real-Time Scheduled Automatic Pill Dispenser

## Project Description

This project presents the design and implementation of a real-time clock-based automatic pill dispenser that delivers medication at predefined times throughout the day. The system integrates sensing, timing, control logic, and actuation to ensure reliable and user-aware dispensing. The core of the system is an Arduino Uno, which coordinates all subsystems. A DS3231 real-time clock module provides accurate timekeeping and enables scheduling of multiple daily dose times. At each scheduled time, the system checks the state of the pill tray using an analog Hall effect sensor (SS49E), which detects whether the tray is inserted via mini magnets. If the tray is in place, a 28BYJ-48 5V stepper motor, driven by a ULN2003 driver, rotates a compartmentalized pill wheel by 45 degrees to dispense one dose. A green LED indicates that a pill has been dispensed and is waiting in the tray, while a red LED indicates that the tray is missing and dispensing is temporarily blocked. The system implements state-based control logic to ensure safe and correct operation, including detecting tray removal as a user action to take the medication and preventing dispensing when:

- the tray was not removed following the dispense of a previous dose, indicating that the user forgot to take the pills, and the pills are still in the tray.
- the tray is absent, indicating that the user forgot to return the tray.

The mechanical structure of the dispenser consists of a 3D-printed pill wheel and tray, fabricated using PLA to enable precise geometry and rapid prototyping of the rotating compartment system, while providing rigidity and stability for mounting the motor and holding multiple doses of medication. A plywood lid is used to enclose and support the top of the device, allowing easy access for maintenance and refilling. This combination of materials allows for a balance between cost, manufacturability, structural support, and ease of modification during the design process. Additionally, the motor is fully de-energized after each movement to minimize power consumption and prevent overheating. The circuit is implemented on a solderless breadboard as a functional prototype, demonstrating a complete and integrated electromechanical system without permanent embedded hardware fabrication.The system was validated through repeated testing across multiple scheduled events, demonstrating reliable time-based triggering, consistent mechanical dispensing, and stable sensor-driven state transitions. Future work may focus on improving enclosure robustness, integrating a user interface such as an LCD display or alert system, and enabling wireless connectivity for remote monitoring and configuration, moving the design toward a deployable assistive device.

## Key Features

- Time-based automated pill dispensing using RTC scheduling
- Sensor-driven safety logic to prevent incorrect dispensing
- Mechanical indexing system with precise 45° rotation per dose
- Energy-efficient motor control with zero idle current draw
- User-aware interaction via tray detection instead of manual input

## Design Constraints

1. Budget control: $200 max
2. Include electrical, mechanical, and software/firmware system

## Engineering Challenges and Design Decisions

- Selected Hall effect sensing over force-based detection after determining that pill mass was insufficient for reliable actuation, improving system robustness.
- Implemented state-based control logic to handle edge cases such as missed doses and tray removal, ensuring safe and predictable operation.
- Optimized stepper motor control by eliminating idle coil energization, reducing power consumption and preventing thermal buildup.
- Designed precise mechanical interfaces using calibrated clearances (0.2–0.6 mm) to ensure proper fits and reliable motion without post-processing.
- Balanced material selection by combining 3D-printed PLA for complex geometry and plywood for structural simplicity and accessibility.

## System Architecture

### Microcontroller

- Arduino UNO R3: program the RTC so that at a preset time, pill would be dispensed. Program the Stepper motor to rotate 1/8 of a full rotation everytime it receives a signal from the RTC.

### Input Devices

- DS3231 RTC module: a real-time-clock module. Pre-set time to take pill (e.g 8:00 a.m. EST). Sends signal to stepper motor to rotate 1/8 of a full rotation, turns on Green LED when it's time to take pill.

  ![DS3231 RTC](images_and_videos/Plan/1_1.png)

- Hall Effect Sensor SS49E: senses wheter the pill tray is inserted or removed. If removed, lights up Red LED to remind user to return pill tray, and also prevent dispensing of next pill while tray is removed.

  ![DS3231 RTC](images_and_videos/Plan/1_2.png)

### Output Devices

- ULN2003 Driver Board & Stepper Motor 28BYJ-48: rotates 1/8 turn to dispense next dose of pill, when signal recieved from RTC module.
- Green LED: turns on when signal recieved from RTC module, reminding user it is time to take pill. Turns off when pill tray removal detected through input of hall effect sensor.
- RED LED :turns on when tray is removed, turns off when tray is returned. Using hall effect sensor, and embedded magnet in the tray.

### Actuator

- ULN2003 Driver Board & Stepper Motor 28BYJ-48: rotates 1/8 turn to dispense next dose of pill, when signal recieved from RTC module.

### Sensor

- Magnet & Hall Effect Sensor SS49E: senses wheter the pill tray is inserted or removed.

## Materials used

1. Prusament PLA for:
   - Chamber leaves
   - Container Base (body of Automatic Pill Dispenser)
   - Pill tray

2. Plywood for:
   - Lid

## Bill of Materials

| Item No. | Item Name                                   | Description                                              | Quantity | Source                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     | Cost ($)               |
| -------- | ------------------------------------------- | -------------------------------------------------------- | -------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------- |
| 1        | Arduino Uno R3                              | Main microcontroller board controlling entire system     | 1        | [Amazon](https://www.amazon.ca/Elegoo-Board-ATmega328P-ATMEGA16U2-Arduino/dp/B01EWOE0UU/ref=sr_1_7?crid=3I0B9PW1MPR5O&dib=eyJ2IjoiMSJ9.MazmhFfn-DF8W5oyX_S-tG7UKTuvL-UsrsK_gfaMyT6ItHsZxjaDRfl9dGrMgclYcrscUldWWZgGQfoCNxobQCtmkWU5dnJ8IoSsgSFbBzSswauoxCF8LZ6wpdYC-1_ITdPmKG20uYIfmPf6vCgkTkUwTBzVElun8Juh4opnElfx_jRe2IlxjXemIM5vP_xATHDhCVO0-ddgPUML_Ox0inarQu-U0r0VMrkZ1NadScE4ZP6IgmBzVy5jFx7wZg3iYrko6iAguirkxTk338FjJTc5AX1YNyKtCTAgI-UJN7A.L40GaZRgPCcCf3v9NU2VMcolWi-Pu2WNYYya9SkSlfw&dib_tag=se&keywords=arduino+uno&qid=1773714849&sprefix=arduino+uno%2Caps%2C176&sr=8-7)                                                                      | 21.99                  |
| 2        | DS3231 RTC Module                           | Real-time clock module for scheduling pill dispensing    | 1        | [Amazon](https://www.amazon.ca/DS3231-Precision-Memory-Arduino-Raspberry/dp/B07F1349S3/ref=sr_1_4_sspa?crid=1GWFWW7DKF8A0&dib=eyJ2IjoiMSJ9.oB7v-c6Vk0NfYfowC0AsiYxHx00wsu0QG1w1QfHXW-urRd91aMP6Ud9AKPFtJB8o4uTAfrb6wvVh0xvTnlOiOW16xSpkEWoTGEqmYk8qajHScDYAKOX6CEyBrQdH3Lf85oN263Ej3gdqeIH7-bqAP4Q8oJnMZYmw5Ywn_2wQYF4DZis8YJlttGJBSI4IqG_Z9Us_LBSzUU0VTAThOO6dYaNxcs9RjGFMqn4CGuOn3rkbrEc2DW6T8e6qB29dW2XKSVELfSdBUulbECqbiXC6W1mpQmXbWf1gCljFGLuEiRw.HKvqZpIDv9daKdlUd_5Uj-U83yUYXpO3wu7qC0rar_k&dib_tag=se&keywords=Real+Time+Clock+Module&qid=1774105361&sprefix=real+time+clock+module%2Caps%2C115&sr=8-4-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) | 4.63                   |
| 3        | ULN2003 Driver + 28BYJ-48 Stepper Motor set | 5V stepper motor for rotating pill wheel                 | 1        | [Amazon](https://www.amazon.ca/Stepper-ULN2003-Driver-28BYJ-48-4-Phase/dp/B0B1F3DJYF/ref=asc_df_B0B1F3DJYF?tag=bingshopdesk-20&linkCode=df0&hvadid=79852225270018&hvnetw=o&hvqmt=e&hvbmt=be&hvdev=c&hvlocint=&hvlocphy=124419&hvtargid=pla-4583451691276140&psc=1)                                                                                                                                                                                                                                                                                                                                                                                         | 5.82                   |
| 4        | Hall Effect Sensor (SS49E)                  | Magnetic sensor for detecting tray insertion and removal | 1        | [Newark](https://canada.newark.com/honeywell/ss49e/hall-effect-sensor-linear-sip/dp/09J1786)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               | 0.89                   |
| 5        | Mini Disc Magnets (5×3 mm)                  | Magnets used to trigger Hall effect sensor               | 4        | [Amazon](https://www.amazon.ca/dp/B09MMX6NN3?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | 0.8                    |
| 6        | Green LED                                   | Indicates pill dispensed / waiting state                 | 1        | [Newark](https://www.newark.com/multicomp-pro/mcl034lgd/led-green-t-1-3mm-3-2mcd-570nm/dp/14N9376?MER=sy-me-pd-mi-alte)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    | 1.05                   |
| 7        | Red LED                                     | Indicates tray missing / system status                   | 1        | [Newark](https://www.newark.com/broadcom/hlmp-d150/led-5mm-red-3mcd-637nm/dp/39K9949)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      | 0.60                   |
| 8        | 220Ω Resistors                              | Current-limiting resistors for LEDs                      | 2        | [Amazon](https://www.amazon.ca/uxcell-Tolerance-Resistors-Electronic-Experiments/dp/B07LGLC192/ref=sr_1_8?dib=eyJ2IjoiMSJ9.8GqzpZJFU9LOQx8coTzjOLibtE_z_mf_WvG9PTVEQBorexROu5a03QgyqHNOiZQ091iratU-fTHxeEYXx9IeyY3Jaqr2xcTtTVl4_0Q6muUMT4ETO8WyC5ekVDIDkCjVRK4N_JS0kkoGtiYPfLYFV_dNNDZnuZJ1d_7aWqo7UiZ_I99bh4ryYk9nVRATp3YWkuB6LN2Y3DPmp7Szw8zUi7VaSVc76rcB1JBDmPbFLtpsuiw7z3AgnBynw7OCzZ-SBsqV9ZpBNpRaN3GBdDzOi8wJV95jVk91hnHUPD61x8w.alN_BDFiGbyyG71bo4gt1-KbcuEMMnAKK-6Y37R8tZ0&dib_tag=se&keywords=220+ohm+resistor&qid=1774106643&sr=8-8)                                                                                                             | 0.1                    |
| 9        | Breadboard                                  | Prototyping board for circuit connections                | 1        | [Amazon](https://www.amazon.ca/Breadboard-Solderless-Prototype-Distribution-Connecting/dp/B01EV6LJ7G/ref=sr_1_3?crid=15L27Y4G3S39F&dib=eyJ2IjoiMSJ9.x1RtHO-Ps7kZi3pQXJMAjh3ppacHE2MnI1t8pl9Ya447yy3rBz3mCvgl6mabmmQtEMvPOS9yQSDqj_T4Q_qR70HVkqQawCo1lbWjsJfou53uFrN554qXbHSKr90WqCpfBlp7_MBXpPyhFgHguOMyYgT7fHvdwLuNlEX7Vmh1Ig0jWv1OlStOzSuZxGC8P0SD1oudUFTQmozEm-ZghgzXgK82heeIqzGotIxHIjQ_8xCNjHNCsd2-RWkhBUaujJDlosIB-yBpKOio1CZK_puylhXOK73GbmKkNNbs_xhZ2Vs.a3tQZK5MRoPMJfw69gjdv_NOdONnyEy3-UXkETSIZ8c&dib_tag=se&keywords=Breadboard&qid=1774106496&s=industrial&sprefix=breadboard%2Cindustrial%2C81&sr=1-3&th=1)                                   | 4.33                   |
| 10       | Jumper Wires                                | Used for electrical connections                          | 1 unit   | [DigiKey](https://www.digikey.ca/en/products/detail/encore-wire/C2003A-12-02/4455018)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      | 1.65                   |
| 11       | Prusament PLA                               | Used for 3D printed parts                                | 267.51 g | Local hardware store                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | 7.49                   |
| 12       | Plywood                                     | Used for top lid                                         | 1        | Local hardware store                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | 1.5                    |
| 13       | Screws                                      | Used to secure the stepper motor to the container base   | 2        | Local hardware store                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | 0.2                    |
|          |                                             |                                                          |          |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            | **Total Cost: $51.05** |

## Concept Development

![Rough Draft](images_and_videos/Plan/3.png)

## System Operation

### Initial Design Flow Chart

![Initial Design Flow Chart](images_and_videos/Plan/2_1.png)

### Finalized Design Flow Chart

![Finalized Design Flow Chart](images_and_videos/Plan/2_2.jpg)

## CAD of Automatic Pill Dispenser

### Components

Click [here](files/1_CAD_pill-dispenser/) to view the CAD files and Exploded View Drawings.

- Chamber Leaves
- Container Base
- Pill Tray

### Total Clearance used in design

| Fit Type          | Total Clearance |
| ----------------- | --------------- |
| Loose sliding fit | 0.6 mm          |
| Sliding fit       | 0.4 mm          |
| Tight fit         | 0.2 mm          |

### Chamber Leaves

#### Top view

![Chamber Leaves](images_and_videos/CAD/leaves_1.png)

#### Side view 1

![Chamber Leaves](images_and_videos/CAD/leaves_2.png)

#### Side view 2

![Chamber Leaves](images_and_videos/CAD/leaves_3.png)

#### Isometric

![Chamber Leaves](images_and_videos/CAD/leaves_4.png)

### Container Base

#### Top view

![Container Base](images_and_videos/CAD/container_1.png)

#### Side view

![Container Base](images_and_videos/CAD/container_2.png)

#### Side view

![Container Base](images_and_videos/CAD/container_3.png)

#### Isometric 1

![Container Base](images_and_videos/CAD/container_4.png)

#### Isometric 2

![Container Base](images_and_videos/CAD/container_5.png)

### Pill Tray

#### Top view

![Pill Tray](images_and_videos/CAD/tray_1.png)

#### Side view

![Pill Tray](images_and_videos/CAD/tray_2.png)

#### Front view

![Pill Tray](images_and_videos/CAD/tray_3.png)

#### Isometric

![Pill Tray](images_and_videos/CAD/tray_4.png)

### Assembly

#### Top view

![Assembly](images_and_videos/CAD/assembly_1.png)

#### Isometric 1

![Assembly](images_and_videos/CAD/assembly_2.png)

#### Isometric 2

![Assembly](images_and_videos/CAD/assembly_3.png)

#### Exploded View

![Exploded View](images_and_videos/CAD/exploded_view.png)

## 3D Printing of Parts

#### Overview of the 3D Printed Parts
Pill-O-Matic: Real-Time Scheduled Automatic Pill Dispenser
Click [here](files/3_3d_print_pill-dispenser/) to view the 3D printing files.

![Overview of the 3D Printed Parts](images_and_videos/3D_Printing_and_Results/0.png)
![Overview of the 3D Printed Parts](images_and_videos/3D_Printing_and_Results/11.png)
![Overview of the 3D Printed Parts](images_and_videos/3D_Printing_and_Results/32.png)
![Overview of the 3D Printed Parts](images_and_videos/3D_Printing_and_Results/31.png)

#### Print Results

![Results](images_and_videos/3D_Printing_and_Results/40.jpg)
![Results](images_and_videos/3D_Printing_and_Results/41.jpg)
![Results](images_and_videos/3D_Printing_and_Results/42.jpg)
![Results](images_and_videos/3D_Printing_and_Results/43.jpg)
![Results](images_and_videos/3D_Printing_and_Results/44.jpg)

## Subsystem Validation

### Hall Effect Sensor Module

#### Overview

![Hall Effect Sensor Module](images_and_videos/Device_Demonstration/13.jpg)
![Hall Effect Sensor Module](images_and_videos/Device_Demonstration/10.jpg)

#### Breadboard wiring

![Hall Effect Sensor Module](images_and_videos/Device_Demonstration/11.jpg)

#### Arduino UNO wiring

![Hall Effect Sensor Module](images_and_videos/Device_Demonstration/12.jpg)

#### CLICK IMAGE BELOW TO VIEW VIDEO

[![Hall Effect Sensor Module](images_and_videos/Device_Demonstration/14.png)](images_and_videos/Device_Demonstration/14.mp4)

### RTC Module

#### Overview

![RTC Module](images_and_videos/Device_Demonstration/20.jpg)

#### Arduino UNO wiring

![RTC Module](images_and_videos/Device_Demonstration/21.jpg)

#### CLICK IMAGE BELOW TO VIEW VIDEO

[![RTC Module](images_and_videos/Device_Demonstration/22.png)](images_and_videos/Device_Demonstration/22.mp4)

## Final System Circuit Diagram

Click [here](images_and_videos/Plan/Pill-O-Matic_circuit.png) to view the circuit diagram: Pill-O-Matic_circuit.png

![Final System Circuit Diagram](images_and_videos/Plan/Pill-O-Matic_circuit.png)

## Final System Demonstration

Click [here](files/4_code/Pill_O_Matic_code/Pill_O_Matic_code.ino) to view the source code.

### Overview

![Overview](images_and_videos/Device_Demonstration/30.jpg)

#### CLICK IMAGES BELOW TO VIEW VIDEO

[![Demonstration: pill dispensing at pre-set time](images_and_videos/Device_Demonstration/35.png)](images_and_videos/Device_Demonstration/35.mp4)

[![Demonstration: pill dispensing at pre-set time](images_and_videos/Device_Demonstration/36.png)](images_and_videos/Device_Demonstration/36.mp4)

### Breadboard wiring

![Breadboard wiring](images_and_videos/Device_Demonstration/31.jpg)

### Arduino UNO wiring

![Arduino UNO wiring](images_and_videos/Device_Demonstration/34.jpg)

### Hall Effect Sensor SS49E Placement

![Hall Effect Sensor SS49E Placement](images_and_videos/Device_Demonstration/32.jpg)

### ULN2003 Driver Board & Stepper Motor 28BYJ-48 wiring

![ULN2003 Driver Board & Stepper Motor 28BYJ-48 wiring](images_and_videos/Device_Demonstration/33.jpg)

#### Special note on Stepper Motor 28BYJ-48

- The system uses Stepper Motor 28BYJ-48 5V driven by a ULN2003 driver board, and by default the motor coils remain energized after movement, which causes the motor to keep drawing high current (250 mA) even while idle.

- This default behavior leads to unnecessary power consumption and heat generation, which is undesirable for a pill dispenser that only needs brief indexed motion and does not require continuous holding torque between dispensing events.

- To solve this, a custom `turnOffStepper()` function was added to the code to set all four motor control pins LOW after each movement, which de-energizes the coils and reduces idle current to approximately zero.

```cpp
void turnOffStepper() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void dispenseOnePill() {
  stepperMotor.step(stepsPerDose);  // Rotate one compartment
  turnOffStepper();                 // De-energize motor after movement
}
```

#### DC Power supply reading: Stepper Motor 28BYJ-48 - OFF

![Stepper Motor 28BYJ-48: OFF](images_and_videos/Device_Demonstration/33_1.jpg)

#### DC Power supply reading: Stepper Motor 28BYJ-48 - ON

![Stepper Motor 28BYJ-48: ON](images_and_videos/Device_Demonstration/33_2.jpg)

#### Special Case 1 - to avoid pill piling up in tray: pill dispensed -> user did not take pill -> next dispensign time reached -> pause dispensing of next dosage until pill taken to avoid pill piling up in tray.

[![Special Case 1 - to avoid pill piling up in tray](images_and_videos/Device_Demonstration/37.png)](images_and_videos/Device_Demonstration/37.mp4)

#### Special Case 2 - to avoid dispensing pill when tray removed: time to take pill -> pill tray not detected -> wait until pill tray inserted to dispense pill.

[![Special Case 2 - to avoid dispensing pill when tray removed](images_and_videos/Device_Demonstration/38.png)](images_and_videos/Device_Demonstration/38.mp4)

## Reflection on the Process

### What: what was done? what went well/not well during the process? what was the result?

#### What was done

- An Arduino-based automatic pill dispenser was designed and built integrating CAD, 3D printing, electronics, and embedded programming.
- The system combined RTC scheduling, sensor feedback, and stepper motor actuation into a single functional design.

#### What went well

- CAD dimensions were accurate, resulting in precise fits and smooth sliding between components.
- Proper clearance selection eliminated the need for rework during assembly.
- A 30% infill base provided strong structural support and reliable screw retention for the motor mount.
- Stepper motor control logic minimized power consumption by de-energizing coils when idle and prevented overheating.
- Edge cases were handled effectively, preventing dispensing when the tray was missing and avoiding over-dispensing when pills were uncollected.
- System integration produced stable and predictable behavior during operation.

#### What did not go well

- The Hall effect sensor had a limited range of approximately 10 mm, requiring close breadboard placement and reducing compactness and aesthetics.
- Excess support material was used during 3D printing, leading to unnecessary material usage and inefficiency.

#### What was the result

- The final outcome was a fully functional and reliable prototype that met all core design objectives.

### So What: what is the importance and significance of what was done?

- The system addresses real-world medication challenges such as missed doses, incorrect pill selection, and reliance on separate reminder systems.
- It automates routine healthcare tasks and reduces cognitive load, especially for elderly or busy users.
- It improves medication adherence by ensuring consistent timing and controlled dispensing.
- It reduces human error by eliminating confusion associated with multi-compartment pill boxes.
- It integrates reminder and dispensing functions into a single system, removing the need for multiple tools.
- It enhances safety by preventing over-dispensing and handling edge cases such as a missing tray or uncollected pills.
- It demonstrates a practical application of embedded systems in solving real healthcare problems.
- It highlights the value of system-level design through the integration of mechanical, electrical, and software components.
- It establishes a foundation for scalable assistive technology that can be extended to smart health monitoring and IoT systems.

### Now What: what could further be done?

- Sensing system can be improved using more compact and reliable alternatives such as limit switches or optical sensors.
- Mechanical design can be optimized to reduce support material in 3D printing and improve print efficiency.
- Electrical system can transition to a perfboard-based embedded design to reduce loose wiring and improve reliability and portability.
- Power system can be upgraded with battery integration to improve potability and enable standalone operation.
- The Hall Effect Sensor can be mounted independently from the breadboard to allow flexible placement and a cleaner design.
- Additional system features can be added, including voice or audio reminders, missed-dose tracking, and safety lock mechanisms.
- An LCD/touch screen display can be integrated to enable user input without having to touch code, effectively improving usability and user feedback.
- IoT connectivity can be integrated to enable real-time monitoring, mobile app notifications, and caregiver alerts for missed doses.
- The system can be expanded into a smart health platform with data logging, usage analytics, and integration with wearable or health systems for long-term tracking.
