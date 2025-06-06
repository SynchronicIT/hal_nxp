# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if (CONFIG_MCUX_COMPONENT_driver.clock)
    mcux_component_version(1.0.1)
    mcux_add_source( SOURCES fsl_clock.c fsl_clock.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.edma_soc)
    mcux_component_version(2.0.0)
    mcux_add_source( SOURCES fsl_edma_soc.c fsl_edma_soc.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.iomuxc)
    mcux_component_version(1.0.0)
    mcux_add_source( SOURCES fsl_iomuxc.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.memory)
    mcux_component_version(1.0.0)
    mcux_add_source( SOURCES fsl_memory.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.misc_soc)
    mcux_component_version(2.0.0)
    mcux_add_source( SOURCES fsl_misc_soc.c fsl_misc_soc.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.sentinel)
    mcux_component_version(2.0.3)
    mcux_add_source( SOURCES fsl_sentinel.c fsl_sentinel.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.mipi_dsi_soc)
    mcux_component_version(2.0.0)
    mcux_add_source( SOURCES fsl_soc_mipi_dsi.h )
    mcux_add_include( INCLUDES . )
endif()

if (CONFIG_MCUX_COMPONENT_driver.trdc_soc)
    mcux_component_version(2.0.0)
    mcux_add_source( SOURCES fsl_trdc_soc.h )
    mcux_add_include( INCLUDES . )
endif()
