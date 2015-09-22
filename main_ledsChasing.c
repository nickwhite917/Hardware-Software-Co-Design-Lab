
/***********************************************************************
* Eric Payne
* Crystin Stoll
* Nick White
*
* Module:  LED chasing program
* File:    main_ledsChasing.c
* Purpose: Key0 initiates LED which moves left and right, back and forth
*          The five switches (sw4-sw0) control the speed of the LED
*          Once initiated Key0 starts the LED at the far right LED
*
* Revision History: version 1.0 	Date: 9/10/2015
*
***********************************************************************/
#include "io.h"
#include "alt_types.h"
#include "system.h"

static int ledGo;
static int direction;
static alt_u16 led_pattern = 0x0000;    // initial pattern

/***********************************************************************
* function: key_get_command_v0()
* purpose:  get key0 press
* argument:
*   key_base: base address of key PIO
*
***********************************************************************/
void key_get_command_v0(alt_u32 key_base)
{
	ledGo = ~(IORD(key_base, 0)) & 0x1; // bitwise NOT - key0 is active low
}

/***********************************************************************
* function: sw_get_command_v0()
* purpose:  get flashing period from switches
* argument:
*   sw_base: base address of switch PIO
*   prd: pointer to period
* return:
*   updated prd
* note:
***********************************************************************/
void sw_get_command_v0(alt_u32 sw_base, int *prd)
{
  *prd = IORD(sw_base, 0) & 0x0000001F;  // read flashing period
}

/***********************************************************************
* function: led_chase_v0()
* purpose:  move LED left and right
* argument:
*   ledg_base: base address of green LED PIO
*   ledr_base: base address of red LED PIO
*   prd: flashing period in ms
* return:
* note:
*   - The delay is done by estimating execution time of a dummy for loop
*
***********************************************************************/
void led_chase_v0(alt_u32 ledg_base, alt_u32 ledr_base, int prd)
{

  //static alt_u16 ledr_pattern = 0x0000;
  unsigned long i, itr;

  if(ledGo == 1)
  {
	  led_pattern = 0x8000;	// LED position to far right side
	  IOWR(ledr_base, 0, led_pattern>>8);     // write RED LEDs
	  IOWR(ledg_base, 0, 0x0000);      		  // turn off green
  }
  else
  {
	     // led at far right so move left
	  	 if(led_pattern == 0x0001)
	  	 {
	  		 direction = 1; //left
	  	 }

	  	 // led at far left so move right
	  	 else if (led_pattern == 0x8000)
	  	 {
	  		  direction = 0; //right
	  	 }

	  	 // shift bit in corresponding direction
	  	 if(direction == 1)
	  	 {
	  		led_pattern = led_pattern << 1U;
	  	 }
	  	 else if (direction == 0)
	  	 {
	  		  led_pattern = led_pattern >> 1U;
	  	 }

	  	 // red led range
	  	 if (led_pattern <= 0x8000 && led_pattern >= 0x0100)
	  	 {
	  		 /* need to shift led_pattern 8 bits because red LEDs
	  		    are 7 to 0 bits while led_pattern is 16-bits 	  */
	  		IOWR(ledr_base, 0, led_pattern>>8);     // write RED LEDs
	  		IOWR(ledg_base, 0, 0x0000);      		// turn off green

	  	 }

	  	 // green led range
	  	 else if (led_pattern <= 0x0080 && led_pattern >= 0x0001)
	  	 {
	  		 // no need to shift bits because they're mapping matches
	  		  IOWR(ledg_base, 0, led_pattern);      // write GRN LEDs
	  		  IOWR(ledr_base, 0, 0x0000);      		// turn off red
	  	 }
  }

	 // itr is used for slowing and speeding LED
     itr = prd * 5000;
     for (i=0; i<itr; i ++){}             // dummy loop for delay

}

/***********************************************************************
* function: main()
* purpose:  top-level program
* note:
***********************************************************************/
int main()
{
  int prd = 0;
  direction = 0;
  ledGo = 0;
  IOWR(LED_GREEN_BASE, 0, led_pattern);   // turn off red
  IOWR(LED_RED_BASE, 0, led_pattern);     // turn off red
  while(1)
  {
	key_get_command_v0(PUSHBUTTON_BASE);
    sw_get_command_v0(SWITCH_BASE ,&prd);
    led_chase_v0(LED_GREEN_BASE,LED_RED_BASE, prd);
  }
  return 0;
}



