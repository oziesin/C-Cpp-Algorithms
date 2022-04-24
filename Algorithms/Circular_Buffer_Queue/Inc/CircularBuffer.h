/* This module can be use in C/C++ Projects both. 
 * Includes static circular queue data structre.
 * Modify @CIRCULAR_BUFFER_LENGTH for your need.
 * @FUN Push pushes the data end of the array.
 * @FUN Pop gets the data of the beggining of the array.
 * @FUN GetFreeSpace gets the free space in the array.
 * @FUN Clear set 0 whole array member.
 * @FUN Init is constructer function.
 */

#ifndef _CIRCULAR_BUFFER_MODULE_H_
#define _CIRCULAR_BUFFER_MODULE_H_

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
    #include <iostream>
    extern "C" {
#else
    #include <stdio.h>
#endif



#define CIRCULAR_BUFFER_LENGTH       ( 12 )
#define CIRCULAR_BUFFER_LAST_IDX     ( CIRCULAR_BUFFER_LENGTH - 1 )

typedef enum
{
    errOK,
    errNoFreeSpace,
    errBufferEmpty,
    errBufferFull
}eBufferErrors_t;

typedef struct
{
    uint8_t* puchead;
    uint8_t* puctail;
    uint8_t  tucCircularBuff[ CIRCULAR_BUFFER_LENGTH + 1 ];

}stBuffer_t;

#ifndef __cplusplus

struct CircularBuffer_Object
{
    stBuffer_t stBuffer;

    eBufferErrors_t ( *Init )( struct CircularBuffer_Object *this );
    eBufferErrors_t ( *Push ) ( struct CircularBuffer_Object *this, const void *Data, size_t Size );
    eBufferErrors_t ( *Pop ) ( struct CircularBuffer_Object *this, void* Data, size_t Size );
    eBufferErrors_t (*GetFreeSpace) ( struct CircularBuffer_Object *this, uint8_t *FreeSpace );
    eBufferErrors_t ( *Clear ) ( struct CircularBuffer_Object *this );

};
typedef struct CircularBuffer_Object CircularBuffer_Obj_t;

 eBufferErrors_t CircularBufferInit( CircularBuffer_Obj_t *this );
 eBufferErrors_t CircularBufferPush( CircularBuffer_Obj_t *this, const void *Data, size_t Size );
 eBufferErrors_t CircularBufferPop( CircularBuffer_Obj_t *this, void* Data, size_t Size );
 eBufferErrors_t CircularBufferGetFreeSpace(CircularBuffer_Obj_t *this, uint8_t *FreeSpace );
 eBufferErrors_t CircularBufferClear( CircularBuffer_Obj_t *this );
 void CircularBufferFuncConfig( CircularBuffer_Obj_t *this );
#else
}
class CircularBuffer
{
private:   
    stBuffer_t stBuffer;
public:

    eBufferErrors_t CircularBufferPush(const void* vpData,size_t stSize);
    eBufferErrors_t CircularBufferPop(void* vpData, size_t Size);
    eBufferErrors_t CircularBufferGetFreeSpace( uint8_t *FreeSpace );
    eBufferErrors_t CircularBufferClear();
    CircularBuffer(/* args */);
};
#endif  /* #ifndef __cplusplus */

#endif /* _CIRCULAR_BUFFER_MODULE_H_ */