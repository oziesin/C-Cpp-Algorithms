#include "CircularBuffer.h"

int main(  )
{
  
    CircularBuffer CircularBuffer_Obj;
    uint16_t ADC_data[] = {2048,4002,168,1235,4005,3891} ; // test
    uint16_t PopData[15];   // Test
    uint8_t u8Status;

    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[0],sizeof(*ADC_data));
    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[1],sizeof(*ADC_data));
    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[2],sizeof(*ADC_data));
    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[3],sizeof(*ADC_data));

    u8Status = CircularBuffer_Obj.CircularBufferPop((void*)&PopData[0],sizeof(PopData[0]));
    u8Status = CircularBuffer_Obj.CircularBufferPop((void*)&PopData[1],sizeof(PopData[1]));
    u8Status = CircularBuffer_Obj.CircularBufferPop((void*)&PopData[2],sizeof(PopData[2]));

    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[4],sizeof(*ADC_data));
    u8Status = CircularBuffer_Obj.CircularBufferPush( (void*) &ADC_data[5],sizeof(*ADC_data));
    
}