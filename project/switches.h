#ifndef switches_included
#define switches_included

#define SW1 BIT0    // P2.0
#define SW2 BIT1    // P2.1
#define SW3 BIT2    // P2.2
#define SW4 BIT3    // P2.3

#define SWITCHES SW1 | SW2 | SW3 | SW4   // 0000 1111

void switch_init();
void switch_interrupt_handler();

extern char sw1_state_down, sw1_state_changed; // effectively boolean
extern char sw2_state_down, sw2_state_changed;
extern char sw3_state_down, sw3_state_changed;
extern char sw4_state_down, sw4_state_changed;

#endif
