# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.flexio_i2c_master)
    mcux_component_version(2.5.0)

    mcux_add_source(SOURCES fsl_flexio_i2c_master.c fsl_flexio_i2c_master.h)

    mcux_add_include(INCLUDES .)

endif()
