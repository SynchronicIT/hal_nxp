/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/* Macro definition remap workaround. */
#if (defined(MCG_C2_EREFS_MASK) && !(defined(MCG_C2_EREFS0_MASK)))
#define MCG_C2_EREFS0_MASK MCG_C2_EREFS_MASK
#endif
#if (defined(MCG_C2_HGO_MASK) && !(defined(MCG_C2_HGO0_MASK)))
#define MCG_C2_HGO0_MASK MCG_C2_HGO_MASK
#endif
#if (defined(MCG_C2_RANGE_MASK) && !(defined(MCG_C2_RANGE0_MASK)))
#define MCG_C2_RANGE0_MASK MCG_C2_RANGE_MASK
#endif
#if (defined(MCG_C6_CME_MASK) && !(defined(MCG_C6_CME0_MASK)))
#define MCG_C6_CME0_MASK MCG_C6_CME_MASK
#endif

/* PLL fixed multiplier when there is not PRDIV and VDIV. */
#define PLL_FIXED_MULT (375U)
/* Max frequency of the reference clock used for internal clock trim. */
#define TRIM_REF_CLK_MIN (8000000U)
/* Min frequency of the reference clock used for internal clock trim. */
#define TRIM_REF_CLK_MAX (16000000U)
/* Max trim value of fast internal reference clock. */
#define TRIM_FIRC_MAX (5000000U)
/* Min trim value of fast internal reference clock. */
#define TRIM_FIRC_MIN (3000000U)
/* Max trim value of fast internal reference clock. */
#define TRIM_SIRC_MAX (39063U)
/* Min trim value of fast internal reference clock. */
#define TRIM_SIRC_MIN (31250U)

#define MCG_S_IRCST_VAL (((uint32_t)MCG->S & (uint32_t)MCG_S_IRCST_MASK) >> (uint32_t)MCG_S_IRCST_SHIFT)
#define MCG_S_CLKST_VAL (((uint32_t)MCG->S & (uint32_t)MCG_S_CLKST_MASK) >> (uint32_t)MCG_S_CLKST_SHIFT)
#define MCG_S_IREFST_VAL (((uint32_t)MCG->S & (uint32_t)MCG_S_IREFST_MASK) >> (uint32_t)MCG_S_IREFST_SHIFT)
#define MCG_S_PLLST_VAL (((uint32_t)MCG->S & (uint32_t)MCG_S_PLLST_MASK) >> (uint32_t)MCG_S_PLLST_SHIFT)
#define MCG_C1_FRDIV_VAL ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT)
#define MCG_C2_LP_VAL (((uint32_t)MCG->C2 & (uint32_t)MCG_C2_LP_MASK) >> (uint32_t)MCG_C2_LP_SHIFT)
#define MCG_C2_RANGE_VAL ((MCG->C2 & MCG_C2_RANGE_MASK) >> MCG_C2_RANGE_SHIFT)
#define MCG_SC_FCRDIV_VAL ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT)
#define MCG_S2_PLLCST_VAL (((uint32_t)MCG->S2 & (uint32_t)MCG_S2_PLLCST_MASK) >> (uint32_t)MCG_S2_PLLCST_SHIFT)
#define MCG_C7_OSCSEL_VAL ((MCG->C7 & MCG_C7_OSCSEL_MASK) >> MCG_C7_OSCSEL_SHIFT)
#define MCG_C4_DMX32_VAL ((MCG->C4 & MCG_C4_DMX32_MASK) >> MCG_C4_DMX32_SHIFT)
#define MCG_C4_DRST_DRS_VAL ((MCG->C4 & MCG_C4_DRST_DRS_MASK) >> MCG_C4_DRST_DRS_SHIFT)
#define MCG_C7_PLL32KREFSEL_VAL ((MCG->C7 & MCG_C7_PLL32KREFSEL_MASK) >> MCG_C7_PLL32KREFSEL_SHIFT)
#define MCG_C5_PLLREFSEL0_VAL ((MCG->C5 & MCG_C5_PLLREFSEL0_MASK) >> MCG_C5_PLLREFSEL0_SHIFT)
#define MCG_C11_PLLREFSEL1_VAL ((MCG->C11 & MCG_C11_PLLREFSEL1_MASK) >> MCG_C11_PLLREFSEL1_SHIFT)
#define MCG_C11_PRDIV1_VAL ((MCG->C11 & MCG_C11_PRDIV1_MASK) >> MCG_C11_PRDIV1_SHIFT)
#define MCG_C12_VDIV1_VAL ((MCG->C12 & MCG_C12_VDIV1_MASK) >> MCG_C12_VDIV1_SHIFT)
#define MCG_C5_PRDIV0_VAL ((uint8_t)(MCG->C5 & MCG_C5_PRDIV0_MASK) >> MCG_C5_PRDIV0_SHIFT)
#define MCG_C6_VDIV0_VAL ((uint8_t)(MCG->C6 & MCG_C6_VDIV0_MASK) >> MCG_C6_VDIV0_SHIFT)

#define OSC_MODE_MASK (MCG_C2_EREFS0_MASK | MCG_C2_HGO0_MASK | MCG_C2_RANGE0_MASK)

#define SIM_CLKDIV1_OUTDIV1_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)
#define SIM_CLKDIV1_OUTDIV2_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT)
#define SIM_CLKDIV1_OUTDIV3_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV3_MASK) >> SIM_CLKDIV1_OUTDIV3_SHIFT)
#define SIM_CLKDIV1_OUTDIV4_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT)
#define SIM_SOPT1_OSC32KSEL_VAL ((SIM->SOPT1 & SIM_SOPT1_OSC32KSEL_MASK) >> SIM_SOPT1_OSC32KSEL_SHIFT)
#define SIM_SOPT2_PLLFLLSEL_VAL ((SIM->SOPT2 & SIM_SOPT2_PLLFLLSEL_MASK) >> SIM_SOPT2_PLLFLLSEL_SHIFT)
#define SIM_CLKDIV3_PLLFLLDIV_VAL ((SIM->CLKDIV3 & SIM_CLKDIV3_PLLFLLDIV_MASK) >> SIM_CLKDIV3_PLLFLLDIV_SHIFT)
#define SIM_CLKDIV3_PLLFLLFRAC_VAL ((SIM->CLKDIV3 & SIM_CLKDIV3_PLLFLLFRAC_MASK) >> SIM_CLKDIV3_PLLFLLFRAC_SHIFT)

/* MCG_S_CLKST definition. */
enum _mcg_clkout_stat
{
    kMCG_ClkOutStatFll, /* FLL.            */
    kMCG_ClkOutStatInt, /* Internal clock. */
    kMCG_ClkOutStatExt, /* External clock. */
    kMCG_ClkOutStatPll  /* PLL.            */
};

