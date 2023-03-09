#include "bh1750.h"
#include "i2c.h"

#define bh1750_i2c hi2c2

static	uint8_t		BH1750_Send_Cmd(BH1750_MODE cmd);
static 	uint8_t 	BH1750_Read_Dat(uint8_t* dat);
static 	uint16_t	BH1750_Dat_To_Lux(uint8_t* dat);

static uint8_t	BH1750_Send_Cmd(BH1750_MODE cmd)
{
	return HAL_I2C_Master_Transmit(&bh1750_i2c, BH1750_ADDR_WRITE, (uint8_t*)&cmd, 1, 0xFFFF);
}

static uint8_t BH1750_Read_Dat(uint8_t* dat)
{
	return HAL_I2C_Master_Receive(&bh1750_i2c, BH1750_ADDR_READ, dat, 2, 0xFFFF);
}

static uint16_t BH1750_Dat_To_Lux(uint8_t* dat)
{
	uint16_t lux = 0;
	lux = dat[0];
	lux <<= 8;
	lux |= dat[1];
	lux = (int)(lux/1.2);
	return lux;
}

uint16_t Get_BH1750_Value(void)
{
	uint8_t dat[2] = {0};
	uint16_t lux;
	if(HAL_OK != BH1750_Send_Cmd(ONCE_H_MODE))
	{
		return 0;
	}
	HAL_Delay(120);
	if(HAL_OK != BH1750_Read_Dat(dat))
	{
		return 0;
	}
	lux = BH1750_Dat_To_Lux(dat);
	return lux;
}
