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
	enumCommandState  = CMMD_WAIT; // inicializa o controle de mensagens da uart para waiting
	tagCommandsCtxt.uiCurrentCmndSize = 0; // tamanho da mensagem = 0
	Usart_Ctrl_Init(); // inicializa a uart
}

void command_ProcessLoop(void)
{
	switch (enumCommandState) {
		case CMMD_WAIT: // se estiver em waitng
			tagCommandsCtxt.uiCurrentCmndSize = getData((uint8_t*)tagCommandsCtxt.pcBuff); // lê a mensagem da uart
			if(tagCommandsCtxt.uiCurrentCmndSize > 0 && tagCommandsCtxt.uiCurrentCmndSize < 512) // verifica se tem uma mensagem de tamanho válido
			{
				enumCommandState = CMMD_VALID; // seta o estado para válido
			}
			break;

		case CMMD_VALID: // Se o comando for valido
			if( tagCommandsCtxt.uiCurrentCmndSize >= 4 ) // Se ele tiver mais que 4 caracteres
			{
				enumCommandState = CMMD_STRACT_DATA; // mudo o estado  para estrair data
			}
			else
			{
				enumCommandState = CMMD_WAIT; // muda o estado para waiting
			}
			break;

		case CMMD_STRACT_DATA: // se o estado for estrarir data
			// CC:PAYLOAD - > esse é o padrão do protocolo

			for(i=0;i<2;i++) // pegar o comando
			{
				aux[i] =tagCommandsCtxt.pcBuff[i];
			}
			tagCommandsCtxt.ucCurrentCommand = str2int((uint8_t*)aux); // passa o comando para inteiro

			for(i=0;i<tagCommandsCtxt.uiCurrentCmndSize-2;i++) // pega o valor do payload
			{
				tagCommandsCtxt.pcBuff[i] = tagCommandsCtxt.pcBuff[i+3];
			}

			enumCommandState = CMMD_PARSE; // muda o estado para parse
			break;

		case CMMD_PARSE: // se o estado for parse
			switch (tagCommandsCtxt.ucCurrentCommand)
			{
				case CMMD_MAX_TEMP: // se o comando for de temperatura
					if(strlen(tagCommandsCtxt.pcBuff) > 0)
					{
						Display_State_setMaxValue2Temp(strtoul(tagCommandsCtxt.pcBuff, 0, 10)); // seta o valor máximo de temperatura para o progress bar da Web
						memset(tagCommandsCtxt.pcBuff,'\0',COMMANDS_MAX_BUFF_SIZE); // limpa o buffer
					}
					break;

				case CMMD_MAX_LIGHT: // se o comando for de luz
					Display_State_setMaxValue2Light(strtoul(tagCommandsCtxt.pcBuff, NULL, 10)); // seta o valor máximo em lumininosidade para o progress bar da Web
					memset(tagCommandsCtxt.pcBuff,'\0',COMMANDS_MAX_BUFF_SIZE); // limpa o buffer
					break;

				default:
					break;
			}

			enumCommandState = CMMD_WAIT; // Muda o estado para wait
			break;

		default:
			break;
	}
}

