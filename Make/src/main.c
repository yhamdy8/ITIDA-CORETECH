#include<stdio.h>
#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"DIO_interface.h"
#include"PORT_interface.h"


void main(void)
{

    GROUP_voidInitDIR();
    //port a pin 1 op
    // 
    while(1)
    {   
        for(int i=0; i<8; i++)
        {
            DIO_u8_Set_Pin_Value(DIO_u8_GROUP_A, i, DIO_u8_PIN_HIGH);
            _delay_ms(500);
        }
        DIO_u8_Set_Port_Value(DIO_u8_GROUP_A, 0x0);
        _delay_ms(100);
    }
}