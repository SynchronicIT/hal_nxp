# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.wdog32)
    mcux_component_version(2.1.0)

    mcux_add_source(SOURCES fsl_wdog32.h fsl_wdog32.c)

    mcux_add_include(INCLUDES .)

endif()
