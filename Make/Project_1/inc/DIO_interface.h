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

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_u8_GROUP_A 	1
#define DIO_u8_GROUP_B 	2
#define DIO_u8_GROUP_C	3
#define DIO_u8_GROUP_D	4 


#define DIO_u8_PIN_LOW		0
#define DIO_u8_PIN_HIGH		1

#define DIO_u8_PORT_LOW 	0
#define DIO_u8_PORT_HIGH 	255

#define DIO_u8_PIN_0 0
#define DIO_u8_PIN_1 1
#define DIO_u8_PIN_2 2
#define DIO_u8_PIN_3 3
#define DIO_u8_PIN_4 4
#define DIO_u8_PIN_5 5
#define DIO_u8_PIN_6 6
#define DIO_u8_PIN_7 7
#define DIO_u8_PIN_1 1
#define DIO_u8_PIN_1 1

#define Correct_value			0
#define Incorrect_Direction 	1
#define Incorrect_Pin_ID		2
#define Incorrect_Port_ID		3
#define Incorrect_Value			4


u8 DIO_u8_Set_Pin_Value(u8 Copy_u8_Port_ID,u8 Copy_u8_Pin_ID,u8 Copy_u8_Pin_Value);

u8 DIO_u8_Set_Port_Value( u8 Copy_u8_Port_ID, u8 Copy_u8_Port_Value );

u8 DIO_u8_Get_Pin_Value(u8 Copy_u8_Port_ID, u8 Copy_u8_Pin_ID, u8* Copy_pu8_Pin_Value);

u8 DIO_u8_Get_Port_Value(u8 Copy_u8_Port_ID, u8* Copy_pu8_Port_Value);



#endif