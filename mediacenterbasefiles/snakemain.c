#include "stdio.h"
#include "stdlib.h"
#include "LPC17xx.h"
#include "KBD.h"
#include "GLCD.h"
#include "LED.h"
#define delaysnke 18
int x, y,size,fast, xfood, yfood; 
int direct = 0; 
int prev_direct = 0; 
int jv = 0; 
int jp = KBD_RIGHT; 
int sk[100][2]; //snake array
int collision = 0;
void food(){
	int i;
	xfood = rand()%9;
	yfood = rand()%20;
	for(i=0;i<size;i++){
		if(xfood == sk[i][0])
			if(yfood == sk[i][1])
				food();	}
	GLCD_DisplayChar(xfood,yfood,1,0x81); }
void intialbod(){
	int i; //counting
	// sets the head first then followed by the body
	for(i=0;i<size;i++){
		
		if(direct==0){ //R
			sk[i][0] = x; 
			sk[i][1] = y-1;			
		}
		if(direct==1){//L
			sk[i][0] = x;
			sk[i][1] = y+1;			
		}
		if(direct==2){//D
			sk[i][0] = x+1; 
			sk[i][1] = y;			
		}
		if(direct==3){//U
			sk[i][0] = x-1;
			sk[i][1] = y;		
		}	} }
void clearsk(){
	int i;
	for(i=0;i<size;i++){
		sk[i][0]=1;
		sk[i][1]=1;
	} }
void plusbody(){
	size++;
	if(fast != 0)
		fast--;
	} 	
	void dealy1 (int count){
	count <<= delaysnke;
	while(count--); }
void check(){
	int i;
	//food collision
	if(xfood == sk[0][0])
		if(yfood == sk[0][1]){
			plusbody();
			food(); 	}
	//tail collision 
	for(i=1;i<size;i++){
		if(sk[0][0] == sk[i][0])
			if(sk[0][1] == sk[i][1])
				collision = 1; }
	    //collision to wall
		//right wall
		if(sk[0][1] == 19 && sk[1][1] == 18)
			collision = 1;
		//left wall
		if(sk[0][1] == 0 && sk[1][1] == 1)
			collision = 1;
		//bottom wall
		if(sk[0][0] == 9 && sk[1][0] == 8)
			collision = 1;
		//top wall
		if(sk[0][0] == 0 && sk[1][0] == 1)
			collision = 1;  }

void movement(){
	int i;
	switch(direct){
		case 0://R
						for(i=size;i>0;i--){
							if(i -1 == 0){
								sk[0][1] = y;
								sk[0][0] = x;				
							}else{
								GLCD_DisplayChar(sk[i-1][0],sk[i-1][1],1,' ');
								sk[i-1][1] = sk[i-2][1];
								sk[i-1][0] = sk[i-2][0];
							}
					}		
					for(i=1;i<size;i++){
						GLCD_DisplayChar(sk[0][0],sk[0][1],1,0xd7);
						GLCD_DisplayChar(sk[i][0],sk[i][1],1,0x82);
					}
					dealy1(fast);
						
			
			break;
		case 1: //L
						for(i=size;i>0;i--){
						if(i -1 == 0){
							sk[0][1] = y;
							sk[0][0] = x;				
						}else{
							GLCD_DisplayChar(sk[i-1][0],sk[i-1][1],1,' ');
							sk[i-1][1] = sk[i-2][1];
							sk[i-1][0] = sk[i-2][0];
						}
					}
					for(i=1;i<size;i++){
						GLCD_DisplayChar(sk[0][0],sk[0][1],1,	0xd7);
						GLCD_DisplayChar(sk[i][0],sk[i][1],1,0x82);
					}
					dealy1(fast);
			
			break;
		case 2://D
						for(i=size;i>0;i--){
						if(i -1 == 0){
							sk[0][1] = y;
							sk[0][0] = x;				
						}else{
							GLCD_DisplayChar(sk[i-1][0],sk[i-1][1],1,' ');
							sk[i-1][1] = sk[i-2][1];
							sk[i-1][0] = sk[i-2][0]; 	}	}
					for(i=1;i<size;i++){
						GLCD_DisplayChar(sk[0][0],sk[0][1],1,	0xd7);
						GLCD_DisplayChar(sk[i][0],sk[i][1],1,0x82);
					}
					dealy1(fast);
			break;
		case 3://U		for(i=size;i>0;i--){
						if(i-1 == 0){
							sk[0][1] = y;
							sk[0][0] = x;				
						}else{
							GLCD_DisplayChar(sk[i-1][0],sk[i-1][1],1,' ');
							sk[i-1][1] = sk[i-2][1];
							sk[i-1][0] = sk[i-2][0]; } }
					for(i=1;i<size;i++){
						GLCD_DisplayChar(sk[0][0],sk[0][1],1,	0xd7);
						GLCD_DisplayChar(sk[i][0],sk[i][1],1,0x82);  }
					dealy1(fast);
			break;	}
	check(); }	
