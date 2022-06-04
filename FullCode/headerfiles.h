#include <avr/io.h>
#include "registerFunctions.h"
#include <util/delay.h>
#include "LCD.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include <avr/io.h>
#include <inttypes.h>
#include "MPU6050_res_define.h"
#include "I2C_Master_H_file.h"
#include "mpu6050.h"
#include "pwm.h"
#include "usart.h"
#include "Track.h"
#include "gsmmessage.h"

//pin definitions
#define flame 4
#define led 6
#define buzzer 7
#define alcohol 5
#define musicSystem 5
#define irsensor 6

//function prototypes
void ringAlarm();
void stopAlarm();
void onHazardLight();
void playRadio();
void PWM_init();
void offHazardLight();
int isDriverSleepingIR();
void sendLocation();

