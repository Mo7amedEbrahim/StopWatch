/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                HWC :     BUTTON	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "BUTTON.h"

/**
* @brief Initialize the button on the specified port and pin.
  This function sets the direction of the specified button pin to input and enables the internal pull-up resistor.
* @param Port The port number of the button.
* @param Pin The pin number of the button.
* @return ES_t Returns the error state. Returns ES_OK if the button was successfully initialized, returns ES_NOK otherwise.
*/
ES_t BUTTON_Init(u8 Port,u8 Pin){
  ES_t Local_enuErrorstate = ES_NOK;
    // Set the button pin as input
  DIO_SetPinDirection(Port, Pin, INPUT);

  // Enable the internal pull-up resistor for the button pin
  DIO_SetPinValue(Port, Pin, HIGH);

	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

/**

*@brief Get the current value of the button on the specified port and pin.
 This function returns the current value (high or low) of the specified button pin.
*@param Port The port number of the button.
*@param Pin The pin number of the button.
*@return u8 Returns the current value of the button pin. Returns high (1) if the button is pressed, returns low (0) otherwise.
*/

u8 BUTTON_u8GetValue(u8 Port,u8 Pin){
    // Read the value of the button pin
    return DIO_u8GetPinValue(Port, Pin);
}

