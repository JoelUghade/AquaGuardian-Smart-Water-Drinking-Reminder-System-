#include <lpc21xx.h>
#include "delay.h"
#include "define.h"
#include <string.h>


#define Buzzer  0	//@p0.0
#define YLED  2	 //p.0.2
#define RLED  3
#define GLED  4
#define BUT	 6 //

//file
#include "rtc_main.h"
#include "KPM.h"	  
#include "lcd_defines.h"
#include "lcd.h"
#include "interrupt.h"
#include "display.h"
#include "reminder.h"
#include "middlecheck.h"
