#ifndef switches_included
#define switches_included

#define SW1 BIT3    // P2.3, switch 1

#define SWITCHES SW1 | SW2 | SW3 | SW4   // 0000 1111

void switch_init();
void switch_interrupt_handler();

extern char sw1_state_down, sw1_state_changed; // effectively boolean

#endif
