//kod zrodlowy
#include "gra.h"
#include "interfejs.h"

using namespace std;

Gra::Gra(){

    wyzerujplansze();
    wyzerujzbite();
    wyzerujMRpionek();
    wyzerujMRpole();

    temp = 0;
    etap = 0;
    zbijanie = 0;
    nast_zbijanie = 0;

    setMouseTracking(true);
}
Gra::~Gra() {}

void Gra::wyzerujplansze() {

    for (i=0; i<12; i++)
        for (j=0; j<12; j++)
            planszagry[i][j] = -100;
    for (i=2; i<10; i++)
        for (j=2; j<10; j++)
            planszagry[i][j] = 0;
}

void Gra::wyzerujzbite() {

    for (i=0; i<12; i++)
        for (j=0; j<12; j++)
            zbite_pionki[i][j] = 0;
}

void Gra::wyzerujMRpionek() {

    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            MRpionek[i][j] = 0;
}

void Gra::wyzerujMRpole() {

    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            MRpole[i][j] = 0;
}

void Gra::nowagra() {

    wyzerujplansze();

    for (i=2 ; i<10 ; i++)
        for (j=2 ; j<10 ; j++) {
            if ((i==2 || i==4) && (j==3 || j==5 || j==7 || j==9))
                planszagry[i][j] = 2;
            if (i==3 && (j==2 || j==4 || j==6 || j==8))
                planszagry[i][j] = 2;
            if ((i==7 || i==9) && (j==2 || j==4 || j==6 || j==8))
                planszagry[i][j] = 1;
            if (i==8 && (j==3 || j==5 || j==7 || j==9))
                planszagry[i][j] = 1;
        }

    wyzerujMRpole();
    nast_zbijanie = 0;

    etap = 1;
    emit zmianaetapu("<br>TERAZ<br><b>BIALE<br></b>");
    emit saveOn();

    repaint();
}

void Gra::zapiszgra() {

     ofstream fout("warcabyzapisz.sav");
     for (i=2; i<10; i++)
        for (j=2; j<10; j++) {
            if (planszagry[i][j]>0)
                fout << planszagry[i][j] << endl;
            else
                fout << -planszagry[i][j] << endl;
            }

     fout << etap;
     fout.close();
}

void Gra::wczytajgre() {

    wyzerujplansze();

    ifstream fin("warcabyzapisz.sav");

    if(!fin.fail()){
        for (i=2; i<10; i++)
            for (j=2; j<10; j++)
                fin >> planszagry[i][j];
        fin >> etap;
        fin.close();

        if(etap==1)
            emit zmianaetapu("<br>TERAZZ<br><b>BIALE<br></b>");
        if(etap==2)
            emit zmianaetapu("<br>TERAZ<br><b>CZARNE<br></b>");
        emit saveOn();

        wyzerujMRpole();
        nast_zbijanie = 0;

        repaint();
    }
}

