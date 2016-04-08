include( CMakeForceCompiler )

set(CMAKE_FIND_ROOT_PATH "/home/zaiyangli/Desktop/gcc-linaro-5.1-2015.08-x86_64_arm-eabi/")

set( CMAKE_SYSTEM_NAME Linux )
set( CMAKE_SYSTEM_PROCESSOR arm)
set( LINARO_PATH "/home/zaiyangli/Desktop/gcc-linaro-5.1-2015.08-x86_64_arm-eabi/bin/" )
set( CROSS_COMPILE arm-eabi- )
set( LINKER_FILE  "${CMAKE_SOURCE_DIR}/image.ld" )

CMAKE_FORCE_C_COMPILER( ${LINARO_PATH}${CROSS_COMPILE}gcc GNU )

set( CMAKE_OBJCOPY ${LINARO_PATH}${CROSS_COMPILE}objcopy
        CACHE FILEPATH "The toolchain objcopy command " FORCE)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a8 -mabi=aapcs -ffreestanding -std=gnu99")

set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_FILE} -lc -lgcc")

set( CMAKE_C_COMPILER ${LINARO_PATH}${CROSS_COMPILE}gcc)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
set( CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )