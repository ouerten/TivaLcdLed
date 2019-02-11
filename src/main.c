#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "time.h"

#include "lcd16x2.h"
#include "phaseLockedLoop.h"
#include "systemTimer.h"

unsigned long cpu_freq;
void init_port_E() {
   volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
   SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;   // 1) E portunun osilatörünü etkinleştir
   tmp = SYSCTL_RCGCGPIO_R;
   GPIO_PORTE_LOCK_R = 0x4C4F434B;
   GPIO_PORTE_CR_R = 0x3F;         //PE5-0 değişikliklerine izin ver
    			 // Sadece PE0 kilidinin açılması gerekir, diğer bitler kilitlenemez
   GPIO_PORTE_AMSEL_R = 0x00;    	//PE'de analog devre dışı bırak
   GPIO_PORTE_PCTL_R = 0x00000000;
   GPIO_PORTE_DIR_R = 0x0F;
   GPIO_PORTE_AFSEL_R = 0x00;
   GPIO_PORTE_PUR_R = 0x30;
   GPIO_PORTE_DEN_R = 0x3F;      	// portE 5-0 giriş çıkış  etkinlerştir.
   }
int main(void)
{

  init_port_E();
  pll_init();
  systick_init();

  set_cpu_freq(3,1);
  cpu_freq = get_cpu_freq();

  lcd_init();

  volatile unsigned int delay;
  while(1){
	int i,j;
	j=i;
	i=rand()%4;
    if(j!=i){

    	   if(i==0){   // Kirmizi led yakildigi zaman olacak islemler.
           GPIO_PORTE_DATA_R |= 0b00000001;
           GPIO_PORTE_DATA_R &= 0b00000001;
           ekran_git(1,1);
           ekran_string("Kocaeli Uni");
           for (delay = 0 ; delay<4999999 ; delay++);
           ekran_git(2,1);
           ekran_string("Oguzhan Erten");
    }


	        else if(i==1){  // beyaz led yakildigi zaman olacak islemler

	    	GPIO_PORTE_DATA_R |= 0b00000010;
	        GPIO_PORTE_DATA_R &= 0b00000010;
	        ekran_git(2,1);
	        ekran_string("Oguzhan Erten");
	        for (delay = 0 ; delay<4999999 ; delay++);
	        ekran_git(1,1);
	        ekran_string("Kocaeli Uni");
   }


	        else if(i==2){   // yesil led yakildigi zaman olacak islemler
            int k;
	     	GPIO_PORTE_DATA_R |= 0b00000100;
	     	GPIO_PORTE_DATA_R &= 0b00000100;
		    for(k=1;k<17;k++){
		    ekran_git(1,k);
		    ekran_string("Kocaeli Uni");
		    for (delay = 0 ; delay<1000000 ; delay++);
		    ekran_sil();
   }

		    for (delay = 0 ; delay<4999999 ; delay++);

	     	for(k=1;k<17;k++){

			ekran_git(2,k);
		    ekran_string("Oguzhan Erten");

	        for (delay = 0 ; delay<1000000 ; delay++);
            ekran_sil();
	   }
   }




	    else if(i==3){    //mavi led yakildigi zaman olacak islemler
        int k;
		GPIO_PORTE_DATA_R |= 0b00001000;
		GPIO_PORTE_DATA_R &= 0b00001000;
		for(k=16;k>0;k--){
				ekran_git(1,k);
				ekran_string("Kocaeli Uni");
				for (delay = 0 ; delay<1000000 ; delay++);
				ekran_sil();

				}
				for (delay = 0 ; delay<4999999 ; delay++);


				for(k=16;k>0;k--){

					ekran_git(2,k);
				    ekran_string("Oguzhan Erten");

			    for (delay = 0 ; delay<1000000 ; delay++);
		        ekran_sil();
				 }

	    }


    for (delay = 0 ; delay<7200000 ; delay++);
	ekran_sil();
    }
  }
  while(1);
  }
