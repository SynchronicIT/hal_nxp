# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.pwm)
    mcux_component_version(2.8.4)

    mcux_add_source(SOURCES fsl_pwm.c fsl_pwm.h)

    mcux_add_include(INCLUDES .)

endif()
