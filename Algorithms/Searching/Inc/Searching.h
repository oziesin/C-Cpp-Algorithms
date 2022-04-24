#ifndef _SEARCHING_H_
#define _SEARCHING_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define DATA_TYPE     uint8_t
#define SEARCH_FAULT  0xFF

typedef enum
{
    False,
    True
}e_Bool;

DATA_TYPE LinearSearch( DATA_TYPE* puxData, size_t uxLen ,DATA_TYPE uxLookUp );
DATA_TYPE BinarySearch( DATA_TYPE* puxData, DATA_TYPE uxLeft, DATA_TYPE uxRight, DATA_TYPE uxLookUp );
DATA_TYPE JumpSearch( DATA_TYPE* puxData, size_t uxLen ,DATA_TYPE uxLookUp );
e_Bool exactMatch(char *text, char *pat);
e_Bool StringSearch(char *text, char *pat);

#endif /* _SEARCHING_H_ */