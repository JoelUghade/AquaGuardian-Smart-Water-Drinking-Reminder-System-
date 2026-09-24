//interuppts
#include <lpc21xx.h>
#include "types.h"
#define EINT0_VIC_CHNO 14
#define EINT0_PIN_FUNC   0x0000000C
#include "lcd.h"
#include "lcd_defines.h"
#include "KPM.h"
#include "rtc_main.h"
#include "delay.h"

extern int dg,alarm,check_al,reminder;

void eint0_isr(void) __irq;




void Init_Interrupt(void){

	   	 //Cfg p0.1 as EINT0 input
	PINSEL0&=~(3<<(1*2));
	PINSEL0|=EINT0_PIN_FUNC;
	
	VICIntEnable=1<<EINT0_VIC_CHNO;

	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	//load isr addr into irq slot 0
	VICVectAddr0=(u32 )eint0_isr;
	
	EXTMODE=1<<0;
}



void eint0_isr(void) __irq
{
	int key=0 ,check_dg=0,flag=0,phour=0,pmin=0,goal=24/dg;
	CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0+5);
				StrLCD("MENU");
				delay_s(1);	
	while(1){

	//display menu
				 

					CmdLCD(GOTO_LINE1_POS0);
				StrLCD("1. TIME  ");
				StrLCD("2.Goals");
					CmdLCD(GOTO_LINE2_POS0);
				StrLCD("3. Exit");
								
				
					
		//wait for key
				key=keyscan();
				switch(key)
				{
					 case '1':
					 {
					 /// display and get data in phour and pmin
					 		CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0+5);
								StrLCD("RTC");
							CmdLCD(GOTO_LINE2_POS0+2);
								StrLCD("MODIFICATION");
							delay_s(2);
			hr:				CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
								StrLCD("1. Hours");
							CmdLCD(GOTO_LINE2_POS0);
								phour=ReadNum();
									if(phour >23)
									{
										CmdLCD(CLEAR_LCD);
											StrLCD("Wrong Input");
										CmdLCD(GOTO_LINE2_POS0+3);
											StrLCD("(0-23)");
											
										delay_s(2);
										goto hr;
									}

			mi:				CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
								StrLCD("2. Minutes");
							CmdLCD(GOTO_LINE2_POS0);
								pmin=ReadNum();
								if(pmin>59)
									{
										CmdLCD(CLEAR_LCD);
											StrLCD("Wrong Input");
										CmdLCD(GOTO_LINE2_POS0+3) ;
											StrLCD("(0-59)");
										delay_s(2);
										goto mi;
									}

						

							// display done
							CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
								StrLCD("Time is Updated");
						/*	CmdLCD(GOTO_LINE2_POS0);
								U32LCD(phour);
								StrLCD(":");
								U32LCD(pmin);
						*/
								delay_s(1);

					//modify the hour and min
					if(phour != -1 && pmin!=-1)
						 	SetRTCTimeInfo(phour,pmin,0);
					else if( phour==-1 && pmin ==-1 )
						SetRTCTimeInfo(HOUR,MIN,0);
					else if( phour==-1 )
						SetRTCTimeInfo(HOUR,pmin,0);
					else if( pmin ==-1)
						SetRTCTimeInfo(phour,MIN,0);
					
						alarm=MIN;													//----
						check_al=alarm+reminder;		

							//exit
							flag=1;							
							CmdLCD(CLEAR_LCD);

					 }
					 		break;
					case '2': 	{
								 CmdLCD(CLEAR_LCD);
								 CmdLCD(0x80);
								 	StrLCD("1. Duration ");
								 CmdLCD(GOTO_LINE2_POS0);
								 	StrLCD("2. No. of Goals");
								 key=keyscan();
								 goal=24/reminder;
								 switch(key)
								 {
								 	case '2':{	  
						changeduration:	CmdLCD(CLEAR_LCD);
													while(1)
												{
												CmdLCD(GOTO_LINE1_POS0);
													StrLCD("Change the daily");
												CmdLCD(GOTO_LINE2_POS0);
													StrLCD("Goals : ");
												
													check_dg=ReadNum();
												
												if(check_dg<=0 || check_dg>goal)
												{
													CmdLCD(CLEAR_LCD);
													CmdLCD(0x80+3);
													StrLCD(" Wrong Input");
													CmdLCD(GOTO_LINE2_POS0+1);
														StrLCD("less than ");
														U32LCD(goal);
													delay_s(2);
													CmdLCD(CLEAR_LCD);
												}
												else
												{
													dg=check_dg;
													flag=1;
													CmdLCD(CLEAR_LCD);
													StrLCD("Updated Daily");
													CmdLCD(GOTO_LINE2_POS0 );
													StrLCD("Goals: ");
													U32LCD(dg);
													delay_s(2);
													CmdLCD(CLEAR_LCD);
													break;
												}
											}
											 	
										}
										break;
									
									case'1':
									{
						dur:		CmdLCD(CLEAR_LCD);
										CmdLCD(0x80);
											  StrLCD("Duration (hrs)");
											CmdLCD(GOTO_LINE2_POS0);
										key=ReadNum();
										if(key>8 || key==0)
										{
											CmdLCD(CLEAR_LCD);
												StrLCD("  Wrong input");
											delay_s(1);
												goto dur;
										}
										goal=24/key;
											if(dg>goal)
											{
												CmdLCD(CLEAR_LCD);
												CmdLCD(0x80+1);
													StrLCD(" Not compatible ");	
												CmdLCD(GOTO_LINE2_POS0+4);												
													StrLCD("with Goals");
													CmdLCD(CLEAR_LCD);
												CmdLCD(0x80+1);
													StrLCD("Need to change");	
												CmdLCD(GOTO_LINE2_POS0+4);												
													StrLCD("Goals");	
												delay_s(1);
												 reminder=key;
												goto changeduration;		
											}

									  //// updated
										CmdLCD(CLEAR_LCD);
										CmdLCD(GOTO_LINE1_POS0+3 );
													StrLCD("Updated");
													 reminder=key;
													delay_s(2);		
									}


								   }	

					
								}
							break;
					case '3':
							flag=1; 
					break;

					
				}
			


		if(flag==1)
		{
			alarm=MIN;
			check_al=alarm+reminder;
			break;
		}
	}	

 //clear eint0 status in vic
	VICVectAddr=0;
	//clear eint0 status in EIP
	EXTINT=1<<0;
}

