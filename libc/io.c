//
// Created by zaiyangli on 4/2/16.
//
#include "io.h"
io_buffer stdout_buffer = {
        .buf="", .size=0, .auto_flush=1,.stream = NULL
};
io_buffer stdin_buffer = {
        .buf="", .size=0, .auto_flush=1,.stream = NULL
};
io_buffer stderr_buffer = {
        .buf="", .size=0, .auto_flush=1,.stream = NULL
};


static uint32_t format_float(double val, char* buf, uint32_t size){
    return 0;
}

static uint32_t format_int(double val, char* buf, uint32_t size){
    return 0;
}

void printf(const char* format, ...){
    char convertBuffer[BUF_SIZE];
    va_list vars;

    int iVal = 0;
    float fVal = 0.0f;
    char* strVal = NULL;
    unsigned int uiVal = 0;
    int length = 0;
    va_start(vars, format);

    int skip = 0;
    while( *format != '\0' ){
        for(; *format!='\0' && *format!='%' ; format++) skip++;
        puts_n(format-skip, skip);
        skip = 0;
        if(*format == '%'){
            format++;
            switch(*format){
                case 'd':
                    iVal = va_arg(vars, int);
                    length = format_int(iVal, convertBuffer, BUF_SIZE);
                    puts_n(convertBuffer, length);
                    iVal = 0;
                    format++;
                    break;
                case 'e':
                    fVal = va_arg(vars, double);
                    length = format_float(fVal, convertBuffer, BUF_SIZE);
                    puts_n(convertBuffer, length);
                    fVal = 0.0f;
                    format++;
                    break;
                case 's':
                    strVal = va_arg(vars, char*);
                    puts(strVal);
                    strVal = NULL;
                    format++;
                    break;
                case 'c':
                    iVal = va_arg(vars, int);
                    putchar(iVal);
                    iVal = 0;
                    format++;
                    break;
                case 'x':
                    iVal = va_arg(vars, int);
                    format++;
                    break;
                case 'u':
                    uiVal = va_arg(vars, unsigned int);
                    format++;
                default:
                    break;
            }
        }
    }
    va_end(vars);
}

void initialize_buffer(io_buffer *buffer, int auto_flush, int clear){
    buffer->size=0;
    buffer->auto_flush = auto_flush;
    if(clear){
        memset(buffer->buf, BUF_SIZE, 0);
    }
}
void write_to_buffer(io_buffer* buffer, const char* str, int size){
    //assert(buffer->size <= BUF_SIZE);
    while(size > 0) {
        int free = BUF_SIZE - buffer->size;
        int overflow = size - free;
        if (overflow < 1) {
            memcpy(&buffer->buf[buffer->size], str, size);
            buffer->size += size;
            return;
        }else {
            memcpy(&buffer->buf[buffer->size], str, free);
            if(buffer->auto_flush)
                flush_buffer(buffer, buffer->stream);
            else return;
            str += size;
            size -= free;
        }
    }
}

int is_buffer_full(io_buffer* buffer){
    return buffer->size==BUF_SIZE;
}
void flush_buffer(io_buffer* buffer, io_stream* st){
    int i = 0;
    memset(buffer->buf, BUF_SIZE, 0);
    buffer->size=0;
}

void puts(const char* str){
    write_to_buffer(&stdout_buffer, str, strlen(str));
}
void puts_n(const char* str, int len){
    write_to_buffer(&stdout_buffer, str, len);
}
void gets(const char* buf, int size){

}
void putchar(int c){
    char ch[1] = {(char)c};

    write_to_buffer(&stdout_buffer, ch, 1);
}
int getchar(){
    return 0;
}