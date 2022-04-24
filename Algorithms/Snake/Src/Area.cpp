#include "Area.h"

/*************************************************** GOTOXY  ***************************************************
 * @Brief This function put the cursor to x,y coordinate on terminal.
 * @Param x is coordinate x .
 * @Param y is coordinate y .
 ****************************************************************************************************************/
void GotoXY(uint8_t x , uint8_t y)
{
    COORD Coord;
    Coord.X = x;
    Coord.Y = y;
    SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), Coord );
}

/*************************************************** SHOW AREA  ***************************************************
 * @Brief This function shows the Area matrix on terminal.
 ****************************************************************************************************************/
void Area::ShowArea()
{
    GotoXY(0,0);
    for (uint8_t i = 0; i < AREA_HEIGHT; ++i)
    {
        for (uint8_t j = 0; j < AREA_WIDTH; ++j)
        {
            std::cout << this->area[j][i];
        }
        std::cout << std::endl;
    }
}

/********************************************** CREATE BOUNDARIES  **********************************************
 * @Brief This function puts frame in Area matrix. 
 ****************************************************************************************************************/
void Area::CreateBoundaries()
{
    for (uint8_t i = 0; i < AREA_WIDTH; ++i)
    {
        this->area[i][0] = BOUNDARIES_CHAR;
        this->area[i][AREA_HEIGHT-1] = BOUNDARIES_CHAR;
    }
    for (uint8_t i = 0; i < AREA_HEIGHT; ++i)
    {
        this->area[0][i] = BOUNDARIES_CHAR;
        this->area[AREA_WIDTH - 1][i] = BOUNDARIES_CHAR;
    }
}

/************************************************ DEFAULT AREA  ************************************************
* @Brief This function puts frame and clear the area in Area matrix. 
****************************************************************************************************************/
void Area::DefaultArea()
{
    for (uint8_t i = 0; i < AREA_HEIGHT; ++i)
    {
        for (uint8_t j = 0; j < AREA_WIDTH; ++j)
        {
            this->area[j][i] = DEFAULT_SPACE_CHAR;
        }
    }
}

/************************************************ DEFAULT AREA  ************************************************
* @Brief This function writes param str in the middle point of terminal
****************************************************************************************************************/
void Area::ExitArea(std::string str)
{
    this->DefaultArea();
    this->ShowArea();
    GotoXY( AREA_WIDTH / 2, AREA_HEIGHT / 2);
    std::cout << str << std::endl;
}