void Gra::sprawdzMRpionek(int kol) {

    wyzerujMRpionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(planszagry[i][j]){
            case 1: {
                if (kol==1)
                    if(planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -1: {
                if (kol==1)
                    if(planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 2: {
                if (kol==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -2: {
                if (kol==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 11: {
                if (kol==1)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -11: {
                if (kol==1)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 12: {
                if (kol==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -12: {
                if (kol==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            default: {}
        }
    }
}

void Gra::sprawdzMBpionek(int kol) {

    wyzerujMRpionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(planszagry[i][j]){
            case 1: {
                if (kol==1) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==2 || planszagry[i-1][j-1]==12 || planszagry[i-1][j-1]==-2 || planszagry[i-1][j-1]==-12) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==2 || planszagry[i-1][j+1]==12 || planszagry[i-1][j+1]==-2 || planszagry[i-1][j+1]==-12) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==2 || planszagry[i+1][j-1]==12 || planszagry[i+1][j-1]==-2 || planszagry[i+1][j-1]==-12) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==2 || planszagry[i+1][j+1]==12 || planszagry[i+1][j+1]==-2 || planszagry[i+1][j+1]==-12) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case -1: {
                if (kol==1) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==2 || planszagry[i-1][j-1]==12 || planszagry[i-1][j-1]==-2 || planszagry[i-1][j-1]==-12) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==2 || planszagry[i-1][j+1]==12 || planszagry[i-1][j+1]==-2 || planszagry[i-1][j+1]==-12) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==2 || planszagry[i+1][j-1]==12 || planszagry[i+1][j-1]==-2 || planszagry[i+1][j-1]==-12) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==2 || planszagry[i+1][j+1]==12 || planszagry[i+1][j+1]==-2 || planszagry[i+1][j+1]==-12) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case 2: {
                if (kol==2) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==1 || planszagry[i-1][j-1]==11 || planszagry[i-1][j-1]==-1 || planszagry[i-1][j-1]==-11) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==1 || planszagry[i-1][j+1]==11 || planszagry[i-1][j+1]==-1 || planszagry[i-1][j+1]==-11) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==1 || planszagry[i+1][j-1]==11 || planszagry[i+1][j-1]==-1 || planszagry[i+1][j-1]==-11) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==1 || planszagry[i+1][j+1]==11 || planszagry[i+1][j+1]==-1 || planszagry[i+1][j+1]==-11) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case -2: {
                if (kol==2) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==1 || planszagry[i-1][j-1]==11 || planszagry[i-1][j-1]==-1 || planszagry[i-1][j-1]==-11) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==1 || planszagry[i-1][j+1]==11 || planszagry[i-1][j+1]==-1 || planszagry[i-1][j+1]==-11) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==1 || planszagry[i+1][j-1]==11 || planszagry[i+1][j-1]==-1 || planszagry[i+1][j-1]==-11) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==1 || planszagry[i+1][j+1]==11 || planszagry[i+1][j+1]==-1 || planszagry[i+1][j+1]==-11) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case 11: {
                if (kol==1) {
                    for (temp=0; temp<7; temp++) {
                        if (zbite_pionki[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11)
                            break;
                        if ((planszagry[i+1+temp][j-1-temp]==2 || planszagry[i+1+temp][j-1-temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12) && zbite_pionki[i+1+temp][j-1-temp]==0) {
                         if (planszagry[i+2+temp][j-2-temp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (temp=0; temp<7; temp++) {
                        if (zbite_pionki[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11)
                            break;
                        if ((planszagry[i+1+temp][j+1+temp]==2 || planszagry[i+1+temp][j+1+temp]==12 || planszagry[i+1+temp][j+1+temp]==-2 || planszagry[i+1+temp][j+1+temp]==-12) && zbite_pionki[i+1+temp][j+1+temp]==0) {
                         if (planszagry[i+2+temp][j+2+temp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (temp=0; temp<7; temp++) {
                        if (zbite_pionki[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11)
                            break;
                        if ((planszagry[i-1-temp][j-1-temp]==2 || planszagry[i-1-temp][j-1-temp]==12 || planszagry[i-1-temp][j-1-temp]==-2 || planszagry[i-1-temp][j-1-temp]==-12) && zbite_pionki[i-1-temp][j-1-temp]==0) {
                         if (planszagry[i-2-temp][j-2-temp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (temp=0; temp<7; temp++) {
                        if (zbite_pionki[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11)
                            break;
                        if ((planszagry[i-1-temp][j+1+temp]==2 || planszagry[i-1-temp][j+1+temp]==12 || planszagry[i-1-temp][j+1+temp]==-2 || planszagry[i-1-temp][j+1+temp]==-12) && zbite_pionki[i-1-temp][j+1+temp]==0) {
                         if (planszagry[i-2-temp][j+2+temp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                }
            } break;
            case -11: {
                    if (kol==1) {
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==11)
                                break;
                            if ((planszagry[i+1+temp][j-1-temp]==2 || planszagry[i+1+temp][j-1-temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12) && zbite_pionki[i+1+temp][j-1-temp]==0) {
                             if (planszagry[i+2+temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==11)
                                break;
                            if ((planszagry[i+1+temp][j+1+temp]==2 || planszagry[i+1+temp][j+1+temp]==12 || planszagry[i+1+temp][j+1+temp]==-2 || planszagry[i+1+temp][j+1+temp]==-12) && zbite_pionki[i+1+temp][j+1+temp]==0) {
                             if (planszagry[i+2+temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==11)
                                break;
                            if ((planszagry[i-1-temp][j-1-temp]==2 || planszagry[i-1-temp][j-1-temp]==12 || planszagry[i-1-temp][j-1-temp]==-2 || planszagry[i-1-temp][j-1-temp]==-12) && zbite_pionki[i-1-temp][j-1-temp]==0) {
                             if (planszagry[i-2-temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==11)
                                break;
                            if ((planszagry[i-1-temp][j+1+temp]==2 || planszagry[i-1-temp][j+1+temp]==12 || planszagry[i-1-temp][j+1+temp]==-2 || planszagry[i-1-temp][j+1+temp]==-12) && zbite_pionki[i-1-temp][j+1+temp]==0) {
                             if (planszagry[i-2-temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case 12: {
                    if (kol==2) {
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==2 || planszagry[i+1+temp][j-1-temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12)
                                break;
                            if ((planszagry[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11) && zbite_pionki[i+1+temp][j-1-temp]==0) {
                             if (planszagry[i+2+temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==2 || planszagry[i+1+temp][j+1+temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12)
                                break;
                            if ((planszagry[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==11 || planszagry[i+1+temp][j+1+temp]==-1 || planszagry[i+1+temp][j+1+temp]==-11) && zbite_pionki[i+1+temp][j+1+temp]==0) {
                             if (planszagry[i+2+temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==2 || planszagry[i-1-temp][j-1-temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12)
                                break;
                            if ((planszagry[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==11 || planszagry[i-1-temp][j-1-temp]==-1 || planszagry[i-1-temp][j-1-temp]==-11) && zbite_pionki[i-1-temp][j-1-temp]==0) {
                             if (planszagry[i-2-temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==2 || planszagry[i-1-temp][j+1+temp]==12 || planszagry[i+1+temp][j-1-temp]==-2 || planszagry[i+1+temp][j-1-temp]==-12)
                                break;
                            if ((planszagry[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==11 || planszagry[i-1-temp][j+1+temp]==-1 || planszagry[i-1-temp][j+1+temp]==-11) && zbite_pionki[i-1-temp][j+1+temp]==0) {
                             if (planszagry[i-2-temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case -12: {
                    if (kol==2) {
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==2 || planszagry[i+1+temp][j-1-temp]==12)
                                break;
                            if ((planszagry[i+1+temp][j-1-temp]==1 || planszagry[i+1+temp][j-1-temp]==11 || planszagry[i+1+temp][j-1-temp]==-1 || planszagry[i+1+temp][j-1-temp]==-11) && zbite_pionki[i+1+temp][j-1-temp]==0) {
                             if (planszagry[i+2+temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==2 || planszagry[i+1+temp][j+1+temp]==12)
                                break;
                            if ((planszagry[i+1+temp][j+1+temp]==1 || planszagry[i+1+temp][j+1+temp]==11 || planszagry[i+1+temp][j+1+temp]==-1 || planszagry[i+1+temp][j+1+temp]==-11) && zbite_pionki[i+1+temp][j+1+temp]==0) {
                             if (planszagry[i+2+temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==2 || planszagry[i-1-temp][j-1-temp]==12)
                                break;
                            if ((planszagry[i-1-temp][j-1-temp]==1 || planszagry[i-1-temp][j-1-temp]==11 || planszagry[i-1-temp][j-1-temp]==-1 || planszagry[i-1-temp][j-1-temp]==-11) && zbite_pionki[i-1-temp][j-1-temp]==0) {
                             if (planszagry[i-2-temp][j-2-temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (temp=0; temp<7; temp++) {
                            if (zbite_pionki[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==2 || planszagry[i-1-temp][j+1+temp]==12)
                                break;
                            if ((planszagry[i-1-temp][j+1+temp]==1 || planszagry[i-1-temp][j+1+temp]==11 || planszagry[i-1-temp][j+1+temp]==-1 || planszagry[i-1-temp][j+1+temp]==-11) && zbite_pionki[i-1-temp][j+1+temp]==0) {
                             if (planszagry[i-2-temp][j+2+temp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            default: {}
        }
    }
}

//funkcja Filip - sprawdz pole MB//

void Gra::sprawdzMBpole(int x, int y, int pionek) {

    wyzerujMRpole();

    switch(pionek){
    case 1: {
            if (planszagry[x-2][y-2]==0 && (planszagry[x-1][y-1]==2 || planszagry[x-1][y-1]==12) && zbite_pionki[x-1][y-1]==0) {
                MRpole[x-4][y-4] = 1;
                MRpole[x-3][y-3] = 2;
            }
            if (planszagry[x-2][y+2]==0 && (planszagry[x-1][y+1]==2 || planszagry[x-1][y+1]==12) && zbite_pionki[x-1][y+1]==0) {
                MRpole[x-4][y] = 1;
                MRpole[x-3][y-1] = 2;
            }
            if (planszagry[x+2][y-2]==0 && (planszagry[x+1][y-1]==2 || planszagry[x+1][y-1]==12) && zbite_pionki[x+1][y-1]==0) {
                MRpole[x][y-4] = 1;
                MRpole[x-1][y-3] = 2;
            }
            if (planszagry[x+2][y+2]==0 && (planszagry[x+1][y+1]==2 || planszagry[x+1][y+1]==12) && zbite_pionki[x+1][y+1]==0) {
                MRpole[x][y] = 1;
                MRpole[x-1][y-1] = 2;
            }
        } break;
    case 2: {
            if (planszagry[x-2][y-2]==0 && (planszagry[x-1][y-1]==1 || planszagry[x-1][y-1]==11) && zbite_pionki[x-1][y-1]==0) {
                MRpole[x-4][y-4] = 1;
                MRpole[x-3][y-3] = 2;
            }
            if (planszagry[x-2][y+2]==0 && (planszagry[x-1][y+1]==1 || planszagry[x-1][y+1]==11) && zbite_pionki[x-1][y+1]==0) {
                MRpole[x-4][y] = 1;
                MRpole[x-3][y-1] = 2;
            }
            if (planszagry[x+2][y-2]==0 && (planszagry[x+1][y-1]==1 || planszagry[x+1][y-1]==11) && zbite_pionki[x+1][y-1]==0) {
                MRpole[x][y-4] = 1;
                MRpole[x-1][y-3] = 2;
            }
            if (planszagry[x+2][y+2]==0 && (planszagry[x+1][y+1]==1 || planszagry[x+1][y+1]==11) && zbite_pionki[x+1][y+1]==0) {
                MRpole[x][y] = 1;
                MRpole[x-1][y-1] = 2;
            }
        } break;


    case 11: {
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x+1+temp][y-1-temp]==1 || planszagry[x+1+temp][y-1-temp]==1 || planszagry[x+1+temp][y-1-temp]==11)
                    break;
                if ((planszagry[x+1+temp][y-1-temp]==2 || planszagry[x+1+temp][y-1-temp]==12) && zbite_pionki[x+1+temp][y-1-temp]==0) {
                   if (planszagry[x+2+temp][y-2-temp]==0) {
                        MRpole[x+temp][y-4-temp] = 1;
                        MRpole[x-1+temp][y-3-temp] = 2;
                   }
                   break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x+1+temp][y+1+temp]==1 || planszagry[x+1+temp][y+1+temp]==1 || planszagry[x+1+temp][y+1+temp]==11)
                    break;
                if ((planszagry[x+1+temp][y+1+temp]==2 || planszagry[x+1+temp][y+1+temp]==12) && zbite_pionki[x+1+temp][y+1+temp]==0) {
                    if (planszagry[x+2+temp][y+2+temp]==0) {
                        MRpole[x+temp][y+temp] = 1;
                        MRpole[x-1+temp][y-1+temp] = 2;
                    }
                    break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x-1-temp][y-1-temp]==1 || planszagry[x-1-temp][y-1-temp]==1 || planszagry[x-1-temp][y-1-temp]==11)
                    break;
                if ((planszagry[x-1-temp][y-1-temp]==2 || planszagry[x-1-temp][y-1-temp]==12) && zbite_pionki[x-1-temp][y-1-temp]==0) {
                    if (planszagry[x-2-temp][y-2-temp]==0) {
                        MRpole[x-4-temp][y-4-temp] = 1;
                        MRpole[x-3-temp][y-3-temp] = 2;
                    }
                    break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x-1-temp][y+1+temp]==1 || planszagry[x-1-temp][y+1+temp]==1 || planszagry[x-1-temp][y+1+temp]==11)
                    break;
                if ((planszagry[x-1-temp][y+1+temp]==2 || planszagry[x-1-temp][y+1+temp]==12) && zbite_pionki[x-1-temp][y+1+temp]==0) {
                    if (planszagry[x-2-temp][y+2+temp]==0) {
                        MRpole[x-4-temp][y+temp] = 1;
                        MRpole[x-3-temp][y-1+temp] = 2;
                    }
                    break;
                }
            }
        } break;
    case 12: {
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x+1+temp][y-1-temp]==1 || planszagry[x+1+temp][y-1-temp]==2 || planszagry[x+1+temp][y-1-temp]==12)
                    break;
                if ((planszagry[x+1+temp][y-1-temp]==1 || planszagry[x+1+temp][y-1-temp]==11) && zbite_pionki[x+1+temp][y-1-temp]==0) {
                   if (planszagry[x+2+temp][y-2-temp]==0) {
                        MRpole[x+temp][y-4-temp] = 1;
                        MRpole[x-1+temp][y-3-temp] = 2;
                   }
                   break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x+1+temp][y+1+temp]==1 || planszagry[x+1+temp][y+1+temp]==2 || planszagry[x+1+temp][y+1+temp]==12)
                    break;
                if ((planszagry[x+1+temp][y+1+temp]==1 || planszagry[x+1+temp][y+1+temp]==11) && zbite_pionki[x+1+temp][y+1+temp]==0) {
                    if (planszagry[x+2+temp][y+2+temp]==0) {
                        MRpole[x+temp][y+temp] = 1;
                        MRpole[x-1+temp][y-1+temp] = 2;
                    }
                    break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x-1-temp][y-1-temp]==1 || planszagry[x-1-temp][y-1-temp]==2 || planszagry[x-1-temp][y-1-temp]==12)
                    break;
                if ((planszagry[x-1-temp][y-1-temp]==1 || planszagry[x-1-temp][y-1-temp]==11) && zbite_pionki[x-1-temp][y-1-temp]==0) {
                    if (planszagry[x-2-temp][y-2-temp]==0) {
                        MRpole[x-4-temp][y-4-temp] = 1;
                        MRpole[x-3-temp][y-3-temp] = 2;
                    }
                    break;
                }
            }
            for (temp=0; temp<7; temp++){
                if (zbite_pionki[x-1-temp][y+1+temp]==1 || planszagry[x-1-temp][y+1+temp]==2 || planszagry[x-1-temp][y+1+temp]==12)
                    break;
                if ((planszagry[x-1-temp][y+1+temp]==1 || planszagry[x-1-temp][y+1+temp]==11) && zbite_pionki[x-1-temp][y+1+temp]==0) {
                    if (planszagry[x-2-temp][y+2+temp]==0) {
                        MRpole[x-4-temp][y+temp] = 1;
                        MRpole[x-3-temp][y-1+temp] = 2;
                    }
                    break;
                }
            }
        } break;
    default: {}
    }
}

void Gra::mouseMoveEvent(QMouseEvent *event) {
    poz_x = event->y();
    poz_y = event->x();
    repaint();
}

void Gra::mousePressEvent(QMouseEvent *event){
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
                            wyzerujzbite();
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
                        if(((planszagry[poz_x+2][poz_y+2]==1 || planszagry[poz_x+2][poz_y+2]==11) && MRpionek[poz_x][poz_y]==1) && nast_zbijanie==0)
                            {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(planszagry[i][j]<0)
                                        planszagry[i][j] = -planszagry[i][j];

                            planszagry[poz_x+2][poz_y+2] = -planszagry[poz_x+2][poz_y+2];

                            if(zbijanie==0)
                                sprawdzMBpole(poz_x+2, poz_y+2, -planszagry[poz_x+2][poz_y+2]);
                            else
                                sprawdzMBpole(poz_x+2, poz_y+2, -planszagry[poz_x+2][poz_y+2]);
                            }
                        if(planszagry[poz_x+2][poz_y+2]==0 && MRpole[poz_x][poz_y]==1)
                            {
                                for (i=2; i<10; i++)
                                    for (j=2; j<10; j++)
                                        if(planszagry[i][j]<0)
                                        {
                                            planszagry[poz_x+2][poz_y+2] = -planszagry[i][j];

                                            planszagry[i][j] = 0;
                                        }

                                if(zbijanie>0)
                                    {
                                    if(MRpole[poz_x+1][poz_y+1]==2)
                                        zbite_pionki[poz_x+3][poz_y+3] = 1;
                                    if(MRpole[poz_x-1][poz_y-1]==2)
                                        zbite_pionki[poz_x+1][poz_y+1] = 1;
                                    if(MRpole[poz_x+1][poz_y-1]==2)
                                        zbite_pionki[poz_x+3][poz_y+1] = 1;
                                    if(MRpole[poz_x-1][poz_y+1]==2)
                                        zbite_pionki[poz_x+1][poz_y+3] = 1;
                                    }

                                if(zbijanie>0)
                                    {
                                    nast_zbijanie = 0;
                                    sprawdzMBpole(poz_x+2, poz_y+2, planszagry[poz_x+2][poz_y+2]);
                                    for (i=0; i<8; i++)
                                        for (j=0; j<8; j++)
                                            if(MRpole[i][j]==1)
                                            {
                                                nast_zbijanie++;
                                                break;
                                            }
                                    }

                                if(nast_zbijanie>0)
                                    planszagry[poz_x+2][poz_y+2] = -planszagry[poz_x+2][poz_y+2];

                                if(nast_zbijanie>0)
                                    etap = 1;
                                else
                                    {
                                    wyzerujMRpole();

                                    if(poz_x==0)
                                        planszagry[poz_x+2][poz_y+2] = 11;

                                    for (i=2; i<10; i++)
                                        for (j=2; j<10; j++)
                                            if(zbite_pionki[i][j]==1)
                                                planszagry[i][j] = 0;

                                    nast_zbijanie = 0;
                                    etap = 2;
                                    }
                             }
                    }
                    break;

                case 2:
                    {
                        if(nast_zbijanie==0)
                            {
                            wyzerujzbite();
                            sprawdzMBpionek(2);
                            zbijanie = 0;
                            for (i=0; i<8; i++)
                                for (j=0; j<8; j++)
                                    if(MRpionek[i][j]==1)
                                    {
                                        zbijanie++;
                                        break;
                                    }
                            if (zbijanie==0)
                                sprawdzMRpionek(2);
                            }

                        if(((planszagry[poz_x+2][poz_y+2]==2 || planszagry[poz_x+2][poz_y+2]==12) && MRpionek[poz_x][poz_y]==1) && nast_zbijanie==0)
                            {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(planszagry[i][j]<0)
                                        planszagry[i][j] = -planszagry[i][j];

                            planszagry[poz_x+2][poz_y+2] = -planszagry[poz_x+2][poz_y+2];

                            if(zbijanie==0)
                                sprawdzMBpole(poz_x+2, poz_y+2, -planszagry[poz_x+2][poz_y+2]);
                            else
                                sprawdzMBpole(poz_x+2, poz_y+2, -planszagry[poz_x+2][poz_y+2]);
                            }
                        if(planszagry[poz_x+2][poz_y+2]==0 && MRpole[poz_x][poz_y]==1)
                            {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if (planszagry[i][j]<0)
                                    {
                                        planszagry[poz_x+2][poz_y+2] = -planszagry[i][j];

                                        planszagry[i][j] = 0;
                                    }

                            if(zbijanie>0)
                                {
                                if(MRpole[poz_x+1][poz_y+1]==2)
                                    zbite_pionki[poz_x+3][poz_y+3] = 1;
                                if(MRpole[poz_x-1][poz_y-1]==2)
                                    zbite_pionki[poz_x+1][poz_y+1] = 1;
                                if(MRpole[poz_x+1][poz_y-1]==2)
                                    zbite_pionki[poz_x+3][poz_y+1] = 1;
                                if(MRpole[poz_x-1][poz_y+1]==2)
                                    zbite_pionki[poz_x+1][poz_y+3] = 1;
                                }

                            if(zbijanie>0)
                                {
                                nast_zbijanie = 0;
                                sprawdzMBpole(poz_x+2, poz_y+2, planszagry[poz_x+2][poz_y+2]);
                                for (i=0; i<8; i++)
                                    for (j=0; j<8; j++)
                                        if(MRpole[i][j]==1)
                                        {
                                            nast_zbijanie++;
                                            break;
                                        }
                                }

                            if(nast_zbijanie>0)
                                planszagry[poz_x+2][poz_y+2] = -planszagry[poz_x+2][poz_y+2];

                            if(nast_zbijanie>0)
                                etap = 2;
                            else
                                {
                                wyzerujMRpole();

                                if(poz_x==7)
                                    planszagry[poz_x+2][poz_y+2] = 12;

                                for (i=2; i<10; i++)
                                    for (j=2; j<10; j++)
                                        if(zbite_pionki[i][j]==1)
                                            planszagry[i][j] = 0;

                                nast_zbijanie = 0;
                                etap = 1;
                                }
                            }
                    } break;
                default: {}
        }

        if(nast_zbijanie>0)
            emit saveOff();
        else
            if(etap!=0)
                emit saveOn();

        if(etap==2)
            {
            etap = -1;
            for (i=2; i<10; i++)
                for (j=2; j<10; j++)
                    if(planszagry[i][j]==2 || planszagry[i][j]==12 || planszagry[i][j]==-2 || planszagry[i][j]==-12)
                        etap = 2;
            if(etap!=-1)
            {
                sprawdzMRpionek(2);
                etap = -1;
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRpionek[i][j]==1)
                            etap = 2;
            }
            if(etap==-1)
            {
                sprawdzMBpionek(2);
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRpionek[i][j]==1)
                            etap = 2;
            }
        }

        if (etap==1)
            {
                etap = -2;
                for (i=2; i<10; i++)
                    for (j=2; j<10; j++)
                        if(planszagry[i][j]==1 || planszagry[i][j]==11 || planszagry[i][j]==-1 || planszagry[i][j]==-11)
                            etap = 1;
                if(etap!=-2)
                {
                    sprawdzMRpionek(1);
                    etap = -2;
                    for (i=0; i<8; i++)
                        for (j=0; j<8; j++)
                            if(MRpionek[i][j]==1)
                                etap = 1;
                }
                if(etap==-2)
                {
                    sprawdzMBpionek(1);
                    for (i=0; i<8; i++)
                        for (j=0; j<8; j++)
                            if(MRpionek[i][j]==1)
                                etap = 1;
                }
            }


        if (etap<0)
            wyzerujMRpole();

        if(etap==1)
            emit zmianaetapu("<br>TERAZ<br><b>BIALYCH<br></b>");
        if(etap==2)
            emit zmianaetapu("<br>TERAZ<br><b>CZARNYCH<br></b>");
        if(etap==-1)
            {
            emit zmianaetapu("<br>WYGRANA<br><b>BIALYCH<br></b>");
            emit saveOff();
            }
        if(etap==-2)
            {
            emit zmianaetapu("<br>WYGRANA<br><b>CZARNYCH<br></b>");
            emit saveOff();
            }

        repaint();
    }
}
//<<<<<<< HEAD
// FUNKCJA KINGI mousePressEvent

void Gra::paintEvent(QPaintEvent*) {

  int szerPola = this->width()/8;
  int wysPola = this->height()/8;

  int x;
  int y = 0;

  QPainter rysownik(this);
  for (int i=0 ; i<8 ; i++) {
        x=0;
        for (int j=0 ; j<8 ; j++) {
            if((i%2==0 && j%2!=0) || (i%2!=0 && j%2==0)) {
                rysownik.setBrush(QBrush(QColor(128, 64, 0)));
                rysownik.drawRect(x, y, szerPola, wysPola);
            }
            else {
                rysownik.setBrush(QBrush(QColor(225, 226, 163)));
                rysownik.drawRect(x, y, szerPola, wysPola);
            }

            if (MRpole[i][j]==1) {
                rysownik.setBrush(QBrush(Qt::green));
                rysownik.drawRect(x, y, szerPola, wysPola);
            }
            if (MRpole[i][j]==2) {
                rysownik.setBrush(QBrush(Qt::red));
                rysownik.drawRect(x, y, szerPola, wysPola);
            }

            switch(planszagry[i+2][j+2]) {
            case 1: {
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case 2: {
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case 11: {
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case 12: {
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case -1: {
                    rysownik.setBrush(QBrush(Qt::yellow));
                    rysownik.drawRect(x, y, szerPola, wysPola);
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case -2: {
                    rysownik.setBrush(QBrush(Qt::yellow));
                    rysownik.drawRect(x, y, szerPola, wysPola);
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case -11: {
                    rysownik.setBrush(QBrush(Qt::yellow));
                    rysownik.drawRect(x, y, szerPola, wysPola);
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case -12: {
                    rysownik.setBrush(QBrush(Qt::yellow));
                    rysownik.drawRect(x, y, szerPola, wysPola);
                    rysownik.setBrush(QBrush(Qt::black));
                    rysownik.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    rysownik.setBrush(QBrush(Qt::white));
                    rysownik.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            default: {}
            }
            x=x+szerPola;
        }
        y=y+wysPola;
  }
}

//=======
//>>>>>>> 8456af2c33280d3291565588da469acf3e3336f1

