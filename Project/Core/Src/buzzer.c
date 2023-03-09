#include "buzzer.h"

void warning(uint8_t parameter_1, uint8_t parameter_2, uint8_t parameter_3)
{
	if(parameter_3<=parameter_1 || parameter_3>=parameter_2)
	{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
	}
}