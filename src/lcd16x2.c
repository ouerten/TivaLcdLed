#include "lcd16x2.h"
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "systemTimer.h"

void ekran_char(char c)
{
  LCD_RS(1);
  delay_ms(2);
  LCD_DATA = ((c & 0xF0) >> 4);
  EN_ACKAPA();
  LCD_DATA =  (c & 0x0F);
  EN_ACKAPA();
}

void ekran_yap(unsigned char c)
{
  LCD_RS(0);
  delay_ms(2);
  LCD_DATA = ((c & 0xF0) >> 4);
  EN_ACKAPA();
  LCD_DATA =  (c & 0x0F);
  EN_ACKAPA();
}

void ekran_sil(void)
{
  ekran_yap(0x01);
  delay_ms(10);
}

void ekran_string(const char* s)
{
  while(*s)
    ekran_char(*s++);
}

void ekran_git(char x, char y)
{
  if(x==1)
    ekran_yap(0x80+((y-1)%16));
  else
    ekran_yap(0xC0+((y-1)%16));
}

void lcd_init()
{
  SYSCTL_RCGC2_R     |=  SYSCTL_RCGC2_GPIOB;
  GPIO_PORTB_DIR_R   |=  0x03;
  GPIO_PORTB_AFSEL_R &= ~0x03;
  GPIO_PORTB_DEN_R   |=  0x03;
  GPIO_PORTB_PCTL_R   =  0xFFFFFF00;
  GPIO_PORTB_AMSEL_R &=  0x03;
  SYSCTL_RCGC2_R     |=  SYSCTL_RCGC2_GPIOD;
  GPIO_PORTD_DIR_R   |=  0x0F;
  GPIO_PORTD_AFSEL_R &= ~0x0F;
  GPIO_PORTD_DEN_R   |=  0x0F;
  GPIO_PORTD_PCTL_R  &=  0xFFFF0000;
  GPIO_PORTD_AMSEL_R &= ~0x0F;
  LCD_RS(0);
  LCD_EN(0);
  ekran_yap(0x28);
  ekran_yap(0x0C);
  ekran_yap(0x06);
  ekran_yap(0x80);
  ekran_yap(0x28);
  ekran_sil();
}
