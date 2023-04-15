/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			            ***************************/
/*************                HWC :     7Segment	              ***************************/
/*************                VERSION : 1.00		            ***************************/
/****************************************************************************************/
/****************************************************************************************/

#include "7SEG.h"
#if CONFIG == COMMON_CATHODE
static u8 SevenSegCath[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
#elif CONFIG == COMMON_ANODE
static u8 SevenSegAnode[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
#endif
ES_t _7SEG_Init(u8 Port){
    ES_t Local_enuErrorstate = ES_NOK;
    DIO_SetPortDirection(Port,0x7F);
    Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t _7SEG_Display(u8 Port, u8 Number){
    ES_t Local_enuErrorstate = ES_NOK;
    if(Number <= 9 && Number >=0){
    #if CONFIG == COMMON_CATHODE 
        DIO_SetPortValue(Port,SevenSegCath[Number]);
    #elif CONFIG == COMMON_ANODE
        DIO_SetPortValue(Port,SevenSegAnode[Number]);
    #endif
    Local_enuErrorstate = ES_OK;
    }
    else{
        Local_enuErrorstate = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorstate;
}
