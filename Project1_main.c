
#include <ti/devices/msp432p4xx/driverlib/driverlib.h> 	//Drivers for the board
#include <ti/grlib/grlib.h>  				//  Graphics Library for the LCD Screen
#include "LcdDriver/Crystalfontz128x128_ST7735.h"  	//  Library used for displaying on the LCD Screen

// include the colors file
#include "colors.h"

//////////////Definitions/////////////////////////////////////

// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0

// The bitmask for left Launchpad Board button, also known as Button1 or Launchpad S1
#define LEFT_BUTTON BIT1      // P1.1
#define LEFT_LED BIT0         // P1.0

// The bitmask of the right Launchpad Board button

#define RIGHT_BUTTON BIT4      //P1.4
#define LRED_LED BIT0          //P2.0
#define LBLUE_LED BIT2         //P2.2
#define LGREEN_LED BIT1        //P2.1

// The bitmask for the LED on the Booster Pack
#define RED_LED BIT6           //P2.6
#define GREEN_LED BIT4         //P2.4
#define BLUE_LED BIT6          //P5.6

// The bitmask for the two buttons (S1 and S2 on the booster pack)
#define BUTTONB_1 BIT1         // P5.1
#define BUTTONB_2 BIT5         // P3.5


////////////Function Declarations/////////////////////////////

// This function initializes everything including the setup of the project
void initialize(Graphics_Context *g_sContext, drawn_color_t *pick);

// These functions initialize the graphics
void InitGraphics(Graphics_Context *g_sContext);
void InitFonts();

// This function initializes all the needed GPIO pins
void InitGPIO();

// This function displays the texts needed for the project on the LCD screen
void DisplayFunction(Graphics_Context *g_sContext, drawn_color_t *pick);

// Function for matching the displayed colors
bool colorsMatched(drawn_color_t *pick);

// This function is used to Read the Button input on the LaunchPad and the BoosterXL.
// From the input combinations, you must produce correct output for the LED1 on the Launchpad and RGB LED on the BoosterXL
void BoosterLEDColors(drawn_color_t *pick);

// This function is used to produce the output for the LED2 on the Launchpad
void LED2Colors(color_selected_t picked);

//The following functions are used for turning on and off the LED on the launchpad and the boosterpack
void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();

void TurnOn_Launchpad_LEDR();
void TurnOff_Launchpad_LEDR();

void TurnOn_Launchpad_LEDB();
void TurnOff_Launchpad_LEDB();

void TurnOn_Launchpad_LEDG();
void TurnOff_Launchpad_LEDG();

void TurnOn_Booster_LEDR();
void TurnOff_Booster_LEDR();

void TurnOn_Booster_LEDB();
void TurnOff_Booster_LEDB();

void TurnOn_Booster_LEDG();
void TurnOff_Booster_LEDG();

//The following methods returns the status of the buttons on the launchpad and the boosterpack such as they are on or off
char SwitchStatus_Launchpad_Button1();
char SwitchStatus_Launchpad_Button2();

char SwitchStatus_Booster_Button1();
char SwitchStatus_Booster_Button2();

/////////////The Function Definitions////////////////////////////

// Main function is the applicator's entry point
int main(void)
{

    //Initialize structures
    drawn_color_t pick;
    Graphics_Context g_sContext;
    initialize(&g_sContext, &pick);

    // Program event loop
    while (1)
    {
	// LCD printing
	DisplayFunction(&g_sContext, &pick);

      	// Lighting up LED2 of Launchpad
	LED2Colors(pick.picked);

	// Reading the status of the buttons, lighting up the BoosterPack LED
	BoosterLEDColors(&pick);
    }
}

// TODO: You need to complete this function
// This function lights up the LED2 on Launchpad based on the chosen color.
// For example, if the "Red" is picked, then LED2_RED should be turned on and the other two LED2s should be off.
// If the Purple is picked, the LED2_BLUE and LED2_RED should be on and the LED2_GREEN should be off.
void LED2Colors(color_selected_t picked)
{
    switch(picked)
    {
	case Red:
	    TurnOn_Launchpad_LEDR();
	    TurnOff_Launchpad_LEDB();
	    TurnOff_Launchpad_LEDG();
	    break;

	case Blue:
	    TurnOff_Launchpad_LEDR();
	    TurnOn_Launchpad_LEDB();
	    TurnOff_Launchpad_LEDG();
	    break;

	case Green:
	    TurnOff_Launchpad_LEDR();
	    TurnOff_Launchpad_LEDB();
	    TurnOn_Launchpad_LEDG();
	    break;

	case Orange:
	    TurnOn_Launchpad_LEDR();
	    TurnOff_Launchpad_LEDB();
	    TurnOn_Launchpad_LEDG();
	    break;

	case Purple:
	    TurnOn_Launchpad_LEDR();
	    TurnOn_Launchpad_LEDB();
	    TurnOff_Launchpad_LEDG();
	    break;

	case White:
	    TurnOn_Launchpad_LEDR();
	    TurnOn_Launchpad_LEDB();
	    TurnOn_Launchpad_LEDG();
	    break;

	default:
	    TurnOff_Launchpad_LEDR();
	    TurnOff_Launchpad_LEDB();
	    TurnOff_Launchpad_LEDG();
    }
}

