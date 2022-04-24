#ifndef _SORTING_H_
#define _SORTING_H_

#include <stdio.h>
#include <stdint.h>

#define mSWAP(a, b) ( ( a == b ) ? a : ( a ^= b, b ^= a,a ^= b ) )
//#define mMIN(a,b)   ( ( a <= b ) ? a : b )
//#define mMID(a)     ( ( a % 2 == 0 ) ? ( a / 2 ) : (( a / 2 ) + 1 ) )

void InsertionSort( uint8_t * data, uint8_t Len );

void SelectionSort( uint8_t *data, uint8_t Len );

void BubbleSort( uint8_t *data, uint8_t Len );

void ShellSort( uint8_t *data, uint8_t Len );

void Heapify(uint8_t *data, uint8_t Len, uint8_t idx);
void HeapSort( uint8_t *data, uint8_t Len );

#endif /* _SORTING_H_ */