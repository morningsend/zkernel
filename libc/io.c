//
// Created by zaiyangli on 4/2/16.
//
#include "io.h"




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
                    break;
                case '%':
                    putchar('%');
                    format++;
                    break;
                default:
                    break;
            }
        }
    }
    va_end(vars);
    stream_flush(&stdout_stream);
}

void puts(char* str){
    stream_write(&stdout_stream, str, strlen(str));
    stream_flush(&stdout_stream);
}
void puts_n(char* str, int len){
    stream_write(&stdout_stream, str, len);
}
void gets(char* buf, int size){
    stream_read(&stdin_stream, buf, size);
}
void putchar(int c){
    char ch[1] = {(char)c};
    stream_write(&stdin_stream, ch, 1);
}
int getchar(){
    return EOF;
}