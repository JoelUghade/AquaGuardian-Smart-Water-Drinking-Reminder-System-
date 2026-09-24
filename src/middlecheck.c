#include "header.h"

extern int rg,dg,cg,alarm,check_al,reminder;
int check_mid=0;

	//create water 
	u8 cgramLUT[16]={0x00,0x11,0x11,0x1f,0x1f,0x1f,0x1f,0x00,
					0x00,0x11,0x11,0x11,0x11,0x1f,0x1f,0x00};

void INT(void)
{
	int check_mid=0;


	//intialise
	 IODIR0|= (1<<YLED) | (1<<Buzzer) | (1<<RLED) | (1<<GLED);
//	 IOSET0|=// |(1<<YLED)  | (1<<RLED) | (1<<GLED)  ;



	Init_Interrupt();
	//initialize keypad
	Init_KPM();
	//initialize rtc
	RTC_Init();
	//initailize LCD
	InitLCD();
	// Set the initial time (hours, minutes, seconds)
//	SetRTCTimeInfo(12,0,0);



	
	//CGRAM ready
	BuildCGRAM(cgramLUT,16);
	//scroll
					
	rg=dg-cg;
	//GetRTCTimeInfo(&hour,&min,&sec);
	alarm=MIN;
														//----
	check_al=alarm+reminder;

	IOSET0|=(1<<YLED)  | (1<<RLED) | (1<<GLED)  ;
}

void complete(void)
{
				CmdLCD(CLEAR_LCD);
				IOCLR0=1<<GLED;
				CmdLCD(GOTO_LINE1_POS0+1);
					StrLCD("CONGRATULATION");
				CmdLCD(GOTO_LINE2_POS0+2);
				StrLCD("GOAL ACHIEVED");			 
				delay_s(5);
				IOSET0=1<<GLED;
			}
			
void middlecheck(void)
   	{
					while(1)
					{
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0);
							StrLCD("Drink Water?");	
				mid:		CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0);
							StrLCD("Did you Drink?");
						CmdLCD(GOTO_LINE2_POS0);
							StrLCD("1.Yes  2. No");
						check_mid=keyscan();
							if(check_mid=='1')
								{
									cg++;
									//reminder reset;
									check_al=alarm+reminder;
									//redled
									IOSET0|=1<<RLED;									

									LCD_DONE();
									break;

								}
							else if(check_mid=='2')
							{	
								CmdLCD(CLEAR_LCD);
								CmdLCD(0x80+3);
									StrLCD("Great!!");
								
								delay_s(2);
									break;
							}
							else
							{
								CmdLCD(CLEAR_LCD);
								CmdLCD(0x80);
									StrLCD("Wrong Input");
								delay_s(1);
								goto mid;
							}

					}
				// for defaultreset of reminder
			alarm=MIN;													//----
			check_al=alarm+reminder;

			}
