#include "Snake.h"

HANDLE hEvent;
HANDLE hTimerQueue = NULL;

using namespace std;

uint8_t Keys[e_DirMax];

/************************************************* HIDE CURSOR  *************************************************
 * @Brief This function hide the cursor on terminal.
 ****************************************************************************************************************/
void HideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out,&cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out,&cursorInfo);
}

/*************************************************** READ KEY *************************************************** 
 * @Brief This function reads the key asynchronous.
 ****************************************************************************************************************/
void ReadKey()
{
    for (uint8_t i = 0; i < e_DirMax; ++i)
    {
        *( Keys + i ) = (uint8_t)( GetAsyncKeyState( i + VK_LEFT ));
    }
}

/************************************************* KEY CONTROL ************************************************** 
 * @Brief This function determines the directon of snake.
 * @Param mySnake is Snake object
 ****************************************************************************************************************/
void KeyControl(Snake *mySnake)
{
  ReadKey();
  if ( Keys[e_DirLeft] != 0 )
  {
    if ( mySnake->stSnake[0].Dir != e_DirRight )
    {
      mySnake->stSnake[0].Dir = e_DirLeft;
    }
  }
  else if ( Keys[e_DirRight] != 0 )
  {
    if ( mySnake->stSnake[0].Dir != e_DirLeft )
    {
      mySnake->stSnake[0].Dir = e_DirRight;
    }
  }
  else if ( Keys[e_DirUp] != 0 )
  {
    if ( mySnake->stSnake[0].Dir != e_DirDown )
    {
      mySnake->stSnake[0].Dir = e_DirUp;
    }
  }
  else if ( Keys[e_DirDown] != 0 )
  {
    if ( mySnake->stSnake[0].Dir != e_DirUp )
    {
      mySnake->stSnake[0].Dir = e_DirDown;
    }
  }
}

int main(int argc, char *argv[])
{
  Snake mySnake;
  Area  myArea;
  Feed myFeed = Feed ( &myArea, true, 10000 );
  bool isActiveFeed;
  uint8_t i;
  HideCursor();

  while (1)
  { 
    myArea.DefaultArea();
    myArea.CreateBoundaries();

    KeyControl(&mySnake);
    if( isActiveFeed == true )
    {
      myArea.area[myFeed.x][myFeed.y] = FEED_CHAR;
    }
    else
    {
       myArea.area[myFeed.x][myFeed.y] = DEFAULT_SPACE_CHAR;
    }
    isActiveFeed = myFeed.CheckFeed(&myArea, &myFeed);

    mySnake.MoveSnake( &myArea, &myFeed );

    if ( (mySnake.stSnake->x) == myFeed.x && (mySnake.stSnake->y) == myFeed.y)
    {
      myFeed.isActive = false;
      mySnake.GrowSnake();
    }  

    if ( mySnake.CheckConflictSnake ( &myArea ) == true )
    {
      break;
    }
    if( mySnake.QueueLen == MAX_SNAKE_LEN )
    {
      myArea.ExitArea("CONGRATULATIONS YOU WIN.");
      break;
    }

    mySnake.PutSnakeToArea( &myArea );
    myArea.ShowArea();
  }
  return 0;
}
