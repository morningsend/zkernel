//
// Created by zaiyangli on 4/7/16.
//

#ifndef _BOOT_H
#define _BOOT_H
#define MODE_USER 0x10
#define MODE_FIG 0x11
#define MODE_IRQ 0x12
#define MODE_SUPERVISOR 0x13
#define MODE_ABORT 0x17
#define MODE_UNDEFINED 0x1B
#define MODE_SYS 0x1F

/* FIQ and IRQ interrupt mask bits */
#define I_BIT 0x80
#define F_BIT 0x40
#endif //APP1_BOOT_H
