/*
 * color.c
 * Do not Edit
 *  Created on: Dec 17, 2018
 *      Author: Cody
 */

#include "colors.h"

void RandomColor(drawn_color *m_color)
{
    // Select a random color from the enum list from Red to White
    m_color->picked = (color_selected) (rand() % none);

    // The color string text is assigned based on the random color that is generated
    switch (m_color->picked) {
	case Red:
	    m_color->colorText = "Red";
	break;
	case Blue:
	    m_color->colorText = "Blue";
	break;
	case Green:
	    m_color->colorText = "Green";
	break;
	case Purple:
	    m_color->colorText = "Purple";
	    break;
	case Orange:
	    m_color->colorText = "Orange";
	    break;
	case White:
	    m_color->colorText = "White";
	    break;
	default:
	    m_color->colorText = "Invalid Color Picked";
	break;
    }
}

// Initialize the color object
void initColor(drawn_color *m_color){

    // Initial state of the drawn_color object
    m_color->picked = Red; 	// Initial color pick that need to be matched.
    m_color->colorText = "Red"; // Initial Text
    m_color->LEDColor = none;   // Initial BoosterXL LED Color that should be set

}
