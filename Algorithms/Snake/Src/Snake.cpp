#include "Snake.h"

/******************************************* SNAKE PUTSNAKETOAREA  ******************************************* 
 * @Brief This function put pixels from snake to Area matrix.  
 ****************************************************************************************************************/
void Snake::PutSnakeToArea(Area *myArea)
{
  for ( uint16_t i = 0; i < MAX_SNAKE_LEN; ++i )
  {
    if(this->stSnake[i].x == 0 && this->stSnake[i].y == 0 )  
    {
      break;
    }
    myArea->area[ this->stSnake[i].x ][this->stSnake[i].y] = SNAKE_CHAR;
  }
}

/*********************************************** SNAKE MOVESNAKE  *********************************************** 
 * @Brief This function moves the snake and check is feed eaten.  
 * @Param myFeed is the checked  Feed Object.
 ****************************************************************************************************************/
void Snake::MoveSnake( Area *myArea, Feed *mFeed )
{
  uint16_t i = 0;

  for ( i = 0; i < this->QueueLen ; ++i)
  {
    switch ( this->stSnake[i].Dir )
    {
      case e_DirRight:
      {
        ++this->stSnake[i].x;
        if(this->stSnake[i].x > AREA_WIDTH - 2 )
        {
          this->stSnake[i].x = 1;
        }
      }   
      break;
      case e_DirLeft:
      {
        --this->stSnake[i].x;
        if(this->stSnake[i].x < 1 )
        {
          this->stSnake[i].x = AREA_WIDTH - 2;
        }
      }
      break;
      case e_DirUp:
      {
        --this->stSnake[i].y;
        if(this->stSnake[i].y < 1 )
        {
          this->stSnake[i].y = AREA_HEIGHT - 2;
        }
      }
      break;
      case e_DirDown:
      {
        ++this->stSnake[i].y;
        if(this->stSnake[i].y > AREA_HEIGHT -2 )
        {
          this->stSnake[i].y = 1;
        }
      }
      break;

      default:
          return;
      break;
    }
    
  }
  
  for ( i = this->QueueLen - 1 ; i > 0; i--)
  {
    this->stSnake[i].Dir = this->stSnake[i - 1].Dir;
  }
}

/*********************************************** SNAKE GROWSNAKE  *********************************************** 
 * @Brief This function grows the snake length.
 ****************************************************************************************************************/
void Snake::GrowSnake()
{
    if( this->QueueLen >= MAX_SNAKE_LEN )
    {
        return;
    }
    switch ( this->stSnake[ this->QueueLen - 1].Dir )
        {
        case e_DirRight:
            this->stSnake[this->QueueLen].x =  this->stSnake[this->QueueLen - 1].x - 1;
            this->stSnake[this->QueueLen].y = this->stSnake[this->QueueLen - 1].y;
            this->stSnake[this->QueueLen].Dir = this->stSnake[this->QueueLen - 1].Dir;
            ++this->QueueLen;
        break;
        case e_DirLeft:
            this->stSnake[this->QueueLen].x =  this->stSnake[this->QueueLen - 1].x + 1;
            this->stSnake[this->QueueLen].y = this->stSnake[this->QueueLen - 1].y;
            this->stSnake[this->QueueLen].Dir = this->stSnake[this->QueueLen - 1].Dir;
            ++this->QueueLen;
        break;
        case e_DirUp:
            this->stSnake[this->QueueLen].x =  this->stSnake[this->QueueLen - 1].x ;
            this->stSnake[this->QueueLen].y = this->stSnake[this->QueueLen - 1].y + 1;
            this->stSnake[this->QueueLen].Dir = this->stSnake[this->QueueLen - 1].Dir;
            ++this->QueueLen;
        break;
        case e_DirDown:
            this->stSnake[this->QueueLen].x =  this->stSnake[this->QueueLen - 1].x;
            this->stSnake[this->QueueLen].y = this->stSnake[this->QueueLen - 1].y - 1;
            this->stSnake[this->QueueLen].Dir = this->stSnake[this->QueueLen - 1].Dir;
            ++this->QueueLen;
        break;
        default:
            return;
        break;
        }

}

/****************************************** SNAKE CHECKCONFLICTSNAKE  ****************************************** 
 * @Brief This function cheks the snake conflict.
 ****************************************************************************************************************/
bool Snake::CheckConflictSnake(Area *myArea)
{
  uint8_t i;
  for ( i = 1; i < this->QueueLen; i++)
    {
      if ( this->stSnake[i].x == this->stSnake[0].x )
      {
        if ( this->stSnake[i].y == this->stSnake[0].y )  
        {
          myArea->ExitArea("YOU LOSE");
          return true;
        }
      }
    }
    return false;
}

Snake::Snake(/* args */)
{
    memset(this->stSnake,0,sizeof(this->stSnake));

    this->stSnake[0].x = 40;
    this->stSnake[0].y = 10;
    this->stSnake[0].Dir = e_DirRight;
    this->QueueLen = 1;

}