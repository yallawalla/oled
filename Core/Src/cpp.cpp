#include "main.h"
#include "RJA_SSD1306.h"

extern "C" {
	OLED *oled;
	
	void	makeNew(I2C_HandleTypeDef *hi2c) {
		oled = new OLED();
		if(HAL_I2C_IsDeviceReady(hi2c,oled->getCAddress(),1,10) == HAL_OK) {
			oled->init(hi2c);
			oled->fill(0);
			oled->drawFullscreen();
			oled->circle(60,30,20,1);
			oled->text(30,25,"hello",1,0,2);
			oled->drawFullscreen();
			HAL_Delay(3000);
			oled->fill(0);
			oled->drawFullscreen();
		}
	}
}



