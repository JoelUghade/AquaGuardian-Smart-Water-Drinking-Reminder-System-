//KPM.c
#include "types.h"
#include "define.h"
#include "delay.h"
#include"KPM_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include <lpc21xx.h>

u8 KPMLUT[4][4]=
{
	{'1','2','3','B'},
	{'4','5','6','*'},
	{'7','8','9','-'},
	{'C','0','=','E'}
};

void Init_KPM(void)
{
	WRITENIBBLE(IODIR1,ROW0,15);
	//IODIR1|=1<<18 | 1<<19 |1<<20 |1<<21;
}

u32 colscan(void)
{
	if(READNIBBLE(IOPIN1,COL0)<15)
		return 0;
	else
		return 1;
}

u32 colcheck(void)
{
	u32 cno;
	for(cno=0;cno<4;cno++)
	{
		if((READBIT(IOPIN1,(cno+COL0)))==0)
			break;

	}
	return cno;
}

u32 rowcheck(void)
{
	u32 rno;
	for(rno=0;rno<4;rno++)
	{
		WRITENIBBLE(IOPIN1,ROW0,(~(1<<rno)));
		if(colscan()==0)
			break;
	}
	IOCLR1=15<<ROW0;
	return rno;
}



u32 keyscan (void)
{
	u32 rno,cno,key;
	//wait for switch to press
	while(colscan());
	//find rno
	rno=rowcheck();
	//find cno
	cno=colcheck();
	key=KPMLUT[rno][cno];
	while(!colscan());
	delay_ms(400);
	return key;
}



 u32 ReadNum(void)

{

	u8 key;

	u32 num=0,pos=0,i;

	while(1)

	{
		 CmdLCD(DSP_ON_CUR_BLK);
		key=keyscan();
		         //-------
		if(key == 'E' && pos == 0)
		{

		 	CmdLCD(DSP_ON_CUR_OFF);
			return (-1);
		}

		else if(key>='0'&&key<='9')

		{
			 pos++;
			num=(num*10)+(key-48);
			U32LCD(num%10);
				
		}
		else if(key =='B')
		{

			 num=num/10;
			  i=pos;
			  while(i--)
				 CmdLCD(SHIFT_DSP_LEFT);
			 StrLCD("                ");
			 i=16;
			  while(i--)
				 CmdLCD(SHIFT_DSP_LEFT);
		//	 delay_s(1);
//	 	 CmdLCD(GOTO_LINE2_POS0);												   4
			pos--;
			if(num!=0)
			 U32LCD(num);

		}
		else if( key =='E' )

			break;
		if(pos>6)
				break;
		
	//delay  for one input
	   	delay_ms(500);
	}
	 CmdLCD(DSP_ON_CUR_OFF);
	return num;

}


