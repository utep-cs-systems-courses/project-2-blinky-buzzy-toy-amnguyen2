#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

static char state = 0;
static char new_red_on;
static char new_green_on;

static char f = 0; // for dimming functionality. is the led being flashed right now?

static int beat = 0; // current beat in song
const int D4 = 6810; // musical notes 
const int E4 = 6067;
const int F4 = 5726;
const int G4 = 5102;
const int A4 = 4545;
const int B4 = 4049;
const int C5 = 3822;
const int D5 = 3405;
const int E5 = 3033;


void sm_update_led()
{
  char dimness = 8; // higher dimness = lower brightness
  f++; // f iterates from 0 to 'dimness'
  if (f > dimness) f = 0; // reset f back to 0
  
  switch(state) {
  case 0: // state 0
    new_red_on = 0;
    new_green_on = 0;
    break;
  case 1: // state 1
    new_red_on = 0;
    new_green_on = 1;
    break;
  case 2: // state 2
    new_red_on = 1;
    new_green_on = 0;
    break;
  case 3:
    new_red_on = (f == 0);
    new_green_on = (f == 0);
  }

  if (red_on != new_red_on) {
    red_on = new_red_on;
    led_changed = 1;
  }

  if (green_on != new_green_on) {
    green_on = new_green_on;
    led_changed = 1;
  }
}

void sm_update_buzzer()
{
  switch(state) {
  case 0: // state 0
    buzzer_set_period(0); // silent
    break;
  case 1: // state 1
    buzzer_set_period(F4);
    break;
  case 2: // state 2
    buzzer_set_period(A4);
    break;
  case 3: // state 3
    buzzer_set_period(B4);
    break;
  }
}

void sm_play_song()
{
  // F,A,B,B,F,A,B,B,F,A,B,
  // E,D,D,B,C,B,G,E,E,D,E,G,E,E
  int song[24] = {F4, A4, B4, B4, F4, A4, B4, B4, F4, A4, B4,
		E5, D5, D5, B4, C5, B4, G4, E4, E4, D4, E4, G4, E4};

  while (beat < 24) {
    buzzer_set_period(song[beat]);
    __delay_cycles(20000);
    beat++;
  }
 
  return;
}

void state_advance()
{
  /* state 0 (initial):
     - lights are off
     - buzzer is silent
  */
  
  if (sw1_state_down) {
    /* state 1:
       - green light turns bright
       - buzzer plays A4
     */
    state = 1;
    
  } else if (sw2_state_down) {
    /* state 2:
       - green light turns off
       - red light turns bright
       - buzzer plays B4
    */
    state = 2;

  } else if (sw3_state_down) {
    /* state 3:
       - green light turns dim
       - red light turns dim
       - buzzer plays D5
    */
    state = 3;

  } else if (sw4_state_down) {
    // advance state automatically (0,1,2,3,0)
    state++;
    if (state > 3) {
      state = 0;
    }
  }
}
