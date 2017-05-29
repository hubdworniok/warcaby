void Gra::sprawdzMBpole(int x, int y, int pionek) {

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


    case 11: {
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==11)
                    break;
                if ((plansza[x+1+tmp][y-1-tmp]==2 || plansza[x+1+tmp][y-1-tmp]==12) && zbite[x+1+tmp][y-1-tmp]==0) {
                   if (plansza[x+2+tmp][y-2-tmp]==0) {
                        MRpole[x+tmp][y-4-tmp] = 1;
                        MRpole[x-1+tmp][y-3-tmp] = 2;
                   }
                   break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==11)
                    break;
                if ((plansza[x+1+tmp][y+1+tmp]==2 || plansza[x+1+tmp][y+1+tmp]==12) && zbite[x+1+tmp][y+1+tmp]==0) {
                    if (plansza[x+2+tmp][y+2+tmp]==0) {
                        MRpole[x+tmp][y+tmp] = 1;
                        MRpole[x-1+tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==11)
                    break;
                if ((plansza[x-1-tmp][y-1-tmp]==2 || plansza[x-1-tmp][y-1-tmp]==12) && zbite[x-1-tmp][y-1-tmp]==0) {
                    if (plansza[x-2-tmp][y-2-tmp]==0) {
                        MRpole[x-4-tmp][y-4-tmp] = 1;
                        MRpole[x-3-tmp][y-3-tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==11)
                    break;
                if ((plansza[x-1-tmp][y+1+tmp]==2 || plansza[x-1-tmp][y+1+tmp]==12) && zbite[x-1-tmp][y+1+tmp]==0) {
                    if (plansza[x-2-tmp][y+2+tmp]==0) {
                        MRpole[x-4-tmp][y+tmp] = 1;
                        MRpole[x-3-tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
        } break;
    case 12: {
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==2 || plansza[x+1+tmp][y-1-tmp]==12)
                    break;
                if ((plansza[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==11) && zbite[x+1+tmp][y-1-tmp]==0) {
                   if (plansza[x+2+tmp][y-2-tmp]==0) {
                        MRpole[x+tmp][y-4-tmp] = 1;
                        MRpole[x-1+tmp][y-3-tmp] = 2;
                   }
                   break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==2 || plansza[x+1+tmp][y+1+tmp]==12)
                    break;
                if ((plansza[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==11) && zbite[x+1+tmp][y+1+tmp]==0) {
                    if (plansza[x+2+tmp][y+2+tmp]==0) {
                        MRpole[x+tmp][y+tmp] = 1;
                        MRpole[x-1+tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==2 || plansza[x-1-tmp][y-1-tmp]==12)
                    break;
                if ((plansza[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==11) && zbite[x-1-tmp][y-1-tmp]==0) {
                    if (plansza[x-2-tmp][y-2-tmp]==0) {
                        MRpole[x-4-tmp][y-4-tmp] = 1;
                        MRpole[x-3-tmp][y-3-tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==2 || plansza[x-1-tmp][y+1+tmp]==12)
                    break;
                if ((plansza[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==11) && zbite[x-1-tmp][y+1+tmp]==0) {
                    if (plansza[x-2-tmp][y+2+tmp]==0) {
                        MRpole[x-4-tmp][y+tmp] = 1;
                        MRpole[x-3-tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
        } break;
    default: {}
    }
}
