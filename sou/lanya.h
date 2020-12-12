#ifndef _lanya_h_
#define _lanya_h_

#define uchar unsigned char
#define uint unsigned int
extern unsigned int pl,zkb,wendui,wenduo;

extern uchar djb,diwen,gaowen;



void timerInit();
void uart_send_byte(unsigned char dat);
void uart_send_str(unsigned char *s);
void uart_interrupt(void);
#endif