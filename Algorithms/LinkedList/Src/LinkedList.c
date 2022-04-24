#include "LinkedList.h"

#ifdef __cplusplus 

LinkedList::LinkedList()
{
  std::cout << "Bit :" << this->Status.b0Init << std::endl;
  TRACE_ASSERT( ! this->Status.b0Init );

  this->Node = new Node_t; 
  this->Node->Next = NULL;
  this->Node->Data = 0;
  this->Size = 1;

  std::cout << "Linked List Initialize Cpp" << std::endl;
}

LinkedList::~LinkedList()
{
  uint8_t Status;

  while ( this->Size > 0 )
  {
    Status = this->Delete();
  }
  std::cout << "All List Deleted." << std::endl;
}

eBufferErrors_t LinkedList::Add ( DATA_TYPE Data )
{
  if ( this->Status.b1FirstData == 0 )
  {
    this->Status.b1FirstData = 1;
    this->Node->Data = Data;
    this->Node->Next = NULL;
    return errOK;
  }

  else if( this->Size == LIST_LENGTH )
  {
    std::cout << "Linked List is Full." << std::endl;
    return errNoFreeSpace;
  }

  Node_t *Temp;

  Temp = this->Node;

  while (Temp->Next != NULL)
  {
    Temp = Temp->Next;
  }
  Temp->Next = new Node_t;
  Temp=Temp->Next;

  Temp->Data = Data;
  Temp->Next = NULL;

  ++this->Size;
  return errOK;
  
}
 
eBufferErrors_t LinkedList::Delete ()
{
  if ( this->Status.b1FirstData == 0 )
  {
    std::cout << "Linked Lis is Empty" << std::endl;
    
    return errBufferEmpty;
  }
  else if ( this->Node->Next == NULL )
  {
    this->Status.b1FirstData = 0;

    delete(this->Node);

    --this->Size;

    return errOK;
  }

  Node_t *Temp;

  Temp = this->Node;

  while (Temp->Next->Next != NULL)
  {
    Temp = Temp->Next;
  }

  Temp->Next= NULL;
  Temp=Temp->Next;

  delete(Temp);
  --this->Size;

  return errOK;
}

void LinkedList::Print ()
{
  Node_t *Temp;
  uint8_t idx;

  Temp = this->Node;
  std::cout << "****    **" << std::endl;
  for ( idx = 0; idx <this->Size - 1 ; ++idx)
  {
    std::cout << "DATA  : " << Temp->Data << std::endl;
    Temp=Temp->Next;
  }
}
#else

eBufferErrors_t Init( LinkedList_Obj_t *this)
{
// printf("Bit :%d\n",this->Status.b0Init);
TRACE_ASSERT( ! this->Status.b0Init );

this->Node = malloc( sizeof( Node_t ) ); 
this->Node->Next = NULL;
this->Node->Data = 0;
this->Size = 1;

printf("Linked List Initialize C\n");

return errOK;
}

eBufferErrors_t Add(LinkedList_Obj_t *this,DATA_TYPE Data)
{
if ( this->Status.b1FirstData == 0 )
{
  this->Status.b1FirstData = 1;
  this->Node->Data = Data;
  this->Node->Next = NULL;
  return errOK;
}

else if( this->Size == LIST_LENGTH )
{
  printf("Linked List is Full.\n");
  return errNoFreeSpace;
}

Node_t *Temp;

Temp = this->Node;

while (Temp->Next != NULL)
{
  Temp = Temp->Next;
}
Temp->Next = malloc( sizeof ( Node_t ) );
Temp=Temp->Next;

Temp->Data = Data;
Temp->Next = NULL;

++this->Size;
return errOK;
}

eBufferErrors_t Delete( LinkedList_Obj_t *this )
{
if ( this->Status.b1FirstData == 0 )
{
    printf("Linked Lis is Empty");
    return errBufferEmpty;
}
else if ( this->Node->Next == NULL )
{
  this->Status.b1FirstData = 0;

  free(this->Node);

  --this->Size;

  return errOK;
}

Node_t *Temp;

Temp = this->Node;

while (Temp->Next->Next != NULL)
{
  Temp = Temp->Next;
}

Temp->Next= NULL;
Temp=Temp->Next;

free(Temp);
--this->Size;

return errOK;
}

eBufferErrors_t Clear( LinkedList_Obj_t *this )
{
uint8_t Status;
if ( ! (this->Size > 0) )
{
  return errBufferEmpty;
}

while ( this->Size > 0 )
{
  Status = this->Delete(this);
  TRACE_ASSERT( Status != errOK );
}
return errOK;
}

void  Print( struct LinkedList_Object *this )
{
  Node_t *Temp;
  uint8_t idx;

  Temp = this->Node;
  printf("****    **\n");
  for ( idx = 0; idx <this->Size - 1 ; ++idx)
  {
    printf("DATA  : %d\n",Temp->Data);
    Temp=Temp->Next;
  }
}

void LinkedListFuncConfig( LinkedList_Obj_t* this)
{
  this->Init = Init;
  this->Add = Add;
  this->Delete = Delete;
  this->Clear = Clear;
  this->Print = Print;
  this->Status.b0Init = 1;
}
#endif  /*  #ifdef __cplusplus */