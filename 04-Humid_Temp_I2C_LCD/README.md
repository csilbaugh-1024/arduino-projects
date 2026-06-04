# Humidity and Temperature Monitor with I2C LCD

## Project Goal
I left my window open to sleep one particularly warm and humid night, and I woke up the next morning to bedsheets that had been made wet and completely uncomfortable by the humidity. Because I never want this to happen again, I decided to make a device that continuously monitors temperature and humidity, and it will alert me if both readings exceed a certain threshold. This project will use the DHT11 sensor, which will display temperature and humidity readings on a 16x2 LCD that will update every minute. If both the temperature and humidity meet or exceed a threshold, the device will illuminate a red LED to indicate that I should close my window. Because it takes up to 12 pins to connect a 16x2 LCD in 8-bit mode, this project implements an I2C backpack to optimize the design by reducing the number of pins needed to only 4, those being GND, VCC, SDA, and SCL.

## Components
- ELEGOO UNO R3 (Arduino-compatible)
- 1x DHT11 sensor
- 1x 16x2 Liquid Crystal Display (LCD)
- 1x I2C backpack
- 1x LED ("alarm" indicator)
- 1x 220Ω resistor
- Jumper Wires
- Breadboard

## The DHT11
The DHT11 is a small, low-cost sensor that measures temperature in a range of 0-50 degrees celsius with an accuracy of 2 degrees, and it measures humidity in a range of 20-80% with 5% accuracy. It runs on 3-5 volts, and its digital communication pins use the same voltage. The DHT11 operates with a minimum sampling period of one second. Though this seems slow, it is plenty for this project because the temperature and humidity of the environment change very slowly. The sensor has four pins, but this project uses the sensor mounted onto a breakout board such that only three pins are required: VCC (5V), GND, and DATA.

## The LCD
This system uses a 16x2 liquid crystal display (LCD) whose contrast can be controlled with a potentiometer. Because this LCD requires so many pins to operate fully (usually 12), it will be implemented in this project with an I2C backpack soldered onto it to reduce the number of wires needed and simplify system complexity. The specific I2C backpack used in this project also has its own potentiometer, so there is no potentiometer wired in the circuit.

## What Is I2C?
I2C, which stands for "inter-integrated circuit", is a serial communication protocol that is useful in microcontroller systems with multiple peripheral components like sensors or displays. In this specific project, I2C is used via a breakout board "backpack" soldered to all 16 pins of the LCD. There is no use of I2C with the DHT11. Because I2C only uses two pins for communication, it is excellent for simplifying wiring. These pins are called "SCL", the clock pin, and "SDA", the data pin. Because I2C is "synchronous", meaning it follows the clock, the SCL pin exists to synchronize communication with the microcontroller's clock. The SDA pin, on the other hand, is a bidirectional data line that receives and transmits data as needed. The SDA pin can send data to the I2C backpack, which then directs data to the correct pin of the LCD. Each device in an I2C system corresponds to a unique "address", which ensures that data is sent to the right location, and the backpack's circuitry itself directs the data to its intended pin. In this project, there will only be one address: the LCD's.

So, the idea of I2C is that multiple different components are connected to the same communication line, but they are all given different addresses. Data is sent along this communication line with a specific destination, that being some component's address, and this ensures that components get only the information meant for them. Then, this information is distributed to the appropriate pins. Though this system of connecting multiple different components to the same communication line appears as if it would cause problematic interference between devices, it works because each component is treated as a destination with an address, and data is sent to a specific destination. In other words, one communication line behaves as n different communication lines where n is the number of devices connected, and the I2C module manages sending the right data to the right pins. This example is, unfortunately, slightly restricted because there is only one device being connected to I2C, but it is nevertheless a clear example of the optimization that I2C can bring to a system.

## Assembling I2C
The LCD I use in this project does not come with an I2C backpack, so I researched and ordered one that can be attached. However, the backpack came with its own set of breakout pins already soldered to it. So, my first step is to de-solder one of the components' set of pins. 

Original LCD

<img width="433" height="287" alt="LCD_Original" src="https://github.com/user-attachments/assets/44aa24a0-c3b6-46df-8895-e9e153c2ec7e" />

Original I2C Backpack

<img width="332" height="357" alt="I2C_Original" src="https://github.com/user-attachments/assets/5abf2580-c1e7-462d-95ae-51032b2bd529" />

Initially, I planned on de-soldering the pins on the I2C backpack so that I could attach it to the LCD's set of pins. However, I switched my approach and decided to de-solder the pins on the LCD because the connections were larger, which makes them easier to remove. So, the new plan is to attach the pinless LCD to the set of pins on the backpack.

De-soldered LCD

<img width="406" height="307" alt="LCD_Desoldered" src="https://github.com/user-attachments/assets/235bda26-72c2-4175-8e45-86631b76b3f4" />

Now that the I2C backpack has been soldered to the LCD, I am ready to build the device.

