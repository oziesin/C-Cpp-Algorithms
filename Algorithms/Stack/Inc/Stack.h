/* This module can be use in C/C++ Projects both. 
 * Includes static Stack data structre.
 * Modify @STACK_LENGTH for your need.
 * Modify @DATA_TYPE for your need
 * @FUN Push pushes the data end of the array.
 * @FUN Pop gets the last data of the array.
 * @FUN GetFreeSpace gets the free space in the array.
 * @FUN Clear set 0 whole array member.
 * @FUN Init is constructer function.
 */
#ifndef _STACK_MODULE_H_
#define _STACK_MODULE_H_

#ifdef __cplusplus
    #include <iostream>
    extern "C" {
#else
    #include <stdio.h>
#endif

#include <stdint.h>
#include <string.h>

#define STACK_LENGTH       ( 12 )
#define DATA_TYPE           uint16_t
typedef enum
{
    errOK,
    errNoFreeSpace,
    errBufferEmpty,
    errBufferFull
}eBufferErrors_t;

typedef struct
{
    DATA_TYPE* puctop;
    DATA_TYPE  Buffer[ STACK_LENGTH  ];

}stBuffer_t;

#ifndef __cplusplus

struct Stack_Object
{
    stBuffer_t stBuffer;

    eBufferErrors_t ( *Init )( struct Stack_Object *this );
    eBufferErrors_t ( *Push ) ( struct Stack_Object *this, DATA_TYPE *Data);
    eBufferErrors_t ( *Pop ) ( struct Stack_Object *this, DATA_TYPE *Data );
    eBufferErrors_t (*GetFreeSpace) (struct Stack_Object *this, DATA_TYPE *FreeSpace );
    eBufferErrors_t ( *Clear ) ( struct Stack_Object *this );

};
typedef struct Stack_Object Stack_Obj_t;

 eBufferErrors_t StackInit( Stack_Obj_t *this);
 eBufferErrors_t StackPush( Stack_Obj_t *this, DATA_TYPE *Data );
 eBufferErrors_t StackPop( Stack_Obj_t *this, DATA_TYPE* Data );
 eBufferErrors_t StackGetFreeSpace(Stack_Obj_t *this, DATA_TYPE *FreeSpace );
 eBufferErrors_t StackClear( Stack_Obj_t *this );
 void StackFuncConfig( Stack_Obj_t* this);

#else
}
class Stack
{
private:   
    stBuffer_t stBuffer;
public:

    eBufferErrors_t DataPush( DATA_TYPE *Data  );
    eBufferErrors_t DataPop( DATA_TYPE* Data );
    eBufferErrors_t GetFreeSpace( DATA_TYPE *FreeSpace );
    eBufferErrors_t StackClear();
    Stack(/* args */);
};
#endif /* #ifndef __cplusplus */

#endif /* _STACK_MODULE_H_ */