#include "LinkedList.h"

int main(int argc,char **argv) 
{
  LinkedList_Obj_t LinkedList_Obj;
  eBufferErrors_t  Status;
  
  LinkedListFuncConfig( &LinkedList_Obj );
  
  Status = LinkedList_Obj.Init(&LinkedList_Obj);

  TRACE_ASSERT( Status != errOK );

  for (uint8_t i = 1; i < 6; i++)
  {
    Status = LinkedList_Obj.Add(&LinkedList_Obj,10*i);
    TRACE_ASSERT( Status != errOK );
  }
  
  LinkedList_Obj.Print( &LinkedList_Obj );

  Status = LinkedList_Obj.Clear( &LinkedList_Obj );
}


