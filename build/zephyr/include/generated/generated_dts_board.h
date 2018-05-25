/**************************************************
 * Generated include file for bbc,microbit
 *               DO NOT MODIFY
 */

#ifndef _DEVICE_TREE_BOARD_H
#define _DEVICE_TREE_BOARD_H

/* flash-controller@4001E000 */
#define NRF_NRF51_FLASH_CONTROLLER_4001E000_BASE_ADDRESS_0	0x4001e000
#define NRF_NRF51_FLASH_CONTROLLER_4001E000_LABEL		"NRF_FLASH_DRV_NAME"
#define NRF_NRF51_FLASH_CONTROLLER_4001E000_SIZE_0		1304
#define NRF_NRF51_FLASH_CONTROLLER_4001E000_BASE_ADDRESS	NRF_NRF51_FLASH_CONTROLLER_4001E000_BASE_ADDRESS_0
#define NRF_NRF51_FLASH_CONTROLLER_4001E000_SIZE		NRF_NRF51_FLASH_CONTROLLER_4001E000_SIZE_0

/* flash@0 */
#define CONFIG_FLASH_BASE_ADDRESS_0		0x0
#define CONFIG_FLASH_LOAD_OFFSET		0
#define CONFIG_FLASH_LOAD_SIZE			0
#define CONFIG_FLASH_SIZE_0			256
#define FLASH_LABEL				"NRF_FLASH"
#define FLASH_NRF_FLASH_LABEL			"NRF_FLASH"
#define FLASH_NRF_FLASH_WRITE_BLOCK_SIZE	4
#define FLASH_WRITE_BLOCK_SIZE			4
#define CONFIG_FLASH_BASE_ADDRESS		CONFIG_FLASH_BASE_ADDRESS_0
#define CONFIG_FLASH_SIZE			CONFIG_FLASH_SIZE_0

/* memory@20000000 */
#define CONFIG_SRAM_BASE_ADDRESS_0	0x20000000
#define CONFIG_SRAM_SIZE_0		16
#define CONFIG_SRAM_BASE_ADDRESS	CONFIG_SRAM_BASE_ADDRESS_0
#define CONFIG_SRAM_SIZE		CONFIG_SRAM_SIZE_0

/* i2c@40003000 */
#define NORDIC_NRF5_I2C_40003000_BASE_ADDRESS_0		0x40003000
#define NORDIC_NRF5_I2C_40003000_CLOCK_FREQUENCY	400000
#define NORDIC_NRF5_I2C_40003000_IRQ_0			3
#define NORDIC_NRF5_I2C_40003000_IRQ_0_PRIORITY		1
#define NORDIC_NRF5_I2C_40003000_LABEL			"I2C_0"
#define NORDIC_NRF5_I2C_40003000_SIZE_0			4096
#define NORDIC_NRF5_I2C_40003000_BASE_ADDRESS		NORDIC_NRF5_I2C_40003000_BASE_ADDRESS_0
#define NORDIC_NRF5_I2C_40003000_SIZE			NORDIC_NRF5_I2C_40003000_SIZE_0

/* interrupt-controller@e000e100 */
#define ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS		2
#define ARM_V6M_NVIC_E000E100_BASE_ADDRESS_0			0xe000e100
#define ARM_V6M_NVIC_E000E100_SIZE_0				3072
#define ARM_V6M_NVIC_E000E100_BASE_ADDRESS			ARM_V6M_NVIC_E000E100_BASE_ADDRESS_0
#define ARM_V6M_NVIC_E000E100_SIZE				ARM_V6M_NVIC_E000E100_SIZE_0

/* uart@40002000 */
#define CONFIG_UART_CONSOLE_ON_DEV_NAME			"UART_0"
#define NORDIC_NRF_UART_40002000_BASE_ADDRESS_0		0x40002000
#define NORDIC_NRF_UART_40002000_CURRENT_SPEED		115200
#define NORDIC_NRF_UART_40002000_IRQ_0			2
#define NORDIC_NRF_UART_40002000_IRQ_0_PRIORITY		1
#define NORDIC_NRF_UART_40002000_LABEL			"UART_0"
#define NORDIC_NRF_UART_40002000_SIZE_0			4096
#define NORDIC_NRF_UART_40002000_BASE_ADDRESS		NORDIC_NRF_UART_40002000_BASE_ADDRESS_0
#define NORDIC_NRF_UART_40002000_SIZE			NORDIC_NRF_UART_40002000_SIZE_0


/* Following definitions fixup the generated include */
/* SoC level DTS fixup file */

#define CONFIG_NUM_IRQ_PRIO_BITS	ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#define CONFIG_UART_NRF5_IRQ_PRI	NORDIC_NRF_UART_40002000_IRQ_0_PRIORITY
#define CONFIG_UART_NRF5_BAUD_RATE	NORDIC_NRF_UART_40002000_CURRENT_SPEED
#define CONFIG_UART_NRF5_NAME		NORDIC_NRF_UART_40002000_LABEL

#define FLASH_DEV_NAME			NRF_NRF51_FLASH_CONTROLLER_4001E000_LABEL

#define CONFIG_I2C_0_BASE_ADDR		NORDIC_NRF5_I2C_40003000_BASE_ADDRESS_0
#define CONFIG_I2C_0_NAME		NORDIC_NRF5_I2C_40003000_LABEL
#define CONFIG_I2C_0_BITRATE		NORDIC_NRF5_I2C_40003000_CLOCK_FREQUENCY
#define CONFIG_I2C_0_IRQ_PRI		NORDIC_NRF5_I2C_40003000_IRQ_0_PRIORITY
#define CONFIG_I2C_0_IRQ		NORDIC_NRF5_I2C_40003000_IRQ_0

#define CONFIG_I2C_1_BASE_ADDR		NORDIC_NRF5_I2C_40004000_BASE_ADDRESS_0
#define CONFIG_I2C_1_NAME		NORDIC_NRF5_I2C_40004000_LABEL
#define CONFIG_I2C_1_BITRATE		NORDIC_NRF5_I2C_40004000_CLOCK_FREQUENCY
#define CONFIG_I2C_1_IRQ_PRI		NORDIC_NRF5_I2C_40004000_IRQ_0_PRIORITY
#define CONFIG_I2C_1_IRQ		NORDIC_NRF5_I2C_40004000_IRQ_0

/* End of SoC Level DTS fixup file */

#endif