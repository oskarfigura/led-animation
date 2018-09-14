/*
 *  main.c
 *
 *  Two buttons, one used to switch LEDs on and the other to switch them off 
 *  Created on: 31 Jan 2013
 *  Author: Oskar Figura
 *  Demo: https://youtu.be/KFQCP3L45aE
 *  Notes: One of my first programs written in C
 */

//Includes
#include <avr/io.h>
#include <util/delay.h>
 
//Macros
#define BTN_ON (1<<PD0)
#define BTN_OFF (1<<PD1)
 
//Main loop
int main(void)
{
    //Initialization
    DDRC = 0xFF;     //PORT C out
    PORTC = 0xFF;    //PORT C set to high state
    DDRD &= ~(BTN_ON | BTN_OFF); //PORT D BTN_ON and BTN_OFF set as inputs
    PORTD |= BTN_ON | BTN_OFF;   //PORT D BTN_ON and BTN_OFF pull up to VCC (internal resistor)

    void EFFECT_ON (void);  //Declare EFFECT_ON function to switch LEDs ON
    void EFFECT_OFF (void); //Declare EFFECT_OFF function to switch LEDs OFF

    uint8_t BTN_PRESSED (uint8_t BTN);   //Declare BTN_PRESSED function

    while(1)                                                
    {
        if(BTN_PRESSED(BTN_ON))
        {
            EFFECT_ON();                              
        }
        else if(BTN_PRESSED(BTN_OFF))
        {
            EFFECT_OFF();                             
        }
    }
}
 
//Switch series of LEDs ON in order with a 250ms delay between each LED
void EFFECT_ON (void)
{
    //Turn LEDs from PD0 to PD7 ON
    for(int8_t i=0; i<=7; i++) 
    {
        PORTC &= ~(1<<i);
        _delay_ms (250);
    }
}

//Switch series of LEDs OFF in order with a 250ms delay between each LED
void EFFECT_OFF (void)
{
    //Turn LEDs from PD0 to PD7 OFF
    for(int8_t i=7; i>=0; i--)              
    {
        PORTC |= (1<<i);
        _delay_ms (250);
    }
}
 
//Check for low state on any of the buttons
uint8_t BTN_PRESSED (uint8_t BTN)
{
    //Any of the buttons pressed?
    if( !(PIND & BTN) )
    {
        _delay_ms(80); //Ensures a button has been pressed
        if( !(PIND & BTN) )        
        {
            return 1;                              
        }
    }
    return 0;                                             
}