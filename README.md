# NP2 Tech Glove #

## Glove Structure ##
### **Firmware** ###
First of all while the Glove is turned on it waits for a signal. The risiver send a message via the NRF24L01 and the Glove recognize what kind of information the risive want.The whole calculation process is becoming in the Glove's firmware and then it only send the result to the resiver. In this way I decrease the amount of data that is going to be transimitted so even faster transimision.
### **Hardware** ###
#### Flex Sensors ####

Flex Sensor is creating a voltage divider with a **10k** resitor and every sensor dipending on the spot of bending is giving almost the same value in each sensor

![alt text](https://nb1949.files.wordpress.com/2015/05/flexsensor1.png)

|              | Finger1 | Finger2 | Finger3 | Finger4 |
|-------------:|--------:|--------:|--------:|--------:|
|Normal        |   500   |   550   |  570    |   600   |
|Bended        |   750   |   750   |   750   |   800   |
|Trigger Point |   700   |   700   |   700   |   750   |

#### Gyroscope ####
The gyroscope that I use is the MPU6050 which is accelameter too. 
* In the Arm mode the only the **Y axis** of the gyroscope is getting used and that determines the way that servo turn (clockwise or anti-clowise). While the gyroscope is in **45°- 90°** then the servos start to turn clockwise. while the gyroscope is in **250° - 330°** the the servos turn anti-clockwise. And there is also a null state that when it is in **0°- 45°** or in **330° - 360°** the servos stay in the same position. 

* In the Car mode the 2 Main Axis is getting used the **X and Y**. The way that the Glove is turned on the glove sends a unique combination of 1 and 0 for its option that then in car is getting converted as turn on/off the motor.

![alt text](https://howtomechatronics.com/wp-content/uploads/2019/04/Arduino-and-MPU6050-Circuit-Diagram.png)

#### RF Communication ####
I am using the **NRF24L01** module which can send data over **2Mbps** and transimetted over **100 meters** away at max range. That mean that we can have fast transimition of datas in a long range which is perfect for my project. It also has two-way communication which also make itt apropriate for this project because in this way the Glove can know the resiver and get basic data from him.

![alt text](https://sites.google.com/site/mccworkshop2016/_/rsrc/1472690573840/mysensors-mcc-tutorials/mysensors-getting-started/arduino-nano-rf24.png?height=301&width=320)

#### Battery ####
I am using is a 3.7Volt Li-Po battery that with a compination with a step up it step up the volts to 12V. Then I connect it in the Vin pin and in GND.


## Arm Structure ##

### **Firmware** ###
At the biginning the Arduino starts sending pulses its second with his ID so the Glove can send the correct data in the resiver. Then when tyhe Glove have get the ID the resiver get the data and simply write it in the [Servos](#servos). But the Arm also have to save potitions and the recall it in order to complete a task. That is succesfully being done by the [button](#button) in cmpination with the [screen](#screen).

### **Hardware** ###
#### Servos ####
The Servos need PWN signal in order to work properly. So I am using pins 3,5,6,9 which is PWM pins in the Arduino nano. I am using the **"VarSpeedServo"** library which allows me to contol the speed of servos. So while I repeat the moves the movements is becoming more soft and smoother.

#### RF Communication ####
Is the same with [Glove's RF Communication](#rf-communication)

#### Screen ####
I am using the **OLED 0.96" I2C display** which is being controlled by the I2C communication of Arduino. So I can display basic data and inform the user abaout what is currently happening in the Arduino. 
![alt text](https://i.pinimg.com/originals/f5/5b/9f/f55b9f4f21a93a1a6ff7f4b19305965a.png)

#### Button ####
I also have a button. That dedermines the position that is going to be saved by simple pressing it. By long pressing the button for 2 seconds resets the process of saving if it is in Real Time Mode and if it is in Repeat Mode then it exit it. The button is also has another use. While the user wants to stop using the Real time mode and has save his moves then he double press the button and go in Repeat Mode.

#### Power Supply ####
The power supply Can be somethink that provides a DC 5-24v in Vin pin or a usb port like a laptop, power bank.

