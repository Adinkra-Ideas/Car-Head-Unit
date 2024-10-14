/*!
 * @file apsc.h
 *
 * @name Adinkra-Ideas Piracer Steering Servo Control HAL (APTC) 
 * 
 * The Lib is a HAL DLL for the PCA9685 Microprocessor powering
 * the Steering Servo on the Waveshare Piracer Robot Car.
 * Written by Daniel Uyi "Adinkra-Ideas" for a Hobby Project.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef APSC_H
#define APSC_H

#include <fcntl.h>      //open
#include <sys/ioctl.h>  //ioctl
#include <stdint.h>     //uint8_t

// Crossplatform, both ALL POSIX compliant systems AND Windows
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> //read, write
#endif

#if defined(DEBUG_EN) || defined(TEST_EN)
 // printf for debug
#endif
#include <stdio.h>

//#define NULL 0

// Directions
static const uint8_t APSC_LEFT = 115; 		// mapped to 0
static const uint8_t APSC_STRAIGHT = 185;	// mapped to 70
static const uint8_t APSC_RIGHT = 255;		// mapped to 140
static const uint8_t APSC_MAPPING_DIFF = 115;	// so that caller can send 0 but program convert it to 115
static const uint8_t APSC_MAX_BEFORE_MAPPING = 140;	// max value that caller can send coz it will be added to MAPPING_DIFF

uint8_t apsc_init();
void    apsc_init_write(const uint8_t * reg);
uint8_t apsc_write_data(const uint8_t *buf, const uint8_t len);
uint8_t read_m(uint8_t *read_buf, const uint8_t len);
void 	apsc_setSteering(const uint8_t direction);

#endif //APSC_H