/* MCG_S_PLLST definition. */
enum _mcg_pllst
{
    kMCG_PllstFll, /* FLL is used. */
    kMCG_PllstPll  /* PLL is used. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Slow internal reference clock frequency. */
static uint32_t s_slowIrcFreq = 32768U;
/* Fast internal reference clock frequency. */
static uint32_t s_fastIrcFreq = 4000000U;
/* The MCG external PLL clock frequency. */
static uint32_t s_extPllFreq = 0U;

/* External XTAL0 (OSC0) clock frequency. */
volatile uint32_t g_xtal0Freq;
/* External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the MCG external reference clock frequency.
 *
 * Get the current MCG external reference clock frequency in Hz. It is
 * the frequency select by MCG_C7[OSCSEL]. This is an internal function.
 *
 * @return MCG external reference clock frequency in Hz.
 */
static uint32_t CLOCK_GetMcgExtClkFreq(void);

/*!
 * @brief Get the MCG FLL external reference clock frequency.
 *
 * Get the current MCG FLL external reference clock frequency in Hz. It is
 * the frequency after by MCG_C1[FRDIV]. This is an internal function.
 *
 * @return MCG FLL external reference clock frequency in Hz.
 */
static uint32_t CLOCK_GetFllExtRefClkFreq(void);

/*!
 * @brief Get the MCG FLL reference clock frequency.
 *
 * Get the current MCG FLL reference clock frequency in Hz. It is
 * the frequency select by MCG_C1[IREFS]. This is an internal function.
 *
 * @return MCG FLL reference clock frequency in Hz.
 */
static uint32_t CLOCK_GetFllRefClkFreq(void);

/*!
 * @brief Get the frequency of clock selected by MCG_C2[IRCS].
 *
 * This clock's two output:
 *  1. MCGOUTCLK when MCG_S[CLKST]=0.
 *  2. MCGIRCLK when MCG_C1[IRCLKEN]=1.
 *
 * @return The frequency in Hz.
 */
static uint32_t CLOCK_GetInternalRefClkSelectFreq(void);

/*!
 * @brief Get the MCG PLL/PLL0 reference clock frequency.
 *
 * Get the current MCG PLL/PLL0 reference clock frequency in Hz.
 * This is an internal function.
 *
 * @return MCG PLL/PLL0 reference clock frequency in Hz.
 */
static uint32_t CLOCK_GetPll0RefFreq(void);

/*!
 * @brief Calculate the RANGE value base on crystal frequency.
 *
 * To setup external crystal oscillator, must set the register bits RANGE
 * base on the crystal frequency. This function returns the RANGE base on the
 * input frequency. This is an internal function.
 *
 * @param freq Crystal frequency in Hz.
 * @return The RANGE value.
 */
static uint8_t CLOCK_GetOscRangeFromFreq(uint32_t freq);

#ifndef MCG_USER_CONFIG_FLL_STABLE_DELAY_EN
/*!
 * @brief Delay function to wait FLL stable.
 *
 * Delay function to wait FLL stable in FEI mode or FEE mode, should wait at least
 * 1ms. Every time changes FLL setting, should wait this time for FLL stable.
 */
static void CLOCK_FllStableDelay(void);
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

#ifndef MCG_USER_CONFIG_FLL_STABLE_DELAY_EN
static void CLOCK_FllStableDelay(void)
{
    /*
       Should wait at least 1ms. Because in these modes, the core clock is 100MHz
       at most, so this function could obtain the 1ms delay.
     */
    volatile uint32_t i = 30000U;
    while (0U != (i--))
    {
        __NOP();
    }
}
#else  /* With MCG_USER_CONFIG_FLL_STABLE_DELAY_EN defined. */
/* Once user defines the MCG_USER_CONFIG_FLL_STABLE_DELAY_EN to use their own delay function, they have to
 * create their own CLOCK_FllStableDelay() function in application code. Since the clock functions in this
 * file would call the CLOCK_FllStableDelay() regardless how it is defined.
 */
extern void CLOCK_FllStableDelay(void);
#endif /* MCG_USER_CONFIG_FLL_STABLE_DELAY_EN */

static uint32_t CLOCK_GetMcgExtClkFreq(void)
{
    uint32_t freq;

    switch (MCG_C7_OSCSEL_VAL)
    {
        case 0U:
            /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
            assert(0U != g_xtal0Freq);
            freq = g_xtal0Freq;
            break;
        case 1U:
            /* Please call CLOCK_SetXtal32Freq base on board setting before using XTAL32K/RTC_CLKIN clock. */
            assert(0U != g_xtal32Freq);
            freq = g_xtal32Freq;
            break;
        case 2U:
            freq = MCG_INTERNAL_IRC_48M;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetFllExtRefClkFreq(void)
{
    /* FllExtRef = McgExtRef / FllExtRefDiv */
    uint8_t frdiv;
    uint8_t range;
    uint8_t oscsel;

    uint32_t freq = CLOCK_GetMcgExtClkFreq();

    frdiv = MCG_C1_FRDIV_VAL;
    freq >>= frdiv;

    range  = MCG_C2_RANGE_VAL;
    oscsel = MCG_C7_OSCSEL_VAL;

    /*
       When should use divider 32, 64, 128, 256, 512, 1024, 1280, 1536.
       1. MCG_C7[OSCSEL] selects IRC48M.
       2. MCG_C7[OSCSEL] selects OSC0 and MCG_C2[RANGE] is not 0.
    */
    if (((0U != range) && ((uint8_t)kMCG_OscselOsc == oscsel)) || ((uint8_t)kMCG_OscselIrc == oscsel))
    {
        switch (frdiv)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                freq >>= 5u;
                break;
            case 6:
                /* 64*20=1280 */
                freq /= 20u;
                break;
            case 7:
                /* 128*12=1536 */
                freq /= 12u;
                break;
            default:
                freq = 0u;
                break;
        }
    }

    return freq;
}

static uint32_t CLOCK_GetInternalRefClkSelectFreq(void)
{
    uint32_t freq;

    if ((uint8_t)kMCG_IrcSlow == MCG_S_IRCST_VAL)
    {
        /* Slow internal reference clock selected*/
        freq = s_slowIrcFreq;
    }
    else
    {
        /* Fast internal reference clock selected*/
        freq = s_fastIrcFreq >> MCG_SC_FCRDIV_VAL;
    }

    return freq;
}

static uint32_t CLOCK_GetFllRefClkFreq(void)
{
    uint32_t freq;

    /* If use external reference clock. */
    if ((uint8_t)kMCG_FllSrcExternal == MCG_S_IREFST_VAL)
    {
        freq = CLOCK_GetFllExtRefClkFreq();
    }
    /* If use internal reference clock. */
    else
    {
        freq = s_slowIrcFreq;
    }

    return freq;
}

static uint32_t CLOCK_GetPll0RefFreq(void)
{
    /* MCG external reference clock. */
    return CLOCK_GetMcgExtClkFreq();
}

static uint8_t CLOCK_GetOscRangeFromFreq(uint32_t freq)
{
    uint8_t range;

    if (freq <= 39063U)
    {
        range = 0U;
    }
    else if (freq <= 8000000U)
    {
        range = 1U;
    }
    else
    {
        range = 2U;
    }

    return range;
}

/*!
 * brief Get the OSC0 external reference undivided clock frequency (OSC0ERCLK_UNDIV).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkUndivFreq(void)
{
    uint32_t freq;
    if ((OSC0->CR & OSC_CR_ERCLKEN_MASK) != 0U)
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        freq = g_xtal0Freq;
    }
    else
    {
        freq = 0U;
    }
    return freq;
}

/*!
 * brief Get the OSC0 external reference divided clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkDivFreq(void)
{
    uint32_t freq;
    uint8_t temp;
    if ((OSC0->CR & OSC_CR_ERCLKEN_MASK) != 0U)
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        temp = OSC0->DIV & OSC_DIV_ERPS_MASK;
        freq = g_xtal0Freq >> ((temp) >> OSC_DIV_ERPS_SHIFT);
    }
    else
    {
        freq = 0U;
    }
    return freq;
}

/*!
 * brief Get the external reference 32K clock frequency (ERCLK32K).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetEr32kClkFreq(void)
{
    uint32_t freq;

    switch (SIM_SOPT1_OSC32KSEL_VAL)
    {
        case 0U: /* OSC 32k clock  */
            freq = (CLOCK_GetOsc0ErClkDivFreq() == 32768U) ? 32768U : 0U;
            break;
        case 2U: /* RTC 32k clock  */
            /* Please call CLOCK_SetXtal32Freq base on board setting before using XTAL32K/RTC_CLKIN clock. */
            assert(g_xtal32Freq);
            freq = g_xtal32Freq;
            break;
        case 3U: /* LPO clock      */
            freq = LPO_CLK_FREQ;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*!
 * brief Get the output clock frequency selected by SIM[PLLFLLSEL].
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPllFllSelClkFreq(void)
{
    uint32_t freq;

    switch (SIM_SOPT2_PLLFLLSEL_VAL)
    {
        case 0U: /* FLL. */
            freq = CLOCK_GetFllFreq();
            break;
        case 1U: /* PLL. */
            freq = CLOCK_GetPll0Freq();
            break;
        case 2U: /* USB1 PFD */
            freq = CLOCK_GetExtPllFreq();
            break;
        case 3U: /* MCG IRC48M. */
            freq = MCG_INTERNAL_IRC_48M;
            break;
        default:
            freq = 0U;
            break;
    }

    freq *= (SIM_CLKDIV3_PLLFLLFRAC_VAL + 1U);
    freq /= (SIM_CLKDIV3_PLLFLLDIV_VAL + 1U);
    return freq;
}

/*!
 * brief Get the OSC0 external reference clock frequency (OSC0ERCLK).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkFreq(void)
{
    return CLOCK_GetOsc0ErClkDivFreq();
}

/*!
 * brief Get the platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1UL);
}

/*!
 * brief Get the flash clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV4_VAL + 1UL);
}

/*!
 * brief Get the flexbus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlexBusClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV3_VAL + 1UL);
}

/*!
 * brief Get the bus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV2_VAL + 1UL);
}

/*!
 * brief Get the core clock or system clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1UL);
}

/*!
 * brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 * The MCG must be properly configured before using this function.
 *
 * param clockName Clock names defined in clock_name_t
 * return Clock frequency value in Hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
        case kCLOCK_PlatClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1UL);
            break;
        case kCLOCK_BusClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV2_VAL + 1UL);
            break;
        case kCLOCK_FlexBusClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV3_VAL + 1UL);
            break;
        case kCLOCK_FlashClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV4_VAL + 1UL);
            break;
        case kCLOCK_PllFllSelClk:
            freq = CLOCK_GetPllFllSelClkFreq();
            break;
        case kCLOCK_Er32kClk:
            freq = CLOCK_GetEr32kClkFreq();
            break;
        case kCLOCK_Osc0ErClk:
            freq = CLOCK_GetOsc0ErClkDivFreq();
            break;
        case kCLOCK_Osc0ErClkUndiv:
            freq = CLOCK_GetOsc0ErClkUndivFreq();
            break;
        case kCLOCK_McgFixedFreqClk:
            freq = CLOCK_GetFixedFreqClkFreq();
            break;
        case kCLOCK_McgInternalRefClk:
            freq = CLOCK_GetInternalRefClkFreq();
            break;
        case kCLOCK_McgFllClk:
            freq = CLOCK_GetFllFreq();
            break;
        case kCLOCK_McgPll0Clk:
            freq = CLOCK_GetPll0Freq();
            break;
        case kCLOCK_McgIrc48MClk:
            freq = MCG_INTERNAL_IRC_48M;
            break;
        case kCLOCK_LpoClk:
            freq = LPO_CLK_FREQ;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * brief Set the clock configure in SIM module.
 *
 * This function sets system layer clock settings in SIM module.
 *
 * param config Pointer to the configure structure.
 */
void CLOCK_SetSimConfig(sim_clock_config_t const *config)
{
    SIM->CLKDIV1 = config->clkdiv1;
    CLOCK_SetPllFllSelClock(config->pllFllSel, config->pllFllDiv, config->pllFllFrac);
    CLOCK_SetEr32kClock(config->er32kSrc);
}

/*! brief Enable USB FS clock.
 *
 * param src  USB FS clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB FS clock.
 */
bool CLOCK_EnableUsbfs0Clock(clock_usb_src_t src, uint32_t freq)
{
    /* In current implementation, USBPFDCLK is not used for USB FS. */
    assert(kCLOCK_UsbSrcUsbPfd != src);

    bool ret = true;

    CLOCK_DisableClock(kCLOCK_Usbfs0);

    if (kCLOCK_UsbSrcExt == src)
    {
        SIM->SOPT2 &= ~SIM_SOPT2_USBSRC_MASK;
    }
    else
    {
        switch (freq)
        {
            case 120000000U:
                SIM->CLKDIV2 = SIM_CLKDIV2_USBDIV(4) | SIM_CLKDIV2_USBFRAC(1);
                break;
            case 96000000U:
                SIM->CLKDIV2 = SIM_CLKDIV2_USBDIV(1) | SIM_CLKDIV2_USBFRAC(0);
                break;
            case 72000000U:
                SIM->CLKDIV2 = SIM_CLKDIV2_USBDIV(2) | SIM_CLKDIV2_USBFRAC(1);
                break;
            case 48000000U:
                SIM->CLKDIV2 = SIM_CLKDIV2_USBDIV(0) | SIM_CLKDIV2_USBFRAC(0);
                break;
            default:
                ret = false;
                break;
        }

        SIM->SOPT2 = ((SIM->SOPT2 & ~(SIM_SOPT2_PLLFLLSEL_MASK | SIM_SOPT2_USBSRC_MASK)) | (uint32_t)src);
    }

    CLOCK_EnableClock(kCLOCK_Usbfs0);

    if (kCLOCK_UsbSrcIrc48M == src)
    {
        USB0->CLK_RECOVER_IRC_EN = 0x03U;
        USB0->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;
    }
    return ret;
}

/*! brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * param src  USB HS does not care about the clock source, here must be ref kCLOCK_UsbSrcUnused.
 * param freq USB HS does not care about the clock source, so this parameter is ignored.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq)
{
    /* Source and freq are not used for USB HS. */
    src  = src;
    freq = freq;

    SIM->SCGC3 |= SIM_SCGC3_USBHS_MASK;

    SIM->USBPHYCTL = ((SIM->USBPHYCTL & ~(SIM_USBPHYCTL_USB3VOUTTRG_MASK)) | SIM_USBPHYCTL_USB3VOUTTRG(6U) /* 3.310V */
                      | SIM_USBPHYCTL_USBVREGSEL_MASK); /* VREG_IN1 */

    USBPHY->PLL_SIC |= USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK; /* Enable USB clock output from USB PHY PLL */

    return true;
}

/*! brief Disable USB HS clock.
 *
 * Disable USB HS clock, this function should not be called after
 * ref CLOCK_DisableUsbhs0PhyPllClock.
 */
void CLOCK_DisableUsbhs0Clock(void)
{
    USBPHY->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK; /* Disable USB clock output from USB PHY PLL */
    SIM->SCGC3 &= ~SIM_SCGC3_USBHS_MASK;
}

/*! brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * param src  USB HS PHY PLL clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq)
{
    volatile uint32_t i;
    uint32_t phyPllDiv = 0U;

    /*
     * In order to bring up the internal 480MHz USB PLL clock, should make sure:
     * 1. 32kHz IRC clock enable by setting IRCLKEN bit in MCG_C1 register.
     * 2. External reference clock enable on XTAL by setting ERCLKEN bit in OSC_CR register.
     */
    assert(MCG->C1 & MCG_C1_IRCLKEN_MASK);
    assert(0U == (MCG->C2 & MCG_C2_IRCS_MASK));
    assert(OSC0->CR & OSC_CR_ERCLKEN_MASK);

