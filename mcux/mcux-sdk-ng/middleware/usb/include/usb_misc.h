/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_MISC_H__
#define __USB_MISC_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define big endian */
#define USB_BIG_ENDIAN (0U)
/*! @brief Define little endian */
#define USB_LITTLE_ENDIAN (1U)

/*! @brief Define current endian */
#ifndef ENDIANNESS
#define ENDIANNESS USB_LITTLE_ENDIAN
#endif
/*! @brief Define default timeout value */
#if (defined(USE_RTOS) && (USE_RTOS > 0))
#define USB_OSA_WAIT_TIMEOUT (osaWaitForever_c)
#else
#define USB_OSA_WAIT_TIMEOUT (0U)
#endif /* (defined(USE_RTOS) && (USE_RTOS > 0)) */

/*! @brief Define USB printf */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

extern int DbgConsole_Printf(const char *fmt_s, ...);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @brief Definition to select sdk or toolchain printf, scanf. */
#ifndef SDK_DEBUGCONSOLE
#define SDK_DEBUGCONSOLE 1U
#endif

/*! @brief 0U: DEBUGCONSOLE_REDIRECT_TO_TOOLCHAIN, 1U: DEBUGCONSOLE_REDIRECT_TO_SDK, 2U: DEBUGCONSOLE_DISABLE*/
#if defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE == 0U)
#define usb_echo printf
#elif defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE == 1U)
#define usb_echo DbgConsole_Printf
#elif defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE == 2U)
static inline int USB_DbgConsole_Disabled(void)
{
    return -1;
}
#define usb_echo(...) USB_DbgConsole_Disabled()
#endif

#if defined(__ICCARM__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED __packed
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED
#endif

#elif defined(__GNUC__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED __attribute__((__packed__))
#endif

#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION))

#ifndef STRUCT_PACKED
#define STRUCT_PACKED _Pragma("pack(1U)")
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED _Pragma("pack()")
#endif

#elif (defined(__DSC__) || defined(__CW__))

#ifndef STRUCT_PACKED
#define STRUCT_PACKED
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED __attribute__((packed))
#endif
#endif

#define USB_SHORT_GET_LOW(x)  (((uint16_t)x) & 0xFFU)
#define USB_SHORT_GET_HIGH(x) ((uint8_t)(((uint16_t)x) >> 8U) & 0xFFU)

#define USB_LONG_GET_BYTE0(x) ((uint8_t)(((uint32_t)(x))) & 0xFFU)
#define USB_LONG_GET_BYTE1(x) ((uint8_t)(((uint32_t)(x)) >> 8U) & 0xFFU)
#define USB_LONG_GET_BYTE2(x) ((uint8_t)(((uint32_t)(x)) >> 16U) & 0xFFU)
#define USB_LONG_GET_BYTE3(x) ((uint8_t)(((uint32_t)(x)) >> 24U) & 0xFFU)

#define USB_MEM4_ALIGN_MASK (0x03U)

/* accessory macro */
#define USB_MEM4_ALIGN(n)  ((n + 3U) & (0xFFFFFFFCu))
#define USB_MEM32_ALIGN(n) ((n + 31U) & (0xFFFFFFE0u))
#define USB_MEM64_ALIGN(n) ((n + 63U) & (0xFFFFFFC0u))

/* big/little endian */
#define SWAP2BYTE_CONST(n) ((((n)&0x00FFU) << 8U) | (((n)&0xFF00U) >> 8U))
#define SWAP4BYTE_CONST(n) \
    ((((n)&0x000000FFU) << 24U) | (((n)&0x0000FF00U) << 8U) | (((n)&0x00FF0000U) >> 8U) | (((n)&0xFF000000U) >> 24U))

#define USB_ASSIGN_VALUE_ADDRESS_LONG_BY_BYTE(n, m)      \
    {                                                    \
        *((uint8_t *)&(n))     = *((uint8_t *)&(m));     \
        *((uint8_t *)&(n) + 1) = *((uint8_t *)&(m) + 1); \
        *((uint8_t *)&(n) + 2) = *((uint8_t *)&(m) + 2); \
        *((uint8_t *)&(n) + 3) = *((uint8_t *)&(m) + 3); \
    }

