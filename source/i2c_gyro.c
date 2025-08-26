/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    i2c_gyro.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

#define ACCEL_I2C_ADDR 0x1DU
#define DATA_REG_ADDR 0x0DU


int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;

    uint8_t buffer[7];
    memset((void *)buffer, 0, sizeof(buffer));
    uint8_t txBuff =  0x0DU;

    /* Initialize master I2C module with default config */
    i2c_master_config_t MasterConfig;
    I2C_MasterGetDefaultConfig(&MasterConfig);

    I2C_MasterInit(BOARD_ACCEL_I2C_BASEADDR, &MasterConfig, 12000000U);

    I2C_Enable(BOARD_ACCEL_I2C_BASEADDR, true);

    /* Initialize the master by sending a start bit, device address, write bit
       	 */
    PRINTF("%d\r\n", I2C_MasterStart(BOARD_ACCEL_I2C_BASEADDR, 0x1DU, kI2C_Write));

    /* Write the address for the register we want to read */
    I2C_MasterWriteBlocking(BOARD_ACCEL_I2C_BASEADDR, &txBuff, 1U, kI2C_TransferRepeatedStartFlag);

    PRINTF("%d\r\n", I2C_MasterStart(BOARD_ACCEL_I2C_BASEADDR, 0x1DU, kI2C_Read));

    PRINTF("%d\r\n", I2C_MasterReadBlocking(BOARD_ACCEL_I2C_BASEADDR, buffer, 1U, kI2C_TransferDefaultFlag));
    PRINTF("%d, %d, %d, %d, %d, %d, %d\r\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
    while(1) {
        i++ ;

//        PRINTF("%d\r\n", I2C_MasterStart(BOARD_ACCEL_I2C_BASEADDR, 0x1DU, kI2C_Write));
//        PRINTF("%d, %d, %d, %d, %d, %d, %d\r\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */

        for (int x = 0; x < 200; x++) {
        	__asm volatile ("nop");
        }
    }
    return 0 ;
}