    if (24000000U == freq)
    {
        phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(0U);
    }
    else if (16000000U == freq)
    {
        phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(1U);
    }
    else if (12000000U == freq)
    {
        phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(2U);
    }
    else
    {
        return false;
    }

    /* Source and freq are not used for USB HS. */
    src = src;

    SIM->SCGC3 |= SIM_SCGC3_USBHSPHY_MASK;
    SIM->SOPT2 |= SIM_SOPT2_USBREGEN_MASK;

    i = 500000U;
    while ((i--) != 0UL)
    {
        __NOP();
    }

    USBPHY->TRIM_OVERRIDE_EN = 0x01U;                 /* Override the trim. */
    USBPHY->CTRL &= ~USBPHY_CTRL_SFTRST_MASK;         /* release PHY from reset */
    USBPHY->PLL_SIC |= USBPHY_PLL_SIC_PLL_POWER_MASK; /* power up PLL */
    USBPHY->PLL_SIC = (USBPHY->PLL_SIC & ~USBPHY_PLL_SIC_PLL_DIV_SEL_MASK) | phyPllDiv;
    USBPHY->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_BYPASS_MASK; /* Clear bypass bit */
    USBPHY->CTRL &= ~USBPHY_CTRL_CLKGATE_MASK;          /* Clear to 0U to run clocks */

    /* Wait for lock. */
    while ((USBPHY->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK) == 0UL)
    {
    }

    return true;
}

/*! brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void)
{
    USBPHY->CTRL |= USBPHY_CTRL_CLKGATE_MASK;          /* Set to 1U to gate clocks */
    USBPHY->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_POWER_MASK; /* Power down PLL */
    SIM->SOPT2 &= ~SIM_SOPT2_USBREGEN_MASK;
    SIM->SCGC3 &= ~SIM_SCGC3_USBHSPHY_MASK;
}

/*! brief Enable USB HS PFD clock.
 *
 * This function enables USB HS PFD clock. It should be called after function
 * ref CLOCK_EnableUsbhs0PhyPllClock.
 * The PFD output clock is selected by the parameter p src. When the p src is
 * ref kCLOCK_UsbPfdSrcExt, then the PFD outout is from external crystal
 * directly, in this case, the p frac is not used. In other cases, the PFD_FRAC
 * output clock frequency is 480MHz*18/frac, the PFD output frequency is based
 * on the PFD_FRAC output.
 *
 * param frac The value set to PFD_FRAC, it must be in the range of 18 to 35.
 * param src Source of the USB HS PFD clock (USB1PFDCLK).
 */
void CLOCK_EnableUsbhs0PfdClock(uint8_t frac, clock_usb_pfd_src_t src)
{
    assert((frac <= 35U) && (frac >= 18U));
    uint32_t fracFreq = (480000U * 18U / frac) * 1000U;

    USBPHY->ANACTRL = (USBPHY->ANACTRL & ~(USBPHY_ANACTRL_PFD_FRAC_MASK | USBPHY_ANACTRL_PFD_CLK_SEL_MASK)) |
                      (USBPHY_ANACTRL_PFD_FRAC(frac) | USBPHY_ANACTRL_PFD_CLK_SEL(src));

    USBPHY->ANACTRL &= ~USBPHY_ANACTRL_PFD_CLKGATE_MASK;
    while ((USBPHY->ANACTRL & USBPHY_ANACTRL_PFD_STABLE_MASK) == 0U)
    {
    }

    if (kCLOCK_UsbPfdSrcExt == src)
    {
        s_extPllFreq = g_xtal0Freq;
    }
    else if (kCLOCK_UsbPfdSrcFracDivBy4 == src)
    {
        s_extPllFreq = fracFreq / 4U;
    }
    else if (kCLOCK_UsbPfdSrcFracDivBy2 == src)
    {
        s_extPllFreq = fracFreq / 2U;
    }
    else
    {
        s_extPllFreq = fracFreq;
    }
}

/*! brief Disable USB HS PFD clock.
 *
 * This function disables USB HS PFD clock. It should be called before function
 * ref CLOCK_DisableUsbhs0PhyPllClock.
 */
void CLOCK_DisableUsbhs0PfdClock(void)
{
    USBPHY->ANACTRL |= USBPHY_ANACTRL_PFD_CLKGATE_MASK;
    s_extPllFreq = 0U;
}

/*!
 * brief Gets the MCG output clock (MCGOUTCLK) frequency.
 *
 * This function gets the MCG output clock frequency in Hz based on the current MCG
 * register value.
 *
 * return The frequency of MCGOUTCLK.
 */
uint32_t CLOCK_GetOutClkFreq(void)
{
    uint32_t mcgoutclk;
    uint32_t clkst  = (uint32_t)MCG_S_CLKST_VAL;
    uint32_t pllcst = MCG_S2_PLLCST_VAL;

    switch (clkst)
    {
        case (uint32_t)kMCG_ClkOutStatPll:
            switch (pllcst)
            {
                case (uint32_t)kMCG_PllClkSelExtPll:
                    mcgoutclk = CLOCK_GetExtPllFreq();
                    break;
                case (uint32_t)kMCG_PllClkSelPll0:
                    mcgoutclk = CLOCK_GetPll0Freq();
                    break;
                default:
                    mcgoutclk = 0U;
                    break;
            }
            break;
        case (uint32_t)kMCG_ClkOutStatFll:
            mcgoutclk = CLOCK_GetFllFreq();
            break;
        case (uint32_t)kMCG_ClkOutStatInt:
            mcgoutclk = CLOCK_GetInternalRefClkSelectFreq();
            break;
        case (uint32_t)kMCG_ClkOutStatExt:
            mcgoutclk = CLOCK_GetMcgExtClkFreq();
            break;
        default:
            mcgoutclk = 0U;
            break;
    }

    return mcgoutclk;
}

/*!
 * brief Gets the MCG FLL clock (MCGFLLCLK) frequency.
 *
 * This function gets the MCG FLL clock frequency in Hz based on the current MCG
 * register value. The FLL is enabled in FEI/FBI/FEE/FBE mode and
 * disabled in low power state in other modes.
 *
 * return The frequency of MCGFLLCLK.
 */
uint32_t CLOCK_GetFllFreq(void)
{
    static const uint16_t fllFactorTable[4][2] = {{640, 732}, {1280, 1464}, {1920, 2197}, {2560, 2929}};

    uint8_t drs, dmx32;
    uint32_t freq;
    uint32_t ret;

    /* If FLL is not enabled currently, then return 0U. */
    if ((((MCG->C2 & MCG_C2_LP_MASK) != 0U) || ((MCG->S & MCG_S_PLLST_MASK) != 0U)))
    {
        ret = 0U;
    }
    else
    {
        /* Get FLL reference clock frequency. */
        freq = CLOCK_GetFllRefClkFreq();
        if (0U == freq)
        {
            ret = freq;
        }
        else
        {
            drs   = MCG_C4_DRST_DRS_VAL;
            dmx32 = MCG_C4_DMX32_VAL;
            ret   = freq * fllFactorTable[drs][dmx32];
        }
    }

    return ret;
}

/*!
 * brief Gets the MCG internal reference clock (MCGIRCLK) frequency.
 *
 * This function gets the MCG internal reference clock frequency in Hz based
 * on the current MCG register value.
 *
 * return The frequency of MCGIRCLK.
 */
uint32_t CLOCK_GetInternalRefClkFreq(void)
{
    uint32_t freq;

    /* If MCGIRCLK is gated. */
    if (0U == (MCG->C1 & MCG_C1_IRCLKEN_MASK))
    {
        freq = 0U;
    }
    else
    {
        freq = CLOCK_GetInternalRefClkSelectFreq();
    }

    return freq;
}

/*!
 * brief Gets the MCG fixed frequency clock (MCGFFCLK) frequency.
 *
 * This function gets the MCG fixed frequency clock frequency in Hz based
 * on the current MCG register value.
 *
 * return The frequency of MCGFFCLK.
 */
uint32_t CLOCK_GetFixedFreqClkFreq(void)
{
    uint32_t freq = CLOCK_GetFllRefClkFreq();
    uint32_t ret;

    /* MCGFFCLK must be no more than MCGOUTCLK/8. */
    if ((freq <= (CLOCK_GetOutClkFreq() / 8U)) && (0U != freq))
    {
        ret = freq;
    }
    else
    {
        ret = 0U;
    }

    return ret;
}

/*!
 * brief Gets the MCG PLL0 clock (MCGPLL0CLK) frequency.
 *
 * This function gets the MCG PLL0 clock frequency in Hz based on the current MCG
 * register value.
 *
 * return The frequency of MCGPLL0CLK.
 */
