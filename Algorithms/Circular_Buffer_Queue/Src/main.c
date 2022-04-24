
#include "CircularBuffer.h"

  uint16_t ADC_data[] = {2048,4002,168,1235,4005,3891};
  uint16_t PopData[15];

int main(int argc,char **argv) 
{
  CircularBuffer_Obj_t CircularBuffer_Obj;

  CircularBufferFuncConfig( &CircularBuffer_Obj );

  CircularBuffer_Obj.Init( &CircularBuffer_Obj );
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[0],sizeof(ADC_data[0]));
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[1],sizeof(ADC_data[0]));
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[2],sizeof(ADC_data[0]));
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[3],sizeof(ADC_data[0]));
  CircularBuffer_Obj.Pop(&CircularBuffer_Obj ,&PopData[0],sizeof(PopData[0]));
  CircularBuffer_Obj.Pop(&CircularBuffer_Obj ,&PopData[1],sizeof(PopData[0]));
  CircularBuffer_Obj.Pop(&CircularBuffer_Obj ,&PopData[2],sizeof(PopData[0]));
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[4],sizeof(ADC_data[0]));
  CircularBuffer_Obj.Push(&CircularBuffer_Obj ,&ADC_data[5],sizeof(ADC_data[0]));

}

