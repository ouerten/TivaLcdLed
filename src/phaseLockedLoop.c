#include "phaseLockedLoop.h"

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#include "inc/hw_sysctl.h"

void pll_init(void)
{

  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  SYSCTL_RCC_R  &= ~SYSCTL_RCC_XTAL_M;
  SYSCTL_RCC_R  |= SYSCTL_RCC_XTAL_16MHZ;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_SYSDIV2_M;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_SYSDIV2LSB;


  set_cpu_freq(3,1);

  while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0);
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

void set_cpu_freq(char sysdiv, char lsb)
{
  SYSCTL_RCC2_R &= ~0x1FC00000;
  SYSCTL_RCC2_R |= (sysdiv << 23) | (lsb << 22);
}

unsigned long get_cpu_freq(void)
{
  char sysdiv,lsb;

  sysdiv = (SYSCTL_RCC2_R & 0x1F800000) >> 23;
  lsb    = (SYSCTL_RCC2_R &   0x400000) >> 22;

  return ((unsigned long)(400000000)/(2 * sysdiv + 1 + lsb));
}
