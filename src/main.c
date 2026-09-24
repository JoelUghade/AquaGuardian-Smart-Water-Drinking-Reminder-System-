#include "header.h"

s32 hour,min,sec;

int dg=16,cg=0,rg=0,check_al,alarm,reminder=1,flagofcomplete=0;;

int main()
{	
		INT();
	while(1)	  
	{
		//display on lcd
		 display_main();
		
		if(MIN>=check_al && (cg<dg))										 //---
		{
			reminderr();
		}


		// if the he drink in the middle
		if(((READBIT(IOPIN0,BUT))==0) )
		{
			middlecheck();
		}
		/// daily consume is completed
			if((cg==dg) && (flagofcomplete==0))
			{	
				flagofcomplete=1;
				complete();
			}
			// to set the Remaining 
			rg=dg-cg;

	  		// if 24h rhr reset
			if(HOUR==0 && MIN==0 && sec<=2)
			{
				cg=0;
				dg=16;	
				flagofcomplete=0;
			}			
	}

}


