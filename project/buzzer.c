#include <msp430.h>
#include "../demos/timerLib/libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void play_song()
{
  int D4 = 6810; // musical notes 
  int E4 = 6067;
  int F4 = 5726;
  int G4 = 5102;
  int A4 = 4545;
  int B4 = 4049;
  int C5 = 3822;
  int D5 = 3405;
  int E5 = 3033;
  
  int song[25] = {F4, A4, B4, B4, F4, A4, B4, B4, F4, A4, B4,
		  E5, D5, D5, B4, C5, B4, G4, E4, E4, 0, D4, E4, G4, E4};

  for (int i = 0; i < 25; i++) {
    buzzer_set_period(song[i]);
    __delay_cycles(5000000);
  }
  buzzer_set_period(0); // silence buzzer
  return;
}
