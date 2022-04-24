/*******************************************************************************/
/*************************Include Headers**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*************************Macro Definations***************************************/
#define DISABLE     ( 0 )
#define ENABLE      ( 1 )
/*************************Type Defination***************************************/
typedef uint8_t     StateID_t;       

typedef union
{
    uint8_t ucByte;
    struct
    {
        uint8_t  b0:1;
        uint8_t  b1:1;
        uint8_t  b2:1;
        uint8_t  b3:1;
        uint8_t  b4:1;
        uint8_t  b5:1;
        uint8_t  b6:1;
        uint8_t  b7:1;
    }stBits;
    
} stSTA_Bits_t;


typedef struct
{
    StateID_t   stSrcState;
    StateID_t   stDstState;
    StateID_t   stCurState;
}stSTA_t;

typedef struct 
{
    void (*Main)(StateID_t);     
}SystemState_t;
/*************************Global Variables***************************************/
    stSTA_t stSTA;
    SystemState_t SystemState;
    stSTA_Bits_t stSTA_Bits;
/*************************Function Decleration***************************************/
void SysStateChangeTo( StateID_t stTargetState );
void StatePwrOn(void);
void StateIdle(void);
void StateMenu(void);
/************************************************************************/

#define mSTATES_TM( eState ,fncState)    eState

typedef enum
{
    #include "StatesAll.h"
    ,eStateMax
}eStatesId_t;

#if ( defined mSTATES_TM )
    #undef mSTATES_TM
#endif  /* ( defined mSTATES_TM ) */

#define mSTATES_TM( eState ,fncState)    fncState

const SystemState_t tstStates[]=
{
  #include "StatesAll.h"
};
/************************************************************************/

int main()
{
    do
    {
        tstStates[stSTA.stDstState].Main(stSTA.stSrcState);       

    } while (1);
}

void StatePwrOn(void)
{
    printf("State Pwr On\n");
    SysStateChangeTo( eStateIdle );
}
void StateIdle(void)
{
    printf("State Idle \n");
    SysStateChangeTo( eStateMenu );
    printf("MENU YE GECIS \n");

}
void StateMenu(void)
{
    printf("State Menu\n");
    SysStateChangeTo( eStateIdle );
    printf("IDLE GECIS \n");
}

void SysStateChangeTo( StateID_t stTargetState )
{
    if ( stTargetState < eStateMax )
    {
        stSTA.stSrcState = stSTA.stDstState;
        stSTA.stDstState = stTargetState;
    }
}
