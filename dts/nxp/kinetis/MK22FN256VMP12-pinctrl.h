/*
 * NOTE: Autogenerated file by gen_soc_headers.py
 * for MK22FN256VMP12/signal_configuration.xml
 *
 * Copyright 2024, NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ZEPHYR_DTS_BINDING_MK22FN256VMP12_
#define _ZEPHYR_DTS_BINDING_MK22FN256VMP12_

#define KINETIS_MUX(port, pin, mux)		\
	(((((port) - 'A') & 0xF) << 28) |	\
	(((pin) & 0x3F) << 22) |		\
	(((mux) & 0x7) << 8))

#define PTA0 KINETIS_MUX('A',0,1) /* PTA_0 */
#define UART0_CTS_b_PTA0 KINETIS_MUX('A',0,2) /* PTA_0 */
#define FTM0_CH5_PTA0 KINETIS_MUX('A',0,3) /* PTA_0 */
#define JTAG_TCLK_PTA0 KINETIS_MUX('A',0,7) /* PTA_0 */
#define PTA1 KINETIS_MUX('A',1,1) /* PTA_1 */
#define UART0_RX_PTA1 KINETIS_MUX('A',1,2) /* PTA_1 */
#define FTM0_CH6_PTA1 KINETIS_MUX('A',1,3) /* PTA_1 */
#define JTAG_TDI_PTA1 KINETIS_MUX('A',1,7) /* PTA_1 */
#define PTA2 KINETIS_MUX('A',2,1) /* PTA_2 */
#define UART0_TX_PTA2 KINETIS_MUX('A',2,2) /* PTA_2 */
#define FTM0_CH7_PTA2 KINETIS_MUX('A',2,3) /* PTA_2 */
#define JTAG_TDO_PTA2 KINETIS_MUX('A',2,7) /* PTA_2 */
#define TRACE_SWO_PTA2 KINETIS_MUX('A',2,7) /* PTA_2 */
#define PTA3 KINETIS_MUX('A',3,1) /* PTA_3 */
#define UART0_RTS_b_PTA3 KINETIS_MUX('A',3,2) /* PTA_3 */
#define FTM0_CH0_PTA3 KINETIS_MUX('A',3,3) /* PTA_3 */
#define JTAG_TMS_PTA3 KINETIS_MUX('A',3,7) /* PTA_3 */
#define PTA4 KINETIS_MUX('A',4,1) /* PTA_4 */
#define LLWU_P3_PTA4 KINETIS_MUX('A',4,1) /* PTA_4 */
#define FTM0_CH1_PTA4 KINETIS_MUX('A',4,3) /* PTA_4 */
#define NMI_b_PTA4 KINETIS_MUX('A',4,7) /* PTA_4 */
#define PTA5 KINETIS_MUX('A',5,1) /* PTA_5 */
#define USB_CLKIN_PTA5 KINETIS_MUX('A',5,2) /* PTA_5 */
#define FTM0_CH2_PTA5 KINETIS_MUX('A',5,3) /* PTA_5 */
#define I2S0_TX_BCLK_PTA5 KINETIS_MUX('A',5,6) /* PTA_5 */
#define JTAG_TRST_b_PTA5 KINETIS_MUX('A',5,7) /* PTA_5 */
#define PTA12 KINETIS_MUX('A',12,1) /* PTA_12 */
#define FTM1_CH0_PTA12 KINETIS_MUX('A',12,3) /* PTA_12 */
#define I2S0_TXD0_PTA12 KINETIS_MUX('A',12,6) /* PTA_12 */
#define FTM1_QD_PHA_PTA12 KINETIS_MUX('A',12,7) /* PTA_12 */
#define LLWU_P4_PTA13 KINETIS_MUX('A',13,1) /* PTA_13 */
#define PTA13 KINETIS_MUX('A',13,1) /* PTA_13 */
#define FTM1_CH1_PTA13 KINETIS_MUX('A',13,3) /* PTA_13 */
#define I2S0_TX_FS_PTA13 KINETIS_MUX('A',13,6) /* PTA_13 */
#define FTM1_QD_PHB_PTA13 KINETIS_MUX('A',13,7) /* PTA_13 */
#define EXTAL0_PTA18 KINETIS_MUX('A',18,0) /* PTA_18 */
#define PTA18 KINETIS_MUX('A',18,1) /* PTA_18 */
#define FTM0_FLT2_PTA18 KINETIS_MUX('A',18,3) /* PTA_18 */
#define FTM_CLKIN0_PTA18 KINETIS_MUX('A',18,4) /* PTA_18 */
#define XTAL0_PTA19 KINETIS_MUX('A',19,0) /* PTA_19 */
#define PTA19 KINETIS_MUX('A',19,1) /* PTA_19 */
#define FTM1_FLT0_PTA19 KINETIS_MUX('A',19,3) /* PTA_19 */
#define FTM_CLKIN1_PTA19 KINETIS_MUX('A',19,4) /* PTA_19 */
#define LPTMR0_ALT1_PTA19 KINETIS_MUX('A',19,6) /* PTA_19 */
#define ADC1_SE8_PTB0 KINETIS_MUX('B',0,0) /* PTB_0 */
#define ADC0_SE8_PTB0 KINETIS_MUX('B',0,0) /* PTB_0 */
#define LLWU_P5_PTB0 KINETIS_MUX('B',0,1) /* PTB_0 */
#define PTB0 KINETIS_MUX('B',0,1) /* PTB_0 */
#define I2C0_SCL_PTB0 KINETIS_MUX('B',0,2) /* PTB_0 */
#define FTM1_CH0_PTB0 KINETIS_MUX('B',0,3) /* PTB_0 */
#define FTM1_QD_PHA_PTB0 KINETIS_MUX('B',0,6) /* PTB_0 */
#define ADC0_SE9_PTB1 KINETIS_MUX('B',1,0) /* PTB_1 */
#define ADC1_SE9_PTB1 KINETIS_MUX('B',1,0) /* PTB_1 */
#define PTB1 KINETIS_MUX('B',1,1) /* PTB_1 */
#define I2C0_SDA_PTB1 KINETIS_MUX('B',1,2) /* PTB_1 */
#define FTM1_CH1_PTB1 KINETIS_MUX('B',1,3) /* PTB_1 */
#define FTM1_QD_PHB_PTB1 KINETIS_MUX('B',1,6) /* PTB_1 */
#define ADC0_SE12_PTB2 KINETIS_MUX('B',2,0) /* PTB_2 */
#define PTB2 KINETIS_MUX('B',2,1) /* PTB_2 */
#define I2C0_SCL_PTB2 KINETIS_MUX('B',2,2) /* PTB_2 */
#define UART0_RTS_b_PTB2 KINETIS_MUX('B',2,3) /* PTB_2 */
#define FTM0_FLT3_PTB2 KINETIS_MUX('B',2,6) /* PTB_2 */
#define ADC0_SE13_PTB3 KINETIS_MUX('B',3,0) /* PTB_3 */
#define PTB3 KINETIS_MUX('B',3,1) /* PTB_3 */
#define I2C0_SDA_PTB3 KINETIS_MUX('B',3,2) /* PTB_3 */
#define UART0_CTS_b_PTB3 KINETIS_MUX('B',3,3) /* PTB_3 */
#define FTM0_FLT0_PTB3 KINETIS_MUX('B',3,6) /* PTB_3 */
#define PTB16 KINETIS_MUX('B',16,1) /* PTB_16 */
#define SPI1_SOUT_PTB16 KINETIS_MUX('B',16,2) /* PTB_16 */
#define UART0_RX_PTB16 KINETIS_MUX('B',16,3) /* PTB_16 */
#define FTM_CLKIN0_PTB16 KINETIS_MUX('B',16,4) /* PTB_16 */
#define EWM_IN_PTB16 KINETIS_MUX('B',16,6) /* PTB_16 */
#define PTB17 KINETIS_MUX('B',17,1) /* PTB_17 */
#define SPI1_SIN_PTB17 KINETIS_MUX('B',17,2) /* PTB_17 */
#define UART0_TX_PTB17 KINETIS_MUX('B',17,3) /* PTB_17 */
#define FTM_CLKIN1_PTB17 KINETIS_MUX('B',17,4) /* PTB_17 */
#define EWM_OUT_b_PTB17 KINETIS_MUX('B',17,6) /* PTB_17 */
#define PTB18 KINETIS_MUX('B',18,1) /* PTB_18 */
#define FTM2_CH0_PTB18 KINETIS_MUX('B',18,3) /* PTB_18 */
#define I2S0_TX_BCLK_PTB18 KINETIS_MUX('B',18,4) /* PTB_18 */
#define FTM2_QD_PHA_PTB18 KINETIS_MUX('B',18,6) /* PTB_18 */
#define PTB19 KINETIS_MUX('B',19,1) /* PTB_19 */
#define FTM2_CH1_PTB19 KINETIS_MUX('B',19,3) /* PTB_19 */
#define I2S0_TX_FS_PTB19 KINETIS_MUX('B',19,4) /* PTB_19 */
#define FTM2_QD_PHB_PTB19 KINETIS_MUX('B',19,6) /* PTB_19 */
#define ADC0_SE14_PTC0 KINETIS_MUX('C',0,0) /* PTC_0 */
#define PTC0 KINETIS_MUX('C',0,1) /* PTC_0 */
#define SPI0_PCS4_PTC0 KINETIS_MUX('C',0,2) /* PTC_0 */
#define PDB0_EXTRG_PTC0 KINETIS_MUX('C',0,3) /* PTC_0 */
#define USB_SOF_OUT_PTC0 KINETIS_MUX('C',0,4) /* PTC_0 */
#define ADC0_SE15_PTC1 KINETIS_MUX('C',1,0) /* PTC_1 */
#define LLWU_P6_PTC1 KINETIS_MUX('C',1,1) /* PTC_1 */
#define PTC1 KINETIS_MUX('C',1,1) /* PTC_1 */
#define SPI0_PCS3_PTC1 KINETIS_MUX('C',1,2) /* PTC_1 */
#define UART1_RTS_b_PTC1 KINETIS_MUX('C',1,3) /* PTC_1 */
#define FTM0_CH0_PTC1 KINETIS_MUX('C',1,4) /* PTC_1 */
#define I2S0_TXD0_PTC1 KINETIS_MUX('C',1,6) /* PTC_1 */
#define LPUART0_RTS_b_PTC1 KINETIS_MUX('C',1,7) /* PTC_1 */
#define CMP1_IN0_PTC2 KINETIS_MUX('C',2,0) /* PTC_2 */
#define ADC0_SE4b_PTC2 KINETIS_MUX('C',2,0) /* PTC_2 */
#define PTC2 KINETIS_MUX('C',2,1) /* PTC_2 */
#define SPI0_PCS2_PTC2 KINETIS_MUX('C',2,2) /* PTC_2 */
#define UART1_CTS_b_PTC2 KINETIS_MUX('C',2,3) /* PTC_2 */
#define FTM0_CH1_PTC2 KINETIS_MUX('C',2,4) /* PTC_2 */
#define I2S0_TX_FS_PTC2 KINETIS_MUX('C',2,6) /* PTC_2 */
#define LPUART0_CTS_b_PTC2 KINETIS_MUX('C',2,7) /* PTC_2 */
#define CMP1_IN1_PTC3 KINETIS_MUX('C',3,0) /* PTC_3 */
#define LLWU_P7_PTC3 KINETIS_MUX('C',3,1) /* PTC_3 */
#define PTC3 KINETIS_MUX('C',3,1) /* PTC_3 */
#define SPI0_PCS1_PTC3 KINETIS_MUX('C',3,2) /* PTC_3 */
#define UART1_RX_PTC3 KINETIS_MUX('C',3,3) /* PTC_3 */
#define FTM0_CH2_PTC3 KINETIS_MUX('C',3,4) /* PTC_3 */
#define CLKOUT_PTC3 KINETIS_MUX('C',3,5) /* PTC_3 */
#define I2S0_TX_BCLK_PTC3 KINETIS_MUX('C',3,6) /* PTC_3 */
#define LPUART0_RX_PTC3 KINETIS_MUX('C',3,7) /* PTC_3 */
#define PTC4 KINETIS_MUX('C',4,1) /* PTC_4 */
#define LLWU_P8_PTC4 KINETIS_MUX('C',4,1) /* PTC_4 */
#define SPI0_PCS0_PTC4 KINETIS_MUX('C',4,2) /* PTC_4 */
#define UART1_TX_PTC4 KINETIS_MUX('C',4,3) /* PTC_4 */
#define FTM0_CH3_PTC4 KINETIS_MUX('C',4,4) /* PTC_4 */
#define CMP1_OUT_PTC4 KINETIS_MUX('C',4,6) /* PTC_4 */
#define LPUART0_TX_PTC4 KINETIS_MUX('C',4,7) /* PTC_4 */
#define LLWU_P9_PTC5 KINETIS_MUX('C',5,1) /* PTC_5 */
#define PTC5 KINETIS_MUX('C',5,1) /* PTC_5 */
#define SPI0_SCK_PTC5 KINETIS_MUX('C',5,2) /* PTC_5 */
#define LPTMR0_ALT2_PTC5 KINETIS_MUX('C',5,3) /* PTC_5 */
#define I2S0_RXD0_PTC5 KINETIS_MUX('C',5,4) /* PTC_5 */
#define CMP0_OUT_PTC5 KINETIS_MUX('C',5,6) /* PTC_5 */
#define FTM0_CH2_PTC5 KINETIS_MUX('C',5,7) /* PTC_5 */
#define CMP0_IN0_PTC6 KINETIS_MUX('C',6,0) /* PTC_6 */
#define LLWU_P10_PTC6 KINETIS_MUX('C',6,1) /* PTC_6 */
#define PTC6 KINETIS_MUX('C',6,1) /* PTC_6 */
#define SPI0_SOUT_PTC6 KINETIS_MUX('C',6,2) /* PTC_6 */
#define PDB0_EXTRG_PTC6 KINETIS_MUX('C',6,3) /* PTC_6 */
#define I2S0_RX_BCLK_PTC6 KINETIS_MUX('C',6,4) /* PTC_6 */
#define I2S0_MCLK_PTC6 KINETIS_MUX('C',6,6) /* PTC_6 */
#define CMP0_IN1_PTC7 KINETIS_MUX('C',7,0) /* PTC_7 */
#define PTC7 KINETIS_MUX('C',7,1) /* PTC_7 */
#define SPI0_SIN_PTC7 KINETIS_MUX('C',7,2) /* PTC_7 */
#define USB_SOF_OUT_PTC7 KINETIS_MUX('C',7,3) /* PTC_7 */
#define I2S0_RX_FS_PTC7 KINETIS_MUX('C',7,4) /* PTC_7 */
#define ADC1_SE4b_PTC8 KINETIS_MUX('C',8,0) /* PTC_8 */
#define CMP0_IN2_PTC8 KINETIS_MUX('C',8,0) /* PTC_8 */
#define PTC8 KINETIS_MUX('C',8,1) /* PTC_8 */
#define I2S0_MCLK_PTC8 KINETIS_MUX('C',8,4) /* PTC_8 */
#define ADC1_SE5b_PTC9 KINETIS_MUX('C',9,0) /* PTC_9 */
#define CMP0_IN3_PTC9 KINETIS_MUX('C',9,0) /* PTC_9 */
#define PTC9 KINETIS_MUX('C',9,1) /* PTC_9 */
#define I2S0_RX_BCLK_PTC9 KINETIS_MUX('C',9,4) /* PTC_9 */
#define FTM2_FLT0_PTC9 KINETIS_MUX('C',9,6) /* PTC_9 */
#define ADC1_SE6b_PTC10 KINETIS_MUX('C',10,0) /* PTC_10 */
#define PTC10 KINETIS_MUX('C',10,1) /* PTC_10 */
#define I2C1_SCL_PTC10 KINETIS_MUX('C',10,2) /* PTC_10 */
#define I2S0_RX_FS_PTC10 KINETIS_MUX('C',10,4) /* PTC_10 */
#define ADC1_SE7b_PTC11 KINETIS_MUX('C',11,0) /* PTC_11 */
#define PTC11 KINETIS_MUX('C',11,1) /* PTC_11 */
#define LLWU_P11_PTC11 KINETIS_MUX('C',11,1) /* PTC_11 */
#define I2C1_SDA_PTC11 KINETIS_MUX('C',11,2) /* PTC_11 */
#define LLWU_P12_PTD0 KINETIS_MUX('D',0,1) /* PTD_0 */
#define PTD0 KINETIS_MUX('D',0,1) /* PTD_0 */
#define SPI0_PCS0_PTD0 KINETIS_MUX('D',0,2) /* PTD_0 */
#define UART2_RTS_b_PTD0 KINETIS_MUX('D',0,3) /* PTD_0 */
#define LPUART0_RTS_b_PTD0 KINETIS_MUX('D',0,6) /* PTD_0 */
#define ADC0_SE5b_PTD1 KINETIS_MUX('D',1,0) /* PTD_1 */
#define PTD1 KINETIS_MUX('D',1,1) /* PTD_1 */
#define SPI0_SCK_PTD1 KINETIS_MUX('D',1,2) /* PTD_1 */
#define UART2_CTS_b_PTD1 KINETIS_MUX('D',1,3) /* PTD_1 */
#define LPUART0_CTS_b_PTD1 KINETIS_MUX('D',1,6) /* PTD_1 */
#define LLWU_P13_PTD2 KINETIS_MUX('D',2,1) /* PTD_2 */
#define PTD2 KINETIS_MUX('D',2,1) /* PTD_2 */
#define SPI0_SOUT_PTD2 KINETIS_MUX('D',2,2) /* PTD_2 */
#define UART2_RX_PTD2 KINETIS_MUX('D',2,3) /* PTD_2 */
#define LPUART0_RX_PTD2 KINETIS_MUX('D',2,6) /* PTD_2 */
#define I2C0_SCL_PTD2 KINETIS_MUX('D',2,7) /* PTD_2 */
#define PTD3 KINETIS_MUX('D',3,1) /* PTD_3 */
#define SPI0_SIN_PTD3 KINETIS_MUX('D',3,2) /* PTD_3 */
#define UART2_TX_PTD3 KINETIS_MUX('D',3,3) /* PTD_3 */
#define LPUART0_TX_PTD3 KINETIS_MUX('D',3,6) /* PTD_3 */
#define I2C0_SDA_PTD3 KINETIS_MUX('D',3,7) /* PTD_3 */
#define LLWU_P14_PTD4 KINETIS_MUX('D',4,1) /* PTD_4 */
#define PTD4 KINETIS_MUX('D',4,1) /* PTD_4 */
#define SPI0_PCS1_PTD4 KINETIS_MUX('D',4,2) /* PTD_4 */
#define UART0_RTS_b_PTD4 KINETIS_MUX('D',4,3) /* PTD_4 */
#define FTM0_CH4_PTD4 KINETIS_MUX('D',4,4) /* PTD_4 */
#define EWM_IN_PTD4 KINETIS_MUX('D',4,6) /* PTD_4 */
#define SPI1_PCS0_PTD4 KINETIS_MUX('D',4,7) /* PTD_4 */
#define ADC0_SE6b_PTD5 KINETIS_MUX('D',5,0) /* PTD_5 */
#define PTD5 KINETIS_MUX('D',5,1) /* PTD_5 */
#define SPI0_PCS2_PTD5 KINETIS_MUX('D',5,2) /* PTD_5 */
#define UART0_CTS_b_PTD5 KINETIS_MUX('D',5,3) /* PTD_5 */
#define FTM0_CH5_PTD5 KINETIS_MUX('D',5,4) /* PTD_5 */
#define EWM_OUT_b_PTD5 KINETIS_MUX('D',5,6) /* PTD_5 */
#define SPI1_SCK_PTD5 KINETIS_MUX('D',5,7) /* PTD_5 */
#define ADC0_SE7b_PTD6 KINETIS_MUX('D',6,0) /* PTD_6 */
#define PTD6 KINETIS_MUX('D',6,1) /* PTD_6 */
#define LLWU_P15_PTD6 KINETIS_MUX('D',6,1) /* PTD_6 */
#define SPI0_PCS3_PTD6 KINETIS_MUX('D',6,2) /* PTD_6 */
#define UART0_RX_PTD6 KINETIS_MUX('D',6,3) /* PTD_6 */
#define FTM0_CH6_PTD6 KINETIS_MUX('D',6,4) /* PTD_6 */
#define FTM0_FLT0_PTD6 KINETIS_MUX('D',6,6) /* PTD_6 */
#define SPI1_SOUT_PTD6 KINETIS_MUX('D',6,7) /* PTD_6 */
#define PTD7 KINETIS_MUX('D',7,1) /* PTD_7 */
#define UART0_TX_PTD7 KINETIS_MUX('D',7,3) /* PTD_7 */
#define FTM0_CH7_PTD7 KINETIS_MUX('D',7,4) /* PTD_7 */
#define FTM0_FLT1_PTD7 KINETIS_MUX('D',7,6) /* PTD_7 */
#define SPI1_SIN_PTD7 KINETIS_MUX('D',7,7) /* PTD_7 */
#define ADC1_SE4a_PTE0 KINETIS_MUX('E',0,0) /* PTE_0 */
#define PTE0 KINETIS_MUX('E',0,1) /* PTE_0 */
#define SPI1_PCS1_PTE0 KINETIS_MUX('E',0,2) /* PTE_0 */
#define UART1_TX_PTE0 KINETIS_MUX('E',0,3) /* PTE_0 */
#define I2C1_SDA_PTE0 KINETIS_MUX('E',0,6) /* PTE_0 */
#define RTC_CLKOUT_PTE0 KINETIS_MUX('E',0,7) /* PTE_0 */
#define ADC1_SE5a_PTE1 KINETIS_MUX('E',1,0) /* PTE_1 */
#define LLWU_P0_PTE1 KINETIS_MUX('E',1,1) /* PTE_1 */
#define PTE1 KINETIS_MUX('E',1,1) /* PTE_1 */
#define SPI1_SOUT_PTE1 KINETIS_MUX('E',1,2) /* PTE_1 */
#define UART1_RX_PTE1 KINETIS_MUX('E',1,3) /* PTE_1 */
#define I2C1_SCL_PTE1 KINETIS_MUX('E',1,6) /* PTE_1 */
#define SPI1_SIN_PTE1 KINETIS_MUX('E',1,7) /* PTE_1 */
#endif
