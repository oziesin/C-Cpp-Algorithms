
#include "LinkedList.h"


int main(int argc,char **argv) 
{
  LinkedList LinkedList_Obj;
  eBufferErrors_t  Status;
    
  for (uint8_t i = 1; i < 8; i++)
  {
    Status = LinkedList_Obj.Add( 10 * i );
    TRACE_ASSERT( Status != errOK );
  }
  
  LinkedList_Obj.Print();

  Status = LinkedList_Obj.Delete();
  TRACE_ASSERT( Status != errOK );
  Status = LinkedList_Obj.Delete();
  TRACE_ASSERT( Status != errOK );
  Status = LinkedList_Obj.Delete();
  TRACE_ASSERT( Status != errOK );

  LinkedList_Obj.Print();


  return 0;
}