uint32_t CLOCK_GetPll0Freq(void)
{
    uint32_t mcgpll0clk;
    uint32_t freq;

    uint8_t mcgpll0prdiv;
    uint8_t mcgpll0vdiv;
    /* If PLL0 is not enabled, return 0. */
    if (((MCG->S & MCG_S_LOCK0_MASK)) == 0U)
    {
        freq = 0U;
    }
    else
    {
        mcgpll0clk = CLOCK_GetPll0RefFreq();

        /*
         * Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock.
         * Please call CLOCK_SetXtal1Freq base on board setting before using OSC1 clock.
         */
        assert(mcgpll0clk);

        mcgpll0prdiv = ((uint8_t)FSL_FEATURE_MCG_PLL_PRDIV_BASE + MCG_C5_PRDIV0_VAL);
        mcgpll0clk /= (uint32_t)mcgpll0prdiv;
        mcgpll0vdiv = ((uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE + MCG_C6_VDIV0_VAL);
        mcgpll0clk *= (uint32_t)mcgpll0vdiv;

        mcgpll0clk >>= 1UL;
        freq = mcgpll0clk;
    }

    return freq;
}

/*!
 * brief Gets the MCG external PLL frequency.
 *
 * This function gets the MCG external PLL frequency in Hz.
 *
 * return The frequency of the MCG external PLL.
 */
uint32_t CLOCK_GetExtPllFreq(void)
{
    return s_extPllFreq;
}

/*!
 * brief Sets the MCG external PLL frequency.
 *
 * This function sets the MCG external PLL frequency in Hz. The MCG external PLL
 * frequency is passed to the MCG driver using this function. Call this
 * function after the external PLL frequency is changed. Otherwise, the APIs, which are used to get
 * the frequency, may return an incorrect value.
 *
 * param The frequency of MCG external PLL.
 */
void CLOCK_SetExtPllFreq(uint32_t freq)
{
    s_extPllFreq = freq;
}

/*!
 * brief Selects the MCG external reference clock.
 *
 * Selects the MCG external reference clock source, changes the MCG_C7[OSCSEL],
 * and waits for the clock source to be stable. Because the external reference
 * clock should not be changed in FEE/FBE/BLPE/PBE/PEE modes, do not call this function in these modes.
 *
 * param oscsel MCG external reference clock source, MCG_C7[OSCSEL].
 * retval kStatus_MCG_SourceUsed Because the external reference clock is used as a clock source,
 * the configuration should not be changed. Otherwise, a glitch occurs.
 * retval kStatus_Success External reference clock set successfully.
 */
status_t CLOCK_SetExternalRefClkConfig(mcg_oscsel_t oscsel)
{
    bool needDelay;
    uint32_t i;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    /* If change MCG_C7[OSCSEL] and external reference clock is system clock source, return error. */
    if ((MCG_C7_OSCSEL_VAL != oscsel) && (!(MCG->S & MCG_S_IREFST_MASK)))
    {
        return kStatus_MCG_SourceUsed;
    }
#endif /* MCG_CONFIG_CHECK_PARAM */

    if (MCG_C7_OSCSEL_VAL != (uint8_t)oscsel)
    {
        /* If change OSCSEL, need to delay, ERR009878. */
        needDelay = true;
    }
    else
    {
        needDelay = false;
    }

    MCG->C7 = (uint8_t)(MCG->C7 & ~MCG_C7_OSCSEL_MASK) | MCG_C7_OSCSEL(oscsel);
    if (needDelay)
    {
        /* ERR009878 Delay at least 50 micro-seconds for external clock change valid. */
        i = 1500U;
        while (0U != (i--))
        {
            __NOP();
        }
    }

    return kStatus_Success;
}

/*!
 * brief Configures the Internal Reference clock (MCGIRCLK).
 *
 * This function sets the \c MCGIRCLK base on parameters. It also selects the IRC
 * source. If the fast IRC is used, this function sets the fast IRC divider.
 * This function also sets whether the \c MCGIRCLK is enabled in stop mode.
 * Calling this function in FBI/PBI/BLPI modes may change the system clock. As a result,
 * using the function in these modes it is not allowed.
 *
 * param enableMode MCGIRCLK enable mode, OR'ed value of ref _mcg_irclk_enable_mode.
 * param ircs       MCGIRCLK clock source, choose fast or slow.
 * param fcrdiv     Fast IRC divider setting (\c FCRDIV).
 * retval kStatus_MCG_SourceUsed Because the internal reference clock is used as a clock source,
 * the configuration should not be changed. Otherwise, a glitch occurs.
 * retval kStatus_Success MCGIRCLK configuration finished successfully.
 */
status_t CLOCK_SetInternalRefClkConfig(uint8_t enableMode, mcg_irc_mode_t ircs, uint8_t fcrdiv)
{
    uint32_t mcgOutClkState = (uint32_t)MCG_S_CLKST_VAL;
    mcg_irc_mode_t curIrcs  = (mcg_irc_mode_t)((uint32_t)MCG_S_IRCST_VAL);
    uint8_t curFcrdiv       = MCG_SC_FCRDIV_VAL;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    /* If MCGIRCLK is used as system clock source. */
    if ((uint32_t)kMCG_ClkOutStatInt == mcgOutClkState)
    {
        /* If need to change MCGIRCLK source or driver, return error. */
        if (((kMCG_IrcFast == curIrcs) && (fcrdiv != curFcrdiv)) || (ircs != curIrcs))
        {
            return kStatus_MCG_SourceUsed;
        }
    }
#endif

    /* If need to update the FCRDIV. */
    if (fcrdiv != curFcrdiv)
    {
        /* If fast IRC is in use currently, change to slow IRC. */
        if (((0U != (MCG->C1 & MCG_C1_IRCLKEN_MASK)) || (mcgOutClkState == (uint32_t)kMCG_ClkOutStatInt)) &&
            (kMCG_IrcFast == curIrcs))
        {
            MCG->C2 = (uint8_t)((MCG->C2 & ~MCG_C2_IRCS_MASK) | (MCG_C2_IRCS(kMCG_IrcSlow)));
            while (MCG_S_IRCST_VAL != (uint8_t)kMCG_IrcSlow)
            {
            }
        }
        /* Update FCRDIV. */
        MCG->SC =
            (uint8_t)(MCG->SC & ~(MCG_SC_FCRDIV_MASK | MCG_SC_ATMF_MASK | MCG_SC_LOCS0_MASK)) | MCG_SC_FCRDIV(fcrdiv);
    }

    /* Set internal reference clock selection. */
    MCG->C2 = (uint8_t)((MCG->C2 & ~MCG_C2_IRCS_MASK) | (MCG_C2_IRCS(ircs)));
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK)) | (uint8_t)enableMode);

    /* If MCGIRCLK is used, need to wait for MCG_S_IRCST. */
    if ((mcgOutClkState == (uint32_t)kMCG_ClkOutStatInt) || (0U != (enableMode & (uint32_t)kMCG_IrclkEnable)))
    {
        while (MCG_S_IRCST_VAL != (uint8_t)ircs)
        {
        }
    }

    return kStatus_Success;
}

/*!
 * brief Calculates the PLL divider setting for a desired output frequency.
 *
 * This function calculates the correct reference clock divider (\c PRDIV) and
 * VCO divider (\c VDIV) to generate a desired PLL output frequency. It returns the
 * closest frequency match with the corresponding \c PRDIV/VDIV
 * returned from parameters. If a desired frequency is not valid, this function
 * returns 0.
 *
 * param refFreq    PLL reference clock frequency.
 * param desireFreq Desired PLL output frequency.
 * param prdiv      PRDIV value to generate desired PLL frequency.
 * param vdiv       VDIV value to generate desired PLL frequency.
 * return Closest frequency match that the PLL was able generate.
 */
