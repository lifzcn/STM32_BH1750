#include "steeringengine.h"

void openCurtain()
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2500);
}

void closeCurtain()
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
}
