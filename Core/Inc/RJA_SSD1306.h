/*
 * OLED_ClassV1.h
 *
 *  Created on: Nov 22, 2018
 *      Author: ASUS
 */

//Includes
#include "stm32f4xx_hal.h"  //Change this based on your STM32 Series
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef OLED_CLASSV1_H_
#define OLED_CLASSV1_H_

class OLED
{
private:
	static const int width = 128;
	static const int height = 64;

	static const uint8_t CAddress;
	static const uint8_t DAddress;
	static const bool _cp437;

	I2C_HandleTypeDef *hi2cI;
	static const unsigned char font[];


	#define swap(a, b) { int16_t t = a; a = b; b = t; }
	#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

public:
	bool frame[width][height];	//kept public because of big size, check for alternative
	OLED();
	virtual ~OLED();
	void init(I2C_HandleTypeDef *hi2c1);
	void drawFullscreen();	//I2C_HandleTypeDef *hi2c1
	void drawFullscreen(bool newFrame[128][64]);	//I2C_HandleTypeDef *hi2c1
	void setContrast(uint8_t contrast);
	void inverseDisplay(bool isInverse);
	uint8_t getCAddress();
	uint8_t getDAddress();
	void pixel(int x0, int y0, bool colour, bool locked = 0);	//if locked won't plot outside of region
	void pixels3V(int  x0, int y0, bool colour, bool locked = 0);
	void pixels3H(int x0, int y0, bool colour, bool locked = 0);
	void line(int x0, int y0, int x1, int y1, bool colour, bool locked = 0);	//0 & 1 in last para. can be ambigiuous	//decide on exact int type
	void line(int x0, int y0, int x1, int y1, bool colour, int lineWidth);	//might just combine w/ the above
	void fastHLine(int x0, int y0, int w, bool colour);
	void fastVLine(int x0, int y0, int h, bool colour);
	void triangle(int x0, int y0, int x1, int y1, int x2, int y2, bool colour);
	void triangle(int x0, int y0, int x1, int y1, int x2, int y2, bool colour, int lineWidth);
	void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool colour);
	void circle(int x0, int y0, int r, bool colour);
	void circle(int x0, int y0, int r, bool colour, int lineWidth);
	void thiccCircle(int x0, int y0, int r, bool colour);
	void fillCircle(int x0, int y0, int r, bool colour);
	void fillCircleHelper(int x0, int y0, int r, int cornername, int delta, bool colour);	//was static
	void rectangle(int x0, int y0, int x1, int y1, bool colour);	//works on any quad polygon really
	void rectangle(int x0, int y0, int x1, int y1, bool colour, int lineWidth);	//works on any quad polygon really
	void fillRect(int x0, int y0, int x1, int y1, bool colour);		//basically same as other fill definition
	void connectPoints(int X[], int Y[], int pointsNum, bool colour);
	void connectPoints(int X[], int Y[], int pointsNum, bool colour, int lineWidth);
	void polygon(int X[], int Y[], int pointsNum, bool colour);
	void polygon(int X[], int Y[], int pointsNum, bool colour, int lineWidth);
	void fill(bool colour);	//fill full screen with one colour
	void fill(int x0, int y0, int x1, int y1, bool colour);	//fill defined region with one colour; same as drawing a filled rectangle; add error handling
	void invert();	//same as inverseDisplay(), but done on frame array so probably less efficient
	void invert(int x0, int y0, int x1, int y1);	//a specific part of the screen
	void character(int x, int y, unsigned char c, bool colour, bool bg, int size);
	void text(int x, int y, string s, bool colour, bool bg, int size);
};

#endif /* OLED_CLASSV1_H_ */
