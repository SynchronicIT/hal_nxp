# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.mmau)
    mcux_component_version(2.0.1)

    mcux_add_source(SOURCES fsl_mmau.h fsl_mmau.c)

    mcux_add_include(INCLUDES .)

endif()
