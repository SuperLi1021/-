#ifndef _lanya_h_
#define _lanya_h_

#define uchar unsigned char
#define uint unsigned int
extern unsigned int pl,wendui,wenduo;

extern uchar djb,diwen,gaowen,zkb,zkbb,djbb;



void timerInit();
void uart_send_byte(unsigned char dat);
void uart_send_1();
void uart_send_2();
void uart_send_3();
void uart_send_4();
void uart_send_5();

void uart_send_int(unsigned int s);
void uart_interrupt(void);
#endif