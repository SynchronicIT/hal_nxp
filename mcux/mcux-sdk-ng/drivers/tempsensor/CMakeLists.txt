# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.tempsensor)
    mcux_component_version(2.1.2)

    mcux_add_source(SOURCES fsl_tempsensor.h fsl_tempsensor.c)

    mcux_add_include(INCLUDES .)

endif()
