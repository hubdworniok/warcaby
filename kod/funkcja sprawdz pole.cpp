void Game::sprawdzMBpole(int x, int y, int pionek) {

    wyzerujMRpole();

    switch(pionek){
    case 1: {
            if (plansza[x-2][y-2]==0 && (plansza[x-1][y-1]==2 || plansza[x-1][y-1]==12) && zbite[x-1][y-1]==0) {
                MRpole[x-4][y-4] = 1;
                MRpole[x-3][y-3] = 2;
            }
            if (plansza[x-2][y+2]==0 && (plansza[x-1][y+1]==2 || plansza[x-1][y+1]==12) && zbite[x-1][y+1]==0) {
                MRpole[x-4][y] = 1;
                MRpole[x-3][y-1] = 2;
            }
            if (plansza[x+2][y-2]==0 && (plansza[x+1][y-1]==2 || plansza[x+1][y-1]==12) && zbite[x+1][y-1]==0) {
                MRpole[x][y-4] = 1;
                MRpole[x-1][y-3] = 2;
            }
            if (plansza[x+2][y+2]==0 && (plansza[x+1][y+1]==2 || plansza[x+1][y+1]==12) && zbite[x+1][y+1]==0) {
                MRpole[x][y] = 1;
                MRpole[x-1][y-1] = 2;
            }
        } break;
    case 2: {
            if (plansza[x-2][y-2]==0 && (plansza[x-1][y-1]==1 || plansza[x-1][y-1]==11) && zbite[x-1][y-1]==0) {
                MRpole[x-4][y-4] = 1;
                MRpole[x-3][y-3] = 2;
            }
            if (plansza[x-2][y+2]==0 && (plansza[x-1][y+1]==1 || plansza[x-1][y+1]==11) && zbite[x-1][y+1]==0) {
                MRpole[x-4][y] = 1;
                MRpole[x-3][y-1] = 2;
            }
            if (plansza[x+2][y-2]==0 && (plansza[x+1][y-1]==1 || plansza[x+1][y-1]==11) && zbite[x+1][y-1]==0) {
                MRpole[x][y-4] = 1;
                MRpole[x-1][y-3] = 2;
            }
            if (plansza[x+2][y+2]==0 && (plansza[x+1][y+1]==1 || plansza[x+1][y+1]==11) && zbite[x+1][y+1]==0) {
                MRpole[x][y] = 1;
                MRpole[x-1][y-1] = 2;
            }
        } break;


//niedokoñczone, bêdê jeszcze nad tym pracowa³//
