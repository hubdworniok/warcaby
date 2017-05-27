#include <iostream>
#include <stdlib>
#include "gra.h"

//Konstruktor klasy Game
Game::Game()
{
    Punkty_1 = 0;
    Punkty_2 = 0;
}

//Destuktor klasy Game
Game::~Game() {}


// FUNKCJA KINGI mousePressEvent

void Game::mousePressEvent(QMouseEvent *event)
{
    poz_x = this->poz_x/(this->width()/8);
    poz_y = this->poz_y/(this->height()/8);

    if(event->button()==Qt::LeftButton)
        {

        switch(etap)
        {
                case 1:
                    {
                        if(nast_zbijanie==0)
                            {
                            zerujZbite();
                            sprawdzMBpionek(1);
                            zbijanie = 0;
                            for (i=0; i<8; i++)
                                for (j=0; j<8; j++)
                                    if(MRpionek[i][j]==1)
                                    {
                                        zbijanie++;
                                        break;
                                    }
                            if (zbijanie==0)
                                sprawdzMRpionek(1);
                            }
// FUNKCJA KINGI mousePressEvent