// TODO: You need to complete this function
// This function achieves the following: It checks the status of the Launchpad and the BoosterPack buttons and
// lights up the Left LED and the BoosterPack RGB LED accordingly to Table 1 of the project description. In addition,
// it updates the LEDColor member of the input argument, namely pick.
// For example, if the Left Launchpad button is pressed, the RGB on BoosterPack should light up with Red,
// the Left LED on Launchpad should be off and last but not least, pick->LEDColor should be updated to be "Red".
// Note that the picked color for an invalid button combination should be "none" that is defined in the enum of colors.
void BoosterLEDColors(drawn_color_t *pick)
{
	TurnOff_Booster_LEDR();
	TurnOff_Booster_LEDB();
	TurnOff_Booster_LEDG();
	if((SwitchStatus_Launchpad_Button1() == PRESSED)&&(SwitchStatus_Launchpad_Button2() != PRESSED))
    	{
    	    TurnOn_Booster_LEDR();
    	    TurnOff_Launchpad_LED1();
    	    pick->LEDColor = Red;

    	}
	else if((SwitchStatus_Launchpad_Button2() == PRESSED)&&(SwitchStatus_Launchpad_Button1() != PRESSED))
    	{
    	    TurnOn_Booster_LEDB();
    	    TurnOff_Launchpad_LED1();
    	    pick->LEDColor = Blue;
    	}
	else if((SwitchStatus_Booster_Button1() == PRESSED)&&(SwitchStatus_Booster_Button2() != PRESSED))
    	{
    	    TurnOn_Booster_LEDG();
    	    TurnOff_Launchpad_LED1();
    	    pick->LEDColor = Green;

    	}
	else if((SwitchStatus_Booster_Button2() == PRESSED)&&(SwitchStatus_Booster_Button1() != PRESSED))
    	{
    	    TurnOn_Booster_LEDR();
    	    TurnOn_Booster_LEDG();
    	    TurnOff_Launchpad_LED1();
    	    pick->LEDColor = Orange;
    	}
	else if(((SwitchStatus_Launchpad_Button1() && SwitchStatus_Launchpad_Button2()) == PRESSED) && ((SwitchStatus_Booster_Button1() && SwitchStatus_Booster_Button2()) != PRESSED))
    	{
	    TurnOn_Booster_LEDR();
	    TurnOn_Booster_LEDB();
	    TurnOff_Launchpad_LED1();
	    pick->LEDColor = Purple;
    	}
	else if((SwitchStatus_Booster_Button1() && SwitchStatus_Booster_Button2()) == PRESSED)
    	{
    	    TurnOn_Booster_LEDR();
    	    TurnOn_Booster_LEDG();
    	    TurnOn_Booster_LEDB();
    	    TurnOff_Launchpad_LED1();
    	    pick->LEDColor = White;
    	}
    	else
    	{
    	    TurnOn_Launchpad_LED1();
    	    TurnOff_Booster_LEDR();
    	    TurnOff_Booster_LEDB();
    	    TurnOff_Booster_LEDG();
    	    pick->LEDColor = none;
    	}

}

// TODO: Complete this function such that all the BoosterPack and Launchpad connected pins are configured properly.
void InitGPIO()
{
   //WDT_A_hold(WDT_A_BASE);

    //	For the Left Button Launch Pad
    P1DIR = P1DIR & ~LEFT_BUTTON;
    P1REN |= LEFT_BUTTON;
    P1OUT |= LEFT_BUTTON;

    //For the Left LED on the Launch Pad
    P1DIR |=LEFT_LED;

    //For the Right Button on the Launch Pad
    P1DIR = P1DIR & ~RIGHT_BUTTON;
    P1REN |= RIGHT_BUTTON;
    P1OUT |= RIGHT_BUTTON;

    //Launch Pad LED
    P2DIR |=LRED_LED;    //For the right Red LED on the Launch Pad
    P2DIR |=LBLUE_LED;   //For the right BLue LED on the Launch Pad
    P2DIR |=LGREEN_LED;  //For the right Green LED on the Launch Pad

    //Booster Pack LED
    P2DIR |=RED_LED;     //For the Red LED on the Booster Pack
    P5DIR |=BLUE_LED;    //For the Blue LED on the Booster Pack
    P5REN |=BLUE_LED;
    P2DIR |=GREEN_LED;   //For the Green LED on the Booster Pack

    //For Button 1(S1) on the booster Pack
    P5DIR = P1DIR & ~BUTTONB_1;
    P5REN |= BUTTONB_1;
    P5OUT |= BUTTONB_1;

    //For the Button 1(S2) on the Booster Pack
    P3DIR = P1DIR & ~BUTTONB_2;
    P3REN |= BUTTONB_2;
    P3OUT |= BUTTONB_2;
}

