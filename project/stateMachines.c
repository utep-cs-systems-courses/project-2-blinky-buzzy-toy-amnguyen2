#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

static char state = 0;
static enum {off = 0, dim = 1, bright = 2} ledMode;
static char new_red_on;
static char new_green_on;

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  // state 0: red and green are bright
  // nothing is pressed
  sm_update_led();
  sm_update_buzzer();

  // if state 0 and switch 1 pressed, move to state 1
  if (state == 0 & sw1_state_down == 1) {
    // state 1: both lights dim
    state++;
    sm_update_led();
    sm_update_buzzer();
  }

  // if state 1 and switch 2 is pressed, move to state 2
  else if (state == 1 & sw2_state_down == 1) {
    // state 2: both lights off
    state++;
    sm_update_led();
    sm_update_buzzer();
  }

  // if state 2 and switch 3 is pressed, move to state 3
  else if (state == 2 & sw3_state_down == 1) {
    // state 3: buzzer sound, LEDs stay off
    state++;
    sm_update_buzzer();
  }

  // if state 3 and switch 4 is pressed, move to state 0
  else if (state == 3 & sw4_state_down == 1) {
    // state 2: both lights off
    state = 0;
    sm_update_led();
    sm_update_buzzer();
  }

  led_update();
}
