
#include "Stack.h"

    uint16_t ADC_data[] = {2048,4002,168,1235,4005,3891};
    uint16_t PopData[15];

int main(int argc,char **argv) 
{
    Stack myStack;

    myStack.DataPush(&ADC_data[0]);
    myStack.DataPush( &ADC_data[1]);
    myStack.DataPush( &ADC_data[2]);
    myStack.DataPush( &ADC_data[3]);

    myStack.DataPop( &PopData[0]);
    myStack.DataPop( &PopData[1]);
    myStack.DataPop( &PopData[2]);
    myStack.DataPush( &ADC_data[4]);
    myStack.DataPush( &ADC_data[5]);
}

 