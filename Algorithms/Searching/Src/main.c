#include "Searching.h"


int main()
{
    //uint8_t Array[] = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    uint8_t Array[] = {10, 20, 30, 50, 60, 80, 100, 110, 130, 170};

    uint8_t u8RetVal;
    // u8RetVal = BinarySearch( Array, 0, (sizeof(Array) - 1), 50 );

    //u8RetVal = JumpSearch ( Array, sizeof(Array), 50 );
    
    u8RetVal = StringSearch(" Hello World", "World");

    printf("Return Binary :%d\n",u8RetVal);
}

