//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FILE_H
#define _FILE_H

#include <stdint-gcc.h>
#include "fnode.h"

#define FILE_TYPE_DIRECTORY
#define FILE_TYPE_FILE

typedef struct file_t file;
typedef struct file_t* p_file;

/**
 * File descriptor.
 * library functions that handles file i/o requires a file descriptor objector as argument
 * It is not meant to modified by the user
 */

struct file_f {
    fnode node;
};


#endif //_FILE_H