// Initialization part is always device dependent and therefore does not change much with HAL
void initialize(Graphics_Context *g_sContext, drawn_color_t *pick)
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now. Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    InitGPIO();


    // No Need for Students to modify Code beyond this point to finish the project
    // Initial Color Pick
    initColor(pick);

    // Initialize the graphics
    InitGraphics(g_sContext);
    Graphics_drawString(g_sContext, pick->colorText, -1, 10, 60, true);
    Graphics_drawString(g_sContext, pick->buttonText, -1, 10, 100, true);
}

// Initializes the LCD screen graphics
void InitGraphics(Graphics_Context *g_sContext)
{

    Graphics_initContext(g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(g_sContext, &g_sFontCmtt16);

    InitFonts();
    Graphics_setFont(g_sContext, &g_sFontCmss18b);
    Graphics_clearDisplay(g_sContext);
    Graphics_drawString(g_sContext, "Color to match: ", -1, 5, 30, true);
    Graphics_drawString(g_sContext, "Press: ", -1, 5, 80, true);
}

//Initialize screen fonts
void InitFonts()
{
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}

// Function takes care of Matching  colors and displaying color word text
void DisplayFunction(Graphics_Context *g_sContext, drawn_color_t *pick)
{
    // If the colors have matched move on move this section into a function of it's own
    if(colorsMatched(pick)) {
	SelectColor(pick);
	// print inside here
	Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLUE);
	Graphics_Rectangle R1;
	R1.xMax = 128;
	R1.yMax = 80;
	R1.xMin = 0;
	R1.yMin = 50;
	Graphics_fillRectangle(g_sContext, &R1);
	Graphics_Rectangle R2;
	R2.xMax = 128;
	R2.yMax = 100;
	R2.xMin = 0;
	R2.yMin = 120;
	Graphics_fillRectangle(g_sContext, &R2);
	Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_YELLOW);
	Graphics_drawString(g_sContext, pick->colorText, -1, 10, 60, true);
	Graphics_drawString(g_sContext, pick->buttonText, -1, 10, 100, true);
    }
}

// Function determines if the randomly color displayed on the LCD  matches the color generated by the LCD
bool colorsMatched(drawn_color_t *pick)
{

    if(pick->picked == pick->LEDColor)
    {
	return true;
    }
    else
    {
	return false;
    }
}

//This function returns the status of the left button on the launchpad
char SwitchStatus_Launchpad_Button1()
{
    return (P1IN & LEFT_BUTTON);
}

//This function returns the status of the right button on the launchpad
char SwitchStatus_Launchpad_Button2()
{
    return (P1IN & RIGHT_BUTTON);
}

//This function returns the status of the button1(S1) on the boosterpack
char SwitchStatus_Booster_Button1()
{
    return (P5IN & BUTTONB_1);
}

//This function returns the status of the button2(S2) on the booster
char SwitchStatus_Booster_Button2()
{
    return (P3IN & BUTTONB_2);
}

//This function turns on the left LED on the launchpad
void TurnOn_Launchpad_LED1()
{
    P1OUT = P1OUT |  LEFT_LED;
}

//This function turns off the left LED on the launchpad
void TurnOff_Launchpad_LED1()
{
    P1OUT = P1OUT & ~LEFT_LED;
}


//This function turn on the right LED on the launchpad to red color
void TurnOn_Launchpad_LEDR()
{
    P2OUT = P2OUT | LRED_LED;
}

//This function turn off the right LED on the launchpad to red color
void TurnOff_Launchpad_LEDR()
{
    P2OUT = P2OUT & ~LRED_LED;
}

//This function turn on the right LED on the launchpad to blue color
void TurnOn_Launchpad_LEDB()
{
    P2OUT = P2OUT | LBLUE_LED;
}

////This function turn off the right LED on the launchpad to blue color
void TurnOff_Launchpad_LEDB()
{
    P2OUT = P2OUT & ~LBLUE_LED;
}

//This function turn on the right LED on the launchpad to green color
void TurnOn_Launchpad_LEDG()
{
    P2OUT = P2OUT | LGREEN_LED;
}

//This function turn off the right LED on the launchpad to green color
void TurnOff_Launchpad_LEDG()
{
    P2OUT = P2OUT & ~LGREEN_LED;
}

//This function turns on the red LED on the booster pack
void TurnOn_Booster_LEDR()
{
    P2OUT = P2OUT | RED_LED;
}

//This function turns off the red LED on the booster pack
void TurnOff_Booster_LEDR()
{
    P2OUT = P2OUT & ~RED_LED;
}

//This function turns on the blue LED on the booster pack
void TurnOn_Booster_LEDB()
{
    P5OUT = P5OUT | BLUE_LED;
}

//This function turns off the blue LED on the booster pack
void TurnOff_Booster_LEDB()
{
    P5OUT = P5OUT & ~BLUE_LED;
}

//This function turns on the green LED on the booster pack
void TurnOn_Booster_LEDG()
{
    P2OUT = P2OUT | GREEN_LED;

}

//This function turns off the green LED on the booster pack
void TurnOff_Booster_LEDG()
{
    P2OUT = P2OUT & ~GREEN_LED;
}
