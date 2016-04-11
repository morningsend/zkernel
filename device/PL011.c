#include "PL011.h"

/* Per Table 4.2 (for example: the information is in several places) of
 * 
 * http://infocenter.arm.com/help/topic/com.arm.doc.dui0417d/index.html
 * 
 * we know the device(s) are mapped to fixed addresses in memory, so to
 * allow easier access to the device registers we can simply overlay an
 * associated structure instance for each one.
 */

PL011_t* const UART0 = ( PL011_t* )( 0x10009000 );
PL011_t* const UART1 = ( PL011_t* )( 0x1000A000 );
PL011_t* const UART2 = ( PL011_t* )( 0x1000B000 );
PL011_t* const UART3 = ( PL011_t* )( 0x1000C000 );

int  xtoi( char x ) {
  if      ( ( x >= '0' ) && ( x <= '9' ) ) {
    return (  0 + ( x - '0' ) );
  }
  else if ( ( x >= 'a' ) && ( x <= 'f' ) ) {
    return ( 10 + ( x - 'a' ) );
  }
  else if ( ( x >= 'A' ) && ( x <= 'F' ) ) {
    return ( 10 + ( x - 'A' ) );
  }

  return -1;
}

char itox( int  x ) {
  if     ( ( x >=  0 ) && ( x <=  9 ) ) {
    return '0' + ( x -  0 );
  }
  else if( ( x >= 10 ) && ( x <= 15 ) ) {
    return 'A' + ( x - 10 );
  }

  return -1;
}

void inline PL011_putc( PL011_t* d, uint8_t x ) {
  while( d->FR & 0x20 ) {
    /* wait while transmit FIFO is full */
  }
  d->DR = x;
}

uint32_t PL011_getc( PL011_t* d            ) {
  while( d->FR & 0x10 ) {
    /* wait while receive FIFO is empty */
  }

  return d->DR;
}

void inline PL011_puth( PL011_t* d, uint8_t x ) {
  PL011_putc( d, itox( ( x >> 4 ) & 0xF ) );
  PL011_putc( d, itox( ( x >> 0 ) & 0xF ) );
}

uint8_t PL011_geth( PL011_t* d ) {
  uint8_t x  = ( xtoi( PL011_getc( d ) ) << 4 );
          x |= ( xtoi( PL011_getc( d ) ) << 0 );

  return x;
}


uint32_t PL011_put_bytes( PL011_t* device, const uint8_t* bytes, uint32_t size){
  for(int i = 0; i< size; i++){
    PL011_putc(device, bytes[i]);
  }
  return size;
}

uint32_t PL011_puts( PL011_t* device, const char* bytes) {
  uint32_t i = 0;
  while(bytes[i] != 0){
    PL011_putc(device, bytes[i]);
    i++;
  }
  return i;
}

uint32_t PL011_get_bytes( PL011_t* d, uint8_t* bytes, uint32_t size){
  uint32_t ch = 0;
  uint32_t i = 0;
  for(i = 0; i<size; i++){
    ch = PL011_getc(d);
    bytes[i] = (uint8_t) ch;
  }
  return i;
}

uint32_t PL011_gets( PL011_t* d, uint8_t* bytes, uint32_t size){
  uint32_t ch = 0;
  uint32_t i = 0;
  for(i = 0; i<size; i++){
    ch = PL011_getc_with_echo(d,d);
    if(ch == '\r'){
      bytes[i] = '\n';
      PL011_putc(d, '\n');
      break;
    }else {
      bytes[i] = (uint8_t) ch;
    }
  }
  return i;
}

uint32_t PL011_getc_with_echo(PL011_t* input, PL011_t* echo){
  uint32_t ch = PL011_getc(input);
  PL011_putc(echo, (uint8_t)ch);
  return ch;
}