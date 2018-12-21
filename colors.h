/*
 * colors.h
 * Description: colors.h is used to generate color information.
 *  DO NOT EDIT
 *
 *  Created on: Dec 17, 2018
 *      Author: Cody
 */

#ifndef COLORS_H_
#define COLORS_H_


#include <stdlib.h> // used for random color generation
#include <time.h>  	// used for random color generation
#include <stdint.h>

// Random selection will choose the color that is picked for display
typedef enum {Red, Blue, Green, Purple, Orange, White, none } color_selected;

// Color object
typedef struct{
    color_selected picked;	// Color picked by RandomColor generator sent to LED2 on the Launchpad
    int8_t *colorText; 		// String matching the enum color sent to the BoosterXL LCD display
    color_selected LEDColor;	// LED color combination currently output to the RGB LED on the BoosterXL
}drawn_color;

// Initialize the color object
void initColor(drawn_color *m_color);

// This function will pick a random color and assign it the appropriate String to be used for display
void RandomColor(drawn_color *);


#endif /* COLORS_H_ */
