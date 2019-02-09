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

#include <stdint.h>

// The list of colors we use in this project
typedef enum {Red, Blue, Green, Purple, Orange, White, none } color_selected_t;

// Color struct type
typedef struct{
    color_selected_t picked;	// Color picked by RandomColor generator sent to LED2 on the Launchpad
    int8_t *colorText; 		// String matching the enum color sent to the BoosterXL LCD display
    int8_t *buttonText;
    color_selected_t LEDColor;	// LED color combination currently output to the RGB LED on the BoosterXL
} drawn_color_t;

// Initialize the color strcut
void initColor(drawn_color_t *m_color);

// This function will pick a color and assign it the appropriate String to be used for display
void SelectColor(drawn_color_t *);


#endif /* COLORS_H_ */