uint32_t CLOCK_CalcPllDiv(uint32_t refFreq, uint32_t desireFreq, uint8_t *prdiv, uint8_t *vdiv)
{
    uint8_t ret_prdiv;               /* PRDIV to return. */
    uint8_t ret_vdiv;                /* VDIV to return.  */
    uint8_t prdiv_min;               /* Min PRDIV value to make reference clock in allowed range. */
    uint8_t prdiv_max;               /* Max PRDIV value to make reference clock in allowed range. */
    uint8_t prdiv_cur;               /* PRDIV value for iteration.    */
    uint8_t vdiv_cur;                /* VDIV value for iteration.     */
    uint32_t ret_freq = 0U;          /* PLL output frequency to return. */
    uint32_t diff     = 0xFFFFFFFFU; /* Difference between desireFreq and return frequency. */
    uint32_t ref_div;                /* Reference frequency after PRDIV. */

    /*
       Steps:
       1. Get allowed prdiv with such rules:
          1). refFreq / prdiv >= FSL_FEATURE_MCG_PLL_REF_MIN.
          2). refFreq / prdiv <= FSL_FEATURE_MCG_PLL_REF_MAX.
       2. For each allowed prdiv, there are two candidate vdiv values:
          1). (desireFreq / (refFreq / prdiv)).
          2). (desireFreq / (refFreq / prdiv)) + 1.
          If could get the precise desired frequency, return current prdiv and
          vdiv directly. Otherwise choose the one which is closer to desired
          frequency.
     */

    /* Reference frequency is out of range. */
    if ((refFreq < (uint32_t)FSL_FEATURE_MCG_PLL_REF_MIN) ||
        (refFreq > ((uint32_t)FSL_FEATURE_MCG_PLL_REF_MAX *
                    ((uint32_t)FSL_FEATURE_MCG_PLL_PRDIV_MAX + (uint32_t)FSL_FEATURE_MCG_PLL_PRDIV_BASE))))
    {
        return 0U;
    }

    /* refFreq/PRDIV must in a range. First get the allowed PRDIV range. */
    prdiv_max = (uint8_t)(refFreq / (uint32_t)FSL_FEATURE_MCG_PLL_REF_MIN);
    prdiv_min =
        (uint8_t)((refFreq + (uint32_t)FSL_FEATURE_MCG_PLL_REF_MAX - 1U) / (uint32_t)FSL_FEATURE_MCG_PLL_REF_MAX);

    desireFreq *= 2U;

    /* PRDIV traversal. */
    for (prdiv_cur = prdiv_max; prdiv_cur >= prdiv_min; prdiv_cur--)
    {
        /* Reference frequency after PRDIV. */
        ref_div = refFreq / prdiv_cur;

        vdiv_cur = (uint8_t)(desireFreq / ref_div);

        if ((vdiv_cur < ((uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE - 1U)) ||
            (vdiv_cur > (uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE + 31U))
        {
            /* No VDIV is available with this PRDIV. */
            continue;
        }

        ret_freq = vdiv_cur * ref_div;

        if (vdiv_cur >= (uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE)
        {
            if (ret_freq == desireFreq) /* If desire frequency is got. */
            {
                *prdiv = prdiv_cur - (uint8_t)FSL_FEATURE_MCG_PLL_PRDIV_BASE;
                *vdiv  = vdiv_cur - (uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE;
                return ret_freq / 2U;
            }
            /* New PRDIV/VDIV is closer. */
            if (diff > desireFreq - ret_freq)
            {
                diff      = desireFreq - ret_freq;
                ret_prdiv = prdiv_cur;
                ret_vdiv  = vdiv_cur;
            }
        }
        vdiv_cur++;
        if (vdiv_cur <= ((uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE + 31U))
        {
            ret_freq += ref_div;
            /* New PRDIV/VDIV is closer. */
            if (diff > ret_freq - desireFreq)
            {
                diff      = ret_freq - desireFreq;
                ret_prdiv = prdiv_cur;
                ret_vdiv  = vdiv_cur;
            }
        }
    }

    if (0xFFFFFFFFU != diff)
    {
        /* PRDIV/VDIV found. */
        *prdiv   = ret_prdiv - (uint8_t)FSL_FEATURE_MCG_PLL_PRDIV_BASE;
        *vdiv    = ret_vdiv - (uint8_t)FSL_FEATURE_MCG_PLL_VDIV_BASE;
        ret_freq = (refFreq / ret_prdiv) * ret_vdiv;
        return ret_freq / 2U;
    }
    else
    {
        /* No proper PRDIV/VDIV found. */
        return 0U;
    }
}

/*!
 * brief Enables the PLL0 in FLL mode.
 *
 * This function sets us the PLL0 in FLL mode and reconfigures
 * the PLL0. Ensure that the PLL reference
 * clock is enabled before calling this function and that the PLL0 is not used as a clock source.
 * The function CLOCK_CalcPllDiv gets the correct PLL
 * divider values.
 *
 * param config Pointer to the configuration structure.
 */
void CLOCK_EnablePll0(mcg_pll_config_t const *config)
{
    assert(config);

    uint8_t mcg_c5 = 0U;

    mcg_c5 |= MCG_C5_PRDIV0(config->prdiv);
    MCG->C5 = mcg_c5; /* Disable the PLL first. */

    MCG->C6 = (uint8_t)((MCG->C6 & ~MCG_C6_VDIV0_MASK) | MCG_C6_VDIV0(config->vdiv));

    /* Set enable mode. */
    MCG->C5 |= ((uint8_t)kMCG_PllEnableIndependent | (uint8_t)config->enableMode);

    /* Wait for PLL lock. */
    while (((MCG->S & MCG_S_LOCK0_MASK)) == 0U)
    {
    }
}

/*!
 * brief Set the PLL selection.
 *
 * This function sets the PLL selection between PLL0/PLL1/EXTPLL, and waits for
 * change finished.
 *
 * param pllcs The PLL to select.
 */
void CLOCK_SetPllClkSel(mcg_pll_clk_select_t pllcs)
{
    MCG->C11 = (uint8_t)(((MCG->C11 & ~MCG_C11_PLLCS_MASK)) | MCG_C11_PLLCS(pllcs));
    while ((uint32_t)pllcs != MCG_S2_PLLCST_VAL)
    {
    }
}

/*!
 * brief Sets the OSC0 clock monitor mode.
 *
 * This function sets the OSC0 clock monitor mode. See ref mcg_monitor_mode_t for details.
 *
 * param mode Monitor mode to set.
 */
void CLOCK_SetOsc0MonitorMode(mcg_monitor_mode_t mode)
{
    /* Clear the previous flag, MCG_SC[LOCS0]. */
    MCG->SC &= ~(uint8_t)MCG_SC_ATMF_MASK;

    if (kMCG_MonitorNone == mode)
    {
        MCG->C6 &= ~(uint8_t)MCG_C6_CME0_MASK;
    }
    else
    {
        if (kMCG_MonitorInt == mode)
        {
            MCG->C2 &= ~(uint8_t)MCG_C2_LOCRE0_MASK;
        }
        else
        {
            MCG->C2 |= MCG_C2_LOCRE0_MASK;
        }
        MCG->C6 |= MCG_C6_CME0_MASK;
    }
}

/*!
 * brief Sets the RTC OSC clock monitor mode.
 *
 * This function sets the RTC OSC clock monitor mode. See ref mcg_monitor_mode_t for details.
 *
 * param mode Monitor mode to set.
 */
void CLOCK_SetRtcOscMonitorMode(mcg_monitor_mode_t mode)
{
    uint8_t mcg_c8 = MCG->C8;

    mcg_c8 &= ~(uint8_t)(MCG_C8_CME1_MASK | MCG_C8_LOCRE1_MASK);

    if (kMCG_MonitorNone != mode)
    {
        if (kMCG_MonitorReset == mode)
        {
            mcg_c8 |= MCG_C8_LOCRE1_MASK;
        }
        mcg_c8 |= MCG_C8_CME1_MASK;
    }
    MCG->C8 = mcg_c8;
}

/*!
 * brief Sets the PLL0 clock monitor mode.
 *
 * This function sets the PLL0 clock monitor mode. See ref mcg_monitor_mode_t for details.
 *
 * param mode Monitor mode to set.
 */
void CLOCK_SetPll0MonitorMode(mcg_monitor_mode_t mode)
{
    uint8_t mcg_c8;

    /* Clear previous flag. */
    MCG->S = MCG_S_LOLS0_MASK;

    if (kMCG_MonitorNone == mode)
    {
        MCG->C6 &= (uint8_t)(~MCG_C6_LOLIE0_MASK);
    }
    else
    {
        mcg_c8 = MCG->C8;

        mcg_c8 &= (uint8_t)(~MCG_C8_LOCS1_MASK);

        if (kMCG_MonitorInt == mode)
        {
            mcg_c8 &= (uint8_t)(~MCG_C8_LOLRE_MASK);
        }
        else
        {
            mcg_c8 |= MCG_C8_LOLRE_MASK;
        }
        MCG->C8 = mcg_c8;
        MCG->C6 |= MCG_C6_LOLIE0_MASK;
    }
}

/*!
 * brief Sets the external PLL clock monitor mode.
 *
 * This function ets the external PLL clock monitor mode. See ref mcg_monitor_mode_t
 * for details.
 *
 * param mode Monitor mode to set.
 */
void CLOCK_SetExtPllMonitorMode(mcg_monitor_mode_t mode)
{
    uint8_t mcg_c9 = MCG->C9;

    mcg_c9 &= (uint8_t)(~(MCG_C9_PLL_LOCRE_MASK | MCG_C9_PLL_CME_MASK));

    if (kMCG_MonitorNone != mode)
    {
        if (kMCG_MonitorReset == mode)
        {
            mcg_c9 |= MCG_C9_PLL_LOCRE_MASK;
        }
        mcg_c9 |= MCG_C9_PLL_CME_MASK;
    }
    MCG->C9 = mcg_c9;
}

/*!
 * brief Gets the MCG status flags.
 *
 * This function gets the MCG clock status flags. All status flags are
 * returned as a logical OR of the enumeration ref _mcg_status_flags_t. To
 * check a specific flag, compare the return value with the flag.
 *
 * Example:
 * code
 * To check the clock lost lock status of OSC0 and PLL0.
 * uint32_t mcgFlags;
 *
 * mcgFlags = CLOCK_GetStatusFlags();
 *
 * if (mcgFlags & kMCG_Osc0LostFlag)
 * {
 *     OSC0 clock lock lost. Do something.
 * }
 * if (mcgFlags & kMCG_Pll0LostFlag)
 * {
 *     PLL0 clock lock lost. Do something.
 * }
 * endcode
 *
 * return  Logical OR value of the ref _mcg_status_flags_t.
 */
uint32_t CLOCK_GetStatusFlags(void)
{
    uint32_t ret  = 0U;
    uint8_t mcg_s = MCG->S;

    if ((MCG->SC & MCG_SC_LOCS0_MASK) != 0U)
    {
        ret |= (uint32_t)kMCG_Osc0LostFlag;
    }
    if ((mcg_s & MCG_S_OSCINIT0_MASK) != 0U)
    {
        ret |= (uint32_t)kMCG_Osc0InitFlag;
    }
    if (0U != (MCG->C8 & MCG_C8_LOCS1_MASK))
    {
        ret |= (uint32_t)kMCG_RtcOscLostFlag;
    }
    if ((mcg_s & MCG_S_LOLS0_MASK) != 0U)
    {
        ret |= (uint32_t)kMCG_Pll0LostFlag;
    }
    if ((mcg_s & MCG_S_LOCK0_MASK) != 0U)
    {
        ret |= (uint32_t)kMCG_Pll0LockFlag;
    }
    if ((MCG->C9 & MCG_C9_EXT_PLL_LOCS_MASK) != 0U)
    {
        ret |= (uint32_t)kMCG_ExtPllLostFlag;
    }
    return ret;
}

/*!
 * brief Clears the MCG status flags.
 *
 * This function clears the MCG clock lock lost status. The parameter is a logical
 * OR value of the flags to clear. See ref _mcg_status_flags_t.
 *
 * Example:
 * code
 * To clear the clock lost lock status flags of OSC0 and PLL0.
 *
 * CLOCK_ClearStatusFlags(kMCG_Osc0LostFlag | kMCG_Pll0LostFlag);
 * endcode
 *
 * param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ref _mcg_status_flags_t.
 */
void CLOCK_ClearStatusFlags(uint32_t mask)
{
    uint8_t reg;

    if ((mask & (uint32_t)kMCG_Osc0LostFlag) != 0UL)
    {
        MCG->SC &= (uint8_t)(~MCG_SC_ATMF_MASK);
    }
    if (0U != (mask & (uint32_t)kMCG_RtcOscLostFlag))
    {
        reg     = MCG->C8;
        MCG->C8 = reg;
    }
    if ((mask & (uint32_t)kMCG_Pll0LostFlag) != 0UL)
    {
        MCG->S = MCG_S_LOLS0_MASK;
    }
    if ((mask & (uint32_t)kMCG_ExtPllLostFlag) != 0UL)
    {
        reg     = MCG->C9;
        MCG->C9 = reg;
    }
}

/*!
 * brief Initializes the OSC0.
 *
 * This function initializes the OSC0 according to the board configuration.
 *
 * param  config Pointer to the OSC0 configuration structure.
 */
void CLOCK_InitOsc0(osc_config_t const *config)
{
    uint8_t range = CLOCK_GetOscRangeFromFreq(config->freq);

    OSC_SetCapLoad(OSC0, config->capLoad);

    MCG->C2 = (uint8_t)((MCG->C2 & ~OSC_MODE_MASK) | MCG_C2_RANGE(range) | (uint8_t)config->workMode);
    OSC_SetExtRefClkConfig(OSC0, &config->oscerConfig);

    if ((kOSC_ModeExt != config->workMode) && ((OSC0->CR & OSC_CR_ERCLKEN_MASK) != 0U))
    {
        /* Wait for stable. */
        while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
        {
        }
    }
}

/*!
 * brief Deinitializes the OSC0.
 *
 * This function deinitializes the OSC0.
 */
void CLOCK_DeinitOsc0(void)
{
    OSC0->CR = 0U;
    MCG->C2 &= ~(uint8_t)OSC_MODE_MASK;
}

/*!
 * brief Set the Slow IRC frequency based on the trimmed value
 *
 * param freq The Slow IRC frequency input clock frequency in Hz.
 */
void CLOCK_SetSlowIrcFreq(uint32_t freq)
{
    s_slowIrcFreq = freq;
}

/*!
 * brief Set the Fast IRC frequency based on the trimmed value
 *
 * param freq The Fast IRC frequency input clock frequency in Hz.
 */
void CLOCK_SetFastIrcFreq(uint32_t freq)
{
    s_fastIrcFreq = freq;
}

/*!
 * brief Auto trims the internal reference clock.
 *
 * This function trims the internal reference clock by using the external clock. If
 * successful, it returns the kStatus_Success and the frequency after
 * trimming is received in the parameter p actualFreq. If an error occurs,
 * the error code is returned.
 *
 * param extFreq      External clock frequency, which should be a bus clock.
 * param desireFreq   Frequency to trim to.
 * param actualFreq   Actual frequency after trimming.
 * param atms         Trim fast or slow internal reference clock.
 * retval kStatus_Success ATM success.
 * retval kStatus_MCG_AtmBusClockInvalid The bus clock is not in allowed range for the ATM.
 * retval kStatus_MCG_AtmDesiredFreqInvalid MCGIRCLK could not be trimmed to the desired frequency.
 * retval kStatus_MCG_AtmIrcUsed Could not trim because MCGIRCLK is used as a bus clock source.
 * retval kStatus_MCG_AtmHardwareFail Hardware fails while trimming.
 */
status_t CLOCK_TrimInternalRefClk(uint32_t extFreq, uint32_t desireFreq, uint32_t *actualFreq, mcg_atm_select_t atms)
{
    uint32_t multi; /* extFreq / desireFreq */
    uint32_t actv;  /* Auto trim value. */
    uint8_t mcg_sc;
    status_t status = kStatus_Success;

    static const uint32_t trimRange[2][2] = {
        /*     Min           Max      */
        {TRIM_SIRC_MIN, TRIM_SIRC_MAX}, /* Slow IRC. */
        {TRIM_FIRC_MIN, TRIM_FIRC_MAX}  /* Fast IRC. */
    };

    if ((extFreq > TRIM_REF_CLK_MAX) || (extFreq < TRIM_REF_CLK_MIN))
    {
        status = kStatus_MCG_AtmBusClockInvalid;
    }
    /* Check desired frequency range. */
    else if ((desireFreq < trimRange[atms][0]) || (desireFreq > trimRange[atms][1]))
    {
        status = kStatus_MCG_AtmDesiredFreqInvalid;
    }
    /*
       Make sure internal reference clock is not used to generate bus clock.
       Here only need to check (MCG_S_IREFST == 1).
     */
    else if (MCG_S_IREFST(kMCG_FllSrcInternal) == (MCG->S & MCG_S_IREFST_MASK))
    {
        status = kStatus_MCG_AtmIrcUsed;
    }
    else
    {
        multi = extFreq / desireFreq;
        actv  = multi * 21U;

        if (kMCG_AtmSel4m == atms)
        {
            actv *= 128U;
        }

        /* Now begin to start trim. */
        MCG->ATCVL = (uint8_t)actv;
        MCG->ATCVH = (uint8_t)(actv >> 8U);

        mcg_sc = MCG->SC;
        mcg_sc &= ~(uint8_t)(MCG_SC_ATMS_MASK | MCG_SC_LOCS0_MASK);
        mcg_sc |= (MCG_SC_ATMF_MASK | MCG_SC_ATMS(atms));
        MCG->SC = (mcg_sc | MCG_SC_ATME_MASK);

        /* Wait for MCG finished. */
        while (0U != (MCG->SC & MCG_SC_ATME_MASK))
        {
        }

        /* Error occurs? */
        if (0U != (MCG->SC & MCG_SC_ATMF_MASK))
        {
            /* Clear the failed flag. */
            MCG->SC = mcg_sc;
            status  = kStatus_MCG_AtmHardwareFail;
        }
        else
        {
            *actualFreq = extFreq / multi;

            if (kMCG_AtmSel4m == atms)
            {
                s_fastIrcFreq = *actualFreq;
            }
            else
            {
                s_slowIrcFreq = *actualFreq;
            }
        }
    }

    return status;
}

/*!
 * brief Gets the current MCG mode.
 *
 * This function checks the MCG registers and determines the current MCG mode.
 *
 * return Current MCG mode or error code; See ref mcg_mode_t.
 */
mcg_mode_t CLOCK_GetMode(void)
{
    mcg_mode_t mode = kMCG_ModeError;
    uint32_t clkst  = (uint32_t)MCG_S_CLKST_VAL;
    uint32_t irefst = (uint32_t)MCG_S_IREFST_VAL;
    uint32_t lp     = (uint32_t)MCG_C2_LP_VAL;
    uint32_t pllst  = MCG_S_PLLST_VAL;

    /*------------------------------------------------------------------
                           Mode and Registers
    ____________________________________________________________________

      Mode   |   CLKST    |   IREFST   |   PLLST   |      LP
    ____________________________________________________________________

      FEI    |  00(FLL)   |   1(INT)   |   0(FLL)  |      X
    ____________________________________________________________________

      FEE    |  00(FLL)   |   0(EXT)   |   0(FLL)  |      X
    ____________________________________________________________________

      FBE    |  10(EXT)   |   0(EXT)   |   0(FLL)  |   0(NORMAL)
    ____________________________________________________________________

      FBI    |  01(INT)   |   1(INT)   |   0(FLL)  |   0(NORMAL)
    ____________________________________________________________________

      BLPI   |  01(INT)   |   1(INT)   |   0(FLL)  |   1(LOW POWER)
    ____________________________________________________________________

      BLPE   |  10(EXT)   |   0(EXT)   |     X     |   1(LOW POWER)
    ____________________________________________________________________

      PEE    |  11(PLL)   |   0(EXT)   |   1(PLL)  |      X
    ____________________________________________________________________

      PBE    |  10(EXT)   |   0(EXT)   |   1(PLL)  |   O(NORMAL)
    ____________________________________________________________________

      PBI    |  01(INT)   |   1(INT)   |   1(PLL)  |   0(NORMAL)
    ____________________________________________________________________

      PEI    |  11(PLL)   |   1(INT)   |   1(PLL)  |      X
    ____________________________________________________________________

    ----------------------------------------------------------------------*/

    if (clkst == (uint32_t)kMCG_ClkOutStatFll)
    {
        if ((uint32_t)kMCG_FllSrcExternal == irefst)
        {
            mode = kMCG_ModeFEE;
        }
        else
        {
            mode = kMCG_ModeFEI;
        }
    }
    else if (clkst == (uint32_t)kMCG_ClkOutStatInt)
    {
        if (0U != lp)
        {
            mode = kMCG_ModeBLPI;
        }
        else
        {
            {
                mode = kMCG_ModeFBI;
            }
        }
    }
    else if (clkst == (uint32_t)kMCG_ClkOutStatExt)
    {
        if (0U != lp)
        {
            mode = kMCG_ModeBLPE;
        }
        else
        {
            if ((uint32_t)kMCG_PllstPll == pllst)
            {
                mode = kMCG_ModePBE;
            }
            else
            {
                mode = kMCG_ModeFBE;
            }
        }
    }
    else if (clkst == (uint32_t)kMCG_ClkOutStatPll)
    {
        {
            mode = kMCG_ModePEE;
        }
    }
    else
    {
        /*do nothing*/
    }

    return mode;
}

/*!
 * brief Sets the MCG to FEI mode.
 *
 * This function sets the MCG to FEI mode. If setting to FEI mode fails
 * from the current mode, this function returns an error.
 *
 * param       dmx32  DMX32 in FEI mode.
 * param       drs The DCO range selection.
 * param       fllStableDelay Delay function to  ensure that the FLL is stable. Passing
 *              NULL does not cause a delay.
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 * note If p dmx32 is set to kMCG_Dmx32Fine, the slow IRC must not be trimmed
 * to a frequency above 32768 Hz.
 */
status_t CLOCK_SetFeiMode(mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    mcg_mode_t mode = CLOCK_GetMode();
    if (!((kMCG_ModeFEI == mode) || (kMCG_ModeFBI == mode) || (kMCG_ModeFBE == mode) || (kMCG_ModeFEE == mode)))
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif
    mcg_c4 = MCG->C4;

    /*
       Errata: ERR007993
       Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
       reference clock source changes, then reset to previous value after
       reference clock changes.
     */
    if ((uint8_t)kMCG_FllSrcExternal == MCG_S_IREFST_VAL)
    {
        change_drs = true;
        /* Change the LSB of DRST_DRS. */
        MCG->C4 ^= (1U << MCG_C4_DRST_DRS_SHIFT);
    }

    /* Set CLKS and IREFS. */
    MCG->C1 = (uint8_t)(((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK))) |
                        (MCG_C1_CLKS(kMCG_ClkOutSrcOut)         /* CLKS = 0 */
                         | MCG_C1_IREFS(kMCG_FllSrcInternal))); /* IREFS = 1 */

    /* Wait and check status. */
    while ((uint8_t)kMCG_FllSrcInternal != MCG_S_IREFST_VAL)
    {
    }

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG->C4 = mcg_c4;
    }

    /* In FEI mode, the MCG_C4[DMX32] is set to 0U. */
    MCG->C4 = (uint8_t)((mcg_c4 & ~(MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) |
                        (MCG_C4_DMX32(dmx32) | MCG_C4_DRST_DRS(drs)));

    /* Check MCG_S[CLKST] */
    while ((uint8_t)kMCG_ClkOutStatFll != MCG_S_CLKST_VAL)
    {
    }

    /* Wait for FLL stable time. */
    if (NULL != fllStableDelay)
    {
        fllStableDelay();
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to FEE mode.
 *
 * This function sets the MCG to FEE mode. If setting to FEE mode fails
 * from the current mode, this function returns an error.
 *
 * param   frdiv  FLL reference clock divider setting, FRDIV.
 * param   dmx32  DMX32 in FEE mode.
 * param   drs    The DCO range selection.
 * param   fllStableDelay Delay function to make sure FLL is stable. Passing
 *          NULL does not cause a delay.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetFeeMode(uint8_t frdiv, mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    mcg_mode_t mode = CLOCK_GetMode();
    if (!((kMCG_ModeFEE == mode) || (kMCG_ModeFBI == mode) || (kMCG_ModeFBE == mode) || (kMCG_ModeFEI == mode)))
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif
    mcg_c4 = MCG->C4;

    /*
       Errata: ERR007993
       Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
       reference clock source changes, then reset to previous value after
       reference clock changes.
     */
    if ((uint8_t)kMCG_FllSrcInternal == MCG_S_IREFST_VAL)
    {
        change_drs = true;
        /* Change the LSB of DRST_DRS. */
        MCG->C4 ^= (1U << MCG_C4_DRST_DRS_SHIFT);
    }

    /* Set CLKS and IREFS. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK)) |
                        (MCG_C1_CLKS(kMCG_ClkOutSrcOut)         /* CLKS = 0 */
                         | MCG_C1_FRDIV(frdiv)                  /* FRDIV */
                         | MCG_C1_IREFS(kMCG_FllSrcExternal))); /* IREFS = 0 */

    /* If use external crystal as clock source, wait for it stable. */
    if (MCG_C7_OSCSEL(kMCG_OscselOsc) == (MCG->C7 & MCG_C7_OSCSEL_MASK))
    {
        if (0U != (MCG->C2 & MCG_C2_EREFS_MASK))
        {
            while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
            {
            }
        }
    }

    /* Wait and check status. */
    while ((uint8_t)kMCG_FllSrcExternal != MCG_S_IREFST_VAL)
    {
    }

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG->C4 = mcg_c4;
    }

    /* Set DRS and DMX32. */
    mcg_c4  = (uint8_t)((mcg_c4 & ~(MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) |
                       (MCG_C4_DMX32(dmx32) | MCG_C4_DRST_DRS(drs)));
    MCG->C4 = mcg_c4;

    /* Wait for DRST_DRS update. */
    while (MCG->C4 != mcg_c4)
    {
    }

    /* Check MCG_S[CLKST] */
    while ((uint8_t)kMCG_ClkOutStatFll != MCG_S_CLKST_VAL)
    {
    }

    /* Wait for FLL stable time. */
    if (NULL != fllStableDelay)
    {
        fllStableDelay();
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to FBI mode.
 *
 * This function sets the MCG to FBI mode. If setting to FBI mode fails
 * from the current mode, this function returns an error.
 *
 * param  dmx32  DMX32 in FBI mode.
 * param  drs  The DCO range selection.
 * param  fllStableDelay Delay function to make sure FLL is stable. If the FLL
 *         is not used in FBI mode, this parameter can be NULL. Passing
 *         NULL does not cause a delay.
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 * note If p dmx32 is set to kMCG_Dmx32Fine, the slow IRC must not be trimmed
 * to frequency above 32768 Hz.
 */
status_t CLOCK_SetFbiMode(mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    mcg_mode_t mode = CLOCK_GetMode();

    if (!((kMCG_ModeFEE == mode) || (kMCG_ModeFBI == mode) || (kMCG_ModeFBE == mode) || (kMCG_ModeFEI == mode) ||
          (kMCG_ModeBLPI == mode)))

    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif

    mcg_c4 = MCG->C4;

    MCG->C2 &= ~(uint8_t)MCG_C2_LP_MASK; /* Disable lowpower. */

    /*
       Errata: ERR007993
       Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
       reference clock source changes, then reset to previous value after
       reference clock changes.
     */
    if ((uint8_t)kMCG_FllSrcExternal == MCG_S_IREFST_VAL)
    {
        change_drs = true;
        /* Change the LSB of DRST_DRS. */
        MCG->C4 ^= (1U << MCG_C4_DRST_DRS_SHIFT);
    }

    /* Set CLKS and IREFS. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) |
                        (MCG_C1_CLKS(kMCG_ClkOutSrcInternal)    /* CLKS = 1 */
                         | MCG_C1_IREFS(kMCG_FllSrcInternal))); /* IREFS = 1 */

    /* Wait and check status. */
    while ((uint8_t)kMCG_FllSrcInternal != MCG_S_IREFST_VAL)
    {
    }

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG->C4 = mcg_c4;
    }

    while ((uint8_t)kMCG_ClkOutStatInt != MCG_S_CLKST_VAL)
    {
    }

    MCG->C4 = (uint8_t)((mcg_c4 & ~(MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) |
                        (MCG_C4_DMX32(dmx32) | MCG_C4_DRST_DRS(drs)));

    /* Wait for FLL stable time. */
    if (NULL != fllStableDelay)
    {
        fllStableDelay();
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to FBE mode.
 *
 * This function sets the MCG to FBE mode. If setting to FBE mode fails
 * from the current mode, this function returns an error.
 *
 * param   frdiv  FLL reference clock divider setting, FRDIV.
 * param   dmx32  DMX32 in FBE mode.
 * param   drs    The DCO range selection.
 * param   fllStableDelay Delay function to make sure FLL is stable. If the FLL
 *          is not used in FBE mode, this parameter can be NULL. Passing NULL
 *          does not cause a delay.
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetFbeMode(uint8_t frdiv, mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    mcg_mode_t mode = CLOCK_GetMode();
    if (!((kMCG_ModeFEE == mode) || (kMCG_ModeFBI == mode) || (kMCG_ModeFBE == mode) || (kMCG_ModeFEI == mode) ||
          (kMCG_ModePBE == mode) || (kMCG_ModeBLPE == mode)))
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif

    /* Change to FLL mode. */
    MCG->C6 &= ~(uint8_t)MCG_C6_PLLS_MASK;
    while ((MCG->S & MCG_S_PLLST_MASK) != 0U)
    {
    }

    /* Set LP bit to enable the FLL */
    MCG->C2 &= ~(uint8_t)MCG_C2_LP_MASK;

    mcg_c4 = MCG->C4;

    /*
       Errata: ERR007993
       Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
       reference clock source changes, then reset to previous value after
       reference clock changes.
     */
    if ((uint8_t)kMCG_FllSrcInternal == MCG_S_IREFST_VAL)
    {
        change_drs = true;
        /* Change the LSB of DRST_DRS. */
        MCG->C4 ^= (1U << MCG_C4_DRST_DRS_SHIFT);
    }

    /* Set CLKS and IREFS. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK)) |
                        (MCG_C1_CLKS(kMCG_ClkOutSrcExternal)    /* CLKS = 2 */
                         | MCG_C1_FRDIV(frdiv)                  /* FRDIV = frdiv */
                         | MCG_C1_IREFS(kMCG_FllSrcExternal))); /* IREFS = 0 */

    /* If use external crystal as clock source, wait for it stable. */
    if (MCG_C7_OSCSEL(kMCG_OscselOsc) == (MCG->C7 & MCG_C7_OSCSEL_MASK))
    {
        if (0U != (MCG->C2 & MCG_C2_EREFS_MASK))
        {
            while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
            {
            }
        }
    }

    /* Wait for Reference clock Status bit to clear */
    while ((uint8_t)kMCG_FllSrcExternal != MCG_S_IREFST_VAL)
    {
    }

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG->C4 = mcg_c4;
    }

    /* Set DRST_DRS and DMX32. */
    mcg_c4 = (uint8_t)((mcg_c4 & ~(MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) |
                       (MCG_C4_DMX32(dmx32) | MCG_C4_DRST_DRS(drs)));
    MCG->C4 = mcg_c4;

    /* Wait for clock status bits to show clock source is ext ref clk */
    while ((uint8_t)kMCG_ClkOutStatExt != MCG_S_CLKST_VAL)
    {
    }

    /* Wait for fll stable time. */
    if (NULL != fllStableDelay)
    {
        fllStableDelay();
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to BLPI mode.
 *
 * This function sets the MCG to BLPI mode. If setting to BLPI mode fails
 * from the current mode, this function returns an error.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetBlpiMode(void)
{
#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    if (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatInt)
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif /* MCG_CONFIG_CHECK_PARAM */

    /* Set LP. */
    MCG->C2 |= MCG_C2_LP_MASK;

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to BLPE mode.
 *
 * This function sets the MCG to BLPE mode. If setting to BLPE mode fails
 * from the current mode, this function returns an error.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetBlpeMode(void)
{
#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    if (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatExt)
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif

    /* Set LP bit to enter BLPE mode. */
    MCG->C2 |= MCG_C2_LP_MASK;

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to PBE mode.
 *
 * This function sets the MCG to PBE mode. If setting to PBE mode fails
 * from the current mode, this function returns an error.
 *
 * param   pllcs  The PLL selection, PLLCS.
 * param   config Pointer to the PLL configuration.
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 *
 * note
 * 1. The parameter \c pllcs selects the PLL. For platforms with
 * only one PLL, the parameter pllcs is kept for interface compatibility.
 * 2. The parameter \c config is the PLL configuration structure. On some
 * platforms,  it is possible to choose the external PLL directly, which renders the
 * configuration structure not necessary. In this case, pass in NULL.
 * For example: CLOCK_SetPbeMode(kMCG_OscselOsc, kMCG_PllClkSelExtPll, NULL);
 */
status_t CLOCK_SetPbeMode(mcg_pll_clk_select_t pllcs, mcg_pll_config_t const *config)
{
    /* If external PLL is used, then the config could be NULL. */
    if (kMCG_PllClkSelExtPll != pllcs)
    {
        assert(config);
    }

    /*
       This function is designed to change MCG to PBE mode from PEE/BLPE/FBE,
       but with this workflow, the source mode could be all modes except PEI/PBI.
     */
    MCG->C2 &= (uint8_t)(~MCG_C2_LP_MASK); /* Disable lowpower. */

    /* Change to use external clock first. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) | MCG_C1_CLKS(kMCG_ClkOutSrcExternal));

    /* Wait for CLKST clock status bits to show clock source is ext ref clk */
    while ((MCG->S & (MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) !=
           (MCG_S_IREFST(kMCG_FllSrcExternal) | MCG_S_CLKST(kMCG_ClkOutStatExt)))
    {
    }

    /* Disable PLL first, then configure PLL. */
    MCG->C6 &= (uint8_t)(~MCG_C6_PLLS_MASK);
    while ((MCG->S & MCG_S_PLLST_MASK) != 0U)
    {
    }

    /* Configure the PLL. */
    if (kMCG_PllClkSelPll0 == pllcs)
    {
        CLOCK_EnablePll0(config);
    }

    /* Change to PLL mode. */
    MCG->C6 |= MCG_C6_PLLS_MASK;

    MCG->C11 = (uint8_t)(((MCG->C11 & ~MCG_C11_PLLCS_MASK)) | MCG_C11_PLLCS(pllcs));
    while ((uint32_t)pllcs != MCG_S2_PLLCST_VAL)
    {
    }

    /* Wait for PLL mode changed. */
    while (((MCG->S & MCG_S_PLLST_MASK)) == 0U)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to PEE mode.
 *
 * This function sets the MCG to PEE mode.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 *
 * note This function only changes the CLKS to use the PLL/FLL output. If the
 *       PRDIV/VDIV are different than in the PBE mode, set them up
 *       in PBE mode and wait. When the clock is stable, switch to PEE mode.
 */
status_t CLOCK_SetPeeMode(void)
{
#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    mcg_mode_t mode = CLOCK_GetMode();
    if (kMCG_ModePBE != mode)
    {
        return kStatus_MCG_ModeUnreachable;
    }
#endif

    /* Change to use PLL/FLL output clock first. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcOut));

    /* Wait for clock status bits to update */
    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatPll)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Switches the MCG to FBE mode from the external mode.
 *
 * This function switches the MCG from external modes (PEE/PBE/BLPE/FEE) to the FBE mode quickly.
 * The external clock is used as the system clock source and PLL is disabled. However,
 * the FLL settings are not configured. This is a lite function with a small code size, which is useful
 * during the mode switch. For example, to switch from PEE mode to FEI mode:
 *
 * code
 * CLOCK_ExternalModeToFbeModeQuick();
 * CLOCK_SetFeiMode(...);
 * endcode
 *
 * retval kStatus_Success Switched successfully.
 * retval kStatus_MCG_ModeInvalid If the current mode is not an external mode, do not call this function.
 */
status_t CLOCK_ExternalModeToFbeModeQuick(void)
{
#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    if ((MCG->S & MCG_S_IREFST_MASK) != 0U)
    {
        return kStatus_MCG_ModeInvalid;
    }
#endif /* MCG_CONFIG_CHECK_PARAM */

    /* Disable low power */
    MCG->C2 &= (uint8_t)(~MCG_C2_LP_MASK);

    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcExternal));
    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatExt)
    {
    }

    /* Disable PLL. */
    MCG->C6 &= ~(uint8_t)MCG_C6_PLLS_MASK;
    while ((MCG->S & MCG_S_PLLST_MASK) != 0U)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Switches the MCG to FBI mode from internal modes.
 *
 * This function switches the MCG from internal modes (PEI/PBI/BLPI/FEI) to the FBI mode quickly.
 * The MCGIRCLK is used as the system clock source and PLL is disabled. However,
 * FLL settings are not configured. This is a lite function with a small code size, which is useful
 * during the mode switch. For example, to switch from PEI mode to FEE mode:
 *
 * code
 * CLOCK_InternalModeToFbiModeQuick();
 * CLOCK_SetFeeMode(...);
 * endcode
 *
 * retval kStatus_Success Switched successfully.
 * retval kStatus_MCG_ModeInvalid If the current mode is not an internal mode, do not call this function.
 */
status_t CLOCK_InternalModeToFbiModeQuick(void)
{
#if (defined(MCG_CONFIG_CHECK_PARAM) && MCG_CONFIG_CHECK_PARAM)
    if ((MCG->S & MCG_S_IREFST_MASK) == 0U)
    {
        return kStatus_MCG_ModeInvalid;
    }
#endif

    /* Disable low power */
    MCG->C2 &= ~(uint8_t)MCG_C2_LP_MASK;

    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcInternal));
    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatInt)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to FEI mode during system boot up.
 *
 * This function sets the MCG to FEI mode from the reset mode. It can also be used to
 * set up MCG during system boot up.
 *
 * param  dmx32  DMX32 in FEI mode.
 * param  drs The DCO range selection.
 * param  fllStableDelay Delay function to ensure that the FLL is stable.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 * note If p dmx32 is set to kMCG_Dmx32Fine, the slow IRC must not be trimmed
 * to frequency above 32768 Hz.
 */
status_t CLOCK_BootToFeiMode(mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    return CLOCK_SetFeiMode(dmx32, drs, fllStableDelay);
}

/*!
 * brief Sets the MCG to FEE mode during system bootup.
 *
 * This function sets MCG to FEE mode from the reset mode. It can also be used to
 * set up the MCG during system boot up.
 *
 * param   oscsel OSC clock select, OSCSEL.
 * param   frdiv  FLL reference clock divider setting, FRDIV.
 * param   dmx32  DMX32 in FEE mode.
 * param   drs    The DCO range selection.
 * param   fllStableDelay Delay function to ensure that the FLL is stable.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToFeeMode(
    mcg_oscsel_t oscsel, uint8_t frdiv, mcg_dmx32_t dmx32, mcg_drs_t drs, void (*fllStableDelay)(void))
{
    (void)CLOCK_SetExternalRefClkConfig(oscsel);

    return CLOCK_SetFeeMode(frdiv, dmx32, drs, fllStableDelay);
}

/*!
 * brief Sets the MCG to BLPI mode during system boot up.
 *
 * This function sets the MCG to BLPI mode from the reset mode. It can also be used to
 * set up the MCG during system boot up.
 *
 * param  fcrdiv Fast IRC divider, FCRDIV.
 * param  ircs   The internal reference clock to select, IRCS.
 * param  ircEnableMode  The MCGIRCLK enable mode, OR'ed value of ref _mcg_irclk_enable_mode.
 *
 * retval kStatus_MCG_SourceUsed Could not change MCGIRCLK setting.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToBlpiMode(uint8_t fcrdiv, mcg_irc_mode_t ircs, uint8_t ircEnableMode)
{
    /* If reset mode is FEI mode, set MCGIRCLK and always success. */
    (void)CLOCK_SetInternalRefClkConfig(ircEnableMode, ircs, fcrdiv);

    /* If reset mode is not BLPI, first enter FBI mode. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcInternal));
    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatInt)
    {
    }

    /* Enter BLPI mode. */
    MCG->C2 |= MCG_C2_LP_MASK;

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to BLPE mode during system boot up.
 *
 * This function sets the MCG to BLPE mode from the reset mode. It can also be used to
 * set up the MCG during system boot up.
 *
 * param  oscsel OSC clock select, MCG_C7[OSCSEL].
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToBlpeMode(mcg_oscsel_t oscsel)
{
    (void)CLOCK_SetExternalRefClkConfig(oscsel);

    /* Set to FBE mode. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)) |
                        (MCG_C1_CLKS(kMCG_ClkOutSrcExternal)    /* CLKS = 2 */
                         | MCG_C1_IREFS(kMCG_FllSrcExternal))); /* IREFS = 0 */

    /* If use external crystal as clock source, wait for it stable. */
    if (MCG_C7_OSCSEL(kMCG_OscselOsc) == (MCG->C7 & MCG_C7_OSCSEL_MASK))
    {
        if (0U != (MCG->C2 & MCG_C2_EREFS_MASK))
        {
            while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
            {
            }
        }
    }

    /* Wait for MCG_S[CLKST] and MCG_S[IREFST]. */
    while ((MCG->S & (MCG_S_IREFST_MASK | MCG_S_CLKST_MASK)) !=
           (MCG_S_IREFST(kMCG_FllSrcExternal) | MCG_S_CLKST(kMCG_ClkOutStatExt)))
    {
    }

    /* In FBE now, start to enter BLPE. */
    MCG->C2 |= MCG_C2_LP_MASK;

    return kStatus_Success;
}

/*!
 * brief Sets the MCG to PEE mode during system boot up.
 *
 * This function sets the MCG to PEE mode from reset mode. It can also be used to
 * set up the MCG during system boot up.
 *
 * param   oscsel OSC clock select, MCG_C7[OSCSEL].
 * param   pllcs  The PLL selection, PLLCS.
 * param   config Pointer to the PLL configuration.
 *
 * retval kStatus_MCG_ModeUnreachable Could not switch to the target mode.
 * retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToPeeMode(mcg_oscsel_t oscsel, mcg_pll_clk_select_t pllcs, mcg_pll_config_t const *config)
{
    /* If external PLL is used, then the config could be NULL. */
    if (kMCG_PllClkSelExtPll != pllcs)
    {
        assert(config);
    }

    (void)CLOCK_SetExternalRefClkConfig(oscsel);

    (void)CLOCK_SetPbeMode(pllcs, config);

    /* Change to use PLL output clock. */
    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcOut));
    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatPll)
    {
    }

    return kStatus_Success;
}

