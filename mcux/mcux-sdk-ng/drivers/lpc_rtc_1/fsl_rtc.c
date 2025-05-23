/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_rtc_1"
#endif

#define SECONDS_IN_A_DAY    (86400U)
#define SECONDS_IN_A_HOUR   (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR      (365U)
#define YEAR_RANGE_START    (1970U)
#define YEAR_RANGE_END      (2099U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 *@brief Wait for RTC register is ready to write/read.
 *
 *@note This API must be called if access to RTC registers.
 *
 */
static void RTC_WaitForBusSyncReady(void);

/*!
 * @brief Checks whether the date and time passed in is valid
 *
 * @param datetime Pointer to structure where the date and time details are stored
 *
 * @return Returns false if the date & time details are out of range; true if in range
 */
static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from datetime to seconds
 *
 * @param datetime Pointer to datetime structure where the date and time details are stored
 *
 * @return The result of the conversion in seconds
 */
static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from seconds to a datetime structure
 *
 * @param seconds  Seconds value that needs to be converted to datetime format
 * @param datetime Pointer to the datetime structure where the result of the conversion is stored
 */
static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Wait for the RTC register is ready to read/write. */
static void RTC_WaitForBusSyncReady(void)
{
    uint8_t timeOut = 0U;

    while ((0U == (RTC->ACCSTAT & RTC_ACCSTAT_READY_MASK)) && (timeOut < RTC_SYNC_TIME_OUT_TICKS))
    {
        timeOut++;
    }

    /* Check access, if timeout occurred, please try to raise the value of RTC_SYNC_TIME_OUT_TICKS. */
    assert(RTC->ACCSTAT & RTC_ACCSTAT_READY_MASK);
}

/*!
 *brief Write value to RTC register.
 *
 *note This API will write data to RTC register, all bus synchornous operation will be done.
 *
 */
void RTC_WriteRegister(__IO uint32_t *reg, uint32_t value)
{
    RTC_WaitForBusSyncReady();
    *reg = value;
    RTC_WaitForBusSyncReady();
}

/*!
 * brief Enable the sleep count down auto Start.
 *
 * param base   RTC peripheral base address
 * param enable 1 for enable, 0 for disable.
 */
void RTC_EnableSleepAutoStart(RTC_Type *base, bool enable)
{
    uint32_t reg = 0U;

    if (enable)
    {
        reg = RTC_ReadRegister(&base->CR);
        reg |= RTC_CR_AUTOSTART_MASK;
        RTC_WriteRegister(&base->CR, reg);
    }
    else
    {
        reg = RTC_ReadRegister(&base->CR);
        reg &= ~RTC_CR_AUTOSTART_MASK;
        RTC_WriteRegister(&base->CR, reg);
    }
}

/*!
 *brief Read data from RTC register.
 *
 *note This API will read the RTC's register value.
 *
 */
uint32_t RTC_ReadRegister(__I uint32_t *reg)
{
    uint32_t tmp = 0U;

    RTC_WaitForBusSyncReady();
    tmp = *reg;
    RTC_WaitForBusSyncReady();
    tmp = *reg;
    return tmp;
}

static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Check year, month, hour, minute, seconds */
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) || (datetime->month > 12U) ||
        (datetime->month < 1U) || (datetime->hour >= 24U) || (datetime->minute >= 60U) || (datetime->second >= 60U))
    {
        /* If not correct then error*/
        return false;
    }

    /* Adjust the days in February for a leap year */
    if ((((datetime->year & 3U) == 0) && (datetime->year % 100 != 0)) || (datetime->year % 400 == 0))
    {
        daysPerMonth[2] = 29U;
    }

    /* Check the validity of the day */
    if ((datetime->day > daysPerMonth[datetime->month]) || (datetime->day < 1U))
    {
        return false;
    }

    return true;
}

static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Number of days from begin of the non Leap-year*/
    /* Number of days from begin of the non Leap-year*/
    uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
    uint32_t seconds;

    /* Compute number of days from 1970 till given year*/
    seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    seconds += ((datetime->year / 4) - (1970U / 4));
    /* Add number of days till given month*/
    seconds += monthDays[datetime->month];
    /* Add days in given month. We subtract the current day as it is
     * represented in the hours, minutes and seconds field*/
    seconds += (datetime->day - 1);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
    {
        seconds--;
    }

    seconds = (seconds * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
              (datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

    return seconds;
}

static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime)
{
    assert(datetime);

    uint32_t x;
    uint32_t secondsRemaining, days;
    uint16_t daysInYear;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_IN_A_DAY + 1;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour   = secondsRemaining / SECONDS_IN_A_HOUR;
    secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
    datetime->minute = secondsRemaining / 60U;
    datetime->second = secondsRemaining % SECONDS_IN_A_MINUTE;

    /* Calculate year */
    daysInYear     = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > daysInYear)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year++;

        /* Adjust the number of days for a leap year */
        if (datetime->year & 3U)
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_YEAR + 1;
        }
    }

    /* Adjust the days in February for a leap year */
    if (!(datetime->year & 3U))
    {
        daysPerMonth[2] = 29U;
    }

    for (x = 1U; x <= 12U; x++)
    {
        if (days <= daysPerMonth[x])
        {
            datetime->month = x;
            break;
        }
        else
        {
            days -= daysPerMonth[x];
        }
    }

    datetime->day = days;
}

/*!
 * brief Initalize the RTC mudule.
 *
 * note This API should be called at the beginning of the application using the RTC driver.
 *       This API will help configure the calibration value, count down auto start, enable RTC timer
 *       and the initialized date for counting.
 *
 * param base RTC peripheral base address
 * param config  configuration for initializing RTC.
 */
void RTC_Init(RTC_Type *base, rtc_config_t *config)
{
    uint32_t reg = 0U;

    if (config->enableTimer)
    {
        reg |= RTC_CR_EN_MASK;
    }
    if (config->enableAutoStart)
    {
        reg |= RTC_CR_AUTOSTART_MASK;
    }

    RTC_WriteRegister(&base->CR, reg);

    /* Set calibration value. */
    RTC_WriteRegister(&base->CAL, config->calibrationValue);

    /* Set Date value. */
    RTC_SetDatetime(base, &config->date);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the RTC peripheral clock */
    CLOCK_EnableClock(kCLOCK_Rtc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get default config for RTC setting.
 *        This configure structure will help setup calibration value, formated date value.
 *        And set if enable RTC timer and count down auto start function.
 *
 * param base RTC peripheral base address
 * param config configure structure for setting RTC module. refer to rtc_config_t.
 */
void RTC_GetDefaultConfig(RTC_Type *base, rtc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    memset(config, 0, sizeof(*config));

    config->enableTimer      = false;
    config->enableAutoStart  = true;
    config->calibrationValue = 32768U;
    config->date.year        = 1970U;
    config->date.month       = 1U;
    config->date.day         = 1U;
    config->date.hour        = 0U;
    config->date.minute      = 0U;
    config->date.second      = 0U;
}

/*!
 * brief Sets the RTC date and time according to the given time structure.
 *
 * The RTC counter must be stopped prior to calling this function as writes to the RTC
 * seconds register will fail if the RTC counter is running.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to structure where the date and time details to set are stored
 *
 * return kStatus_Success: Success in setting the time and starting the RTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_SetDatetime(RTC_Type *base, const rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Return error if the time provided is not valid */
    if (!(RTC_CheckDatetimeFormat(datetime)))
    {
        return kStatus_InvalidArgument;
    }

    /* Set time in seconds */
    RTC_WriteRegister(&(base->TIME), RTC_ConvertDatetimeToSeconds(datetime));

    return kStatus_Success;
}

/*!
 * brief Gets the RTC time and stores it in the given time structure.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to structure where the date and time details are stored.
 */
void RTC_GetDatetime(RTC_Type *base, rtc_datetime_t *datetime)
{
    assert(datetime);

    uint32_t seconds = 0;

    seconds = RTC_ReadRegister(&base->TIME);

    RTC_ConvertSecondsToDatetime(seconds, datetime);
}