#define USB_ASSIGN_VALUE_ADDRESS_SHORT_BY_BYTE(n, m)     \
    {                                                    \
        *((uint8_t *)&(n))     = *((uint8_t *)&(m));     \
        *((uint8_t *)&(n) + 1) = *((uint8_t *)&(m) + 1); \
    }

#define USB_ASSIGN_MACRO_VALUE_ADDRESS_LONG_BY_BYTE(n, m) \
    {                                                     \
        *((uint8_t *)&(n))     = (uint8_t)m;              \
        *((uint8_t *)&(n) + 1) = (uint8_t)(m >> 8);       \
        *((uint8_t *)&(n) + 2) = (uint8_t)(m >> 16);      \
        *((uint8_t *)&(n) + 3) = (uint8_t)(m >> 24);      \
    }

#define USB_ASSIGN_MACRO_VALUE_ADDRESS_SHORT_BY_BYTE(n, m) \
    {                                                      \
        *((uint8_t *)&(n))     = (uint8_t)m;               \
        *((uint8_t *)&(n) + 1) = (uint8_t)(m >> 8);        \
    }

#if (ENDIANNESS == USB_BIG_ENDIAN)

#define USB_SHORT_TO_LITTLE_ENDIAN(n)   SWAP2BYTE_CONST(n)
#define USB_LONG_TO_LITTLE_ENDIAN(n)    SWAP4BYTE_CONST(n)
#define USB_SHORT_FROM_LITTLE_ENDIAN(n) SWAP2BYTE_CONST(n)
#define USB_LONG_FROM_LITTLE_ENDIAN(n)  SWAP2BYTE_CONST(n)

#define USB_SHORT_TO_BIG_ENDIAN(n)   (n)
#define USB_LONG_TO_BIG_ENDIAN(n)    (n)
#define USB_SHORT_FROM_BIG_ENDIAN(n) (n)
#define USB_LONG_FROM_BIG_ENDIAN(n)  (n)

