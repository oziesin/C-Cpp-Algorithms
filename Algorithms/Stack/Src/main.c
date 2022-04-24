
#include "Stack.h"




    uint16_t ADC_data[] = {2048,4002,168,1235,4005,3891};
    uint16_t PopData[15];
    

int main(int argc,char **argv) 
{
    Stack_Obj_t Stack_Obj;

    StackFuncConfig( &Stack_Obj );

    Stack_Obj.Init( &Stack_Obj);

    Stack_Obj.Push(&Stack_Obj ,&ADC_data[0]);
    Stack_Obj.Push(&Stack_Obj ,&ADC_data[1]);
    Stack_Obj.Push(&Stack_Obj ,&ADC_data[2]);
    Stack_Obj.Push(&Stack_Obj ,&ADC_data[3]);
    Stack_Obj.Pop(&Stack_Obj ,&PopData[0]);
    Stack_Obj.Pop(&Stack_Obj ,&PopData[1]);
    Stack_Obj.Pop(&Stack_Obj ,&PopData[2]);
    Stack_Obj.Push(&Stack_Obj ,&ADC_data[4]);
    Stack_Obj.Push(&Stack_Obj ,&ADC_data[5]);
}

 