/*
   The transaction matrix. It defines the path for mode switch, the row is for
   current mode and the column is target mode.
   For example, switch from FEI to PEE:
   1. Current mode FEI, next mode is mcgModeMatrix[FEI][PEE] = FBE, so swith to FBE.
   2. Current mode FBE, next mode is mcgModeMatrix[FBE][PEE] = PBE, so swith to PBE.
   3. Current mode PBE, next mode is mcgModeMatrix[PBE][PEE] = PEE, so swith to PEE.
   Thus the MCG mode has changed from FEI to PEE.
 */
static const mcg_mode_t mcgModeMatrix[8][8] = {
    {kMCG_ModeFEI, kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeFEE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE,
     kMCG_ModeFBE}, /* FEI */
    {kMCG_ModeFEI, kMCG_ModeFBI, kMCG_ModeBLPI, kMCG_ModeFEE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE,
     kMCG_ModeFBE}, /* FBI */
    {kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeBLPI, kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeFBI,
     kMCG_ModeFBI}, /* BLPI */
    {kMCG_ModeFEI, kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeFEE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE,
     kMCG_ModeFBE}, /* FEE */
    {kMCG_ModeFEI, kMCG_ModeFBI, kMCG_ModeFBI, kMCG_ModeFEE, kMCG_ModeFBE, kMCG_ModeBLPE, kMCG_ModePBE,
     kMCG_ModePBE}, /* FBE */
    {kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeBLPE, kMCG_ModePBE,
     kMCG_ModePBE}, /* BLPE */
    {kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeFBE, kMCG_ModeBLPE, kMCG_ModePBE,
     kMCG_ModePEE}, /* PBE */
    {kMCG_ModePBE, kMCG_ModePBE, kMCG_ModePBE, kMCG_ModePBE, kMCG_ModePBE, kMCG_ModePBE, kMCG_ModePBE,
     kMCG_ModePBE} /* PEE */
    /*    FEI           FBI           BLPI           FEE           FBE           BLPE           PBE           PEE */
};

