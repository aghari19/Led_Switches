/*
 * color.c
 * Do not Edit
 *  Created on: Dec 17, 2018
 *      Author: Cody
 */

#include "colors.h"

void SelectColor(drawn_color *m_color)
{
    // cycle through color list from the enum list from Red to White

    if (m_color->picked > White){
	m_color->picked = Red;
    }
    else {
	m_color->picked +=1;
    }

    // The color string text is assigned based on the random color that is generated
    switch (m_color->picked) {
	case Red:
	    m_color->colorText = "Red";
	    m_color->buttonText = "L1";
	break;
	case Blue:
	    m_color->colorText = "Blue";
	    m_color->buttonText = "L2";
	break;
	case Green:
	    m_color->colorText = "Green";
	    m_color->buttonText = "S1";
	break;
	case Purple:
	    m_color->colorText = "Purple";
	    m_color->buttonText = "L1 & L2";
	    break;
	case Orange:
	    m_color->colorText = "Orange";
	    m_color->buttonText = "S2";
	    break;
	case White:
	    m_color->colorText = "White";
	    m_color->buttonText = "S1 & S2";
	    break;
	//default:
	  //  m_color->colorText = "Invalid Color Picked";
	//break;
    }
}

// Initialize the color object
void initColor(drawn_color *m_color){

    // Initial state of the drawn_color object
    m_color->picked = Red; 	// Initial color pick that need to be matched.
    m_color->colorText = "Red"; // Initial Text
    m_color->buttonText = "L1";
    m_color->LEDColor = none;   // Initial BoosterXL LED Color that should be set

}
