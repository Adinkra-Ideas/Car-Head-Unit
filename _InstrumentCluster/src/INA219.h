// just a smart way to use printf to write string into myArray
// snprintf(myArray, 19, "/dev/i2c-%d", 800);

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
#include <stdio.h> // printf for debug
#endif

uint8_t ina219_begin_txv();
uint8_t ina219_getRawBattData(uint16_t *read_buf);

