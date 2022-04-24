#include "CircularBuffer.h"

#ifdef __cplusplus

CircularBuffer::CircularBuffer(/* args */)
{
    stBuffer.puctail =  stBuffer.tucCircularBuff ;
    stBuffer.puchead =  stBuffer.tucCircularBuff ;
    memset(  stBuffer.tucCircularBuff , 0, sizeof( stBuffer.tucCircularBuff ) );   
    std::cout << "Circular Buffer Initialize Cpp"<< std::endl;

}

eBufferErrors_t CircularBuffer::CircularBufferPush(const void* vpData,size_t stSize)
{   
    uint8_t FreeSpace, Status;
    
    Status = this->CircularBufferGetFreeSpace(&FreeSpace);

    if ( FreeSpace < stSize )
    {
        return errNoFreeSpace;  // 1 errNoFreeSpace
    }

    if ( (this->stBuffer.puctail) >= &(this->stBuffer.tucCircularBuff[CIRCULAR_BUFFER_LAST_IDX]) )
    {
        this->stBuffer.puctail = this->stBuffer.tucCircularBuff;
    }
    memcpy( this->stBuffer.puctail, vpData, stSize );

    this->stBuffer.puctail += stSize;
    std::cout << " Pushed  " << *(uint16_t*)vpData << std::endl;
    return errOK;   // 0 errOK
}

eBufferErrors_t CircularBuffer::CircularBufferPop(void* vpData, size_t Size)
{
    uint8_t FreeSpace, Status;
    
    Status = this->CircularBufferGetFreeSpace(&FreeSpace);

    if ( FreeSpace == 0 )
    {
        return errBufferEmpty;  // 2 errBufferEmpty
    }

    if ( this->stBuffer.puchead == &this->stBuffer.tucCircularBuff[CIRCULAR_BUFFER_LAST_IDX])
    {
        this->stBuffer.puchead = this->stBuffer.tucCircularBuff;
    }
    memcpy(vpData,this->stBuffer.puchead,Size);
    
    *( this->stBuffer.puchead ) = 0;
    
    this->stBuffer.puchead += Size;
    
    std::cout << " Popped  " << *(uint16_t*)vpData << std::endl;
    return errOK;   // 0 errOK
}

eBufferErrors_t CircularBuffer :: CircularBufferGetFreeSpace( uint8_t *FreeSpace )
{
    
    if( this->stBuffer.puchead > this->stBuffer.puctail )
    {
        *FreeSpace = ( CIRCULAR_BUFFER_LENGTH - ( this->stBuffer.puchead - this->stBuffer.puctail ) - 1 );
    }
    else
    {
        *FreeSpace = ( CIRCULAR_BUFFER_LENGTH - ( this->stBuffer.puctail - this->stBuffer.puchead ) - 1 );
    }
    std::cout << " Get Free Space " << (uint16_t)*FreeSpace << std::endl;
    return errOK;
}

eBufferErrors_t CircularBuffer ::CircularBufferClear()
{
    memset( this->stBuffer.tucCircularBuff, 0, sizeof( this->stBuffer.tucCircularBuff ) );
    std::cout << " Clear All Buffer" << std::endl;

    return errOK;    // 0 errOK               
}
#else


 eBufferErrors_t CircularBufferInit( CircularBuffer_Obj_t *this)
{
    this->stBuffer.puctail = this->stBuffer.tucCircularBuff;
    this->stBuffer.puchead = this->stBuffer.tucCircularBuff;

    memset( this->stBuffer.tucCircularBuff, 0, sizeof( this->stBuffer.tucCircularBuff ) );   

    printf("Circular Buffer Initialize C\n");

    return errOK;
}

 eBufferErrors_t CircularBufferPush( CircularBuffer_Obj_t *this, const void *Data, size_t Size )
{
    uint8_t FreeSpace, Status;

    Status = CircularBufferGetFreeSpace( this,&FreeSpace );

    if ( FreeSpace < Size )
    {
        return errNoFreeSpace;
    }

    if ( this->stBuffer.puctail >= &this->stBuffer.tucCircularBuff[CIRCULAR_BUFFER_LAST_IDX])
    {
        this->stBuffer.puctail = this->stBuffer.tucCircularBuff;
    }
    memcpy( this->stBuffer.puctail, Data, Size );
    this->stBuffer.puctail+=Size;
    printf("Pushed Data %d \n",*(uint16_t*)Data);
    return errOK;
}

 eBufferErrors_t CircularBufferPop( CircularBuffer_Obj_t *this, void* Data, size_t Size)
{
    uint8_t Status, FreeSpace;

    Status = CircularBufferGetFreeSpace( this, &FreeSpace );

    if ( FreeSpace == 0 )
    {
        return errBufferEmpty;
    }

    if ( this->stBuffer.puchead == &this->stBuffer.tucCircularBuff[CIRCULAR_BUFFER_LAST_IDX])
    {
        this->stBuffer.puchead = this->stBuffer.tucCircularBuff;
    }
    memcpy(Data,this->stBuffer.puchead,Size);

    *( this->stBuffer.puchead ) = 0;
    this->stBuffer.puchead+= Size;

    printf("Popped Data %d \n",*(uint16_t*)Data);

    return errOK;
}

 eBufferErrors_t CircularBufferClear( CircularBuffer_Obj_t *this )
{
    memset( this->stBuffer.tucCircularBuff, 0, sizeof( this->stBuffer.tucCircularBuff ) );
    printf(" Clear All Buffer \n");

    return errOK;
}

 eBufferErrors_t CircularBufferGetFreeSpace(CircularBuffer_Obj_t *this, uint8_t *FreeSpace )
{
    if( this->stBuffer.puchead > this->stBuffer.puctail)
    {
        *FreeSpace = ( CIRCULAR_BUFFER_LENGTH - ( this->stBuffer.puchead - this->stBuffer.puctail ) - 1 );
    }
    else
    {
        *FreeSpace = ( CIRCULAR_BUFFER_LENGTH - ( this->stBuffer.puctail - this->stBuffer.puchead ) - 1 );
    }
    
    printf("Getting Free Space %d \n",*FreeSpace);

    return errOK;
}

void CircularBufferFuncConfig( CircularBuffer_Obj_t* CircularBuffer_Obj)
{
    CircularBuffer_Obj->Init = CircularBufferInit;
    CircularBuffer_Obj->Push = CircularBufferPush;
    CircularBuffer_Obj->Pop = CircularBufferPop;
    CircularBuffer_Obj->GetFreeSpace = CircularBufferGetFreeSpace;
    CircularBuffer_Obj->Clear = CircularBufferClear;
}

#endif /* __cplusplus */

