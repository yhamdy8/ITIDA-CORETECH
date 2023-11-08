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

#ifndef GROUP_CONFIG_H_
#define GROUP_CONFIG_H_
	
	/* PORT DIR and VAL default to FLOATING INPUT */
	
/* choose DIR */
#define INPUT	0	
#define OUTPUT	1
 
/* case DIR: INPUT */
#define FLOATING	0
#define PULLUP		1
/* case DIR: OUTPUT */
#define LOW		0
#define HIGH	1	

							/* DIRECTION OF GROUP A */

#define GROUPA_PIN0_DIR		OUTPUT /* ADC0 */
#define GROUPA_PIN1_DIR		OUTPUT /* ADC1 */
#define GROUPA_PIN2_DIR		OUTPUT /* ADC2 */
#define GROUPA_PIN3_DIR		OUTPUT /* ADC3 */
#define GROUPA_PIN4_DIR		OUTPUT /* ADC4 */
#define GROUPA_PIN5_DIR		OUTPUT /* ADC5 */
#define GROUPA_PIN6_DIR		OUTPUT /* ADC6 */
#define GROUPA_PIN7_DIR		OUTPUT /* ADC7 */
							/* VALUES OF GROUP A */
#define GROUPA_PIN0_INITIAL_VAL		LOW
#define GROUPA_PIN1_INITIAL_VAL		LOW
#define GROUPA_PIN2_INITIAL_VAL		LOW
#define GROUPA_PIN3_INITIAL_VAL		LOW
#define GROUPA_PIN4_INITIAL_VAL		LOW
#define GROUPA_PIN5_INITIAL_VAL		LOW
#define GROUPA_PIN6_INITIAL_VAL		LOW
#define GROUPA_PIN7_INITIAL_VAL		LOW

							/* DIRECTION OF GROUP B */

#define GROUPB_PIN0_DIR		INPUT
#define GROUPB_PIN1_DIR		INPUT
#define GROUPB_PIN2_DIR		INPUT /* INT2 */
#define GROUPB_PIN3_DIR		INPUT /* OC0  */
#define GROUPB_PIN4_DIR		INPUT
#define GROUPB_PIN5_DIR		INPUT
#define GROUPB_PIN6_DIR		INPUT
#define GROUPB_PIN7_DIR		INPUT
   	   	   	   	   	   	   	/* VALUES OF GROUP B */
#define GROUPB_PIN0_INITIAL_VAL		FLOATING
#define GROUPB_PIN1_INITIAL_VAL		FLOATING
#define GROUPB_PIN2_INITIAL_VAL		FLOATING
#define GROUPB_PIN3_INITIAL_VAL		FLOATING
#define GROUPB_PIN4_INITIAL_VAL		FLOATING
#define GROUPB_PIN5_INITIAL_VAL		FLOATING
#define GROUPB_PIN6_INITIAL_VAL		FLOATING
#define GROUPB_PIN7_INITIAL_VAL		FLOATING
  
							/* DIRECTION OF GROUP C */

#define GROUPC_PIN0_DIR		INPUT
#define GROUPC_PIN1_DIR		INPUT
#define GROUPC_PIN2_DIR		INPUT
#define GROUPC_PIN3_DIR		INPUT
#define GROUPC_PIN4_DIR		INPUT
#define GROUPC_PIN5_DIR		INPUT
#define GROUPC_PIN6_DIR		INPUT
#define GROUPC_PIN7_DIR		INPUT
							/* VALUES OF GROUP C */
#define GROUPC_PIN0_INITIAL_VAL		FLOATING
#define GROUPC_PIN1_INITIAL_VAL		FLOATING
#define GROUPC_PIN2_INITIAL_VAL		FLOATING
#define GROUPC_PIN3_INITIAL_VAL		FLOATING
#define GROUPC_PIN4_INITIAL_VAL		FLOATING
#define GROUPC_PIN5_INITIAL_VAL		FLOATING
#define GROUPC_PIN6_INITIAL_VAL		FLOATING
#define GROUPC_PIN7_INITIAL_VAL		FLOATING

							/* DIRECTION OF GROUP D */

#define GROUPD_PIN0_DIR		INPUT
#define GROUPD_PIN1_DIR		INPUT
#define GROUPD_PIN2_DIR		INPUT /* INT0 */
#define GROUPD_PIN3_DIR		INPUT /* INT1 */
#define GROUPD_PIN4_DIR		INPUT /* OC1B */
#define GROUPD_PIN5_DIR		INPUT /* OC1A */
#define GROUPD_PIN6_DIR		INPUT
#define GROUPD_PIN7_DIR		INPUT /* OC2  */
							/* VALUES OF GROUP D */
#define GROUPD_PIN0_INITIAL_VAL		FLOATING
#define GROUPD_PIN1_INITIAL_VAL		FLOATING
#define GROUPD_PIN2_INITIAL_VAL		FLOATING
#define GROUPD_PIN3_INITIAL_VAL		FLOATING
#define GROUPD_PIN4_INITIAL_VAL		FLOATING
#define GROUPD_PIN5_INITIAL_VAL		FLOATING
#define GROUPD_PIN6_INITIAL_VAL		FLOATING
#define GROUPD_PIN7_INITIAL_VAL		FLOATING
 

#endif