#ifndef _FEED_H_
#define _FEED_H_

#include "Area.h"
#include <chrono>
#include <thread>
#include <cstdlib>

class Feed
{
private:
public:
  std::chrono::time_point<std::chrono::steady_clock> start,current;
  std::chrono::duration<double> duration;
  uint32_t TimeOut;
  uint8_t  x;
  uint8_t  y;
  bool     isActive;

  bool CheckFeed(Area *myArea,Feed *myFeed);
  Feed(Area *myArea, bool isActv,uint16_t interval);

};

#endif /* _FEED_H_*/