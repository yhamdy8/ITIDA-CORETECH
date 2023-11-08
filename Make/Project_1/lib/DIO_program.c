/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/************************		AUTHOR: Youssef Hamdy			   	***********************/
/************************		LAYER:	MCAL						***********************/
/************************		DRIVER: DIO							***********************/
/************************		VERSION: 1.00						***********************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_register.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


u8 DIO_u8_Set_Pin_Value(u8 Copy_u8_Port_ID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Value){
	if( (Copy_u8_Port_ID >= DIO_u8_GROUP_A ) && (Copy_u8_Port_ID<= DIO_u8_GROUP_D ) )
	{
		if( (Copy_u8_Pin_ID >= DIO_u8_PIN_0 ) && (Copy_u8_Pin_ID <= DIO_u8_PIN_7 ) )
		{
			if( (Copy_u8_Pin_Value == DIO_u8_PIN_LOW ) || (Copy_u8_Pin_Value == DIO_u8_PIN_HIGH ) )
					{
				switch(Copy_u8_Port_ID){
					case DIO_u8_GROUP_A :
						ASS_BIT(DIO_u8_PORTA, Copy_u8_Pin_ID, Copy_u8_Pin_Value );
						break;
					case DIO_u8_GROUP_B :
						ASS_BIT(DIO_u8_PORTB, Copy_u8_Pin_ID, Copy_u8_Pin_Value );
						break;
					case DIO_u8_GROUP_C :
						ASS_BIT(DIO_u8_PORTC, Copy_u8_Pin_ID, Copy_u8_Pin_Value );
						break;
					case DIO_u8_GROUP_D :
						ASS_BIT(DIO_u8_PORTD, Copy_u8_Pin_ID, Copy_u8_Pin_Value );
						break;
				}
					}else return Incorrect_Value;
		}else return Incorrect_Pin_ID;
	}else return Incorrect_Port_ID;
	return Correct_value;
}

u8 DIO_u8_Set_Port_Value( u8 Copy_u8_Port_ID, u8 Copy_u8_Port_Value ){
	if( (Copy_u8_Port_ID >= DIO_u8_GROUP_A ) && (Copy_u8_Port_ID<= DIO_u8_GROUP_D ) )
	{
		switch(Copy_u8_Port_ID){
			case DIO_u8_GROUP_A :
				DIO_u8_PORTA = Copy_u8_Port_Value;
				break;
			case DIO_u8_GROUP_B :
				DIO_u8_PORTB = Copy_u8_Port_Value;
				break;
			case DIO_u8_GROUP_C :
				DIO_u8_PORTC = Copy_u8_Port_Value;
				break;
			case DIO_u8_GROUP_D :
				DIO_u8_PORTD = Copy_u8_Port_Value;
				break;
		}
	}else return Incorrect_Port_ID;
	return Correct_value;	
}

u8 DIO_u8_Get_Pin_Value(u8 Copy_u8_Port_ID, u8 Copy_u8_Pin_ID, u8* Copy_pu8_Pin_Value){
	if( (Copy_u8_Port_ID >= DIO_u8_GROUP_A ) && (Copy_u8_Port_ID<= DIO_u8_GROUP_D ) )
	{
		if( (Copy_u8_Pin_ID >= DIO_u8_PIN_0 ) && (Copy_u8_Pin_ID <= DIO_u8_PIN_7 ) )
		{
			switch(Copy_u8_Port_ID){
				case DIO_u8_GROUP_A :
					*Copy_pu8_Pin_Value= GET_BIT(DIO_u8_PINA,Copy_u8_Pin_ID);
					break;
				case DIO_u8_GROUP_B :
					*Copy_pu8_Pin_Value= GET_BIT(DIO_u8_PINB,Copy_u8_Pin_ID);
					break;
				case DIO_u8_GROUP_C :
					*Copy_pu8_Pin_Value= GET_BIT(DIO_u8_PINC,Copy_u8_Pin_ID);
					break;
				case DIO_u8_GROUP_D :
					*Copy_pu8_Pin_Value= GET_BIT(DIO_u8_PIND,Copy_u8_Pin_ID);
					break;
			}
		}else return Incorrect_Pin_ID;
	}else return Incorrect_Port_ID;
	return Correct_value;
}

u8 DIO_u8_Get_Port_Value(u8 Copy_u8_Port_ID, u8* Copy_pu8_Port_Value){
	if( (Copy_u8_Port_ID >= DIO_u8_GROUP_A ) && (Copy_u8_Port_ID<= DIO_u8_GROUP_D ) )
	{
		switch(Copy_u8_Port_ID){
			case DIO_u8_GROUP_A :
				*Copy_pu8_Port_Value = DIO_u8_PINA;
				break;
			case DIO_u8_GROUP_B :
				*Copy_pu8_Port_Value = DIO_u8_PINB;
				break;
			case DIO_u8_GROUP_C :
				*Copy_pu8_Port_Value = DIO_u8_PINC;
				break;
			case DIO_u8_GROUP_D :
				*(Copy_pu8_Port_Value)= DIO_u8_PIND;
				break;
		}
	}else return Incorrect_Port_ID;
	return Correct_value;
}
