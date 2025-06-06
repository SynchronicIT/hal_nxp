/*
** ###################################################################
**     Processors:          LPC5502JBD64
**                          LPC5502JHI48
**                          LPC5502JHI48CPXXXX
**                          LPC5504JBD64
**                          LPC5504JHI48
**                          LPC5504JHI48CPXXXX
**                          LPC5506JBD64
**                          LPC5506JHI48
**                          LPC5506JHI48CPXXXX
**                          LPC55S04JBD64
**                          LPC55S04JHI48
**                          LPC55S06JBD64
**                          LPC55S06JHI48
**
**     Version:             rev. 1.0, 2020-04-09
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for INPUTMUX
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2020-04-09)
**         Initial version based on Niobe4mini
**
** ###################################################################
*/

/*!
 * @file INPUTMUX.h
 * @version 1.0
 * @date 2020-04-09
 * @brief CMSIS Peripheral Access Layer for INPUTMUX
 *
 * CMSIS Peripheral Access Layer for INPUTMUX
 */

#if !defined(INPUTMUX_H_)
#define INPUTMUX_H_                              /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5502JBD64) || defined(CPU_LPC5502JHI48))
#include "LPC5502_COMMON.h"
#elif (defined(CPU_LPC5502JHI48CPXXXX))
#include "LPC5502CPXXXX_COMMON.h"
#elif (defined(CPU_LPC5504JBD64) || defined(CPU_LPC5504JHI48))
#include "LPC5504_COMMON.h"
#elif (defined(CPU_LPC5504JHI48CPXXXX))
#include "LPC5504CPXXXX_COMMON.h"
#elif (defined(CPU_LPC5506JBD64) || defined(CPU_LPC5506JHI48))
#include "LPC5506_COMMON.h"
#elif (defined(CPU_LPC5506JHI48CPXXXX))
#include "LPC5506CPXXXX_COMMON.h"
#elif (defined(CPU_LPC55S04JBD64) || defined(CPU_LPC55S04JHI48))
#include "LPC55S04_COMMON.h"
#elif (defined(CPU_LPC55S06JBD64) || defined(CPU_LPC55S06JHI48))
#include "LPC55S06_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- INPUTMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Peripheral_Access_Layer INPUTMUX Peripheral Access Layer
 * @{
 */

/** INPUTMUX - Size of Registers Arrays */
#define INPUTMUX_SCT0_INMUX_COUNT                 7u
#define INPUTMUX_TIMER0CAPTSEL_COUNT              4u
#define INPUTMUX_TIMER1CAPTSEL_COUNT              4u
#define INPUTMUX_TIMER2CAPTSEL_COUNT              4u
#define INPUTMUX_PINTSEL_COUNT                    8u
#define INPUTMUX_DMA0_ITRIG_INMUX_COUNT           23u
#define INPUTMUX_DMA0_OTRIG_INMUX_COUNT           4u
#define INPUTMUX_TIMER3CAPTSEL_COUNT              4u
#define INPUTMUX_TIMER4CAPTSEL_COUNT              4u
#define INPUTMUX_PINTSECSEL_COUNT                 2u
#define INPUTMUX_DMA1_ITRIG_INMUX_COUNT           10u
#define INPUTMUX_DMA1_OTRIG_INMUX_COUNT           4u

/** INPUTMUX - Register Layout Typedef */
typedef struct {
  __IO uint32_t SCT0_INMUX[INPUTMUX_SCT0_INMUX_COUNT]; /**< Input mux register for SCT0 input, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t TIMER0CAPTSEL[INPUTMUX_TIMER0CAPTSEL_COUNT]; /**< Capture select registers for TIMER0 inputs, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[16];
  __IO uint32_t TIMER1CAPTSEL[INPUTMUX_TIMER1CAPTSEL_COUNT]; /**< Capture select registers for TIMER1 inputs, array offset: 0x40, array step: 0x4 */
       uint8_t RESERVED_2[16];
  __IO uint32_t TIMER2CAPTSEL[INPUTMUX_TIMER2CAPTSEL_COUNT]; /**< Capture select registers for TIMER2 inputs, array offset: 0x60, array step: 0x4 */
       uint8_t RESERVED_3[80];
  __IO uint32_t PINTSEL[INPUTMUX_PINTSEL_COUNT];   /**< Pin interrupt select register, array offset: 0xC0, array step: 0x4 */
  __IO uint32_t DMA0_ITRIG_INMUX[INPUTMUX_DMA0_ITRIG_INMUX_COUNT]; /**< Trigger select register for DMA0 channel, array offset: 0xE0, array step: 0x4 */
       uint8_t RESERVED_4[36];
  __IO uint32_t DMA0_OTRIG_INMUX[INPUTMUX_DMA0_OTRIG_INMUX_COUNT]; /**< DMA0 output trigger selection to become DMA0 trigger, array offset: 0x160, array step: 0x4 */
       uint8_t RESERVED_5[16];
  __IO uint32_t FREQMEAS_REF;                      /**< Selection for frequency measurement reference clock, offset: 0x180 */
  __IO uint32_t FREQMEAS_TARGET;                   /**< Selection for frequency measurement target clock, offset: 0x184 */
       uint8_t RESERVED_6[24];
  __IO uint32_t TIMER3CAPTSEL[INPUTMUX_TIMER3CAPTSEL_COUNT]; /**< Capture select registers for TIMER3 inputs, array offset: 0x1A0, array step: 0x4 */
       uint8_t RESERVED_7[16];
  __IO uint32_t TIMER4CAPTSEL[INPUTMUX_TIMER4CAPTSEL_COUNT]; /**< Capture select registers for TIMER4 inputs, array offset: 0x1C0, array step: 0x4 */
       uint8_t RESERVED_8[16];
  __IO uint32_t PINTSECSEL[INPUTMUX_PINTSECSEL_COUNT]; /**< Pin interrupt secure select register, array offset: 0x1E0, array step: 0x4 */
       uint8_t RESERVED_9[24];
  __IO uint32_t DMA1_ITRIG_INMUX[INPUTMUX_DMA1_ITRIG_INMUX_COUNT]; /**< Trigger select register for DMA1 channel, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_10[24];
  __IO uint32_t DMA1_OTRIG_INMUX[INPUTMUX_DMA1_OTRIG_INMUX_COUNT]; /**< DMA1 output trigger selection to become DMA1 trigger, array offset: 0x240, array step: 0x4 */
       uint8_t RESERVED_11[1264];
  __IO uint32_t DMA0_REQ_ENA;                      /**< Enable DMA0 requests, offset: 0x740 */
       uint8_t RESERVED_12[4];
  __O  uint32_t DMA0_REQ_ENA_SET;                  /**< Set one or several bits in DMA0_REQ_ENA register, offset: 0x748 */
       uint8_t RESERVED_13[4];
  __O  uint32_t DMA0_REQ_ENA_CLR;                  /**< Clear one or several bits in DMA0_REQ_ENA register, offset: 0x750 */
       uint8_t RESERVED_14[12];
  __IO uint32_t DMA1_REQ_ENA;                      /**< Enable DMA1 requests, offset: 0x760 */
       uint8_t RESERVED_15[4];
  __O  uint32_t DMA1_REQ_ENA_SET;                  /**< Set one or several bits in DMA1_REQ_ENA register, offset: 0x768 */
       uint8_t RESERVED_16[4];
  __O  uint32_t DMA1_REQ_ENA_CLR;                  /**< Clear one or several bits in DMA1_REQ_ENA register, offset: 0x770 */
       uint8_t RESERVED_17[12];
  __IO uint32_t DMA0_ITRIG_ENA;                    /**< Enable DMA0 triggers, offset: 0x780 */
       uint8_t RESERVED_18[4];
  __O  uint32_t DMA0_ITRIG_ENA_SET;                /**< Set one or several bits in DMA0_ITRIG_ENA register, offset: 0x788 */
       uint8_t RESERVED_19[4];
  __O  uint32_t DMA0_ITRIG_ENA_CLR;                /**< Clear one or several bits in DMA0_ITRIG_ENA register, offset: 0x790 */
       uint8_t RESERVED_20[12];
  __IO uint32_t DMA1_ITRIG_ENA;                    /**< Enable DMA1 triggers, offset: 0x7A0 */
       uint8_t RESERVED_21[4];
  __O  uint32_t DMA1_ITRIG_ENA_SET;                /**< Set one or several bits in DMA1_ITRIG_ENA register, offset: 0x7A8 */
       uint8_t RESERVED_22[4];
  __O  uint32_t DMA1_ITRIG_ENA_CLR;                /**< Clear one or several bits in DMA1_ITRIG_ENA register, offset: 0x7B0 */
} INPUTMUX_Type;

/* ----------------------------------------------------------------------------
   -- INPUTMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Register_Masks INPUTMUX Register Masks
 * @{
 */

/*! @name SCT0_INMUX - Input mux register for SCT0 input */
/*! @{ */

#define INPUTMUX_SCT0_INMUX_INP_N_MASK           (0x1FU)
#define INPUTMUX_SCT0_INMUX_INP_N_SHIFT          (0U)
/*! INP_N - Input number to SCT0 inputs 0 to 6..
 *  0b00000..SCT_GPI0 function selected from IOCON register
 *  0b00001..SCT_GPI1 function selected from IOCON register
 *  0b00010..SCT_GPI2 function selected from IOCON register
 *  0b00011..SCT_GPI3 function selected from IOCON register
 *  0b00100..SCT_GPI4 function selected from IOCON register
 *  0b00101..SCT_GPI5 function selected from IOCON register
 *  0b00110..SCT_GPI6 function selected from IOCON register
 *  0b00111..SCT_GPI7 function selected from IOCON register
 *  0b01000..T0_OUT0 ctimer 0 match[0] output
 *  0b01001..T1_OUT0 ctimer 1 match[0] output
 *  0b01010..T2_OUT0 ctimer 2 match[0] output
 *  0b01011..T3_OUT0 ctimer 3 match[0] output
 *  0b01100..T4_OUT0 ctimer 4 match[0] output
 *  0b01101..ADC_IRQ interrupt request from ADC
 *  0b01110..GPIOINT_BMATCH
 *  0b01111..None
 *  0b10000..None
 *  0b10001..COMP_OUTPUT output from analog comparator
 *  0b10010..I2S_SHARED_SCK[0] output from I2S pin sharing
 *  0b10011..I2S_SHARED_SCK[1] output from I2S pin sharing
 *  0b10100..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b10101..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b10110..ARM_TXEV interrupt event from cpu0 or cpu1
 *  0b10111..DEBUG_HALTED from cpu0 or cpu1
 *  0b11000-0b11111..None
 */
#define INPUTMUX_SCT0_INMUX_INP_N(x)             (((uint32_t)(((uint32_t)(x)) << INPUTMUX_SCT0_INMUX_INP_N_SHIFT)) & INPUTMUX_SCT0_INMUX_INP_N_MASK)
/*! @} */

/*! @name TIMER0CAPTSEL - Capture select registers for TIMER0 inputs */
/*! @{ */

#define INPUTMUX_TIMER0CAPTSEL_CAPTSEL_MASK      (0x1FU)
#define INPUTMUX_TIMER0CAPTSEL_CAPTSEL_SHIFT     (0U)
/*! CAPTSEL - Input number to TIMER0 capture inputs 0 to 4
 *  0b00000..CT_INP0 function selected from IOCON register
 *  0b00001..CT_INP1 function selected from IOCON register
 *  0b00010..CT_INP2 function selected from IOCON register
 *  0b00011..CT_INP3 function selected from IOCON register
 *  0b00100..CT_INP4 function selected from IOCON register
 *  0b00101..CT_INP5 function selected from IOCON register
 *  0b00110..CT_INP6 function selected from IOCON register
 *  0b00111..CT_INP7 function selected from IOCON register
 *  0b01000..CT_INP8 function selected from IOCON register
 *  0b01001..CT_INP9 function selected from IOCON register
 *  0b01010..CT_INP10 function selected from IOCON register
 *  0b01011..CT_INP11 function selected from IOCON register
 *  0b01100..CT_INP12 function selected from IOCON register
 *  0b01101..CT_INP13 function selected from IOCON register
 *  0b01110..CT_INP14 function selected from IOCON register
 *  0b01111..CT_INP15 function selected from IOCON register
 *  0b10000..CT_INP16 function selected from IOCON register
 *  0b10001..None
 *  0b10010..None
 *  0b10011..None
 *  0b10100..None
 *  0b10101..None
 *  0b10110..COMP_OUTPUT output from analog comparator
 *  0b10111..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b11000..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b11001-0b11111..None
 */
#define INPUTMUX_TIMER0CAPTSEL_CAPTSEL(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_TIMER0CAPTSEL_CAPTSEL_SHIFT)) & INPUTMUX_TIMER0CAPTSEL_CAPTSEL_MASK)
/*! @} */

/*! @name TIMER1CAPTSEL - Capture select registers for TIMER1 inputs */
/*! @{ */

#define INPUTMUX_TIMER1CAPTSEL_CAPTSEL_MASK      (0x1FU)
#define INPUTMUX_TIMER1CAPTSEL_CAPTSEL_SHIFT     (0U)
/*! CAPTSEL - Input number to TIMER1 capture inputs 0 to 4
 *  0b00000..CT_INP0 function selected from IOCON register
 *  0b00001..CT_INP1 function selected from IOCON register
 *  0b00010..CT_INP2 function selected from IOCON register
 *  0b00011..CT_INP3 function selected from IOCON register
 *  0b00100..CT_INP4 function selected from IOCON register
 *  0b00101..CT_INP5 function selected from IOCON register
 *  0b00110..CT_INP6 function selected from IOCON register
 *  0b00111..CT_INP7 function selected from IOCON register
 *  0b01000..CT_INP8 function selected from IOCON register
 *  0b01001..CT_INP9 function selected from IOCON register
 *  0b01010..CT_INP10 function selected from IOCON register
 *  0b01011..CT_INP11 function selected from IOCON register
 *  0b01100..CT_INP12 function selected from IOCON register
 *  0b01101..CT_INP13 function selected from IOCON register
 *  0b01110..CT_INP14 function selected from IOCON register
 *  0b01111..CT_INP15 function selected from IOCON register
 *  0b10000..CT_INP16 function selected from IOCON register
 *  0b10001..None
 *  0b10010..None
 *  0b10011..None
 *  0b10100..None
 *  0b10101..None
 *  0b10110..COMP_OUTPUT output from analog comparator
 *  0b10111..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b11000..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b11001-0b11111..None
 */
#define INPUTMUX_TIMER1CAPTSEL_CAPTSEL(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_TIMER1CAPTSEL_CAPTSEL_SHIFT)) & INPUTMUX_TIMER1CAPTSEL_CAPTSEL_MASK)
/*! @} */

/*! @name TIMER2CAPTSEL - Capture select registers for TIMER2 inputs */
/*! @{ */

#define INPUTMUX_TIMER2CAPTSEL_CAPTSEL_MASK      (0x1FU)
#define INPUTMUX_TIMER2CAPTSEL_CAPTSEL_SHIFT     (0U)
/*! CAPTSEL - Input number to TIMER2 capture inputs 0 to 4
 *  0b00000..CT_INP0 function selected from IOCON register
 *  0b00001..CT_INP1 function selected from IOCON register
 *  0b00010..CT_INP2 function selected from IOCON register
 *  0b00011..CT_INP3 function selected from IOCON register
 *  0b00100..CT_INP4 function selected from IOCON register
 *  0b00101..CT_INP5 function selected from IOCON register
 *  0b00110..CT_INP6 function selected from IOCON register
 *  0b00111..CT_INP7 function selected from IOCON register
 *  0b01000..CT_INP8 function selected from IOCON register
 *  0b01001..CT_INP9 function selected from IOCON register
 *  0b01010..CT_INP10 function selected from IOCON register
 *  0b01011..CT_INP11 function selected from IOCON register
 *  0b01100..CT_INP12 function selected from IOCON register
 *  0b01101..CT_INP13 function selected from IOCON register
 *  0b01110..CT_INP14 function selected from IOCON register
 *  0b01111..CT_INP15 function selected from IOCON register
 *  0b10000..CT_INP16 function selected from IOCON register
 *  0b10001..None
 *  0b10010..None
 *  0b10011..None
 *  0b10100..None
 *  0b10101..None
 *  0b10110..COMP_OUTPUT output from analog comparator
 *  0b10111..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b11000..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b11001-0b11111..None
 */
#define INPUTMUX_TIMER2CAPTSEL_CAPTSEL(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_TIMER2CAPTSEL_CAPTSEL_SHIFT)) & INPUTMUX_TIMER2CAPTSEL_CAPTSEL_MASK)
/*! @} */

/*! @name PINTSEL - Pin interrupt select register */
/*! @{ */

#define INPUTMUX_PINTSEL_INTPIN_MASK             (0x7FU)
#define INPUTMUX_PINTSEL_INTPIN_SHIFT            (0U)
/*! INTPIN - Pin number select for pin interrupt or pattern match engine input. For PIOx_y: INTPIN =
 *    (x * 32) + y. PIO0_0 to PIO1_31 correspond to numbers 0 to 63.
 */
#define INPUTMUX_PINTSEL_INTPIN(x)               (((uint32_t)(((uint32_t)(x)) << INPUTMUX_PINTSEL_INTPIN_SHIFT)) & INPUTMUX_PINTSEL_INTPIN_MASK)
/*! @} */

/*! @name DMA0_ITRIG_INMUX - Trigger select register for DMA0 channel */
/*! @{ */

#define INPUTMUX_DMA0_ITRIG_INMUX_INP_MASK       (0x1FU)
#define INPUTMUX_DMA0_ITRIG_INMUX_INP_SHIFT      (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 22).
 *  0b00000..Pin interrupt 0
 *  0b00001..Pin interrupt 1
 *  0b00010..Pin interrupt 2
 *  0b00011..Pin interrupt 3
 *  0b00100..Timer CTIMER0 Match 0
 *  0b00101..Timer CTIMER0 Match 1
 *  0b00110..Timer CTIMER1 Match 0
 *  0b00111..Timer CTIMER1 Match 1
 *  0b01000..Timer CTIMER2 Match 0
 *  0b01001..Timer CTIMER2 Match 1
 *  0b01010..Timer CTIMER3 Match 0
 *  0b01011..Timer CTIMER3 Match 1
 *  0b01100..Timer CTIMER4 Match 0
 *  0b01101..Timer CTIMER4 Match 1
 *  0b01110..COMP_OUTPUT
 *  0b01111..DMA0 output trigger mux 0
 *  0b10000..DMA0 output trigger mux 1
 *  0b10001..DMA0 output trigger mux 1
 *  0b10010..DMA0 output trigger mux 3
 *  0b10011..SCT0 DMA request 0
 *  0b10100..SCT0 DMA request 1
 *  0b10101..HASH DMA RX trigger
 *  0b10110-0b11111..None
 */
#define INPUTMUX_DMA0_ITRIG_INMUX_INP(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_ITRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA0_ITRIG_INMUX_INP_MASK)
/*! @} */

/*! @name DMA0_OTRIG_INMUX - DMA0 output trigger selection to become DMA0 trigger */
/*! @{ */

#define INPUTMUX_DMA0_OTRIG_INMUX_INP_MASK       (0x1FU)
#define INPUTMUX_DMA0_OTRIG_INMUX_INP_SHIFT      (0U)
/*! INP - DMA trigger output number (decimal value) for DMA channel n (n = 0 to 22). */
#define INPUTMUX_DMA0_OTRIG_INMUX_INP(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_OTRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA0_OTRIG_INMUX_INP_MASK)
/*! @} */

/*! @name FREQMEAS_REF - Selection for frequency measurement reference clock */
/*! @{ */

#define INPUTMUX_FREQMEAS_REF_CLKIN_MASK         (0x1FU)
#define INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT        (0U)
/*! CLKIN - Clock source number (decimal value) for frequency measure function reference clock:
 *  0b00000..External main crystal oscilator (Clock_in).
 *  0b00001..FRO 12MHz clock.
 *  0b00010..FRO 96MHz clock.
 *  0b00011..Watchdog oscillator / FRO1MHz clock.
 *  0b00100..32 kHz oscillator (32k_clk) clock.
 *  0b00101..main clock (main_clock).
 *  0b00110..FREQME_GPIO_CLK_A.
 *  0b00111..FREQME_GPIO_CLK_B.
 */
#define INPUTMUX_FREQMEAS_REF_CLKIN(x)           (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_REF_CLKIN_MASK)
/*! @} */

/*! @name FREQMEAS_TARGET - Selection for frequency measurement target clock */
/*! @{ */

#define INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK      (0x1FU)
#define INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT     (0U)
/*! CLKIN - Clock source number (decimal value) for frequency measure function target clock:
 *  0b00000..External main crystal oscilator (Clock_in).
 *  0b00001..FRO 12MHz clock.
 *  0b00010..FRO 96MHz clock.
 *  0b00011..Watchdog oscillator / FRO1MHz clock.
 *  0b00100..32 kHz oscillator (32k_clk) clock.
 *  0b00101..main clock (main_clock).
 *  0b00110..FREQME_GPIO_CLK_A.
 *  0b00111..FREQME_GPIO_CLK_B.
 */
#define INPUTMUX_FREQMEAS_TARGET_CLKIN(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK)
/*! @} */

/*! @name TIMER3CAPTSEL - Capture select registers for TIMER3 inputs */
/*! @{ */

#define INPUTMUX_TIMER3CAPTSEL_CAPTSEL_MASK      (0x1FU)
#define INPUTMUX_TIMER3CAPTSEL_CAPTSEL_SHIFT     (0U)
/*! CAPTSEL - Input number to TIMER3 capture inputs 0 to 4
 *  0b00000..CT_INP0 function selected from IOCON register
 *  0b00001..CT_INP1 function selected from IOCON register
 *  0b00010..CT_INP2 function selected from IOCON register
 *  0b00011..CT_INP3 function selected from IOCON register
 *  0b00100..CT_INP4 function selected from IOCON register
 *  0b00101..CT_INP5 function selected from IOCON register
 *  0b00110..CT_INP6 function selected from IOCON register
 *  0b00111..CT_INP7 function selected from IOCON register
 *  0b01000..CT_INP8 function selected from IOCON register
 *  0b01001..CT_INP9 function selected from IOCON register
 *  0b01010..CT_INP10 function selected from IOCON register
 *  0b01011..CT_INP11 function selected from IOCON register
 *  0b01100..CT_INP12 function selected from IOCON register
 *  0b01101..CT_INP13 function selected from IOCON register
 *  0b01110..CT_INP14 function selected from IOCON register
 *  0b01111..CT_INP15 function selected from IOCON register
 *  0b10000..CT_INP16 function selected from IOCON register
 *  0b10001..None
 *  0b10010..None
 *  0b10011..None
 *  0b10100..None
 *  0b10101..None
 *  0b10110..COMP_OUTPUT output from analog comparator
 *  0b10111..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b11000..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b11001-0b11111..None
 */
#define INPUTMUX_TIMER3CAPTSEL_CAPTSEL(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_TIMER3CAPTSEL_CAPTSEL_SHIFT)) & INPUTMUX_TIMER3CAPTSEL_CAPTSEL_MASK)
/*! @} */

/*! @name TIMER4CAPTSEL - Capture select registers for TIMER4 inputs */
/*! @{ */

#define INPUTMUX_TIMER4CAPTSEL_CAPTSEL_MASK      (0x1FU)
#define INPUTMUX_TIMER4CAPTSEL_CAPTSEL_SHIFT     (0U)
/*! CAPTSEL - Input number to TIMER4 capture inputs 0 to 4
 *  0b00000..CT_INP0 function selected from IOCON register
 *  0b00001..CT_INP1 function selected from IOCON register
 *  0b00010..CT_INP2 function selected from IOCON register
 *  0b00011..CT_INP3 function selected from IOCON register
 *  0b00100..CT_INP4 function selected from IOCON register
 *  0b00101..CT_INP5 function selected from IOCON register
 *  0b00110..CT_INP6 function selected from IOCON register
 *  0b00111..CT_INP7 function selected from IOCON register
 *  0b01000..CT_INP8 function selected from IOCON register
 *  0b01001..CT_INP9 function selected from IOCON register
 *  0b01010..CT_INP10 function selected from IOCON register
 *  0b01011..CT_INP11 function selected from IOCON register
 *  0b01100..CT_INP12 function selected from IOCON register
 *  0b01101..CT_INP13 function selected from IOCON register
 *  0b01110..CT_INP14 function selected from IOCON register
 *  0b01111..CT_INP15 function selected from IOCON register
 *  0b10000..CT_INP16 function selected from IOCON register
 *  0b10001..None
 *  0b10010..None
 *  0b10011..None
 *  0b10100..None
 *  0b10101..None
 *  0b10110..COMP_OUTPUT output from analog comparator
 *  0b10111..I2S_SHARED_WS[0] output from I2S pin sharing
 *  0b11000..I2S_SHARED_WS[1] output from I2S pin sharing
 *  0b11001-0b11111..None
 */
#define INPUTMUX_TIMER4CAPTSEL_CAPTSEL(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_TIMER4CAPTSEL_CAPTSEL_SHIFT)) & INPUTMUX_TIMER4CAPTSEL_CAPTSEL_MASK)
/*! @} */

/*! @name PINTSECSEL - Pin interrupt secure select register */
/*! @{ */

#define INPUTMUX_PINTSECSEL_INTPIN_MASK          (0x3FU)
#define INPUTMUX_PINTSECSEL_INTPIN_SHIFT         (0U)
/*! INTPIN - Pin number select for pin interrupt secure or pattern match engine input. For PIO0_x:
 *    INTPIN = x. PIO0_0 to PIO0_31 correspond to numbers 0 to 31.
 */
#define INPUTMUX_PINTSECSEL_INTPIN(x)            (((uint32_t)(((uint32_t)(x)) << INPUTMUX_PINTSECSEL_INTPIN_SHIFT)) & INPUTMUX_PINTSECSEL_INTPIN_MASK)
/*! @} */

/*! @name DMA1_ITRIG_INMUX - Trigger select register for DMA1 channel */
/*! @{ */

#define INPUTMUX_DMA1_ITRIG_INMUX_INP_MASK       (0xFU)
#define INPUTMUX_DMA1_ITRIG_INMUX_INP_SHIFT      (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 9).
 *  0b0000..Pin interrupt 0
 *  0b0001..Pin interrupt 1
 *  0b0010..Pin interrupt 2
 *  0b0011..Pin interrupt 3
 *  0b0100..Timer CTIMER0 Match 0
 *  0b0101..Timer CTIMER0 Match 1
 *  0b0110..Timer CTIMER2 Match 0
 *  0b0111..Timer CTIMER4 Match 0
 *  0b1000..DMA1 output trigger mux 0
 *  0b1001..DMA1 output trigger mux 1
 *  0b1010..DMA1 output trigger mux 2
 *  0b1011..DMA1 output trigger mux 3
 *  0b1100..SCT0 DMA request 0
 *  0b1101..SCT0 DMA request 1
 *  0b1110..HASH DMA RX trigger
 *  0b1111..None
 */
#define INPUTMUX_DMA1_ITRIG_INMUX_INP(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_ITRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA1_ITRIG_INMUX_INP_MASK)
/*! @} */

/*! @name DMA1_OTRIG_INMUX - DMA1 output trigger selection to become DMA1 trigger */
/*! @{ */

#define INPUTMUX_DMA1_OTRIG_INMUX_INP_MASK       (0xFU)
#define INPUTMUX_DMA1_OTRIG_INMUX_INP_SHIFT      (0U)
/*! INP - DMA trigger output number (decimal value) for DMA channel n (n = 0 to 9). */
#define INPUTMUX_DMA1_OTRIG_INMUX_INP(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_OTRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA1_OTRIG_INMUX_INP_MASK)
/*! @} */

/*! @name DMA0_REQ_ENA - Enable DMA0 requests */
/*! @{ */

#define INPUTMUX_DMA0_REQ_ENA_REQ_ENA_MASK       (0x7FFFFFU)
#define INPUTMUX_DMA0_REQ_ENA_REQ_ENA_SHIFT      (0U)
/*! REQ_ENA - Controls the 23 request inputs of DMA0. If bit i is '1' the DMA request input #i is enabled.
 *  0b00000000000000000000000..Hash-Crypt DMA request.
 *  0b00000000000000000000010..High Speed SPI (Flexcomm 8) RX.
 *  0b00000000000000000000011..High Speed SPI (Flexcomm 8) TX.
 *  0b00000000000000000000100..Flexcomm Interface 0 RX / I2C Slave.
 *  0b00000000000000000000101..Flexcomm Interface 0 TX / I2C Master.
 *  0b00000000000000000000110..Flexcomm Interface 1 RX / I2C Slave.
 *  0b00000000000000000000111..Flexcomm Interface 1 TX / I2C Master.
 *  0b00000000000000000001000..Flexcomm Interface 3 RX / I2C Slave.
 *  0b00000000000000000001001..Flexcomm Interface 3 TX / I2C Master.
 *  0b00000000000000000001010..Flexcomm Interface 2 RX / I2C Slave.
 *  0b00000000000000000001011..Flexcomm Interface 2 TX / I2C Master.
 *  0b00000000000000000001100..Flexcomm Interface 4 RX / I2C Slave.
 *  0b00000000000000000001101..Flexcomm Interface 4 TX / I2C Master.
 *  0b00000000000000000001110..Flexcomm Interface 5 RX / I2C Slave.
 *  0b00000000000000000001111..Flexcomm Interface 5 TX / I2C Master.
 *  0b00000000000000000010000..Flexcomm Interface 6 RX / I2C Slave.
 *  0b00000000000000000010001..Flexcomm Interface 6 TX / I2C Master.
 *  0b00000000000000000010010..Flexcomm Interface 7 RX / I2C Slave.
 *  0b00000000000000000010011..Flexcomm Interface 6 TX / I2C Master.
 *  0b00000000000000000010101..ADC0 FIFO 0.
 *  0b00000000000000000010110..ADC0 FIFO 1.
 */
#define INPUTMUX_DMA0_REQ_ENA_REQ_ENA(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_REQ_ENA_REQ_ENA_SHIFT)) & INPUTMUX_DMA0_REQ_ENA_REQ_ENA_MASK)
/*! @} */

/*! @name DMA0_REQ_ENA_SET - Set one or several bits in DMA0_REQ_ENA register */
/*! @{ */

#define INPUTMUX_DMA0_REQ_ENA_SET_SET_MASK       (0x7FFFFFU)
#define INPUTMUX_DMA0_REQ_ENA_SET_SET_SHIFT      (0U)
/*! SET - Write : If bit #i = 1, bit #i in DMA0_REQ_ENA register is set to 1; if bit #i = 0 , no change in DMA0_REQ_ENA register */
#define INPUTMUX_DMA0_REQ_ENA_SET_SET(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_REQ_ENA_SET_SET_SHIFT)) & INPUTMUX_DMA0_REQ_ENA_SET_SET_MASK)
/*! @} */

/*! @name DMA0_REQ_ENA_CLR - Clear one or several bits in DMA0_REQ_ENA register */
/*! @{ */

#define INPUTMUX_DMA0_REQ_ENA_CLR_CLR_MASK       (0x7FFFFFU)
#define INPUTMUX_DMA0_REQ_ENA_CLR_CLR_SHIFT      (0U)
/*! CLR - Write : If bit #i = 1, bit #i in DMA0_REQ_ENA register is reset to 0; if bit #i = 0 , no change in DMA0_REQ_ENA register */
#define INPUTMUX_DMA0_REQ_ENA_CLR_CLR(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_REQ_ENA_CLR_CLR_SHIFT)) & INPUTMUX_DMA0_REQ_ENA_CLR_CLR_MASK)
/*! @} */

/*! @name DMA1_REQ_ENA - Enable DMA1 requests */
/*! @{ */

#define INPUTMUX_DMA1_REQ_ENA_REQ_ENA_MASK       (0x3FFU)
#define INPUTMUX_DMA1_REQ_ENA_REQ_ENA_SHIFT      (0U)
/*! REQ_ENA - Controls the 10 request inputs of DMA1. If bit i is '1' the DMA request input #i is enabled.
 *  0b0000000000..Hash-Crypt input DMA request.
 *  0b0000000010..High Speed SPI (Flexcomm 8) RX.
 *  0b0000000011..High Speed SPI (Flexcomm 8) TX.
 *  0b0000000100..Flexcomm Interface 0 RX /I2C Slave.
 *  0b0000000101..Flexcomm Interface 0 TX / I2C Master.
 *  0b0000000110..Flexcomm Interface 1 RX /I2C Slave.
 *  0b0000000111..Flexcomm Interface 1 TX / I2C Master.
 *  0b0000001000..Flexcomm Interface 3 RX / I2C Slave.
 *  0b0000001001..Flexcomm Interface 3 TX / I2C Master.
 */
#define INPUTMUX_DMA1_REQ_ENA_REQ_ENA(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_REQ_ENA_REQ_ENA_SHIFT)) & INPUTMUX_DMA1_REQ_ENA_REQ_ENA_MASK)
/*! @} */

/*! @name DMA1_REQ_ENA_SET - Set one or several bits in DMA1_REQ_ENA register */
/*! @{ */

#define INPUTMUX_DMA1_REQ_ENA_SET_SET_MASK       (0x3FFU)
#define INPUTMUX_DMA1_REQ_ENA_SET_SET_SHIFT      (0U)
/*! SET - Write : If bit #i = 1, bit #i in DMA1_REQ_ENA register is set to 1; if bit #i = 0 , no change in DMA1_REQ_ENA register */
#define INPUTMUX_DMA1_REQ_ENA_SET_SET(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_REQ_ENA_SET_SET_SHIFT)) & INPUTMUX_DMA1_REQ_ENA_SET_SET_MASK)
/*! @} */

/*! @name DMA1_REQ_ENA_CLR - Clear one or several bits in DMA1_REQ_ENA register */
/*! @{ */

#define INPUTMUX_DMA1_REQ_ENA_CLR_CLR_MASK       (0x3FFU)
#define INPUTMUX_DMA1_REQ_ENA_CLR_CLR_SHIFT      (0U)
/*! CLR - Write : If bit #i = 1, bit #i in DMA1_REQ_ENA register is reset to 0; if bit #i = 0 , no change in DMA1_REQ_ENA register */
#define INPUTMUX_DMA1_REQ_ENA_CLR_CLR(x)         (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_REQ_ENA_CLR_CLR_SHIFT)) & INPUTMUX_DMA1_REQ_ENA_CLR_CLR_MASK)
/*! @} */

/*! @name DMA0_ITRIG_ENA - Enable DMA0 triggers */
/*! @{ */

#define INPUTMUX_DMA0_ITRIG_ENA_ITRIG_ENA_MASK   (0x3FFFFFU)
#define INPUTMUX_DMA0_ITRIG_ENA_ITRIG_ENA_SHIFT  (0U)
/*! ITRIG_ENA - Controls the 22 trigger inputs of DMA0. If bit i is '1' the DMA trigger input #i is enabled. */
#define INPUTMUX_DMA0_ITRIG_ENA_ITRIG_ENA(x)     (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_ITRIG_ENA_ITRIG_ENA_SHIFT)) & INPUTMUX_DMA0_ITRIG_ENA_ITRIG_ENA_MASK)
/*! @} */

/*! @name DMA0_ITRIG_ENA_SET - Set one or several bits in DMA0_ITRIG_ENA register */
/*! @{ */

#define INPUTMUX_DMA0_ITRIG_ENA_SET_SET_MASK     (0x3FFFFFU)
#define INPUTMUX_DMA0_ITRIG_ENA_SET_SET_SHIFT    (0U)
/*! SET - Write : If bit #i = 1, bit #i in DMA0_ITRIG_ENA register is set to 1; if bit #i = 0 , no
 *    change in DMA0_ITRIG_ENA register
 */
#define INPUTMUX_DMA0_ITRIG_ENA_SET_SET(x)       (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_ITRIG_ENA_SET_SET_SHIFT)) & INPUTMUX_DMA0_ITRIG_ENA_SET_SET_MASK)
/*! @} */

/*! @name DMA0_ITRIG_ENA_CLR - Clear one or several bits in DMA0_ITRIG_ENA register */
/*! @{ */

#define INPUTMUX_DMA0_ITRIG_ENA_CLR_CLR_MASK     (0x3FFFFFU)
#define INPUTMUX_DMA0_ITRIG_ENA_CLR_CLR_SHIFT    (0U)
/*! CLR - Write : If bit #i = 1, bit #i in DMA0_ITRIG_ENA register is reset to 0; if bit #i = 0 , no
 *    change in DMA0_ITRIG_ENA register
 */
#define INPUTMUX_DMA0_ITRIG_ENA_CLR_CLR(x)       (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA0_ITRIG_ENA_CLR_CLR_SHIFT)) & INPUTMUX_DMA0_ITRIG_ENA_CLR_CLR_MASK)
/*! @} */

/*! @name DMA1_ITRIG_ENA - Enable DMA1 triggers */
/*! @{ */

#define INPUTMUX_DMA1_ITRIG_ENA_ITRIG_ENA_MASK   (0x7FFFU)
#define INPUTMUX_DMA1_ITRIG_ENA_ITRIG_ENA_SHIFT  (0U)
/*! ITRIG_ENA - Controls the 15 trigger inputs of DMA1. If bit i is '1' the DMA trigger input #i is enabled. */
#define INPUTMUX_DMA1_ITRIG_ENA_ITRIG_ENA(x)     (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_ITRIG_ENA_ITRIG_ENA_SHIFT)) & INPUTMUX_DMA1_ITRIG_ENA_ITRIG_ENA_MASK)
/*! @} */

/*! @name DMA1_ITRIG_ENA_SET - Set one or several bits in DMA1_ITRIG_ENA register */
/*! @{ */

#define INPUTMUX_DMA1_ITRIG_ENA_SET_SET_MASK     (0x7FFFU)
#define INPUTMUX_DMA1_ITRIG_ENA_SET_SET_SHIFT    (0U)
/*! SET - Write : If bit #i = 1, bit #i in DMA1_ITRIG_ENA register is set to 1; if bit #i = 0 , no
 *    change in DMA1_ITRIG_ENA register
 */
#define INPUTMUX_DMA1_ITRIG_ENA_SET_SET(x)       (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_ITRIG_ENA_SET_SET_SHIFT)) & INPUTMUX_DMA1_ITRIG_ENA_SET_SET_MASK)
/*! @} */

/*! @name DMA1_ITRIG_ENA_CLR - Clear one or several bits in DMA1_ITRIG_ENA register */
/*! @{ */

#define INPUTMUX_DMA1_ITRIG_ENA_CLR_CLR_MASK     (0x7FFFU)
#define INPUTMUX_DMA1_ITRIG_ENA_CLR_CLR_SHIFT    (0U)
/*! CLR - Write : If bit #i = 1, bit #i in DMA1_ITRIG_ENA register is reset to 0; if bit #i = 0 , no
 *    change in DMA1_ITRIG_ENA register
 */
#define INPUTMUX_DMA1_ITRIG_ENA_CLR_CLR(x)       (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA1_ITRIG_ENA_CLR_CLR_SHIFT)) & INPUTMUX_DMA1_ITRIG_ENA_CLR_CLR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group INPUTMUX_Register_Masks */


/*!
 * @}
 */ /* end of group INPUTMUX_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* INPUTMUX_H_ */

