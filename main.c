// This application uses buttons 1 and 2 and LED 1 on Launchpad
// The operation is such that if you press the button 1, as long as you keep the button pressed,
// the LED1 is on. As soon as you release the button, LED1 is off and stays off until the button is pressed again.
// This program uses Hardware Abstraction Level (HAL) functions that hide away device-specific details.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h> 	//Drivers for the board
#include <ti/grlib/grlib.h>  				//  Graphics Library for the LCD Screen
#include "LcdDriver/Crystalfontz128x128_ST7735.h"  	//  Library used for displaying on the LCD Screen

// include the colors file
#include "colors.h"

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0

// Define the Buttons on the Launchpad Board
#define LEFT_BUTTON BIT1    // P1.1

// TODO: Define the RIGHT_BUTTON
#define RIGHT_BUTTON BIT4   // P1.4

// TODO: Define the Booster XL Buttons S1 and S2
//Booster XL Buttons S1 and S2
#define S1 BIT1   // P5.1
#define S2 BIT5   // P3.5

// Define the LEDs P1.
#define LEFT_LED BIT0       // P1.0

// TODO: Define the Ports for the P2 LEDs
#define RIGHT_RED BIT0;     // P2.0
#define RIGHT_GREEN BIT1;   // P2.1
#define RIGHT_BLUE BIT2;    // P2.2

//TODO: Define the BoosterXL RGB LED ports
#define BOOST_RED BIT6      // P2.6
#define BOOST_GREEN BIT4    // P2.4
#define BOOST_BLUE BIT6     // P5.6

// This function initializes all the peripherals
void initialize(Graphics_Context *g_sContext, drawn_color *pick);
void InitGraphics(Graphics_Context *g_sContext);
void InitFonts();
void DisplayFunction(Graphics_Context *g_sContext, drawn_color *pick);
// Function for matching the displayed colors
bool colorsMatched(drawn_color *pick);

// This function is used to Read the Button input on the LaunchPad and the BoosterXL.
// From the input combinations, you must produce correct output for the LED1 on the Launchpad and RGB LED on the BoosterXL
void BoosterLEDColors(drawn_color *pick);

// This function is used to produce the output for the LED2 on the Launchpad
void LED2Colors(color_selected picked);

// Main function is the applicator's entry point
int main(void) {

    //Initialize objects
    drawn_color pick;
    Graphics_Context g_sContext;
    initialize(&g_sContext, &pick);

    // Program event loop
    while (1) {

	// Handles LCD printing Functionality
	DisplayFunction(&g_sContext, &pick);

	// TODO : You must go to this Function and complete it
	LED2Colors(pick.picked);

	// TODO : You must go to this Function and complete it
	BoosterLEDColors(&pick);

    }
}

// Students Will need to finish this function
void LED2Colors(color_selected picked) {

    // TODO: You must assign the corresponding colors to LED2 using BIT Manipulation
    if(picked == Red) {

	// Ensures only the LED 2  Red light is on.
	P2OUT = P2OUT | RIGHT_RED
	;
	P2OUT = P2OUT & ~RIGHT_GREEN
	;
	P2OUT = P2OUT & ~RIGHT_BLUE
	;
    }
    else if(picked == Blue) {

	// TODO: Enable only the LED 2 Blue light
	P2OUT = P2OUT | RIGHT_BLUE
	;
	P2OUT = P2OUT & ~RIGHT_RED
	;
	P2OUT = P2OUT & ~RIGHT_GREEN
	;

    }
    else if(picked == Green) {

	// TODO:Enable only the LED 2 Green light
	P2OUT = P2OUT & ~RIGHT_RED
	;
	P2OUT = P2OUT & ~RIGHT_BLUE
	;
	P2OUT = P2OUT | RIGHT_GREEN
	;
    }
    else if(picked == Purple) {

	// TODO: Enable the LED 2 to display Purple
	P2OUT = P2OUT | RIGHT_RED
	;
	P2OUT = P2OUT | RIGHT_BLUE
	;
	P2OUT = P2OUT & ~RIGHT_GREEN
	;

    }
    else if(picked == Orange) {

	// TODO: Enable the LED 2 to display Orange (Don't worry if the LED2 and RGB LED Hue's don't match exactly since we aren't doing color scaling in this assignment.)
	P2OUT = P2OUT | RIGHT_RED
	;
	P2OUT = P2OUT & ~RIGHT_BLUE
	;
	P2OUT = P2OUT | RIGHT_GREEN
	;

    }
    else if(picked == White) {

	// TODO: Enable the LED 2 to display White
	P2OUT = P2OUT | RIGHT_RED
	;
	P2OUT = P2OUT | RIGHT_BLUE
	;
	P2OUT = P2OUT | RIGHT_GREEN
	;
    }
    else {

	// TODO: Ensure the LED2 is off
	P2OUT = P2OUT & ~RIGHT_RED
	;
	P2OUT = P2OUT & ~RIGHT_GREEN
	;
	P2OUT = P2OUT & ~RIGHT_BLUE
	;
    }

}

