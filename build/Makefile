# part 1: variables

 PROJECT_PATH     = $(shell find . -mindepth 1 -maxdepth 1 -type d)
 PROJECT_SOURCES  = $(shell find ${PROJECT_PATH} -name *.c -o -name *.s)
 PROJECT_HEADERS  = $(shell find ${PROJECT_PATH}              -name *.h)
 PROJECT_OBJECTS  = $(addsuffix .o, $(basename ${PROJECT_SOURCES}))
 PROJECT_TARGETS  = kernel.elf kernel.bin

 QEMU_PATH        = /usr
 QEMU_GDB         =        127.0.0.1:1233
 QEMU_UART        = stdio
#QEMU_UART       += telnet:127.0.0.1:1235,server
#QEMU_UART       += telnet:127.0.0.1:1236,server

 LINARO_PATH      = /home/zaiyangli/Desktop/gcc-linaro-5.1-2015.08-x86_64_arm-eabi
 LINARO_PREFIX    = arm-eabi

# part 2: build commands

%.o   : %.s
	@${LINARO_PATH}/bin/${LINARO_PREFIX}-as  $(addprefix -I , ${PROJECT_PATH} ${LINARO_PATH}/arm-eabi/libc/usr/include) -mcpu=cortex-a8                                       -g       -o ${@} ${<}
%.o   : %.c
	@${LINARO_PATH}/bin/${LINARO_PREFIX}-gcc $(addprefix -I , ${PROJECT_PATH} ${LINARO_PATH}/arm-eabi/libc/usr/include) -mcpu=cortex-a8 -mabi=aapcs -ffreestanding -std=gnu99 -g -c -O -o ${@} ${<}

%.elf : ${PROJECT_OBJECTS}
	@${LINARO_PATH}/bin/${LINARO_PREFIX}-ld  $(addprefix -L ,                 ${LINARO_PATH}/arm-eabi/libc/usr/lib    ) -T ${*}.ld -o ${@} ${^} -lc -lgcc
%.bin : %.elf
	@${LINARO_PATH}/bin/${LINARO_PREFIX}-objcopy -O binary ${<} ${@}

# part 3: targets

.PRECIOUS   : ${PROJECT_OBJECTS} ${PROJECT_TARGETS}

build       : ${PROJECT_TARGETS}

launch-qemu :;
	@${QEMU_PATH}/bin/qemu-system-arm -M realview-pb-a8 -m 128M -display none -gdb tcp:${QEMU_GDB} $(addprefix -serial , ${QEMU_UART}) -S -kernel kernel.bin

launch-gdb  : ;
	@${LINARO_PATH}/bin/${LINARO_PREFIX}-gdb -ex "file kernel.elf" -ex "target remote ${QEMU_GDB}"

kill-qemu   :
	@-killall --quiet --user ${USER} qemu-system-arm

kill-gdb    :
	@-killall --quiet --user ${USER} ${LINARO_PREFIX}-gdb

clean       : kill-qemu kill-gdb
	@rm -f core ${PROJECT_OBJECTS} ${PROJECT_TARGETS}
