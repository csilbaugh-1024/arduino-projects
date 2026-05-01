# 4-Speed Decoder Fan

## Project Goal
The goal of this project is to create a device that spins a fan at four discrete speeds chosen by the user: off, speed 1, speed 2, and speed 3. Rather than mapping each nonzero speed to its own button, this project makes use of a 2-to-4 binary decoder system, which minimizes cost and hardware complexity without sacrificing performance. 

## Components
 - ELEGOO UNO R3 (Arduino-compatible)
 - 2x pushbutton
 - 3x LED (speed indicator)
 - 3x 220Ω resistor
 - 1x L293D IC
 - 1x Fan blade
 - 1x 3-6V Motor
 - 1x Breadboard Power Supply Module (3.3V/5V)
 - 1x 9V1A adapter
 - Jumper wires
 - Breadboard

## Wiring
Note: The power supply module powers the motor through the L293D while the microcontroller powers the pushbuttons and LEDs.

### Motor Control
| Component: | Pin: | Connected to: |
| ---------- | ---- | ------------- |
| L293D | ENABLE (pin 1) | Arduino pin 5 |
| L293D | DIRB (pin2) | Arduino pin 4 |
| L293D | Output 1 (pin3) | Motor positive terminal |
| L293D | GND (pin 4) | GND |
| L293D | Output 2 (pin 6) | Motor negative terminal |
| L293D | DIRA (pin 7) | Arduino pin 3 |
| L293D | Vs (pin 8) | Power Supply 5v |
| L293D | Vss (pin 16) | Arduino 5v |

### User Inputs
| Component: | Connected to: |
| ---------- | ------------- |
| Button 0 | Arduino pin 8, GND |
| Button 1 | Arduino pin 12, GND |

### Speed Indicators
| Component: | Connected to: |
| ---------- | ------------- |
| LED 0, 220Ω resistor | Arduino pin 11, GND |
| LED 1, 220Ω resistor | Arduino pin 10, GND |
| LED 2, 220Ω resistor | Arduino pin 9, GND |

## Logic Truth Table
Note: since code uses `INPUT_PULLUP` for button logic, a pressed pushbutton reads LOW. This makes the truth table "inverted" compared to standard logic.

| Button 0 | Button 1 | Speed | LED 0 | LED 1 | LED 2 |
| ---------- | ------------- | ----- | ----- | ----- | ----- |
| 1 | 1 | off | 0 | 0 | 0 |
| 0 | 1 | Speed 1 | 1 | 0 | 0 |
| 1 | 0 | Speed 2 | 1 | 1 | 0 |
| 0 | 0 | Speed 3 | 1 | 1 | 1 |

## Hardware and Safety

### Flyback Voltage
Electric motors produce "flyback voltage" when current suddenly stops flowing. This can damage electronics without proper protection, so the L293D uses flyback diodes to prevent harm to the microcontroller.

### Motor Dead Zone (Static Friction)
Because of static friction in the motor, speeds below a certain number will not spin the fan blade unless the static friction is eliminated by, for example, switching down from a higher speed that is capable of overcoming the static friction. In this project, SPEED_1 was set empirically at 125. Lower speeds risk being overpowered by friction.

### Separated Power Sources
In this project, it is useful to keep two different power "domains": one for logic, and one for motor control. Motors draw lots of current and are "noisy" with voltage, and this behavior can cause problems with the logic components. To prevent this, the motor is powered by the L293D's Vs pin from the external power supply, and the logic components are powered by the Arduino directly.

## Video
https://github.com/user-attachments/assets/b7ee8418-9135-430a-8520-649c5673dd96

## How Does It Work?
This system works by using two buttons and binary decoder logic to control four discrete motor speeds, which are indicated by a set of three LEDs. The motor, powered by a power supply module, is controlled with an L293D IC. The two pushbuttons, coded with `INPUT_PULLUP`, produce four different combinations, 00, 01, 10, 11, and each corresponds to a motor speed and a combination of indicator LEDs. This is the decoder logic. This system is useful because it simplifies the design and saves on materials. Furthermore, the motor speeds rely on a system called PWM, pulse width modulation, which uses digital inputs to mimic analog behavior, though the code uses `analogWrite()`. Motor speed is controlled by a "duty cycle", which refers to the percentage of a period in which a signal is high. In greater speeds, the duty cycle is greater because the signal is high for a larger portion of the period. In lower speeds, the duty cycle is lower because the signal is low for a larger portion of the period. As the duty cycle changes, the motor responds accordingly. Finally, the L293D is essential for the system because it satisfies the motor's power needs by supplying more current than the microcontroller does. It also controls the speed and direction of the motor, and it uses flyback diodes to protect the electronics from the flyback voltage the motor generates. 

## What Did I Learn?
As I assembled this device, I was able to deepen my understanding of the Arduino Programming Language and breadboard circuit design, and it was especially helpful to use an important digital logic concept, the decoder, to refine a real system. Beyond these, I learned a lot of new things about implementing electric motors such as the dead zone and the need for a motor driver chip. The driver chip I used, the L293D, taught me about dealing with the flyback voltage a motor generates and the idea of PWM and duty cycles. As I was understanding the L293D, I learned about the importance of consulting datasheets directly and approaching a project with an open mind. The tutorial design that I followed and modified to create this system did not use the Vss pin, but the datasheet specified that it was essential for logic. So, I connected the Vss pin so that the chip would function as intended. Furthermore, I learned about the importance of separating power sources so that the system functions smoothly.