// This function will manipulate the RGB LED on the BoosterXL and the LED1 on the LaunchPad
void BoosterLEDColors(drawn_color *pick) {

    // Left Button is pressed
    if(((P1IN & RIGHT_BUTTON ) != PRESSED) && ((P1IN & LEFT_BUTTON ) == PRESSED) && ((P3IN & S2 ) != PRESSED) && ((P5IN & S1 ) != PRESSED)) {

	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	// Turn on the BoosterXL RED LED
	P2OUT = P2OUT | BOOST_RED;
	P5OUT = P5OUT & ~BOOST_BLUE;
	P2OUT = P2OUT & ~BOOST_GREEN;
	pick->LEDColor = Red;
    }

    // Right Button is pressed
    else if((P1IN & RIGHT_BUTTON ) == PRESSED && ((P1IN & LEFT_BUTTON ) != PRESSED) && ((P3IN & S2 ) != PRESSED) && ((P5IN & S1 ) != PRESSED)) {

	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	// Turn on BoosterXL Blue
	P2OUT = P2OUT & ~BOOST_RED;
	P5OUT = P5OUT | BOOST_BLUE;
	P2OUT = P2OUT & ~BOOST_GREEN;
	pick->LEDColor = Blue;
    }

    // S1 on BoosterXL is pressed and S2 not pressed
    else if(((P1IN & RIGHT_BUTTON ) != PRESSED) && ((P1IN & LEFT_BUTTON ) != PRESSED) && ((P5IN & S1 ) == PRESSED) && ((P3IN & S2 ) != PRESSED)) {
	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	// Turn on BoosterXL Green LED
	P2OUT = P2OUT & ~BOOST_RED;
	P5OUT = P5OUT & ~BOOST_BLUE;
	P2OUT = P2OUT | BOOST_GREEN;
	pick->LEDColor = Green;
    }

    // S2 on BoosterXL is pressed, but make sure that S2 is the only button pressed
    else if(((P1IN & RIGHT_BUTTON ) != PRESSED) && ((P1IN & LEFT_BUTTON ) != PRESSED) && ((P3IN & S2 ) == PRESSED) && ((P5IN & S1 ) != PRESSED)) {
	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	// Turn on the Red, Blue, and Green BoosterXL LEDs.
	P2OUT = P2OUT | BOOST_RED;
	P5OUT = P5OUT & ~BOOST_BLUE;
	P2OUT = P2OUT | BOOST_GREEN;

	pick->LEDColor = Orange;
    }
    // If RIGHT AND LEFT Buttons Pressed
    else if(((P1IN & RIGHT_BUTTON ) == PRESSED) && ((P1IN & LEFT_BUTTON ) == PRESSED) && ((P5IN & S1 ) != PRESSED) && ((P3IN & S2 ) != PRESSED)) {

	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	// BoostXL Purple
	P2OUT = P2OUT | BOOST_RED;
	P5OUT = P5OUT | BOOST_BLUE;
	P2OUT = P2OUT & ~BOOST_GREEN;

	pick->LEDColor = Purple;
    }
    // S1 and S2 Pressed
    else if(((P1IN & RIGHT_BUTTON ) != PRESSED) && (( P1IN & LEFT_BUTTON ) != PRESSED) && (( P5IN & S1 ) == PRESSED) && (( P3IN & S2 ) == PRESSED)) {
	// Turn off Left LED LaunchPad LED
	P1OUT = P1OUT & ~LEFT_LED;
	//
	P2OUT = P2OUT | BOOST_RED;
	P5OUT = P5OUT | BOOST_BLUE;
	P2OUT = P2OUT | BOOST_GREEN;
	pick->LEDColor = White;

    }
    else {
	// Turn on Left LED LaunchPad LED
	P1OUT = P1OUT | LEFT_LED;
	// Booster XL LEDs all off
	P2OUT = P2OUT & ~BOOST_RED;
	P5OUT = P5OUT & ~BOOST_BLUE;
	P2OUT = P2OUT & ~BOOST_GREEN;
	pick->LEDColor = none;
    }
}

// Initialization part is always device dependent and therefore does not change much with HAL
void initialize(Graphics_Context *g_sContext, drawn_color *pick) {

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now. Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing Launchpad LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    P1DIR |= LEFT_LED;

    //P2 LED
    P2DIR |= RIGHT_RED
    ;
    P2DIR |= RIGHT_GREEN
    ;
    P2DIR |= RIGHT_BLUE
    ;

    //BoosterXL LEDs
    P2DIR |= BOOST_RED;
    P2DIR |= BOOST_GREEN;
    P5DIR |= BOOST_BLUE;

    // step 3: Initializing Launchpad S1 (switch 1 or button 1),
    // which is on Pin1 of Port 1 (from page 37 of the Launchpad User Guide)

    // Write 0 to PxDIR
    P1DIR = ~ LEFT_BUTTON;
    P1DIR = ~ RIGHT_BUTTON;

    //Booster XL
    P5DIR = ~ S1;
    P3DIR = ~ S2;

    // write 1 to the PxREB for the bit you want
    P1REN |= LEFT_BUTTON;
    P1REN |= RIGHT_BUTTON;

    //BoosterXL
    P5REN |= S1;
    P3REN |= S2;

    // write 1 to the PxOUT
    P1OUT |= LEFT_BUTTON;
    P1OUT |= RIGHT_BUTTON;

    //BoosterXL
    P5OUT |= S1;
    P3OUT |= S2;

    // No Need for Students to modify Code beyond this point to finish the project
    // Initial Color Pick
    initColor(pick);

    // Initialize the graphics
    InitGraphics(g_sContext);
    Graphics_drawString(g_sContext, pick->colorText, -1, 10, 60, true);
    Graphics_drawString(g_sContext, pick->buttonText, -1, 10, 100, true);
}

// Initializes the LCD screen graphics
void InitGraphics(Graphics_Context *g_sContext) {

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
void InitFonts() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}

// Function takes care of Matching  colors and displaying color word text
void DisplayFunction(Graphics_Context *g_sContext, drawn_color *pick) {
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
bool colorsMatched(drawn_color *pick) {

    if(pick->picked == pick->LEDColor) {
	return true;
    }
    else {
	return false;
    }
}
