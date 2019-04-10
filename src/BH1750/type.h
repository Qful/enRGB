
#ifndef __type_def_h
#define __type_def_h

#define     __I     volatile const   /*!< defines 'read only' permissions     */
#define     __O     volatile         /*!< defines 'write only' permissions    */
#define     __IO    volatile         /*!< defines 'read / write' permissions  */


typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;


typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

typedef unsigned char       BOOL;
typedef unsigned char       BYTE;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#endif
