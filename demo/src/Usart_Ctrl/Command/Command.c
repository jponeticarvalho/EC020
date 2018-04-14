/*
 * Command.c
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#include "Command.h"

/*********************************************************
    private constants.
*********************************************************/
#define COMMANDS_MAX_BUFF_SIZE 120
#define RESPONSE_MAX_BUFF_SIZE 120

/*********************************************************
    private types.
*********************************************************/
typedef enum enum_CommandState
{
	CMMD_WAIT = 0,
	CMMD_VALID,
	CMMD_STRACT_DATA,
	CMMD_PARSE
} tenum_CommandState;

typedef enum enum_Commands
{
	CMMD_MAX_TEMP = 1,
	CMMD_MAX_LIGHT
} tenum_Commands;

/*********************************************************
    private variable.
*********************************************************/
static tenum_CommandState enumCommandState;

static struct tag_CommandsCtxt
{
	uint8_t  			ucCurrentCommand;
	uint16_t 			uiCurrentCmndSize;
	int 			iCurrentRespLen;
	char* 			pcCurrentData;
	char 			pcBuff[COMMANDS_MAX_BUFF_SIZE];
	char 			pcRespBuff[RESPONSE_MAX_BUFF_SIZE];
}tagCommandsCtxt;

static char aux[3];
static int i = 0;

/*********************************************************
    private functions prototypes.
*********************************************************/
uint16_t getData(uint8_t *pucData);
uint8_t str2int(uint8_t *pucData);


/*********************************************************
    private functions.
*********************************************************/
uint16_t getData(uint8_t *pucData)
{

	uint16_t uiDataSize;

	uiDataSize = Usart_Ctrl_getData(pucData);

	return uiDataSize;
}

uint8_t str2int(uint8_t *pucData)
{
	uint8_t ucResponse = 0;

	ucResponse += (pucData[0]-'0')*10;
	ucResponse += (pucData[1]-'0')*1;

	return ucResponse;
}

/*********************************************************
    public functions.
*********************************************************/
void command_Init(void)
{
	enumCommandState  = CMMD_WAIT;
	tagCommandsCtxt.uiCurrentCmndSize = 0;
	Usart_Ctrl_Init();
}

void command_ProcessLoop(void)
{
	switch (enumCommandState) {
		case CMMD_WAIT:
			tagCommandsCtxt.uiCurrentCmndSize = getData((uint8_t*)tagCommandsCtxt.pcBuff);
			if(tagCommandsCtxt.uiCurrentCmndSize > 0 && tagCommandsCtxt.uiCurrentCmndSize < 512)
			{
				enumCommandState = CMMD_VALID;
			}
			break;

		case CMMD_VALID:
			if( tagCommandsCtxt.uiCurrentCmndSize >= 4 )
			{
				enumCommandState = CMMD_STRACT_DATA;
			}
			else
			{
				enumCommandState = CMMD_WAIT;
			}
			break;

		case CMMD_STRACT_DATA:
			for(i=0;i<2;i++)
			{
				aux[i] =tagCommandsCtxt.pcBuff[i];
			}
			tagCommandsCtxt.ucCurrentCommand = str2int((uint8_t*)aux);

			for(i=0;i<tagCommandsCtxt.uiCurrentCmndSize-2;i++)
			{
				tagCommandsCtxt.pcBuff[i] = tagCommandsCtxt.pcBuff[i+3];
			}

			enumCommandState = CMMD_PARSE;
			break;

		case CMMD_PARSE:
			switch (tagCommandsCtxt.ucCurrentCommand)
			{
				case CMMD_MAX_TEMP:
					if(strlen(tagCommandsCtxt.pcBuff) > 0)
					{
						Display_State_setMaxValue2Temp(strtoul(tagCommandsCtxt.pcBuff, 0, 10));
						memset(tagCommandsCtxt.pcBuff,'\0',COMMANDS_MAX_BUFF_SIZE);
					}
					break;

				case CMMD_MAX_LIGHT:
					Display_State_setMaxValue2Light(strtoul(tagCommandsCtxt.pcBuff, NULL, 10));
					break;

				default:
					break;
			}

			enumCommandState = CMMD_WAIT;
			break;

		default:
			break;
	}
}

