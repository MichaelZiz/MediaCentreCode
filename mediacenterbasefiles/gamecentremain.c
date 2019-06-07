#include <stdio.h>
#include "LPC17xx.H"                       
#include "GLCD.h"
#include "LED.h"
#include <RTL.h>
#include "KBD.h"
#include <ctype.h>                    
#include <string.h>                   
#include <stdbool.h>
#include <stdint.h>
#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */
//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
/////////////////////////////////////////////////////////////
void delay(){
	int i=0;	
	for(i=0;i<1000000;i++){}	
}
//extern void mainaudio (void);

int mp3library(){
	GLCD_Clear(White);
	while(1){
	GLCD_SetTextColor(Yellow);
	GLCD_SetBackColor(Blue);
  GLCD_DisplayString(0, 0, __FI, "                                       ");
  GLCD_DisplayString(1, 0, __FI, "       MUSIC                          ");
	GLCD_DisplayString(3, 0, __FI, "      Streaming                    ");
	GLCD_DisplayString(5, 0, __FI, "   Select to Exit            ");
  mainaudio();
	return 0; 
  } }
void mediagallery(void){
	#include "ron.c"
	#include "rap.c"
	#include "ronlol.c"
	int joycounter=0;
	GLCD_Clear(LightGrey);
	while(1){
if(joycounter==0){
			#ifdef __USE_LCD
			GLCD_SetBackColor(LightGrey);
			GLCD_SetTextColor(Yellow);
	GLCD_SetBackColor(Red);
	    GLCD_DisplayString(1, 0, __FI, "    Media Center     ");			
			GLCD_DisplayString(2, 0, __FI, "   PHOTO GALLERY      ");	
	GLCD_SetBackColor(Red);	
			GLCD_SetTextColor(Black);
			GLCD_DisplayString(5, 0, __FI, "   Move JoyStick      ");
			GLCD_DisplayString(6, 0, __FI, "   Left or Right         ");
		GLCD_DisplayString(7, 0, __FI, "   SELECT TO EXIT        ");
			#endif
}
			if(get_button() == KBD_SELECT){
				break;
				
			}
		if(get_button()== KBD_LEFT){
			joycounter--;
			GLCD_Clear(White);
		}
		if(get_button()== KBD_RIGHT){
			joycounter++;
			GLCD_Clear(White);
		}
		if(joycounter>3){
			joycounter=0;
		}
		if(joycounter<0){
			joycounter=3;
		}
		
		if(joycounter==1){
		
	GLCD_Bitmap(80,70,128,128, (unsigned char*)RONLOL_pixel_data);
		}
		if(joycounter==2){
			GLCD_WindowMax();
			GLCD_Bitmap(90,70,128,128, (unsigned char*) GIMP_IMAGE_pixel_data);
		}
		if(joycounter==3){
				GLCD_Bitmap(100,30,102,146, (unsigned char*) RON_pixel_data);			
		}	}
		return;}
int main (void){
	int joycounter = 0; 
	SystemInit();
	LED_Init();
	GLCD_Init();
	KBD_Init();
	 GLCD_Clear(White);                       
  //GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Black);
  GLCD_DisplayString(0, 0, __FI, "     MEDIA CENTER    ");
  GLCD_SetTextColor(Red);
  GLCD_DisplayString(1, 0, __FI, "     MAIN MENU     ");
	GLCD_SetBackColor(LightGrey);
					GLCD_DisplayString(4,0, __FI, "->Gallery");
					GLCD_SetBackColor(White);
					GLCD_DisplayString(6,0, __FI, "MP3 Player    ");
					GLCD_DisplayString(8,0, __FI, "Game    ");
	while(1){		
		while(1){  
	   if(get_button()==KBD_DOWN){
		   joycounter++;
			 delay();
   			}
	if(get_button()== KBD_UP){
			joycounter--;
		delay();
		}
	if(get_button()==KBD_SELECT){
		if(joycounter==0){// gallery
			GLCD_Clear(White);
			mediagallery();
			break;
		}
		if(joycounter==1){// mp3 
			mp3library();
			break;
		}
		if(joycounter==2){// game
			snake();
			break;
		}  }	  
	  	if(joycounter<0){
	  	joycounter=2;
	  	}
	  	if(joycounter>2){
	  	joycounter=0;
	  	}
	 #ifdef __USE_LCD
                          		if(joycounter==0){
									
					GLCD_SetBackColor(LightGrey);
					GLCD_DisplayString(4,0, __FI, "->Gallery");
					GLCD_SetBackColor(White);
					GLCD_DisplayString(6,0, __FI, "MP3 Player   ");
					GLCD_DisplayString(8,0, __FI, "Game    "); }
					
				if(joycounter==1){
					
					GLCD_SetBackColor(White);
					GLCD_DisplayString(4,0, __FI, "Gallery    ");
					GLCD_SetBackColor(LightGrey);
				    GLCD_DisplayString(6,0, __FI, "->MP3 Player");
					GLCD_SetBackColor(White);
					GLCD_DisplayString(8,0, __FI, "Game     ");
				}
				if(joycounter==2){//gg
				
					GLCD_SetBackColor(White);
					GLCD_DisplayString(4,0, __FI, "Gallery    ");
					GLCD_SetBackColor(White);
					GLCD_DisplayString(6,0, __FI, "MP3 Player    ");
					GLCD_SetBackColor(LightGrey);
					GLCD_DisplayString(8,0, __FI, "->Game"); 

					} 
   #endif	} 
		GLCD_Clear(White);
			 GLCD_SetBackColor(White);
		  GLCD_SetTextColor(Black);
			GLCD_DisplayString(0, 0, __FI, "     MEDIA CENTER     ");
			GLCD_SetTextColor(Red);
			GLCD_DisplayString(1, 0, __FI, "     MAIN MENU        ");
			GLCD_SetBackColor(LightGrey);
					GLCD_DisplayString(4,0, __FI, "->Gallery");
					GLCD_SetBackColor(White);
					GLCD_DisplayString(6,0, __FI, "MP3 Player   ");
					GLCD_DisplayString(8,0, __FI, "Game     "); } }