//////////////////////////////////////////////////////
void direction(int joycurrent){
    if(joycurrent== KBD_UP||joycurrent== KBD_DOWN||joycurrent== KBD_RIGHT||joycurrent== KBD_LEFT){		
		if(joycurrent==KBD_UP){
			if (jp == KBD_LEFT || jp == KBD_RIGHT){
				x--;
				if (x < 0){
					x = 9; 	}
				direct = 3;
				prev_direct = direct;
				jp = jv;
				movement(); } 	}		
		if(joycurrent==KBD_DOWN){
			if (jp == KBD_LEFT || jp == KBD_RIGHT){
				x++;
				if (x > 9){
					x = 0; 	}
				direct = 2;
				prev_direct = direct;
				jp = jv;
				movement(); 	}	}		
		if(joycurrent==KBD_LEFT){
			if (jp == KBD_UP || jp == KBD_DOWN){
				y--;
				if (y < 0){
					y = 20; 	}
				direct = 1;
				prev_direct = direct;
				jp = jv;
				movement(); }	}		
		if(joycurrent==KBD_RIGHT){
			if (jp == KBD_UP || jp == KBD_DOWN){
				y++;
				if (y > 20 ){
					y = 0;}
				direct = 0;
				prev_direct = direct;
				jp = jv;
				movement();  }}	
	}else{ 	if(direct==0){//R
			y++;
				if (y > 20){ y = 0;	}
					movement();
					check();
			
		}
		if(direct==1){//L
			y--;
					if (y < 0){
						y = 20;		}
					movement();
					check(); 		}
		if(direct==2){ //D
			x++;
					if (x > 9){ 	x = 0;	}
					movement();
					check();		}
		if(direct==3){//U
			x--;
					if (x < 0){	x = 9;	}
					movement();
					check();	}}}
int snake(){
	int joy_try;
	int gameover, tryagain;
	int done=0;
	GLCD_Init();
	KBD_Init();
	LED_Init();
	while(!done){
		tryagain = 1;
		direct = 0;
		prev_direct = 0;
		jv = 0;
		jp = KBD_RIGHT;
		fast = 15;
		size = 2;
		x = 5;
		y = 10;
		GLCD_Clear(Black);
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(Green);
					GLCD_Clear(White);
					GLCD_SetBackColor(White);
					GLCD_SetTextColor(Black);
		intialbod();
		food();	
		while(collision == 0){
			jv = get_button();
			direction(jv); }
		if(collision == 1){			
			while(1){
			GLCD_DisplayString(2,0,1,"      GAME OVER     ");
			gameover = 0;
			GLCD_DisplayString(3,0,1,"    SELECT TO EXIT     "); 
			if((joy_try = get_button())== KBD_SELECT){
						GLCD_Clear(White);					
						done =1;						
						clearsk();							
						collision=0;						
						return 0;     } }}		
		dealy1(5);	 }
	return 0; }
