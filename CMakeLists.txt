cmake_minimum_required(VERSION 3.2)
project(app1 C ASM)

set ( CMAKE_EXECUTABLE_SUFFIX ".elf")
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a8 -mabi=aapcs -ffreestanding -std=gnu99 -g -O -lc -lgcc ")
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nodefaultlibs" )
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS " -export-dynamic -nostartfiles -lc -lgcc" )
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-a8 -g")
set(RELEASE_SOURCE_FILES libc/string.c libc/string.h libc/math.h libc/math.c libc/io.h libc/io.c
        kernel/boot.S kernel/kernel.c kernel/kernel.h kernel/interrupt.h kernel/interrupt.S
        kernel/device.h kernel/device.c kernel/systemcall.c kernel/systemcall.h
        user/P0.h user/P0.c user/P1.h user/P1.c user/P2.h user/P2.c
        device/disk.c device/disk.h device/GIC.h device/GIC.c device/PL011.c device/PL011.h device/SP804.c device/SP804.h
        kernel/boot.h)

set(TEST_SOURCE_FILES libc/test-main.c libc/test/test.c libc/test/test.h libc/string.c libc/string.h libc/math.h libc/math.c libc/io.h libc/io.c)
add_executable(app1 main.c)
add_executable(kernel ${RELEASE_SOURCE_FILES})
add_executable(tests ${TEST_SOURCE_FILES})


add_custom_command(
        TARGET kernel POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ${CMAKE_BINARY_DIR}/kernel${CMAKE_EXECUTABLE_SUFFIX} -O binary ${CMAKE_BINARY_DIR}/kernel.bin
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "${CMAKE_OBJCOPY} ${CMAKE_BINARY_DIR}/kernel${CMAKE_EXECUTABLE_SUFFIX} -O binary ${CMAKE_BINARY_DIR}/kernel.bin" )