#define USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m)             \
    {                                                       \
        m[3] = (uint8_t)((((uint32_t)(n)) >> 24U) & 0xFFU); \
        m[2] = (uint8_t)((((uint32_t)(n)) >> 16U) & 0xFFU); \
        m[1] = (uint8_t)((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        m[0] = (uint8_t)(((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n)                                                     \
    ((uint32_t)((((uint32_t)n[3]) << 24U) | (((uint32_t)n[2]) << 16U) | (((uint32_t)n[1]) << 8U) | \
                (((uint32_t)n[0]) << 0U)))

#define USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)       \
    {                                              \
        m[0] = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
        m[1] = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
        m[2] = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        m[3] = (((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n)                                                        \
    ((uint32_t)((((uint32_t)n[0]) << 24U) | (((uint32_t)n[1]) << 16U) | (((uint32_t)n[2]) << 8U) | \
                (((uint32_t)n[3]) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m)  \
    {                                             \
        m[1] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        m[0] = (((uint16_t)(n)) & 0xFFU);         \
    }

#define USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n) ((uint16_t)((((uint16_t)n[1]) << 8U) | (((uint16_t)n[0]) << 0U)))

#define USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m)     \
    {                                             \
        m[0] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        m[1] = (((uint16_t)(n)) & 0xFFU);         \
    }

#define USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n) ((uint16_t)((((uint16_t)n[0]) << 8U) | (((uint16_t)n[1]) << 0U)))

#define USB_LONG_TO_LITTLE_ENDIAN_DATA(n, m)                         \
    {                                                                \
        *((uint8_t *)&(m) + 3) = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
        *((uint8_t *)&(m) + 2) = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
        *((uint8_t *)&(m) + 1) = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        *((uint8_t *)&(m) + 0) = (((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_LITTLE_ENDIAN_DATA(n)                                                                 \
    ((uint32_t)(((uint32_t)(*((uint8_t *)&(n) + 3)) << 24U) | ((uint32_t)(*((uint8_t *)&(n) + 2)) << 16U) | \
                ((uint32_t)(*((uint8_t *)&(n) + 1)) << 8U) | ((uint32_t)(*((uint8_t *)&(n))) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_DATA(n, m)                       \
    {                                                               \
        *((uint8_t *)&(m) + 1) = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        *((uint8_t *)&(m))     = ((((uint16_t)(n))) & 0xFFU);       \
    }

#define USB_SHORT_FROM_LITTLE_ENDIAN_DATA(n) \
    ((uint16_t)((uint16_t)(*((uint8_t *)&(n) + 1)) << 8U) | ((uint16_t)(*((uint8_t *)&(n)))))

#else

#define USB_SHORT_TO_LITTLE_ENDIAN(n)   (n)
#define USB_LONG_TO_LITTLE_ENDIAN(n)    (n)
#define USB_SHORT_FROM_LITTLE_ENDIAN(n) (n)
#define USB_LONG_FROM_LITTLE_ENDIAN(n)  (n)

#define USB_SHORT_TO_BIG_ENDIAN(n)   SWAP2BYTE_CONST(n)
#define USB_LONG_TO_BIG_ENDIAN(n)    SWAP4BYTE_CONST(n)
#define USB_SHORT_FROM_BIG_ENDIAN(n) SWAP2BYTE_CONST(n)
#define USB_LONG_FROM_BIG_ENDIAN(n)  SWAP4BYTE_CONST(n)

#define USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m)             \
    {                                                       \
        m[3] = (uint8_t)((((uint32_t)(n)) >> 24U) & 0xFFU); \
        m[2] = (uint8_t)((((uint32_t)(n)) >> 16U) & 0xFFU); \
        m[1] = (uint8_t)((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        m[0] = (uint8_t)(((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n)                                                     \
    ((uint32_t)((((uint32_t)n[3]) << 24U) | (((uint32_t)n[2]) << 16U) | (((uint32_t)n[1]) << 8U) | \
                (((uint32_t)n[0]) << 0U)))

#define USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)       \
    {                                              \
        m[0] = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
        m[1] = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
        m[2] = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        m[3] = (((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n)                                                        \
    ((uint32_t)((((uint32_t)n[0]) << 24U) | (((uint32_t)n[1]) << 16U) | (((uint32_t)n[2]) << 8U) | \
                (((uint32_t)n[3]) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m)  \
    {                                             \
        m[1] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        m[0] = (((uint16_t)(n)) & 0xFFU);         \
    }

#define USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n) ((uint16_t)((((uint16_t)n[1]) << 8U) | (((uint16_t)n[0]) << 0U)))

#define USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m)     \
    {                                             \
        m[0] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        m[1] = (((uint16_t)(n)) & 0xFFU);         \
    }

#define USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n) ((uint16_t)((((uint16_t)n[0]) << 8U) | (((uint16_t)n[1]) << 0U)))

#define USB_LONG_TO_LITTLE_ENDIAN_DATA(n, m)                         \
    {                                                                \
        *((uint8_t *)&(m) + 3) = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
        *((uint8_t *)&(m) + 2) = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
        *((uint8_t *)&(m) + 1) = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
        *((uint8_t *)&(m) + 0) = (((uint32_t)(n)) & 0xFFU);          \
    }

#define USB_LONG_FROM_LITTLE_ENDIAN_DATA(n)                                                                 \
    ((uint32_t)(((uint32_t)(*((uint8_t *)&(n) + 3)) << 24U) | ((uint32_t)(*((uint8_t *)&(n) + 2)) << 16U) | \
                ((uint32_t)(*((uint8_t *)&(n) + 1)) << 8U) | ((uint32_t)(*((uint8_t *)&(n))) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_DATA(n, m)                       \
    {                                                               \
        *((uint8_t *)&(m) + 1) = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
        *((uint8_t *)&(m))     = ((((uint16_t)(n))) & 0xFFU);       \
    }

#define USB_SHORT_FROM_LITTLE_ENDIAN_DATA(n) \
    ((uint16_t)(((uint16_t)(*(((uint8_t *)&(n)) + 1)) << 8U) | ((uint16_t)(*((uint8_t *)&(n))))))

#endif

/*
 * The following MACROs (USB_GLOBAL, USB_BDT, USB_RAM_ADDRESS_ALIGNMENT, etc) are only used for USB device stack.
 * The USB device global variables are put into the section m_usb_global and m_usb_bdt
 * by using the MACRO USB_GLOBAL and USB_BDT. In this way, the USB device
 * global variables can be linked into USB dedicated RAM by USB_STACK_USE_DEDICATED_RAM.
 * The MACRO USB_STACK_USE_DEDICATED_RAM is used to decide the USB stack uses dedicated RAM or not. The value of
 * the macro can be set as 0, USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL, or USB_STACK_DEDICATED_RAM_TYPE_BDT.
 * The MACRO USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL means USB device global variables, including USB_BDT and
 * USB_GLOBAL, are put into the USB dedicated RAM. This feature can only be enabled when the USB dedicated RAM
 * is not less than 2K Bytes.
 * The MACRO USB_STACK_DEDICATED_RAM_TYPE_BDT means USB device global variables, only including USB_BDT, are put
 * into the USB dedicated RAM, the USB_GLOBAL will be put into .bss section. This feature is used for some SOCs,
 * the USB dedicated RAM size is not more than 512 Bytes.
 */
#define USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL 1
#define USB_STACK_DEDICATED_RAM_TYPE_BDT        2

#if defined(__ICCARM__)

#define USB_WEAK_VAR __attribute__((weak))
#define USB_WEAK_FUN __attribute__((weak))
/* disable misra 19.13 */
_Pragma("diag_suppress=Pm120")
#define USB_ALIGN_PRAGMA(x) _Pragma(#x)
    _Pragma("diag_default=Pm120")

#define USB_RAM_ADDRESS_ALIGNMENT(n) USB_ALIGN_PRAGMA(data_alignment = n)
        _Pragma("diag_suppress=Pm120")
#define USB_LINK_SECTION_PART(str)  _Pragma(#str)
#define USB_LINK_DMA_INIT_DATA(sec) USB_LINK_SECTION_PART(location = #sec)
#define USB_LINK_USB_GLOBAL         _Pragma("location = \"m_usb_global\"")
#define USB_LINK_USB_BDT            _Pragma("location = \"m_usb_bdt\"")
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
            _Pragma("diag_default=Pm120")
#define USB_LINK_DMA_NONINIT_DATA      _Pragma("location = \"CacheLineData\"")
#define USB_LINK_NONCACHE_NONINIT_DATA _Pragma("location = \"NonCacheable\"")
#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION))

#define USB_WEAK_VAR                 __attribute__((weak))
#define USB_WEAK_FUN                 __attribute__((weak))
#define USB_RAM_ADDRESS_ALIGNMENT(n) __attribute__((aligned(n)))
#define USB_LINK_DMA_INIT_DATA(sec)  __attribute__((section(#sec)))
#if defined(__CC_ARM)
#define USB_LINK_USB_GLOBAL __attribute__((section("m_usb_global"))) __attribute__((zero_init))
#else
#define USB_LINK_USB_GLOBAL __attribute__((section(".bss.m_usb_global")))
#endif
#if defined(__CC_ARM)
#define USB_LINK_USB_BDT __attribute__((section("m_usb_bdt"))) __attribute__((zero_init))
#else
#define USB_LINK_USB_BDT __attribute__((section(".bss.m_usb_bdt")))
#endif
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
#if defined(__CC_ARM)
#define USB_LINK_DMA_NONINIT_DATA __attribute__((section("CacheLineData"))) __attribute__((zero_init))
#else
#define USB_LINK_DMA_NONINIT_DATA __attribute__((section("CacheLineData")))
#endif
#if defined(__CC_ARM)
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section("NonCacheable"))) __attribute__((zero_init))
#else
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section(".bss.NonCacheable")))
#endif

#elif defined(__GNUC__)

#define USB_WEAK_VAR                 __attribute__((weak))
#define USB_WEAK_FUN                 __attribute__((weak))
#define USB_RAM_ADDRESS_ALIGNMENT(n) __attribute__((aligned(n)))
#define USB_LINK_DMA_INIT_DATA(sec)  __attribute__((section(#sec)))
#define USB_LINK_USB_GLOBAL          __attribute__((section("m_usb_global, \"aw\", %nobits @")))
#define USB_LINK_USB_BDT             __attribute__((section("m_usb_bdt, \"aw\", %nobits @")))
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
#define USB_LINK_DMA_NONINIT_DATA      __attribute__((section("CacheLineData, \"aw\", %nobits @")))
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section("NonCacheable, \"aw\", %nobits @")))

#elif (defined(__DSC__) && defined(__CW__))
#define MAX(a, b)                    (((a) > (b)) ? (a) : (b))
#define USB_WEAK_VAR                 __attribute__((weak))
#define USB_WEAK_FUN                 __attribute__((weak))
#define USB_RAM_ADDRESS_ALIGNMENT(n) __attribute__((aligned(n)))
#define USB_LINK_USB_BDT_BSS
#define USB_LINK_USB_GLOBAL_BSS
#else
#error The tool-chain is not supported.
#endif

#if (defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) || \
    (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))

#if ((defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE)) && (defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)))
#define USB_CACHE_LINESIZE MAX(FSL_FEATURE_L2CACHE_LINESIZE_BYTE, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#elif (defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE))
#define USB_CACHE_LINESIZE MAX(FSL_FEATURE_L2CACHE_LINESIZE_BYTE, 0)
#elif (defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE))
#define USB_CACHE_LINESIZE MAX(0, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#else
#define USB_CACHE_LINESIZE 4U
#endif

#else
#define USB_CACHE_LINESIZE 4U
#endif

#if (USB_CACHE_LINESIZE > 4U)
#define USB_DATA_ALIGN_SIZE USB_CACHE_LINESIZE
#else
/* Change the USB_DATA_ALIGN_SIZE to 4, For the lpcip3511 driver, the lpcip3511 driver will do the memcpy for the
   transfer buffer that is not in the USB dedicated RAM or not aligned to 64-byte boundaries. Hence the changes do not
   bring the risk and improve the RAM usage rate but cause the lower perfromance. If requiring a higher performance on
   the lpcip3511 platform, please change the macro to 64 and put the transfer buffer into the USB dedicated RAM. */
#define USB_DATA_ALIGN_SIZE 4U
#endif

/* Due to the change of USB_DATA_ALIGN_SIZE from 64 to 4 on the lpcip3511 platform, the size of variables defined by
   using this marco may be smaller on the lpcip3511 platform. If users don't want the lpcip3511 driver to do memcpy,
   please use the macro to define the transfer buffer and change the USB_DATA_ALIGN_SIZE to 64 and put the transfer
   buffer into the USB dedicated RAM. */
#define USB_DATA_ALIGN_SIZE_MULTIPLE(n) (((n) + USB_DATA_ALIGN_SIZE - 1U) & (~(USB_DATA_ALIGN_SIZE - 1U)))

#if defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM == USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL)

#define USB_GLOBAL USB_LINK_USB_GLOBAL
#define USB_BDT    USB_LINK_USB_BDT

#if (defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) || \
    (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(CacheLineData.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#if (defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA USB_LINK_USB_GLOBAL
#endif
#endif

#elif defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM == USB_STACK_DEDICATED_RAM_TYPE_BDT)

#define USB_BDT USB_LINK_USB_BDT

#if (defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) || \
    (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_GLOBAL               USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(CacheLineData.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#if (defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_GLOBAL               USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_GLOBAL USB_LINK_USB_GLOBAL_BSS
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA
#endif
#endif

#else

#if (defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) || \
    (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))

#define USB_GLOBAL               USB_LINK_DMA_NONINIT_DATA
#define USB_BDT                  USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(CacheLineData.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA

#else

#if (defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_GLOBAL               USB_LINK_NONCACHE_NONINIT_DATA
#define USB_BDT                  USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_GLOBAL USB_LINK_USB_GLOBAL_BSS
#define USB_BDT    USB_LINK_USB_BDT_BSS
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA
#endif

#endif

#endif

#define USB_DMA_NONINIT_DATA_ALIGN(n) USB_RAM_ADDRESS_ALIGNMENT(n) USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_INIT_DATA_ALIGN(n)    USB_RAM_ADDRESS_ALIGNMENT(n) USB_DMA_DATA_INIT_SUB

#if (defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) || \
    (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_DMA_DATA_NONCACHEABLE USB_LINK_NONCACHE_NONINIT_DATA

#else
#define USB_DMA_DATA_NONCACHEABLE
#endif

#define USB_GLOBAL_DEDICATED_RAM USB_LINK_USB_GLOBAL

/* #define USB_RAM_ADDRESS_NONCACHEREG_ALIGNMENT(n, var) AT_NONCACHEABLE_SECTION_ALIGN(var, n) */
/* #define USB_RAM_ADDRESS_NONCACHEREG(var) AT_NONCACHEABLE_SECTION(var) */

#endif /* __USB_MISC_H__ */
