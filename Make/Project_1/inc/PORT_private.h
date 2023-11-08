/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/************************		AUTHOR: Youssef Hamdy			   	***********************/
/************************		LAYER:	MCAL						***********************/
/************************		DRIVER: GROUP						***********************/
/************************		VERSION: 1.00						***********************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/

#ifndef GROUP_PRIVATE_H_
#define GROUP_PRIVATE_H_

#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0

#define GROUPA_DIR	CONC(GROUPA_PIN7_DIR, GROUPA_PIN6_DIR, GROUPA_PIN5_DIR, GROUPA_PIN4_DIR, GROUPA_PIN3_DIR, GROUPA_PIN2_DIR, GROUPA_PIN1_DIR, GROUPA_PIN0_DIR)
#define GROUPB_DIR	CONC(GROUPB_PIN7_DIR, GROUPB_PIN6_DIR, GROUPB_PIN5_DIR, GROUPB_PIN4_DIR, GROUPB_PIN3_DIR, GROUPB_PIN2_DIR, GROUPB_PIN1_DIR, GROUPB_PIN0_DIR)
#define GROUPC_DIR	CONC(GROUPC_PIN7_DIR, GROUPC_PIN6_DIR, GROUPC_PIN5_DIR, GROUPC_PIN4_DIR, GROUPC_PIN3_DIR, GROUPC_PIN2_DIR, GROUPC_PIN1_DIR, GROUPC_PIN0_DIR)
#define GROUPD_DIR	CONC(GROUPD_PIN7_DIR, GROUPD_PIN6_DIR, GROUPD_PIN5_DIR, GROUPD_PIN4_DIR, GROUPD_PIN3_DIR, GROUPD_PIN2_DIR, GROUPD_PIN1_DIR, GROUPD_PIN0_DIR)
																																								 
																																								 
																																								 
#define GROUPA_INITIAL_VAL	CONC(GROUPA_PIN7_INITIAL_VAL, GROUPA_PIN6_INITIAL_VAL, GROUPA_PIN5_INITIAL_VAL, GROUPA_PIN4_INITIAL_VAL, GROUPA_PIN3_INITIAL_VAL, GROUPA_PIN2_INITIAL_VAL, GROUPA_PIN1_INITIAL_VAL, GROUPA_PIN0_INITIAL_VAL)
#define GROUPB_INITIAL_VAL	CONC(GROUPB_PIN7_INITIAL_VAL, GROUPB_PIN6_INITIAL_VAL, GROUPB_PIN5_INITIAL_VAL, GROUPB_PIN4_INITIAL_VAL, GROUPB_PIN3_INITIAL_VAL, GROUPB_PIN2_INITIAL_VAL, GROUPB_PIN1_INITIAL_VAL, GROUPB_PIN0_INITIAL_VAL)
#define GROUPC_INITIAL_VAL	CONC(GROUPC_PIN7_INITIAL_VAL, GROUPC_PIN6_INITIAL_VAL, GROUPC_PIN5_INITIAL_VAL, GROUPC_PIN4_INITIAL_VAL, GROUPC_PIN3_INITIAL_VAL, GROUPC_PIN2_INITIAL_VAL, GROUPC_PIN1_INITIAL_VAL, GROUPC_PIN0_INITIAL_VAL)
#define GROUPD_INITIAL_VAL	CONC(GROUPD_PIN7_INITIAL_VAL, GROUPD_PIN6_INITIAL_VAL, GROUPD_PIN5_INITIAL_VAL, GROUPD_PIN4_INITIAL_VAL, GROUPD_PIN3_INITIAL_VAL, GROUPD_PIN2_INITIAL_VAL, GROUPD_PIN1_INITIAL_VAL, GROUPD_PIN0_INITIAL_VAL)

#endif