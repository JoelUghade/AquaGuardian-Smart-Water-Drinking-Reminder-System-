
#include "header.h"

extern int sec,cg,rg,alarm,check_al,reminder,dg	 ;
int flag=0,check_ndrink=0;




void LCD_DRINK(void)
{
//	CmdLCD(CLEAR_LCD);
	CmdLCD(0x80+1);
	StrLCD("TIME TO HYDRATE ");
	CmdLCD(GOTO_LINE2_POS0+2);
//	CharLCD(0);
	StrLCD("DRINK WATER!!");
	delay_ms(500);
}

void LCD_DONE(void)
{
	int i;
	IOCLR0|=1<<GLED;
	CmdLCD(CLEAR_LCD);
	CmdLCD(0x80+3);
	StrLCD("GREAT JOB");
	CmdLCD(GOTO_LINE2_POS0);
//	for(i=12-dg;i>0;i--)
//		StrLCD(" ");
	for(i=1;i<=cg;i++)
	{
		CharLCD(1);
	}
	for(i=1;i<=rg;i++)
	{
		CharLCD(0);
	}		



	delay_s(5);
	IOSET0|=1<<GLED;
	CmdLCD(CLEAR_LCD);
}




void reminderr(void)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
			
		
			//if not drink set (check_ndrink)
				check_ndrink=sec+20;
				CmdLCD(CLEAR_LCD);
	  
				// 20 sec times for the reminder
			//	data=20*12000000;				

			while(check_ndrink>=SEC)
			{
										

				//	display_count_not_drink=check_ndrink-sec;
			 
			 	//buzzer
				IOSET0|=1<<Buzzer; 
				// Led
				IOCLR0|=1<<YLED;
				// LCD display
				LCD_DRINK();

				if((READBIT(IOPIN0,BUT))==0)
				{
					cg++;
					rg--;
					//turn of the led anf buzzer

					IOSET0|=1<<RLED;
					IOSET0|=1<<YLED;
					IOCLR0|=1<<Buzzer;
					LCD_DONE();
					flag=1;
					CmdLCD(CLEAR_LCD);
					break;
				}
								
			}
			if(flag==0)
				{
					IOSET0|=1<<YLED;
					IOCLR0|=1<<Buzzer;
					IOCLR0|=1<<RLED;
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0+2);
							StrLCD(" Failed to");
						CmdLCD(GOTO_LINE2_POS0+1);
							StrLCD("Consume Water");
						delay_s(2);
						CmdLCD(CLEAR_LCD);
				}
				else
					flag=0;

			// for defaultreset of reminder
			alarm=MIN;													//----
			check_al=alarm+reminder;
		}
