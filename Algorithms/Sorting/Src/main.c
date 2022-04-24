#include "Sorting.h"

void PrintArr(uint8_t *Arr, size_t Size);
int main()
{
    

//   uint8_t data[] = {7,8,5,2,4,6,3};
    uint8_t data[] = { 12 ,34 ,54 ,2 ,3 };

    PrintArr(data,sizeof(data));

//    InsertionSort(data,sizeof(data));
//    SelectionSort(data,sizeof(data));
    BubbleSort(data,sizeof(data));
//    ShellSort(data,sizeof(data));
//    HeapSort(data,sizeof(data));

    PrintArr(data,sizeof(data));
}

void PrintArr(uint8_t *Arr, size_t Size)
{
    for (uint8_t i = 0; i < Size; i++)
    {
        printf("Data[%d] :%d\n",i,Arr[i]);
    }
}