Successful Attachment Photo 1

<img width="697" height="467" alt="FullSystem0" src="https://github.com/user-attachments/assets/295b453b-aa50-4850-a214-08b863da34e4" />

Successful Attachment Photo 2

<img width="777" height="595" alt="FullSystem1" src="https://github.com/user-attachments/assets/00f12ad7-b2eb-4846-980c-0ffb1af3d169" />

## Wiring

### I2C LCD Control
| Component: | Pin: | Connected to: |
| ---------- | ---- | ------------- |
| I2C Backpack | SCL | Arduino pin A5 |
| I2C Backpack | SDA | Arduino pin A4 |
| I2C Backpack | VCC | Arduino 5v |
| I2C Backpack | GND | GND |

### DHT 11
| Component: | Pin: | Connected to: |
| ---------- | ---- | ------------- |
| DHT 11 | DATA | Arduino pin 4 |
| DHT 11 | VCC | Arduino 5v |
| DHT 11 | GND | GND |

### LED Indicator
| Component: | Connected to: |
| ---------- | ------------- |
| LED, 220Ω resistor | Arduino pin 8, GND |

## Testing
I tested this system in two phases. First, I connected power and verified that the LCD was displaying readings from the DHT11 and refreshing at the desired time. Next, I tested the threshold and LED alarm by breathing on the sensor. As expected, the LCD displayed increased humidity and temperature readings, and the LED illuminated when the threshold conditions were hit. After some time had passed and the sensor readings dropped back below the threshold, the indicator LED turned off. The system was a success.

## Video

https://github.com/user-attachments/assets/be1ef180-5cab-4150-afd1-f3b905b726f9

## Problems and Headaches
This project came with a few obstacles. First, acquiring the I2C backpack did not go as smoothly as expected. After I initially ordered two I2C backpacks, my university residence hall lost the package. So, I ordered more to a pickup location, and this went smoothly. When I began de-soldering, I initially tried removing the set of pins from the I2C backpack, but they got stuck at a "halfway out" point in the board. I suspect this was because I de-soldered the pins badly and caused some solder to remain that was too small to be removed with a tool but still substantial enough to keep at least one of the pins attached to the board. De-soldering the LCD after this, however, went very smoothly. Also, I completely fried my first DHT11 sensor by mistakenly wiring it in reverse polarity. Fortunately, I was able to borrow my friend's DHT11 sensor and complete the project.

## How Does It Work?
This system works by using a DHT11 sensor to sample the temperature and humidity of the surrounding environment every three seconds. According to the datasheet, the recommended maximum frequency is 1 sample per second. Overly high frequencies risk causing "self-heating", where the high current causes the sensor to warm itself. This extra heat can make readings less accurate. Another reason why I chose three seconds is because it makes testing and documenting results significantly quicker than, for example, 60 second intervals. Longer intervals like these would be more useful in projects that involve a prolonged period of sampling because temperature and humidity usually change so slowly. The DHT11 in this project only uses three pins: data, power, and ground. The sensor is powered with 5 volts, and it relays readings to the microcontroller with just one wire connected to the data pin. Furthermore, the code for this project includes a provision for detecting sensor errors. If either temperature or humidity appear as "not a number", meaning there is a problem with the sensor that is causing it to pass invalid readings, the LCD will clear itself and display "Sensor error!" In fact, this is what the LCD was showing as I was frying my first DHT11, and it helped me quickly realize something was wrong. This was a very helpful example of the importance of including protective measures such as this one, though a DHT11 was destroyed.

The arduino relays the data collected by the DHT11 to the I2C backpack on the LCD via the SDA bus. As discussed earlier, the I2C backpack then distrubites the data to the proper pins on the LCD so that it displays temperature and humidity readings. Temperature, in degrees celsius, appears on the upper line, and percent humidity appears on the lower line. Because the DHT11 samples every three seconds, the LCD updates on the same interval.

The microcontroller also checks temperature and humidity against threshold values. These values, 24.0 degrees celsius and 70.0% humidity, are estimates of the kind of conditions that would cause soggy bedsheets overnight. Only when both thresholds are met or exceeded, the LED illuminates to display an "alarm" indicating that I should close my window.

## What Did I Learn?
Completing this project helped me understand I2C at a conceptual level and practice implementing it with a real-world purpose in mind, and it gave me my first experience with using sensors. This project helped me understand how to implement a DHT11 physically in a system, and it taught me how to program the arduino to sample the sensor's readings and display them on the LCD. Unlike all of my previous projects, this one relied on no user input. Instead, the system output is based on the DHT11's readings. Also, frying the first DHT11 helped reinforce to me the importance of being methodical, deliberate, and cautious as I wire and power my projects. Further, this project was my very first experience soldering and de-soldering, and it was useful to practice these skills with a real goal in mind. Overall, this project was a useful learning experience, and it helped me pick up a few new and important skills.
