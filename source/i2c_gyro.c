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
    /* Enter an infinite loop, just incrementing a counter. */

    /* TODO: Initialize master I2C module with default config */
    i2c_master_config_t MasterConfig;
    I2C_MasterGetDefaultConfig(&MasterConfig);

    I2C_MasterInit(BOARD_ACCEL_I2C_BASEADDR, &MasterConfig, 12000000U);

    I2C_Enable(BOARD_ACCEL_I2C_BASEADDR, true);

    PRINTF("%d\r\n", I2C_MasterStart(BOARD_ACCEL_I2C_BASEADDR, 0x1DU, kI2C_Read));

    uint8_t rxBuff[7];

    PRINTF("%d\r\n", I2C_MasterReadBlocking(BOARD_ACCEL_I2C_BASEADDR, rxBuff, 1U, kI2C_TransferRepeatedStartFlag));

    while(1) {
        i++ ;

        PRINTF("%d, %d, %d, %d, %d, %d, %d\r\n", rxBuff[0], rxBuff[1], rxBuff[2], rxBuff[3], rxBuff[4], rxBuff[5], rxBuff[6]);
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
