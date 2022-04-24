#include "Sorting.h"

void InsertionSort( uint8_t *data, uint8_t Len )
{
    uint8_t i,j,key;
    printf("\n Insertion Sorting\n \n");
    for ( i = 1; i < Len; ++i)
    {
        key = data[i];
        j = i-1;
        while ( key <= data[ j ] && ( j >= 0 ) )
        {
            mSWAP(data[j+1],data[j]);
            j--;
        }
    }
}

void SelectionSort( uint8_t *data, uint8_t Len )
{
    uint8_t i, j, idx;
    printf("\n Selection Sorting\n \n");

    for ( i = 0; i < Len-1; ++i)
    {
        idx = i;
        for ( j = i+1; j < Len; ++j)
        {
           if ( data[j] < data[idx] )
           {
               idx = j;
           }
        }
        mSWAP(data[i],data[idx]);
    }
}

void BubbleSort( uint8_t *data, uint8_t Len )
{
    uint8_t i;
    printf("\n Bubble Sorting\n \n");

    while ( Len > 1 )
    {
        for ( i = 0; i < Len-1; i++)
        {
            if ( data[i + 1] < data [i] )
            {
            mSWAP(data[i],data[i+1]);
            }    
        }
        --Len;
    }
}

void ShellSort( uint8_t *data, uint8_t Len )
{
    uint8_t i, j, gap;   
    printf("\n Shell Sorting\n \n");

    for (gap = Len/2 ; gap > 0; gap/=2)
    {
        for ( i = gap; i < Len; i++)
        {
            j = i;
            while ( j >= gap && data[j-gap] > data[j] )
            {
                mSWAP(data[j],data[j-gap]);
                j-=gap;
            }
        }
    } 
}

void Heapify(uint8_t *data, uint8_t Len, uint8_t idx) 
{
    // Find largest among root, left child and right child
    uint8_t largest = idx;
    uint8_t left = 2 * idx + 1;
    uint8_t right = 2 * idx + 2;

    if (left < Len && data[left] > data[largest])
    {
        largest = left;
    }

    if (right < Len && data[right] > data[largest])
    {
        largest = right;
    }
    // Swap and continue heapifying if root is not largest
    if (largest != idx) 
    {
        mSWAP( data[idx], data[largest] );
        Heapify(data, Len, largest);
    }
}

void HeapSort( uint8_t *data, uint8_t Len )
{
    int16_t i;
    printf("\n Heap Sorting\n \n");

    // Build max heap
    i = ( Len / 2 ) - 1;
    while( i >= 0)
    {
      Heapify(data, Len, i);
      --i;
    }
    // Heap sort
    i = Len - 1;
    while( i >= 0 ) 
    {
      mSWAP(data[0], data[i]);
      // Heapify root element to get highest element at root again
      Heapify(data, i, 0);
      --i;
    }
}
