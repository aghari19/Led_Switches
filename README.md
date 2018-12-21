# Project 1 

## Overview:
The purpose for this assignment is for students to gain experience with the microcontroller interfacing and with bit manipulation. You must develop software in the C language that reads the states of the pushbutton switches and controls several LEDS. 
For this assignment, you must perform all I/O using memory-mapped registers. Do not use any DriverLib functions. (An exception is that you may continue to use the functions provided in the starter code.)

This Project demonstrates how to use the GPIO Pins for Input and Output. Using bit manipulation students will implement the following:
	
* Input: Read button presses.	
* Output: Assign LED color values. 

##  Description:

In Project 1 you will develop an application using your TI Launchpad Board with Booster Pack that implements the following:
* Displays text on the BoosterXL LCD screen.
* Reads input from buttons on the Launchpad and BoosterXL.
* Send Output to the Launchpad LED1, LED2, and RGB (Red-Green-Blue) LED BooxterXL.

The application must use the pushbuttons on both boards to manipulate the Red LED1 on the Launchpad and the RGB LEDs on the BoosterXL.  The Initial (reset) state of the Board should be:
* No buttons pressed
* LED1 on Launchpad on
* LED2 on Launchpad RED
* RGB LED on the BoosterXL Off. 

## Starter Code:
The Lab 1 starter code implements the following functionality for you:
* The red LED on the Launchpad is off at the beginning. Pushing and holding down the left button on the Launchpad for the first time turns the red LED on. After releasing the push button, the red LED turns off. In general, holding down the left button turns the LED on and releasing it turns it off.
* The Red light in the LED2 on the Launchpad is on at the beginning and remains on.
* The LCD Screen is on and displaying *Color to match: Red*. This will remain until the RGB LED BoosterXL functionality is implemented. 


## Needed Code :
You will need to add the following functionality to the application for this assignment

Functionality will need to be added to implement the Color Displaying of LED2.
BoosterXL 