/*!
 * brief Sets the MCG to a target mode.
 *
 * This function sets MCG to a target mode defined by the configuration
 * structure. If switching to the target mode fails, this function
 * chooses the correct path.
 *
 * param  config Pointer to the target MCG mode configuration structure.
 * return Return kStatus_Success if switched successfully; Otherwise, it returns an error code #_mcg_status.
 *
 * note If the external clock is used in the target mode, ensure that it is
 * enabled. For example, if the OSC0 is used, set up OSC0 correctly before calling this
 * function.
 */
status_t CLOCK_SetMcgConfig(const mcg_config_t *config)
{
    mcg_mode_t next_mode;
    status_t status = kStatus_Success;

    mcg_pll_clk_select_t pllcs = config->pllcs;

    /* If need to change external clock, MCG_C7[OSCSEL]. */
    if (MCG_C7_OSCSEL_VAL != (uint8_t)(config->oscsel))
    {
        /* If external clock is in use, change to FEI first. */
        if ((uint8_t)kMCG_FllSrcExternal == MCG_S_IREFST_VAL)
        {
            (void)CLOCK_ExternalModeToFbeModeQuick();
            (void)CLOCK_SetFeiMode(config->dmx32, config->drs, NULL);
        }

        (void)CLOCK_SetExternalRefClkConfig(config->oscsel);
    }

    /* Re-configure MCGIRCLK, if MCGIRCLK is used as system clock source, then change to FEI/PEI first. */
    if (MCG_S_CLKST_VAL == (uint8_t)kMCG_ClkOutStatInt)
    {
        MCG->C2 &= ~(uint8_t)MCG_C2_LP_MASK; /* Disable lowpower. */

        {
            (void)CLOCK_SetFeiMode(config->dmx32, config->drs, CLOCK_FllStableDelay);
        }
    }

    /* Configure MCGIRCLK. */
    (void)CLOCK_SetInternalRefClkConfig(config->irclkEnableMode, config->ircs, config->fcrdiv);

    next_mode = CLOCK_GetMode();

    do
    {
        next_mode = mcgModeMatrix[next_mode][config->mcgMode];

        switch (next_mode)
        {
            case kMCG_ModeFEI:
                status = CLOCK_SetFeiMode(config->dmx32, config->drs, CLOCK_FllStableDelay);
                break;
            case kMCG_ModeFEE:
                status = CLOCK_SetFeeMode(config->frdiv, config->dmx32, config->drs, CLOCK_FllStableDelay);
                break;
            case kMCG_ModeFBI:
                status = CLOCK_SetFbiMode(config->dmx32, config->drs, NULL);
                break;
            case kMCG_ModeFBE:
                status = CLOCK_SetFbeMode(config->frdiv, config->dmx32, config->drs, NULL);
                break;
            case kMCG_ModeBLPI:
                status = CLOCK_SetBlpiMode();
                break;
            case kMCG_ModeBLPE:
                status = CLOCK_SetBlpeMode();
                break;
            case kMCG_ModePBE:
                /* If target mode is not PBE or PEE, then only need to set CLKS = EXT here. */
                if ((kMCG_ModePEE == config->mcgMode) || (kMCG_ModePBE == config->mcgMode))
                {
                    if (kMCG_PllClkSelPll0 == pllcs)
                    {
                        status = CLOCK_SetPbeMode(pllcs, &config->pll0Config);
                    }
                    else if (kMCG_PllClkSelExtPll == pllcs)
                    {
                        status = CLOCK_SetPbeMode(pllcs, NULL);
                    }
                    else
                    {
                        /* Add comment to prevent the case of MISRA C-2012 rule 15.7 */
                    }
                }
                else
                {
                    MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCG_ClkOutSrcExternal));
                    while (MCG_S_CLKST_VAL != (uint8_t)kMCG_ClkOutStatExt)
                    {
                    }
                }
                break;
            case kMCG_ModePEE:
                status = CLOCK_SetPeeMode();
                break;
            default:
                assert(false);
                break;
        }
        if (kStatus_Success != status)
        {
            break;
        }
    } while (next_mode != config->mcgMode);

    if (status == kStatus_Success)
    {
        if ((config->pll0Config.enableMode & (uint8_t)kMCG_PllEnableIndependent) != 0U)
        {
            CLOCK_EnablePll0(&config->pll0Config);
        }
        else
        {
            MCG->C5 &= ~(uint8_t)kMCG_PllEnableIndependent;
        }
    }

    return status;
}
