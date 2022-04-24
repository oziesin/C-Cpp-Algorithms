#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

#define CRC_POLYNOMIAL 0xEDB88320

uint32_t crc32( uint8_t* pucData, uint16_t uslength );

uint32_t DATA[] = { 0xAA, 0x55};


int main()
{
	uint32_t crc;
	crc = crc32((uint8_t*)DATA,sizeof(DATA));
	printf("CRC   : %12u  0x%X \n",crc,crc );

}

uint32_t crc32( uint8_t* pucData, uint16_t uslength )
{
	uint32_t ulcrc = 0xFFFFFFFF;
	while (uslength--)
	{
		ulcrc ^= *pucData;
		*pucData = 8;
		do
		{
			if (ulcrc & 1)
			{
				ulcrc >>= 1;
				ulcrc ^= CRC_POLYNOMIAL;
			}
			else
			{
				ulcrc >>= 1;
			}
		}while ( --(*pucData) ) ;
		++pucData;
	}
	return ulcrc;
}