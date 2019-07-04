/*
 * main.c
 *
 *  Created on: 5 Dec 2018
 *      Author: tm2-weber
 *  Version:4.0
 *  Description: This is a duck hunt game. The aim of this game is to "shoot" the ducks with the third button - button2- when they get to LED0.
 *	The LEDs are randomly generated at the start and difficulty. Switches 8 and 9 control the difficulty, while switches 6 and 7 control the speed
 *	The in which the ducks move.
 */

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

/*--------Function Prototypes--------*/
void displayShots(int, int);
void delay(void);
void lose(void);
void win(void);
int ranStart();

/*---------DEFINE SWITCHES---------*/
#define SWITCH1	0x1 	//Switch direction
#define SWITCH6	0x20	//Difficulty
#define SWITCH7	0x40	//Difficulty
#define SWITCH8 0x300	//Speed
#define SWITCH9 0x200	//Speed

/*---------DEFINE SPEEDS-----------*/
#define	SLOWEST	50000 //Delay length to be called later
#define	SLOW	40000
#define	MEDIUM	30000
#define	FAST	20000

/*--------DEFINE DIFFICULTY---------*/
#define EASIEST 99 //level followed by number of shots
#define EASY 60
#define MED 40
#define HARD 20

int main (void) __attribute__ ((weak, alias ("alt_main")));

int alt_main(void){
	alt_u16 led = 0x2AA;
	alt_u16 switches;
	alt_u16 button = 0x00;
	alt_u16 controlSpeed;
	alt_u16 controlDifficulty;
	int i, shot=0, hits = 0;
	int r = ranStart();
	led = ranStart(r);
	int speed = SLOWEST;
	int difficulty = EASIEST;

	while(1){
		button = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
		button = (button) & 0x7;
		button = (button) ^ 0x7;
		switches = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);

//Switch statement to control the speed
		switches = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		switches = (switches & 0xC1);  /*Select the relevant switches*/
		controlSpeed = (switches >> 6) & 0x3;
		led = (led & 0x3FF);    /*Mask out unused bits*/
		switch(controlSpeed){
			case 3	:(speed = FAST); break;
			case 2	:(speed = MEDIUM); break;
			case 1	:(speed = SLOW); break;
			case 0	:(speed = SLOWEST); break;
		}//End speed control

//Switch statement to control the difficulty
		switches = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		switches = (switches & 0x301);  /*Select the relevant switch*/
		controlDifficulty = (switches >> 8) & 0x3;
		led = (led & 0x3FF);    /*Mask out unused bits*/
		switch(controlDifficulty){
			case 3	:	(difficulty = HARD); break;
			case 2	:	(difficulty = MED); break;
			case 1	:	(difficulty	= EASY); break;
			case 0	:	(difficulty = EASIEST); break;
		}//End difficulty control



/*----------DISPLAY AND MOVE LEDS-------*/
        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, led);
        if (switches & SWITCH1){
            if (led & 0x1){
                    led = led >> 1;
                    led += 0x200;   /*Turn most significant bit on*/
                    delay();
                }//End if led & 0x1
             else{
                    led = led >> 1;
                    delay();
                }//End else
   	   	   }//End if switches & SWITCH1
        else {
            if (led & 0x200){
                    led = led << 1;
                    led += 0x1;   /*Turn on least significant bit*/
                }//End if led & 0x200
                else{
                    led = led << 1;
                }//End else move led << 1
   	   	   	  }//End Else

/*------------NUMBER OF SHOTS-----------*/
      		if(button & 0x4){
      			if(led & 0x1){
       			shot++;
       			hits++;
       			led--;
      			}//End if button = 2

       		else{
       			shot++;
       		}//End else if miss
      		}

      displayShots(hits, shot);

/*----------GAME WIN OR LOSE-------------*/
		//LOSE
		if(shot == difficulty){
			lose();
			if(button & 0x1){ /*Reset function*/
				shot = 0;
				hits = 0;
				led = ranStart();
			}//End reset button
		}//End LOSE

		//WIN
		if (led == 0){
			win();
			if(button & 0x1){ /*Reset function*/
				shot = 0;
				hits = 0;
				led = ranStart();
			}//End reset button
		}//End WIN

/*-------DELAY FOR SPEED SETTING---------*/
          i = 0;
          while (i < speed){
        	  i++;
          }//End speed delay loop
/*------------Reset function-------------*/
          if(button & 0x1){
          	shot = 0;
          	hits = 0;
          	led = ranStart();
          }//End reset button


 /*--------STOP BUTTON BEING HELD DOWN----*/
           while(button != 0x0){
        	button = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
        	button = (button) & 0x7;
        	button = (button) ^ 0x7;
      }//End while buttons != 0

	}//End infinite loop
	return 0;
}//End main

void delay(void){
	int d;
	for(d=0; d<10000; d++){}
}//End delay

void displayShots(int hits, int shot){
	alt_u32 displayNum;
	alt_u8 *val;
	alt_u32 hexVal[10] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};


	val = (unsigned char * ) &displayNum;

	*val = hexVal[(shot) %10];			 /*takes shots and hits from main, divides it by the binary of the  */
	*(val + 1) = hexVal[(shot/10) %10];  /*display it needs to be in then finds the modulo of 10 this    	*/
	*(val + 2) = hexVal[(hits) %10]; 	 /*this keeps the number the same but allows the program to not  	*/
	*(val + 3) = hexVal[(hits/10) %10];	 /*overflow and crash once it hits 10 or above. 					*/

	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, displayNum);
}//End display function

void win(void){
	alt_u32 win = 0x41CFCFC8;
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, win);
}//End win function

void lose(void){
	alt_u32 lose = 0xC7C09286;
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, lose);
}//End lose function

int ranStart(){
	int c = rand()%5;
	int pos[5]={0x1A5, 0x31A, 0x3C4, 0x166, 0x139};
	int r = pos[c];

	return r;
}//End random start function
