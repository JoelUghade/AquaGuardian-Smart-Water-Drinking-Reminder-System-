#include "header.h"

extern s32 hour,min,sec,dg,cg,rg;

char str[19]={"Drink Water!!      "};
char temp=0;
int i=0;


void display_main(void)
{
   int n=strlen(str);
	GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
														//----
		CmdLCD(GOTO_LINE1_POS0);		
	
		
		CmdLCD(GOTO_LINE1_POS0+9);
		
		StrLCD(str);
		  // srollrr
		  i=0;
		  temp=str[0];
		  
			for(i=0;i<n-1 ;i++)
			{
			str[i]=str[i+1];
			}
			str[n-1]=temp;
				
			delay_ms(500);  		
			//0CGRAM(0);
			//CmdLCD(CLEAR_LCD);

	//displaying goals

			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("C.");
	  		CharLCD(0);
			StrLCD(":");
				CharLCD((cg/10)+48);
				CharLCD((cg%10)+48);
			StrLCD("/");
	 			CharLCD((dg/10)+48);
				CharLCD((dg%10)+48);
			StrLCD(" ");
			StrLCD("R.");
	  		CharLCD(0);
				StrLCD(":");
					CharLCD((rg/10)+48);
					CharLCD((rg%10)+48);
}
