cmake_minimum_required(VERSION 3.2)
project(app1 C ASM)

set ( CMAKE_EXECUTABLE_SUFFIX ".elf")
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a8 -mabi=aapcs -ffreestanding -std=gnu99 -g -O   ")
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nodefaultlibs" )
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS " -export-dynamic -nostartfiles  -lgcc -Wl,--build-id=none -nodefaultlibs" )
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-a8 -g")
set(RELEASE_SOURCE_FILES libc/string.c libc/string.h libc/math.h libc/math.c libc/io.h libc/io.c
        kernel/boot.S kernel/kernel.c kernel/kernel.h
        device/device.h device/device.c system/systemcall.c system/systemcall.h system/syslib.c system/syslib.h
        user/P0.h user/P0.c user/P1.h user/P1.c user/P2.h user/P2.c
        device/disk.c device/disk.h device/GIC.h device/GIC.c device/PL011.c device/PL011.h device/SP804.c device/SP804.h
        kernel/arm.h kernel/thread.c kernel/thread.h kernel/sys_init.c kernel/sys_init.h user/begin.c user/begin.h kernel/syscall_def.h kernel/syscall_def.c kernel/syscall_impl.c kernel/syscall_impl.h libc/iostream.c libc/iostream.h libc/iobuffer.c libc/iobuffer.h
        user/test/test.c user/test/test.h
        libc/assert.c libc/assert.h kernel/context.c kernel/context.h libc/array.c libc/array.h
        zunit/zunit_assert.c zunit/zunit_assert.h zunit/test_case.c zunit/test_case.h zunit/zunit.c zunit/zunit.h
        libc/allocator.c libc/allocator.h kernel/schedule.c kernel/schedule.h device/timer.c device/timer.h
        kernel/test/kernel_tests.c kernel/test/kernel_tests.h libc/free_list.c libc/free_list.h
        user/shell.c user/shell.h libc/util.c libc/util.h libc/circular_queue.c libc/circular_queue.h
        fs/fnode.c fs/fnode.h fs/fblock.c fs/fblock.h fs/bitmap.c fs/bitmap.h
        fs/test/testdisk.c fs/test/testdisk.h fs/file.c fs/file.h fs/fdisk.c fs/fdisk.h fs/fs.c fs/fs.h fs/path.c fs/path.h fs/ftree.c fs/ftree.h fs/test/testfs.c fs/test/testfs.h libc/fio.c libc/fio.h kernel/mutex.c kernel/mutex.h fs/fstream.c fs/fstream.h)

set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/")


add_executable(kernel ${RELEASE_SOURCE_FILES})

add_custom_command(
        TARGET kernel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/kernel${CMAKE_EXECUTABLE_SUFFIX} ${OUTPUT_PATH}/kernel${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "copy" )

add_custom_command(
        TARGET kernel POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ${CMAKE_BINARY_DIR}/kernel${CMAKE_EXECUTABLE_SUFFIX} -O binary ${OUTPUT_PATH}/kernel.bin
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "${CMAKE_OBJCOPY} ${CMAKE_BINARY_DIR}/kernel${CMAKE_EXECUTABLE_SUFFIX} -O binary ${OUTPUT_PATH}/kernel.bin" )