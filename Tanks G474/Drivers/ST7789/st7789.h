#ifndef __ST7789_H
#define __ST7789_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fonts.h"
#include "color.h"
#include "main.h"
#include "tim.h"
/* choose a Hardware SPI port to use. */
#define ST7789_SPI_PORT hspi1
extern SPI_HandleTypeDef ST7789_SPI_PORT;
/* choose a Hardware PWM to use.*/
#define ST7789_PWM_TIM htim1
extern TIM_HandleTypeDef ST7789_PWM_TIM;
#define ST7789_PWM_CH TIM_CHANNEL_1
#define CHxN	//Enable if using a complementary PWM (CHxN)

/* choose whether use DMA or not */
#define USE_DMA

#define CFG_NO_CS

/* If you want to drive backlight choose if you want PWM or Binary(ON/OFF) control */
#define BL_PWM	//backlite BL_PWM or BL_BIN

/* If u need CS control, comment below*/
//#define CFG_NO_CS
/* Pin connection*/
#define ST7789_RST_PORT LCD_RES_GPIO_Port
#define ST7789_RST_PIN  LCD_RES_Pin

#define ST7789_DC_PORT  LCD__DC_GPIO_Port
#define ST7789_DC_PIN   LCD__DC_Pin

#ifndef CFG_NO_CS
#define ST7789_CS_PORT  GPIOD
#define ST7789_CS_PIN   GPIO_PIN_6
#endif

#define WINVERT(data)((data >> 8) | (data << 8)) //Invert a color (word invert)

/* If u need Backlight control, uncomment below */
//#define BLK_PORT
//#define BLK_PIN
/*
 * Comment one to use another.
 * 3 parameters can be choosed
 * 135x240(0.96 inch) & 240x240(1.3inch) & 170x320(1.9inch)
 * X_SHIFT & Y_SHIFT are used to adapt different display's resolution
 */

/* Choose a type you are using */
//#define USING_135X240
#define USING_240X240
//#define USING_240X320
//#define USING_170X320

/* Choose a display rotation you want to use: (0-3) */
#define ST7789_ROTATION 1

#ifdef USING_135X240

    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 53
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 52
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 52
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 53
    #endif

#endif

#ifdef USING_240X240

#define ST7789_WIDTH 240
#define ST7789_HEIGHT 240

#if ST7789_ROTATION == 0
			#define X_SHIFT 0
			#define Y_SHIFT 80
		#elif ST7789_ROTATION == 1
#define X_SHIFT 80
#define Y_SHIFT 0
#elif ST7789_ROTATION == 2
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 3
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#endif

#endif

#ifdef USING_240X320

#if ST7789_ROTATION == 0
			#define ST7789_WIDTH 240
			#define ST7789_HEIGHT 320
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 1
#define ST7789_WIDTH 320
#define ST7789_HEIGHT 240
#define X_SHIFT 0
#define Y_SHIFT 0
#elif ST7789_ROTATION == 2
			#define ST7789_WIDTH 240
			#define ST7789_HEIGHT 320
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 3
			#define ST7789_WIDTH 320
			#define ST7789_HEIGHT 240
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#endif

#endif

#ifdef USING_170X320

	#if ST7789_ROTATION == 0
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif

#endif

/* Control Registers and constant codes */
#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

/**
 * Memory Data Access Control Register (0x36H)
 * MAP:     D7  D6  D5  D4  D3  D2  D1  D0
 * param:   MY  MX  MV  ML  RGB MH  -   -
 *
 */

/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80
/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40
/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20
/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Advanced options */
#define ST7789_COLOR_MODE_16bit 0x55    //  RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    //  RGB666 (18bit)

/* Basic operations */
#define ST7789_RST_Clr() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_RESET)
#define ST7789_RST_Set() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_SET)

#define ST7789_DC_Clr() HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_RESET)
#define ST7789_DC_Set() HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_SET)
#ifndef CFG_NO_CS
#define ST7789_Select() HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_RESET)
#define ST7789_UnSelect() HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_SET)
#else
#define ST7789_Select() asm("nop")
#define ST7789_UnSelect() asm("nop")
#endif

#define ABS(x) ((x) > 0 ? (x) : -(x))

/* Basic functions. */
void ST7789_Init(void);
void ST7789_SetRotation(uint8_t m);
void ST7789_Fill_Color(uint16_t color);
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd,
    uint16_t color);
void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);

#if defined(BL_PWM) || defined(BL_BIN)
void ST7789_SetBacklight(uint8_t);
#endif

/* Graphical functions. */
void ST7789_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
    uint16_t color);
void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
    uint16_t color);
void ST7789_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
    const uint16_t *data);
void ST7789_DrawImageComp(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
    const uint16_t *data, uint16_t num, uint16_t bcolor,
    uint16_t isTransparent);	//draw a compressed image (RLE)
void ST7789_InvertColors(uint8_t invert);

/* Text functions. */
void ST7789_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font,
    uint16_t color, uint16_t bgcolor);
void ST7789_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font,
    uint16_t color, uint16_t bgcolor);

/* Extented Graphical functions. */
void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
    uint16_t color);
void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
    uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2,
    uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/* Command functions */
void ST7789_TearEffect(uint8_t tear);

/* Utils functions */
void wmemset(uint16_t *destination, uint16_t data, size_t size);

/* Simple test function. */
void ST7789_Test(void);

#ifndef ST7789_ROTATION
    #error You should at least choose a display rotation!
#endif

#ifdef __cplusplus
}
#endif

#endif
