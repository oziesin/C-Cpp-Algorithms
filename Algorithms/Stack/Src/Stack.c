#include "Stack.h"

#ifdef __cplusplus

Stack::Stack(/* args */)
{
    this->stBuffer.puctop = this->stBuffer.Buffer;

    memset( this->stBuffer.Buffer, 0, sizeof( this->stBuffer.Buffer ) );   

    std::cout << "Stack Initialize Cpp" << std::endl;

}

eBufferErrors_t Stack::DataPush( DATA_TYPE *Data  )
{
    DATA_TYPE FreeSpace;
    uint8_t Status;

    Status = this->GetFreeSpace( &FreeSpace );
    if ( FreeSpace < sizeof(Data) )
    {
        return errNoFreeSpace;
    }

    *this->stBuffer.puctop = *Data;

    this->stBuffer.puctop++;

    std::cout << "Pushed Data " << *Data << std::endl;

    return errOK;

}

eBufferErrors_t Stack::DataPop( DATA_TYPE* Data )
{
     DATA_TYPE FreeSpace;
    uint8_t Status;

    Status = this->GetFreeSpace( &FreeSpace );
    if ( FreeSpace == 0 )
    {
        return errBufferEmpty;
    }
    --this->stBuffer.puctop;

    *Data = *this->stBuffer.puctop;

    *( this->stBuffer.puctop ) = 0;

    std::cout << "Popped Data " << *Data << std::endl;

    return errOK;
}

eBufferErrors_t Stack::GetFreeSpace( DATA_TYPE *FreeSpace )
{
    *FreeSpace = ( STACK_LENGTH - ( this->stBuffer.puctop - this->stBuffer.Buffer ) );
 
    std::cout << "Free Space :" << *FreeSpace << std::endl;

    return errOK;
}

eBufferErrors_t Stack::StackClear()
{
    memset( this->stBuffer.Buffer, 0, sizeof( this->stBuffer.Buffer ) );
    std::cout << " Clear All Buffer " << std::endl;

    return errOK;
}

#else
eBufferErrors_t StackInit( Stack_Obj_t *this)
{
    this->stBuffer.puctop = this->stBuffer.Buffer;

    memset( this->stBuffer.Buffer, 0, sizeof( this->stBuffer.Buffer ) );   

    printf("Stack Initialize C\n");

    return errOK;
}

 eBufferErrors_t StackPush( Stack_Obj_t *this, DATA_TYPE *Data )
{
    DATA_TYPE FreeSpace;
    uint8_t Status;

    Status = StackGetFreeSpace( this, &FreeSpace );
    if ( FreeSpace < sizeof(Data) )
    {
        return errNoFreeSpace;
    }

    *this->stBuffer.puctop = *Data;

    this->stBuffer.puctop++;

    printf("Pushed Data %d \n",*Data);

    return errOK;
}

 eBufferErrors_t StackPop( Stack_Obj_t *this, DATA_TYPE* Data )
{
    DATA_TYPE FreeSpace;
    uint8_t Status;

    Status = StackGetFreeSpace( this, &FreeSpace );
    if ( FreeSpace == 0 )
    {
        return errBufferEmpty;
    }
    --this->stBuffer.puctop;

    *Data = *this->stBuffer.puctop;

    *( this->stBuffer.puctop ) = 0;

    printf("Popped Data %d \n",*Data);

    return errOK;
}

 eBufferErrors_t StackClear( Stack_Obj_t *this )
{
    memset( this->stBuffer.Buffer, 0, sizeof( this->stBuffer.Buffer ) );
    printf(" Clear All Buffer \n");

    return errOK;
}

 eBufferErrors_t StackGetFreeSpace(Stack_Obj_t *this, DATA_TYPE *FreeSpace )
{   
    *FreeSpace = ( STACK_LENGTH - ( this->stBuffer.puctop - this->stBuffer.Buffer ) );
 
    printf("Free Space : %d\n",*FreeSpace);

    return errOK;
}

void StackFuncConfig( Stack_Obj_t *this)
{
    this->Init = &StackInit;
    this->Push = &StackPush;
    this->Pop = &StackPop;
    this->GetFreeSpace = &StackGetFreeSpace;
    this->Clear = &StackClear;
}

#endif  /*  #ifdef __cplusplus */