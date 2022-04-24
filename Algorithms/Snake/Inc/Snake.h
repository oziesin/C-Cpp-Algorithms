/* CAN BE CHANGE @MAX_SNAKE_LEN IF YOU WANT TO CHANGE LIMIT OF SNAKE LENGTH.
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Feed.h"

#define MAX_SNAKE_LEN       10

typedef enum
{
    e_DirLeft,
    e_DirUp,
    e_DirRight,
    e_DirDown,
    e_DirMax
}e_Direction;

class Snake
{
private:

    typedef struct
    {
    e_Direction Dir;
    uint8_t     x;
    uint8_t     y;
    }stSnake_t;
public:
    uint16_t QueueLen;
    stSnake_t stSnake[MAX_SNAKE_LEN];

    void PutSnakeToArea(Area *myArea);
    void MoveSnake(Area *myArea, Feed *mFeed);
    void GrowSnake();
    bool CheckConflictSnake(Area *myArea);
    Snake(/* args */);
    // ~Snake();
};


#endif /* _SNAKE_H_*/