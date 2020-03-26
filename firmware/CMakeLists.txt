cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

set(CMAKE_FILES ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_TOOLCHAIN_FILE    ${CMAKE_FILES}/toolchain-gcc-arm-embedded.cmake)

project(OPERATION_AIR)

include(${CMAKE_FILES}/CPM_setup.cmake)


#-----------------------------------------------------------------------
# Build settings
#-----------------------------------------------------------------------

set(EXE_NAME                ventilator)
set(FLASH_ADDR              0x00000000)
set(FLASH_CFG               lpc11uxx)
set(DEBUG_BREAKPOINT_LIMIT  4)
set(DEBUG_WATCHPOINT_LIMIT  2)


# default settings
set(OPTIMIZE s)
set(BLACKMAGIC_DEV /dev/ttyBmpGdb)
set(POWER_TARGET "no")

set(CRP_SETTING "NONE")
set(EN_WATCHDOG 1)

# Include custom settings
# (if this file does not exist, copy it from config.cmake.example)
include(${CMAKE_SOURCE_DIR}/config.cmake)

message(STATUS "Config OPTIMIZE: ${OPTIMIZE}")
message(STATUS "Config BLACKMAGIC_DEV: ${BLACKMAGIC_DEV}")
message(STATUS "Config POWER_TARGET: ${POWER_TARGET}")

message(STATUS "Config CRP_SETTING: ${CRP_SETTING}")
message(STATUS "Config EN_WATCHDOG: ${EN_WATCHDOG}")

set(SYSTEM_LIBRARIES    m c gcc)

set(FLAGS_M0 "-mcpu=cortex-m0")

set(C_FLAGS "-O${OPTIMIZE} -g3 -c -fmessage-length=80 -fno-builtin   \
    -ffunction-sections -fdata-sections -std=gnu99 -mthumb      \
    -fdiagnostics-color=auto")
set(C_FLAGS_WARN "-Wall -Wextra -Wno-unused-parameter           \
    -Wshadow -Wpointer-arith -Winit-self -Wstrict-overflow=2")

set(L_FLAGS "-fmessage-length=80 -nostdlib -specs=nano.specs \
    -mthumb -Wl,--gc-sections")

set(MCU_PLATFORM    lpc11xxx)

add_definitions("${FLAGS_M0} ${C_FLAGS} ${C_FLAGS_WARN}")
add_definitions(-DCORE_M0 -DCHIP_LPC11UXX -DMCU_PLATFORM_${MCU_PLATFORM} -DARM_MATH_CM0 -DARM_MATH_CM0_FAMILY)
add_definitions(-DCRP_SETTING_${CRP_SETTING})
add_definitions(-DEN_WATCHDOG=${EN_WATCHDOG})

# lpc_usb_lib settings
add_definitions(-D__LPC11U1X)


set(ELF_PATH            "${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}")
set(EXE_PATH            "${ELF_PATH}.bin")
set(FLASH_FILE          ${PROJECT_BINARY_DIR}/flash.cfg)

#------------------------------------------------------------------------------
# CPM Modules
#------------------------------------------------------------------------------

# ---- #
# chip_lpc1xxx: use our own src/usb/app_usbd_cfg.h
set(USBD_CFG_INCLUDE "<${CMAKE_CURRENT_SOURCE_DIR}/src/usb/app_usbd_cfg.h>")
add_definitions("-DCHIP_LPC11UXX_USBD_CONFIG_FILE=${USBD_CFG_INCLUDE}")
# --- #


CPM_AddModule("startup_lpc11xxx"
    GIT_REPOSITORY "https://github.com/JitterCompany/startup_lpc11xxx.git"
    GIT_TAG "1.5.1")

CPM_AddModule("lpc_tools"
    GIT_REPOSITORY "https://github.com/JitterCompany/lpc_tools.git"
    GIT_TAG "2.8.3")

CPM_AddModule("chip_lpc11xxx"
    GIT_REPOSITORY "https://github.com/JitterCompany/chip_lpc11xxx.git"
    GIT_TAG "1.4.2")

CPM_AddModule("mcu_timing"
    GIT_REPOSITORY "https://github.com/JitterCompany/mcu_timing.git"
    GIT_TAG "1.6.2")

CPM_AddModule("c_utils"
    GIT_REPOSITORY "https://github.com/JitterCompany/c_utils.git"
    GIT_TAG "1.7")

CPM_AddModule("mcu_debug"
    GIT_REPOSITORY "https://github.com/JitterCompany/mcu_debug.git"
    GIT_TAG "2.1")

CPM_AddModule("cmsis_dsp_lib"
    # SOURCE_DIR "../../lpc/libs/cmsis_dsp_lib")
    GIT_REPOSITORY "https://github.com/JitterCompany/cmsis_dsp_lib.git"
    GIT_TAG "1.1-1")

CPM_Finish()


get_property(startup_linker GLOBAL PROPERTY startup_linker)
message(STATUS "Startup_linker: ${startup_linker}")

set(LINKER_FILES "-L .. -T ${startup_linker}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${L_FLAGS} \
${LINKER_FILES} ${FLAGS_M0}")


#-----------------------------------------------------------------------
# Setup source
#-----------------------------------------------------------------------


file(GLOB SOURCES
"user_settings.c"
"src/*.c"
"src/log_storage/*.c"
"src/RGB_LED/*.c"
"src/usb/*.c"
"src/sensors/*.c"
"src/actuators/*.c"
)

set(CMAKE_SYSTEM_NAME Generic)

include_directories("src/")
include_directories("src/usb")


#-----------------------------------------------------------------------
# Setup executable
#-----------------------------------------------------------------------


if(NOT TARGET version)
    set(FW_VERSION_FILE "${CMAKE_SOURCE_DIR}/src/generated/firmware_version.h")

    add_custom_command(OUTPUT ${FW_VERSION_FILE}
        DEPENDS version
        )

    add_custom_target(version
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake "${FW_VERSION_FILE}" "${BUILD_OPTS}"
        )

endif(NOT TARGET version)


add_executable(${EXE_NAME} ${SOURCES})
target_link_libraries(${EXE_NAME} ${CPM_LIBRARIES})
target_link_libraries(${EXE_NAME} ${SYSTEM_LIBRARIES})

add_custom_target(bin
    # empty flash file
    COMMAND > "${FLASH_FILE}"

    DEPENDS ${EXE_NAME}
    COMMAND ${CMAKE_OBJCOPY} -O binary ${EXE_NAME} ${EXE_NAME}.bin

    # append flash file
    COMMAND echo "${PROJECT_BINARY_DIR}/${EXE_NAME}.bin ${FLASH_ADDR} ${FLASH_CFG}" >> "${PROJECT_BINARY_DIR}/flash.cfg"
    )

add_dependencies(bin version)
add_dependencies(flash bin)
add_dependencies(debug bin)
