/* CAN BE CHANGE @AREA_WIDTH AND @AREA_HEIGH IF YOU WANT TO CHANGE AREA SIZE.
 * CAN BE CHANGE @BOUNDARIES_CHAR IF YOU WANT CHANGE THE FRAME CHARACHTER.
 * CAN BE CHANGE @SNAKE_CHAR IF YOU WANT CHANGE THE SNAKE CHARACHTER.
 * CAN BE CHANGE @FEED_CHAR IF YOU WANT CHANGE THE FEED CHARACHTER.
 */

#ifndef _AREA_H_
#define _AREA_H_

#include <stdint.h>
#include <windows.h>
#include <iostream>

#define AREA_WIDTH          80
#define AREA_HEIGHT         20
#define BOUNDARIES_CHAR     178
#define SNAKE_CHAR          219
#define FEED_CHAR           '*'
#define DEFAULT_SPACE_CHAR  ' '


class Area
{

public:
  uint8_t area[AREA_WIDTH][AREA_HEIGHT];

  void DefaultArea();
  void CreateBoundaries();
  void ExitArea(std::string str);
  void ShowArea();

};

void GotoXY(uint8_t x , uint8_t y);

#endif /* _AREA_H_*/


