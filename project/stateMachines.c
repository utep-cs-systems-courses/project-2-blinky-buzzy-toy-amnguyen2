#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

static char state = 0;
static char new_red_on;
static char new_green_on;

static char f = 0; // for dimming functionality. is the led being flashed right now?

void sm_update_led()
{
  char dimness = 5; // higher dimness = lower brightness
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
    // dim both lights
    new_red_on = (f == 0);
    new_green_on = (f == 0);
    break;
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
    play_song();
    state = 2; // after song is played, auto transition to state 2 
    break;
  case 2: // state 2
    buzzer_set_period(0); // silent
    break;
  case 3: // state 3
    buzzer_set_period(7644); // C4 note
    break;
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
