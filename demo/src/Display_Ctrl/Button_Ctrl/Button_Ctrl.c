/*
 * Button_Ctrl.c
 *
 *  Created on: 05/04/2018
 *      Author: jpone
 */

#include "Button_Ctrl.h"
#include "../../PinDefinition.h"

/*********************************************************
    private constants.
*********************************************************/


/*********************************************************
    private types.
*********************************************************/


/*********************************************************
    private variable.
*********************************************************/


/*********************************************************
    private functions prototypes.
*********************************************************/
void Button_Ctrl_Init_Hw(void);

/*********************************************************
    private functions.
*********************************************************/
void Button_Ctrl_Init_Hw(void)
{
	GPIO_SetDir(PIN_DEFINITION_BUTTON_PORT, 1<<PIN_DEFINITION_BUTTON_BIT_VALUE, PIN_DEFINITION_BUTTON_DIR);

	NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler(void)
{

	Display_State_IncrementState();

}

/*********************************************************
    public functions.
*********************************************************/
void Button_Ctrl_Init(void)
{
	Button_Ctrl_Init_Hw();
}


Bool Button_Ctrl_GetValue(void)
{
	uint32_t port = GPIO_ReadValue((uint8_t)PIN_DEFINITION_BUTTON_PORT);
	uint8_t result = ( (port>>PIN_DEFINITION_BUTTON_BIT_VALUE) & 0x01);
	return result;
}
