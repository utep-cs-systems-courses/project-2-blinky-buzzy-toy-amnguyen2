# Project 2 - Blinky Buzzy Toy

I wrote code to make the MSP430 board into a simple toy. The state machine I wrote
plays notes using the buzzer and flashes the LEDs after pressing the buttons on the green board.

## Running the Program

To compile and run the program on the MSP430, use:

**$ make load**

To clean any unnecessary or temporary files from the project directory:

**$ make clean**

## State Machine

The toy I created uses a state machine. The state machine begins at state 0. 
Pressing the first 3 buttons cause the state machine to advance to any of the 3 states, 
respective to each of the buttons. 
Holding down the fourth button will advance the state machine automatically from state 0, to 1,
to 2, to 3, and back to state 0.

0. Starting State
   - The state machine begins in this state.
   - Both the RED and GREEN LEDs are OFF.
   - The BUZZER is OFF.
   - Must hold SWITCH 4 to advance to this state.
1. State 1
   - The GREEN LED is BRIGHT.
   - The BUZZER plays a song, the user is unable to interrupt it.
   - After the song is played, the machine auto transitions to STATE 2.
   - Must use SWITCH 1 or hold SWITCH 4 to advance to this state.   
2. State 2
   - The RED LED is BRIGHT.
   - The BUZZER is OFF.
   - This state is transitioned to automatically after STATE 1.
   - Must use SWITCH 2 or hold SWITCH 4 to advance to this state.
3. State 3
   - Both the RED and GREEN LEDs are DIM.
   - The BUZZER plays note C4.
   - Must use SWITCH 3 or hold SWITCH 4 to advance to this state.
