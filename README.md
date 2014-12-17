volume
======

Ultrasound based volume control, runs on an arduino, controls the volume on the stereo at the lab.

Components
==========

  * Input: An [HRLV-MaxSonar MB1013](http://www.maxbotix.com/Ultrasonic_Sensors/MB1013.htm)
  * Output: An [RGB LED from sparkfun](https://www.sparkfun.com/products/105)
  * Volume control: A continuous rotation RC servo (like this one)[https://www.sparkfun.com/products/9347]
  * Power control: 9 gram servo (like this one)[http://www.hobbyking.com/hobbyking/store/__662__HXT900_9g_1_6kg_12sec_Micro_Servo.html]

Function
========

There are four "zones" above the table (beneath the ultrasound sensor) which represent 4 different states:

1. 0-50 cm: Deadzone: Nothing happens here.
2. 50-80 cm: Volume down zone: Hold your hand here to turn the volume down.
3. 80-120 cm: Volume up zone: Hold your hand here to turn the volume up.
4. >120 cm: Power toggle zone: Hols your hand here to turn the stereo on/off .. cooldown is 5 seconds.