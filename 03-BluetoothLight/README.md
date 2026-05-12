# Bluetooth Wireless LED

## Project Goal

This project aims to introduce wireless communication using Bluetooth to my Arduino 
portfolio with the HC-05 Bluetooth module. The circuit allows for a user 
to control an LED wirelessly by sending commands from a serial terminal. 
Sending '1' illuminates the LED and sending '0' turns it off.

Furthermore, a key goal in this project was learning the essential engineering skill of researching and ordering a component based on its datasheet and intended role in the project. 

## Components

- ELEGOO UNO R3 (Arduino-compatible)
- 1x HC-05 Bluetooth Module
- 1x LED 
- 1x 220Ω resistor
- 9V battery (barrel jack connector)
- Jumper Wires
- Breadboard

## Wiring

| Component: | Pin: | Connected to: |
| ---------- | ---- | ------------- |
| HC-05 | TXD | Arduino pin 10 |
| HC-05 | RXD | Arduino pin 11 |
| HC-05 | VCC | Arduino 5v | 
| HC-05 | GND | Arduino GND |
| LED | Anode | Arduino pin 7 |
| LED | Cathode | 220Ω resistor, GND |

## The HC-05

### Functionality
Being the primary focus of this project, it is important to clarify the functionality of the
HC-05. It is a Bluetooth SPP (Serial Port Protocol) module that allows for wireless serial communication. "Serial" refers to sending one bit at a time, and Serial Port Protocol (SPP) is useful because it mimics a real wired connection. So, simply put, the HC-05 is designed to send or receive information one bit at a time transferred wirelessly.

### Static Threat
Though it may seem insignificant, static electricity can be very dangerous for the HC-05, which is not as well-protected as an Arduino may be. In fact, static electricity poses a significant threat that may not be so obvious at first because of how well-protected some popular beginner electronics are. Though it is harmless to humans, static electricity can completely destroy electronics. To avoid "frying" the HC-05, it is important to "ground" yourself before touching it. This can be done by touching any large metal object like a doorknob. 

## Video
https://github.com/user-attachments/assets/ab84ea79-6710-4bc7-8aa9-7f6bfd0ac4dd

## Problems and Headaches

### Windows 11
Unfortunately, Windows 11 does not seem to support Bluetooth SPP very well. In the HC-05's case, it was possible to connect it, but the connection was quite inconsistent. The Bluetooth COM port panel freezes when trying to manually add ports, Windows settings may show the HC-05 as "paired" despite it's not truly being paired, and the HC-05 disconnects when trying to open a connection with PuTTY. Therefore, interfacing with an HC-05 via Windows is not a reliable route to take.

### Ubuntu WSL2
As Windows does not work, neither does a simulated Linux environment. Unfortunately, there is simply no way for WSL2 to access Bluetooth on a machine running Windows 11 because it does not have direct access to the Bluetooth radio. This is because WSL2 is a virtual machine and not the computer's operating system.

### iPhone
Though iPhones can surely use Bluetooth, iOS does not support the HC-05's SPP. So, it is not possible to use an iPhone to communicate with an HC-05.

### Flashing Code
When uploading code to the Arduino, the HC-05's TXD and RXD pins cannot be connected to pins 10 and 11, and the wires must be temproarily disconnected. When Arduino IDE uploads code to the microcontroller, it sends serial data, and this data will be "intercepted" and corrupted if the HC-05 is actively connected to pins 10 and 11 during this process. This is because of SoftwareSerial, which monitors pins 10 and 11. So, the wires must be disconnected during upload to prevent the HC-05 from interfering.

### EN Pin Provision
At the outset of this project, the EN (enable) pin on the HC-05 was connected to data pin 9 of the Arduino. However, it was later discovered that this is redundant for this project. It is easier to save on wires and hardware complexity by keeping the HC-05 perpetually enabled rather than implementing a functionality to enable or disable it. At the time this simplification was discovered, the code was not changed accordingly. So, the code posted for this project retains the redundant EN pin provision to be consistent with the code that was used to complete the project.

## How Does It Work?
This project works by using an HC-05 Bluetooth module to receive a wireless signal sent from a Bluetooth serial terminal on an android phone, though any device capable of reliable Bluetooth SPP communication will do. By connecting the HC-05's RXD pin to the Arduino's TXD pin and the HC-05's TXD pin to the Arduino's RXD pin, the Arduino monitors the signal that the HC-05 transmits via TXD and acts accordingly. If the arudino detects that the HC-05 received a '1', it will illuminate the LED, and a '0' will turn it off. This project is powered exclusively by a 9v battery connected to the Arduino's barrel jack to create a "wireless" effect, though it can alternatively be connected to a computer. 

## What Did I Learn?
This project had two separate phases, each with its own different learning experiences. 

In the first phase, preparing to build the circuit, I learned how to research, select, and order the necessary component for my intended goal. This was, of course, the HC-05, and the selection process involved examining component datasheets to determine whether their functionality and capabilities properly aligned with my project goal. Among other things, I selected the HC-05 based on its voltage and use of SPP communication.

The second phase of this project, completing the hardware, taught me how to implement wireless serial communication via an HC-05 to control an LED with a microcontroller. This project involved understanding plenty of new concepts such as serial port protocol and the use of a serial terminal. Consequently, the debugging process was very long, and it involved empirically implementing many different strategies. First, I tried to use my iPhone, and this did not work because iOS does not support SPP. Then, I tried to use my Windows 11 computer. This computer failed because Windows 11 does not reliably support the kind of Bluetooth SPP that the HC-05 uses, and it also failed because WSL2, a virtual machine, was not able to access the computer's Bluetooth radio. Finally, an Android phone with a Bluetooth serial terminal app installed was able to successfully communicate with the HC-05. However, the project goal was not yet achieved. There were still problems with the circuit, and I simplified the code to illuminate the LED if the HC-05 received anything, not just a '0' or '1'. This process of isolating variables helped me to identify where the problem was, which revealed itself to be in the circuitry itself. Additionally, I discovered that the serial terminal was appending carriage return (13) and newline (10) characters to each transmission, which informed how the system handles incoming data. In other words, the serial terminal revealed that sending a '0', for example, actually sent '48' (0 in ASCII code), '13', and '10'. I subsequently fixed the connection and expanded the code back to its intended functionality, which was successful. This debugging practice of empirically finding a correct strategy and isolating variables to identify a problem is perhaps more useful than the knowledge I gained from coding and assembling the hardware itself.
