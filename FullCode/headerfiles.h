#include <avr/io.h>
#include "registerFunctions.h"
#include <util/delay.h>
#include "LCD_16x2_H_file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "USART_Interrupt.h"
#include "ADC.h"
#include "Track.h"
#include <avr/io.h>
#include <inttypes.h>
#include "MPU6050_res_define.h"
#include "I2C_Master_H_file.h"
#include "mpu6050.h"
#include "gsm.h"
//pin definitions
#define flame 4
#define led 0
#define buzzer 7
#define alcohol 6