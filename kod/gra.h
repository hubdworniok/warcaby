#ifndef GRA_H_INCLUDED
#define GRA_H_INCLUDED

#include <iostream>
#include <stdlib>

using namespace std;

class Game : public QWidget
{
    Q_OBJECT;

    public:
        Game();
        ~Game();

        //tutaj wypisa� nazwy funkcji potrzebnych do gry, kt�re b�d� stworzone w gra.cpp//

    private:
        int Punkty_1;
        int Punkty_2;
};





#endif // GRA_H_INCLUDED
