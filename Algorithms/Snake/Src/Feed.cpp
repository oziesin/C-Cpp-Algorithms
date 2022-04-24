#include "Feed.h"

/*********************************************** FEED CHECKFEED  *********************************************** 
 * @Brief This function generate a feed for sneak periodically and check the state.  
 * @Param myFeed is the checked  Feed Object.
 * @Return true if feed still active, otherwise false.
 ****************************************************************************************************************/
bool Feed::CheckFeed(Area *myArea,Feed *myFeed)
{
  myFeed->current = std::chrono::steady_clock::now();
  myFeed->duration = myFeed->current - myFeed->start;
  // cout<< (uint32_t)(myFeed->duration.count()*1000) << endl;

  if( (((uint32_t)(myFeed->duration.count()*1000)) > myFeed->TimeOut) && myFeed->isActive == false )
  {
    do
    {
      myFeed->x = ( 1 + rand() % ( AREA_WIDTH - 1) );
      myFeed->y = ( 1 + rand() % ( AREA_HEIGHT - 1 ) );

    } while ( myArea->area[myFeed->x][myFeed->y] == SNAKE_CHAR && myArea->area[myFeed->x][myFeed->y] == FEED_CHAR );

    myArea->area[myFeed->x][myFeed->y] = FEED_CHAR;
    myFeed->isActive = true;
    myFeed->start = std::chrono::steady_clock::now();

    // cout<< "True" << endl;
  }
  else if( (((uint32_t)(myFeed->duration.count()*1000)) > myFeed->TimeOut) && myFeed->isActive == true )
  {
    // cout<< "False" << endl;
    myArea->area[this->x][this->y] = DEFAULT_SPACE_CHAR;
    myFeed->isActive = false;
    myFeed->start = std::chrono::steady_clock::now();
  }
  return myFeed->isActive;
}

Feed::Feed(Area *myArea, bool isActv,uint16_t interval)
{
  this->isActive = isActv;
  this->start =  std::chrono::steady_clock::now();
  this->TimeOut = interval;

  if( this->isActive == true)
  {
    do
    {
      this->x = ( 1 + rand() % AREA_WIDTH );
      this->y = ( 1 + rand() % AREA_HEIGHT );

    } while ( myArea->area[this->x][this->y] == SNAKE_CHAR && myArea->area[this->x][this->y] == FEED_CHAR );
    
    myArea->area[this->x][this->y] = FEED_CHAR;
  }
}
