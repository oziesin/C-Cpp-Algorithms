#include "stdio.h"
#include "stdint.h"
#include "time.h"

#define MIN_TO_SEC      ( 60 )
#define HOUR_TO_SEC     ( 60 * MIN_TO_SEC )
#define GMT             ( 3 )
#define GMT_BY_SEC      ( GMT * HOUR_TO_SEC )
typedef enum
{
    eIncludedDate,
    eOnlybyDay,
}eTimeConf_t;
struct tm CalcTimeFromUTC ( uint32_t UTC , eTimeConf_t eTimeConf);
int main()
{
    printf("%d",1<<7);
    uint32_t UTC;
    uint32_t UTCbyDay;  //  0-86400 arası
    struct tm stTime;

    while (1)
    {
        printf("UTC by Day :");
        scanf("%d", &UTCbyDay );
        UTCbyDay += GMT_BY_SEC;
        stTime = CalcTimeFromUTC( UTCbyDay, eOnlybyDay );
        printf("Time    : Hour  Min  Sec\n",stTime.tm_hour, stTime.tm_min, stTime.tm_sec ); 
        printf("Time    : %2d    %2d    %2d\n",stTime.tm_hour, stTime.tm_min, stTime.tm_sec ); 
        
    }
    
    stTime = CalcTimeFromUTC( UTCbyDay, eOnlybyDay );
}

struct tm CalcTimeFromUTC ( uint32_t UTC , eTimeConf_t eTimeConf)
{
 static struct tm sttm;

 switch ( eTimeConf )
 {
 case eIncludedDate:
    {
        
    }
 case eOnlybyDay:
    {
        sttm.tm_hour = UTC / HOUR_TO_SEC;
        sttm.tm_min  = ( UTC - ( sttm.tm_hour * HOUR_TO_SEC ) ) / MIN_TO_SEC; 
        sttm.tm_sec = UTC % 60;
        return sttm;
    }
    break;
 
 default:
     break;
 }


}

