/* This module can be use in C/C++ Projects both. 
 * Includes Dynamic LinkedList data structre with boundary.
 * Modify boundary @LIST_LENGTH for your need.
 * Modify @DATA_TYPE for your need
 * @FUN Add Adds the data to end of the list.
 * @FUN Delete deletes the data from end of the list.
 * @FUN Print prints the all list datas.
 * @FUN Clear is deconstructer function.
 * @FUN Init is constructer function.
 */
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_



#ifdef __cplusplus
  #include <iostream>
  extern "C" {
#else
  #include <stdio.h>
  #include "stdlib.h"
#endif /* #ifndef __cplusplus */

#include "stdint.h"
#include "assert.h"

#define LIST_LENGTH                  ( 10 )
#define DATA_TYPE                    uint16_t

#define USE_DEBUG                    1

#ifdef USE_DEBUG
  #define TRACE_ASSERT( Control )      { assert(!Control); }
#else
  #define TRACE_ASSERT( Control )      { }
#endif /* #ifdef USE_DEBUG */

typedef enum
{
    errOK,
    errNoFreeSpace,
    errBufferEmpty,
    errBufferFull
}eBufferErrors_t;

typedef union 
{
  uint8_t u8Status;
  struct 
  {
    uint8_t b0Init:1;
    uint8_t b1FirstData:1;
    uint8_t b2:1;
    uint8_t b3:1;
    uint8_t b4:1;
    uint8_t b5:1;
    uint8_t b6:1;
    uint8_t b7:1;
  };
}Status_t;

struct NodeType
{
  DATA_TYPE  Data;
  struct NodeType* Next;
};

typedef struct NodeType Node_t;

#ifndef __cplusplus
struct LinkedList_Object
{

  Node_t* Node; 

  uint8_t Size;
  Status_t Status;
  
  eBufferErrors_t ( *Init )( struct LinkedList_Object *this);
  eBufferErrors_t ( *Add ) ( struct LinkedList_Object *this, DATA_TYPE Data);
  eBufferErrors_t ( *Delete ) ( struct LinkedList_Object *this );
  eBufferErrors_t ( *Clear ) ( struct LinkedList_Object *this );
  void            ( *Print ) ( struct LinkedList_Object *this );
};   
typedef   struct LinkedList_Object LinkedList_Obj_t;

void LinkedListFuncConfig( LinkedList_Obj_t* LinkedList_Obj_t);

#else 
}
class LinkedList
{
private:   
  Node_t *Node;

  uint8_t Size;
  Status_t Status;

public:

  LinkedList();
  ~LinkedList();
  eBufferErrors_t Add ( DATA_TYPE Data );
  eBufferErrors_t Delete (void);
  void            Print (void);
};

#endif /* #ifndef __cplusplus */


#endif /* _LINKED_LIST_H_ */