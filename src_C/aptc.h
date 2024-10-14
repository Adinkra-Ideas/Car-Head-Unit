/*!
 * @file aptc.h
 *
 * @name Adinkra-Ideas Piracer Throttle Control Library (APTC) 
 * 
 * The Lib is a HAL DLL for the PCA9685 Microprocessor powering
 * the Throttle Motors on the Waveshare Piracer Robot Car.
 * Written by Daniel Uyi "Adinkra-Ideas" for a Hobby Project.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef APTC_H
#define APTC_H

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

static const uint8_t SELECTED_GEAR = 0;
static const uint8_t P_GEAR = 0;
static const uint8_t N_GEAR = 1;
static const uint8_t D_GEAR = 2;
static const uint8_t R_GEAR = 3;

static const uint8_t MAX_FWD_GEAR_CLUTCH = 7;
static const uint8_t MAX_BKW_GEAR_CLUTCH = 2;

// Directions
static const uint8_t APTC_FWD = 0;
static const uint8_t APTC_BKWD = 1;

uint8_t aptc_init();
void    init_write(const uint8_t * reg);
uint8_t write_data(const uint8_t *buf, const uint8_t len);
uint8_t read_m(uint8_t *read_buf, const uint8_t len);
void 	aptc_setSpeed(const uint16_t speed, const uint8_t direction);
void    manual_gear(const uint8_t gear, const uint8_t direction);
void	p_gear_control(uint8_t * gear, uint8_t * gearClutch);
void	n_gear_control(uint8_t * gear, uint8_t * gearClutch);
void	d_gear_control(uint8_t * gear, uint8_t * gearClutch);
void	r_gear_control(uint8_t * gear, uint8_t * gearClutch);
void	accelerate_forward(uint8_t * gearClutch);
void	accelerate_backward(uint8_t * gearClutch);


#endif //APTC_H
