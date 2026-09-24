//interuppts
#define EINT0_VIC_CHNO 14
#define EINT0_PIN_FUNC   0x0000000C
void eint0_isr(void) __irq;


void Init_Interrupt(void);
