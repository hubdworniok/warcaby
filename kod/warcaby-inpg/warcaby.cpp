/*
  Name: Warcaby
  Version: 1.1
  Copyright: GPL GNU
  Author: Bartosz 'Orange' Owczarek
*/

#include "warcaby.h"

using namespace std;

Interface::Interface() {

        game = new Game();

        setWindowTitle("Warcaby v1.1");
        setFixedSize(572,492);

        pbNowa_gra = new QPushButton(tr("&Nowa gra"), this);

        pbZapisz_gre = new QPushButton(tr("&Zapisz gre"), this);
        pbZapisz_gre->setDisabled(true);
        connect(game, SIGNAL(saveOn()), this, SLOT(FsaveOn()));
        connect(game, SIGNAL(saveOff()), this, SLOT(FsaveOff()));

        pbWczytaj_gre = new QPushButton(tr("&Wczytaj gre"), this);

        pbWyjscie = new QPushButton(tr("&Wyjscie"), this);

        infoLabel = new QLabel(tr("<br>ROZPOCZNIJ<br><b>NOWA GRE</b><br>"));
        infoLabel->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
        infoLabel->setAlignment(Qt::AlignCenter);
        connect(game, SIGNAL(zmianaEtap(QString)), infoLabel, SLOT(setText(QString)));
		
        autorLabel = new QLabel(tr("created by<hr><b>Bartosz<li>Owczarek</b>"));
        autorLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *lPrzyciski = new QVBoxLayout();
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(pbNowa_gra);
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(infoLabel);
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(pbZapisz_gre);
        lPrzyciski->addWidget(pbWczytaj_gre);
        lPrzyciski->addWidget(pbWyjscie);
        lPrzyciski->addStretch(10);
        lPrzyciski->addWidget(autorLabel);
        lPrzyciski->addStretch(1);

        QHBoxLayout *lPlansza = new QHBoxLayout();
        lPlansza->addLayout(lPrzyciski);
        lPlansza->addWidget(game);
        lPlansza->setStretch(1,1);

        this->setLayout(lPlansza);

        connect(pbNowa_gra, SIGNAL(clicked()), game, SLOT(newGame()));
        connect(pbZapisz_gre, SIGNAL(clicked()), game, SLOT(saveGame()));
        connect(pbWczytaj_gre, SIGNAL(clicked()), game, SLOT(loadGame()));
        connect(pbWyjscie, SIGNAL(clicked()), this, SLOT(close()));
}
Interface::~Interface() {}

void Interface::FsaveOn() {
    pbZapisz_gre->setDisabled(false);
}

void Interface::FsaveOff() {
    pbZapisz_gre->setDisabled(true);
}

Game::Game(){

    zerujPlansza();
    zerujZbite();
    zerujMRPionek();
    zerujMRPole();

    tmp = 0;
    etap = 0;
    bicie = 0;
    bicieNext = 0;
            
    setMouseTracking(true);
}
Game::~Game() {}

void Game::zerujPlansza() {

    for (i=0; i<12; i++)
        for (j=0; j<12; j++)
            plansza[i][j] = -100;
    for (i=2; i<10; i++)
        for (j=2; j<10; j++)
            plansza[i][j] = 0;
}

void Game::zerujZbite() {

    for (i=0; i<12; i++)
        for (j=0; j<12; j++)
            zbite[i][j] = 0;
}

void Game::zerujMRPionek() {

    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            MRPionek[i][j] = 0;
}

void Game::zerujMRPole() {

    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            MRPole[i][j] = 0;
}

void Game::newGame() {

    zerujPlansza();

    for (i=2 ; i<10 ; i++)
        for (j=2 ; j<10 ; j++) {
            if ((i==2 || i==4) && (j==3 || j==5 || j==7 || j==9))
                plansza[i][j] = 2;
            if (i==3 && (j==2 || j==4 || j==6 || j==8))
                plansza[i][j] = 2;
            if ((i==7 || i==9) && (j==2 || j==4 || j==6 || j==8))
                plansza[i][j] = 1;
            if (i==8 && (j==3 || j==5 || j==7 || j==9))
                plansza[i][j] = 1;
        }

    zerujMRPole();
    bicieNext = 0;

    etap = 1;
    emit zmianaEtap("<br>RUCH<br><b>BIALYCH<br></b>");
    emit saveOn();
    
    repaint();
}

void Game::saveGame() {

     ofstream fout("warcabySave.sav");
     for (i=2; i<10; i++)
        for (j=2; j<10; j++) {
            if (plansza[i][j]>0)
                fout << plansza[i][j] << endl;
            else
                fout << -plansza[i][j] << endl;
            }

     fout << etap;
     fout.close();
}

void Game::loadGame() {

    zerujPlansza();

    ifstream fin("warcabySave.sav");

    if(!fin.fail()){
        for (i=2; i<10; i++)
            for (j=2; j<10; j++)
                fin >> plansza[i][j];
        fin >> etap;
        fin.close();
    
        if(etap==1)
            emit zmianaEtap("<br>RUCH<br><b>BIALYCH<br></b>");
        if(etap==2)
            emit zmianaEtap("<br>RUCH<br><b>CZARNYCH<br></b>");
        emit saveOn();

        zerujMRPole();
        bicieNext = 0;

        repaint();
    }
}

void Game::sprawdzMRPionek(int kolor) {

    zerujMRPionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(plansza[i][j]){
            case 1: {
                if (kolor==1)
                    if(plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case -1: {
                if (kolor==1)
                    if(plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case 2: {
                if (kolor==2)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case -2: {
                if (kolor==2)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case 11: {
                if (kolor==1)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0 || plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case -11: {
                if (kolor==1)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0 || plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case 12: {
                if (kolor==2)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0 || plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            case -12: {
                if (kolor==2)
                    if(plansza[i+1][j-1]==0 || plansza[i+1][j+1]==0 || plansza[i-1][j-1]==0 || plansza[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
            } break;
            default: {}
        }
    }
}

void Game::sprawdzMBPionek(int kolor) {

    zerujMRPionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(plansza[i][j]){
            case 1: {
                if (kolor==1) {
                    if (plansza[i-2][j-2]==0 && (plansza[i-1][j-1]==2 || plansza[i-1][j-1]==12 || plansza[i-1][j-1]==-2 || plansza[i-1][j-1]==-12) && zbite[i-1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i-2][j+2]==0 && (plansza[i-1][j+1]==2 || plansza[i-1][j+1]==12 || plansza[i-1][j+1]==-2 || plansza[i-1][j+1]==-12) && zbite[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j-2]==0 && (plansza[i+1][j-1]==2 || plansza[i+1][j-1]==12 || plansza[i+1][j-1]==-2 || plansza[i+1][j-1]==-12) && zbite[i+1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j+2]==0 && (plansza[i+1][j+1]==2 || plansza[i+1][j+1]==12 || plansza[i+1][j+1]==-2 || plansza[i+1][j+1]==-12) && zbite[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                }
            } break;
            case -1: {
                if (kolor==1) {
                    if (plansza[i-2][j-2]==0 && (plansza[i-1][j-1]==2 || plansza[i-1][j-1]==12 || plansza[i-1][j-1]==-2 || plansza[i-1][j-1]==-12) && zbite[i-1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i-2][j+2]==0 && (plansza[i-1][j+1]==2 || plansza[i-1][j+1]==12 || plansza[i-1][j+1]==-2 || plansza[i-1][j+1]==-12) && zbite[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j-2]==0 && (plansza[i+1][j-1]==2 || plansza[i+1][j-1]==12 || plansza[i+1][j-1]==-2 || plansza[i+1][j-1]==-12) && zbite[i+1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j+2]==0 && (plansza[i+1][j+1]==2 || plansza[i+1][j+1]==12 || plansza[i+1][j+1]==-2 || plansza[i+1][j+1]==-12) && zbite[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                }
            } break;
            case 2: {
                if (kolor==2) {
                    if (plansza[i-2][j-2]==0 && (plansza[i-1][j-1]==1 || plansza[i-1][j-1]==11 || plansza[i-1][j-1]==-1 || plansza[i-1][j-1]==-11) && zbite[i-1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i-2][j+2]==0 && (plansza[i-1][j+1]==1 || plansza[i-1][j+1]==11 || plansza[i-1][j+1]==-1 || plansza[i-1][j+1]==-11) && zbite[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j-2]==0 && (plansza[i+1][j-1]==1 || plansza[i+1][j-1]==11 || plansza[i+1][j-1]==-1 || plansza[i+1][j-1]==-11) && zbite[i+1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j+2]==0 && (plansza[i+1][j+1]==1 || plansza[i+1][j+1]==11 || plansza[i+1][j+1]==-1 || plansza[i+1][j+1]==-11) && zbite[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                }
            } break;
            case -2: {
                if (kolor==2) {
                    if (plansza[i-2][j-2]==0 && (plansza[i-1][j-1]==1 || plansza[i-1][j-1]==11 || plansza[i-1][j-1]==-1 || plansza[i-1][j-1]==-11) && zbite[i-1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i-2][j+2]==0 && (plansza[i-1][j+1]==1 || plansza[i-1][j+1]==11 || plansza[i-1][j+1]==-1 || plansza[i-1][j+1]==-11) && zbite[i-1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j-2]==0 && (plansza[i+1][j-1]==1 || plansza[i+1][j-1]==11 || plansza[i+1][j-1]==-1 || plansza[i+1][j-1]==-11) && zbite[i+1][j-1]==0)
                        MRPionek[i-2][j-2] = 1;
                    if (plansza[i+2][j+2]==0 && (plansza[i+1][j+1]==1 || plansza[i+1][j+1]==11 || plansza[i+1][j+1]==-1 || plansza[i+1][j+1]==-11) && zbite[i+1][j+1]==0)
                        MRPionek[i-2][j-2] = 1;
                }
            } break;
            case 11: {
                if (kolor==1) {
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((plansza[i+1+tmp][j-1-tmp]==2 || plansza[i+1+tmp][j-1-tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12) && zbite[i+1+tmp][j-1-tmp]==0) {
                         if (plansza[i+2+tmp][j-2-tmp]==0)
                            MRPionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((plansza[i+1+tmp][j+1+tmp]==2 || plansza[i+1+tmp][j+1+tmp]==12 || plansza[i+1+tmp][j+1+tmp]==-2 || plansza[i+1+tmp][j+1+tmp]==-12) && zbite[i+1+tmp][j+1+tmp]==0) {
                         if (plansza[i+2+tmp][j+2+tmp]==0)
                            MRPionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((plansza[i-1-tmp][j-1-tmp]==2 || plansza[i-1-tmp][j-1-tmp]==12 || plansza[i-1-tmp][j-1-tmp]==-2 || plansza[i-1-tmp][j-1-tmp]==-12) && zbite[i-1-tmp][j-1-tmp]==0) {
                         if (plansza[i-2-tmp][j-2-tmp]==0)
                            MRPionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((plansza[i-1-tmp][j+1+tmp]==2 || plansza[i-1-tmp][j+1+tmp]==12 || plansza[i-1-tmp][j+1+tmp]==-2 || plansza[i-1-tmp][j+1+tmp]==-12) && zbite[i-1-tmp][j+1+tmp]==0) {
                         if (plansza[i-2-tmp][j+2+tmp]==0)
                            MRPionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                }
            } break;
            case -11: {
                    if (kolor==1) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==11)
                                break;
                            if ((plansza[i+1+tmp][j-1-tmp]==2 || plansza[i+1+tmp][j-1-tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12) && zbite[i+1+tmp][j-1-tmp]==0) {
                             if (plansza[i+2+tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==11)
                                break;
                            if ((plansza[i+1+tmp][j+1+tmp]==2 || plansza[i+1+tmp][j+1+tmp]==12 || plansza[i+1+tmp][j+1+tmp]==-2 || plansza[i+1+tmp][j+1+tmp]==-12) && zbite[i+1+tmp][j+1+tmp]==0) {
                             if (plansza[i+2+tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==11)
                                break;
                            if ((plansza[i-1-tmp][j-1-tmp]==2 || plansza[i-1-tmp][j-1-tmp]==12 || plansza[i-1-tmp][j-1-tmp]==-2 || plansza[i-1-tmp][j-1-tmp]==-12) && zbite[i-1-tmp][j-1-tmp]==0) {
                             if (plansza[i-2-tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==11)
                                break;
                            if ((plansza[i-1-tmp][j+1+tmp]==2 || plansza[i-1-tmp][j+1+tmp]==12 || plansza[i-1-tmp][j+1+tmp]==-2 || plansza[i-1-tmp][j+1+tmp]==-12) && zbite[i-1-tmp][j+1+tmp]==0) {
                             if (plansza[i-2-tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case 12: {
                    if (kolor==2) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==2 || plansza[i+1+tmp][j-1-tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((plansza[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11) && zbite[i+1+tmp][j-1-tmp]==0) {
                             if (plansza[i+2+tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==2 || plansza[i+1+tmp][j+1+tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((plansza[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==11 || plansza[i+1+tmp][j+1+tmp]==-1 || plansza[i+1+tmp][j+1+tmp]==-11) && zbite[i+1+tmp][j+1+tmp]==0) {
                             if (plansza[i+2+tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==2 || plansza[i-1-tmp][j-1-tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((plansza[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==11 || plansza[i-1-tmp][j-1-tmp]==-1 || plansza[i-1-tmp][j-1-tmp]==-11) && zbite[i-1-tmp][j-1-tmp]==0) {
                             if (plansza[i-2-tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==2 || plansza[i-1-tmp][j+1+tmp]==12 || plansza[i+1+tmp][j-1-tmp]==-2 || plansza[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((plansza[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==11 || plansza[i-1-tmp][j+1+tmp]==-1 || plansza[i-1-tmp][j+1+tmp]==-11) && zbite[i-1-tmp][j+1+tmp]==0) {
                             if (plansza[i-2-tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case -12: {
                    if (kolor==2) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==2 || plansza[i+1+tmp][j-1-tmp]==12)
                                break;
                            if ((plansza[i+1+tmp][j-1-tmp]==1 || plansza[i+1+tmp][j-1-tmp]==11 || plansza[i+1+tmp][j-1-tmp]==-1 || plansza[i+1+tmp][j-1-tmp]==-11) && zbite[i+1+tmp][j-1-tmp]==0) {
                             if (plansza[i+2+tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==2 || plansza[i+1+tmp][j+1+tmp]==12)
                                break;
                            if ((plansza[i+1+tmp][j+1+tmp]==1 || plansza[i+1+tmp][j+1+tmp]==11 || plansza[i+1+tmp][j+1+tmp]==-1 || plansza[i+1+tmp][j+1+tmp]==-11) && zbite[i+1+tmp][j+1+tmp]==0) {
                             if (plansza[i+2+tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==2 || plansza[i-1-tmp][j-1-tmp]==12)
                                break;
                            if ((plansza[i-1-tmp][j-1-tmp]==1 || plansza[i-1-tmp][j-1-tmp]==11 || plansza[i-1-tmp][j-1-tmp]==-1 || plansza[i-1-tmp][j-1-tmp]==-11) && zbite[i-1-tmp][j-1-tmp]==0) {
                             if (plansza[i-2-tmp][j-2-tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==2 || plansza[i-1-tmp][j+1+tmp]==12)
                                break;
                            if ((plansza[i-1-tmp][j+1+tmp]==1 || plansza[i-1-tmp][j+1+tmp]==11 || plansza[i-1-tmp][j+1+tmp]==-1 || plansza[i-1-tmp][j+1+tmp]==-11) && zbite[i-1-tmp][j+1+tmp]==0) {
                             if (plansza[i-2-tmp][j+2+tmp]==0)
                                MRPionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            default: {}
        }
    }
}

void Game::sprawdzMRPole(int x, int y, int pionek) {

    zerujMRPole();

    switch(pionek){
    case 1: {
            if (plansza[x-1][y-1]==0)
                MRPole[x-3][y-3] = 1;
            if (plansza[x-1][y+1]==0)
                MRPole[x-3][y-1] = 1;
        } break;
    case 2: {
            if (plansza[x+1][y-1]==0)
                MRPole[x-1][y-3] = 1;
            if (plansza[x+1][y+1]==0)
                MRPole[x-1][y-1] = 1;
        } break;
    case 11: {
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x+1+tmp][y-1-tmp]==0)
                    MRPole[x-1+tmp][y-3-tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x+1+tmp][y+1+tmp]==0)
                    MRPole[x-1+tmp][y-1+tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x-1-tmp][y-1-tmp]==0)
                    MRPole[x-3-tmp][y-3-tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x-1-tmp][y+1+tmp]==0)
                    MRPole[x-3-tmp][y-1+tmp] = 1;
                else
                    break;
            }
        } break;
    case 12: {
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x+1+tmp][y-1-tmp]==0)
                    MRPole[x-1+tmp][y-3-tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x+1+tmp][y+1+tmp]==0)
                    MRPole[x-1+tmp][y-1+tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x-1-tmp][y-1-tmp]==0)
                    MRPole[x-3-tmp][y-3-tmp] = 1;
                else
                    break;
            }
            for (tmp=0; tmp<7; tmp++){
                if(plansza[x-1-tmp][y+1+tmp]==0)
                    MRPole[x-3-tmp][y-1+tmp] = 1;
                else
                    break;
            }
        } break;
    default: {}
    }
}

void Game::sprawdzMBPole(int x, int y, int pionek) {

    zerujMRPole();

    switch(pionek){
    case 1: {
            if (plansza[x-2][y-2]==0 && (plansza[x-1][y-1]==2 || plansza[x-1][y-1]==12) && zbite[x-1][y-1]==0) {
                MRPole[x-4][y-4] = 1;
                MRPole[x-3][y-3] = 2;
            }
            if (plansza[x-2][y+2]==0 && (plansza[x-1][y+1]==2 || plansza[x-1][y+1]==12) && zbite[x-1][y+1]==0) {
                MRPole[x-4][y] = 1;
                MRPole[x-3][y-1] = 2;
            }
            if (plansza[x+2][y-2]==0 && (plansza[x+1][y-1]==2 || plansza[x+1][y-1]==12) && zbite[x+1][y-1]==0) {
                MRPole[x][y-4] = 1;
                MRPole[x-1][y-3] = 2;
            }
            if (plansza[x+2][y+2]==0 && (plansza[x+1][y+1]==2 || plansza[x+1][y+1]==12) && zbite[x+1][y+1]==0) {
                MRPole[x][y] = 1;
                MRPole[x-1][y-1] = 2;
            }
        } break;
    case 2: {
            if (plansza[x-2][y-2]==0 && (plansza[x-1][y-1]==1 || plansza[x-1][y-1]==11) && zbite[x-1][y-1]==0) {
                MRPole[x-4][y-4] = 1;
                MRPole[x-3][y-3] = 2;
            }
            if (plansza[x-2][y+2]==0 && (plansza[x-1][y+1]==1 || plansza[x-1][y+1]==11) && zbite[x-1][y+1]==0) {
                MRPole[x-4][y] = 1;
                MRPole[x-3][y-1] = 2;
            }
            if (plansza[x+2][y-2]==0 && (plansza[x+1][y-1]==1 || plansza[x+1][y-1]==11) && zbite[x+1][y-1]==0) {
                MRPole[x][y-4] = 1;
                MRPole[x-1][y-3] = 2;
            }
            if (plansza[x+2][y+2]==0 && (plansza[x+1][y+1]==1 || plansza[x+1][y+1]==11) && zbite[x+1][y+1]==0) {
                MRPole[x][y] = 1;
                MRPole[x-1][y-1] = 2;
            }
        } break;
    case 11: {
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==1 || plansza[x+1+tmp][y-1-tmp]==11)
                    break;
                if ((plansza[x+1+tmp][y-1-tmp]==2 || plansza[x+1+tmp][y-1-tmp]==12) && zbite[x+1+tmp][y-1-tmp]==0) {
                   if (plansza[x+2+tmp][y-2-tmp]==0) {
                        MRPole[x+tmp][y-4-tmp] = 1;
                        MRPole[x-1+tmp][y-3-tmp] = 2;
                   }
                   break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==11)
                    break;
                if ((plansza[x+1+tmp][y+1+tmp]==2 || plansza[x+1+tmp][y+1+tmp]==12) && zbite[x+1+tmp][y+1+tmp]==0) {
                    if (plansza[x+2+tmp][y+2+tmp]==0) {
                        MRPole[x+tmp][y+tmp] = 1;
                        MRPole[x-1+tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==11)
                    break;
                if ((plansza[x-1-tmp][y-1-tmp]==2 || plansza[x-1-tmp][y-1-tmp]==12) && zbite[x-1-tmp][y-1-tmp]==0) {
                    if (plansza[x-2-tmp][y-2-tmp]==0) {
                        MRPole[x-4-tmp][y-4-tmp] = 1;
                        MRPole[x-3-tmp][y-3-tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==11)
                    break;
                if ((plansza[x-1-tmp][y+1+tmp]==2 || plansza[x-1-tmp][y+1+tmp]==12) && zbite[x-1-tmp][y+1+tmp]==0) {
                    if (plansza[x-2-tmp][y+2+tmp]==0) {
                        MRPole[x-4-tmp][y+tmp] = 1;
                        MRPole[x-3-tmp][y-1+tmp] = 2;
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
                        MRPole[x+tmp][y-4-tmp] = 1;
                        MRPole[x-1+tmp][y-3-tmp] = 2;
                   }
                   break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==2 || plansza[x+1+tmp][y+1+tmp]==12)
                    break;
                if ((plansza[x+1+tmp][y+1+tmp]==1 || plansza[x+1+tmp][y+1+tmp]==11) && zbite[x+1+tmp][y+1+tmp]==0) {
                    if (plansza[x+2+tmp][y+2+tmp]==0) {
                        MRPole[x+tmp][y+tmp] = 1;
                        MRPole[x-1+tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==2 || plansza[x-1-tmp][y-1-tmp]==12)
                    break;
                if ((plansza[x-1-tmp][y-1-tmp]==1 || plansza[x-1-tmp][y-1-tmp]==11) && zbite[x-1-tmp][y-1-tmp]==0) {
                    if (plansza[x-2-tmp][y-2-tmp]==0) {
                        MRPole[x-4-tmp][y-4-tmp] = 1;
                        MRPole[x-3-tmp][y-3-tmp] = 2;
                    }
                    break;
                }
            }
            for (tmp=0; tmp<7; tmp++){
                if (zbite[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==2 || plansza[x-1-tmp][y+1+tmp]==12)
                    break;
                if ((plansza[x-1-tmp][y+1+tmp]==1 || plansza[x-1-tmp][y+1+tmp]==11) && zbite[x-1-tmp][y+1+tmp]==0) {
                    if (plansza[x-2-tmp][y+2+tmp]==0) {
                        MRPole[x-4-tmp][y+tmp] = 1;
                        MRPole[x-3-tmp][y-1+tmp] = 2;
                    }
                    break;
                }
            }
        } break;
    default: {}
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {

    yPos = event->x();
    xPos = event->y();
    repaint();
}

void Game::mousePressEvent(QMouseEvent *event) {

    xPos = this->xPos/(this->width()/8);
    yPos = this->yPos/(this->height()/8);

    if(event->button()==Qt::LeftButton) {

        switch(etap) {
                case 1: {
                        if(bicieNext==0) {
                            zerujZbite();
                            sprawdzMBPionek(1);
                            bicie = 0;
                            for (i=0; i<8; i++)
                                for (j=0; j<8; j++)
                                    if(MRPionek[i][j]==1) {
                                        bicie++;
                                        break;
                                    }
                            if (bicie==0)
                                sprawdzMRPionek(1);
                        }

                        if(((plansza[xPos+2][yPos+2]==1 || plansza[xPos+2][yPos+2]==11) && MRPionek[xPos][yPos]==1) && bicieNext==0) {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(plansza[i][j]<0)
                                        plansza[i][j] = -plansza[i][j];

                            plansza[xPos+2][yPos+2] = -plansza[xPos+2][yPos+2];

                            if(bicie==0)
                                sprawdzMRPole(xPos+2, yPos+2, -plansza[xPos+2][yPos+2]);
                            else
                                sprawdzMBPole(xPos+2, yPos+2, -plansza[xPos+2][yPos+2]);
                        }
                        if(plansza[xPos+2][yPos+2]==0 && MRPole[xPos][yPos]==1) {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(plansza[i][j]<0) {
                                        plansza[xPos+2][yPos+2] = -plansza[i][j];

                                        plansza[i][j] = 0;
                                    }

                            if(bicie>0) {
                                if(MRPole[xPos+1][yPos+1]==2)
                                    zbite[xPos+3][yPos+3] = 1;
                                if(MRPole[xPos-1][yPos-1]==2)
                                    zbite[xPos+1][yPos+1] = 1;
                                if(MRPole[xPos+1][yPos-1]==2)
                                    zbite[xPos+3][yPos+1] = 1;
                                if(MRPole[xPos-1][yPos+1]==2)
                                    zbite[xPos+1][yPos+3] = 1;
                            }

                            if(bicie>0) {
                                bicieNext = 0;
                                sprawdzMBPole(xPos+2, yPos+2, plansza[xPos+2][yPos+2]);
                                for (i=0; i<8; i++)
                                    for (j=0; j<8; j++)
                                        if(MRPole[i][j]==1) {
                                            bicieNext++;
                                            break;
                                        }
                            }

                            if(bicieNext>0)
                                plansza[xPos+2][yPos+2] = -plansza[xPos+2][yPos+2];

                            if(bicieNext>0)
                                etap = 1;
                            else {
                                zerujMRPole();

                                if(xPos==0)
                                    plansza[xPos+2][yPos+2] = 11;

                                for (i=2; i<10; i++)
                                    for (j=2; j<10; j++)
                                        if(zbite[i][j]==1)
                                            plansza[i][j] = 0;

                                bicieNext = 0;
                                etap = 2;
                            }
                        }
                    } break;
                case 2: {
                        if(bicieNext==0) {
                            zerujZbite();
                            sprawdzMBPionek(2);
                            bicie = 0;
                            for (i=0; i<8; i++)
                                for (j=0; j<8; j++)
                                    if(MRPionek[i][j]==1) {
                                        bicie++;
                                        break;
                                    }
                            if (bicie==0)
                                sprawdzMRPionek(2);
                        }

                        if(((plansza[xPos+2][yPos+2]==2 || plansza[xPos+2][yPos+2]==12) && MRPionek[xPos][yPos]==1) && bicieNext==0) {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(plansza[i][j]<0)
                                        plansza[i][j] = -plansza[i][j];

                            plansza[xPos+2][yPos+2] = -plansza[xPos+2][yPos+2];

                            if(bicie==0)
                                sprawdzMRPole(xPos+2, yPos+2, -plansza[xPos+2][yPos+2]);
                            else
                                sprawdzMBPole(xPos+2, yPos+2, -plansza[xPos+2][yPos+2]);
                        }
                        if(plansza[xPos+2][yPos+2]==0 && MRPole[xPos][yPos]==1) {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if (plansza[i][j]<0) {
                                        plansza[xPos+2][yPos+2] = -plansza[i][j];

                                        plansza[i][j] = 0;
                                    }

                            if(bicie>0) {
                                if(MRPole[xPos+1][yPos+1]==2)
                                    zbite[xPos+3][yPos+3] = 1;
                                if(MRPole[xPos-1][yPos-1]==2)
                                    zbite[xPos+1][yPos+1] = 1;
                                if(MRPole[xPos+1][yPos-1]==2)
                                    zbite[xPos+3][yPos+1] = 1;
                                if(MRPole[xPos-1][yPos+1]==2)
                                    zbite[xPos+1][yPos+3] = 1;
                            }

                            if(bicie>0) {
                                bicieNext = 0;
                                sprawdzMBPole(xPos+2, yPos+2, plansza[xPos+2][yPos+2]);
                                for (i=0; i<8; i++)
                                    for (j=0; j<8; j++)
                                        if(MRPole[i][j]==1) {
                                            bicieNext++;
                                            break;
                                        }
                            }

                            if(bicieNext>0)
                                plansza[xPos+2][yPos+2] = -plansza[xPos+2][yPos+2];

                            if(bicieNext>0)
                                etap = 2;
                            else {
                                zerujMRPole();

                                if(xPos==7)
                                    plansza[xPos+2][yPos+2] = 12;

                                for (i=2; i<10; i++)
                                    for (j=2; j<10; j++)
                                        if(zbite[i][j]==1)
                                            plansza[i][j] = 0;

                                bicieNext = 0;
                                etap = 1;
                            }
                        }
                    } break;
                default: {}
        }

        if(bicieNext>0)
            emit saveOff();
        else
            if(etap!=0)
                emit saveOn();

        if(etap==2) {
            etap = -1;
            for (i=2; i<10; i++)
                for (j=2; j<10; j++)
                    if(plansza[i][j]==2 || plansza[i][j]==12 || plansza[i][j]==-2 || plansza[i][j]==-12)
                        etap = 2;
            if(etap!=-1) {
                sprawdzMRPionek(2);
                etap = -1;
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRPionek[i][j]==1)
                            etap = 2;
            }
            if(etap==-1) {
                sprawdzMBPionek(2);
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRPionek[i][j]==1)
                            etap = 2;
            }
        }

        if (etap==1) {
            etap = -2;
            for (i=2; i<10; i++)
                for (j=2; j<10; j++)
                    if(plansza[i][j]==1 || plansza[i][j]==11 || plansza[i][j]==-1 || plansza[i][j]==-11)
                        etap = 1;
            if(etap!=-2) {
                sprawdzMRPionek(1);
                etap = -2;
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRPionek[i][j]==1)
                            etap = 1;
            }
            if(etap==-2) {
                sprawdzMBPionek(1);
                for (i=0; i<8; i++)
                    for (j=0; j<8; j++)
                        if(MRPionek[i][j]==1)
                            etap = 1;
            }
        }

        if (etap<0)
            zerujMRPole();

        if(etap==1)
            emit zmianaEtap("<br>RUCH<br><b>BIALYCH<br></b>");
        if(etap==2)
            emit zmianaEtap("<br>RUCH<br><b>CZARNYCH<br></b>");
        if(etap==-1) {
            emit zmianaEtap("<br>WYGRANA<br><b>BIALYCH<br></b>");
            emit saveOff();
        }
        if(etap==-2) {
            emit zmianaEtap("<br>WYGRANA<br><b>CZARNYCH<br></b>");
            emit saveOff();
        }
			
        repaint();
    }
}

void Game::paintEvent(QPaintEvent*) {

  int szerPola = this->width()/8;
  int wysPola = this->height()/8;

  int x;
  int y = 0;

  QPainter painter(this);
  for (int i=0 ; i<8 ; i++) {
        x=0;
        for (int j=0 ; j<8 ; j++) {
            if((i%2==0 && j%2!=0) || (i%2!=0 && j%2==0)) {
                painter.setBrush(QBrush(QColor(128, 64, 0)));
                painter.drawRect(x, y, szerPola, wysPola);
            }
            else {
                painter.setBrush(QBrush(QColor(225, 226, 163)));
                painter.drawRect(x, y, szerPola, wysPola);
            }

            if (MRPole[i][j]==1) {
                painter.setBrush(QBrush(Qt::green));
                painter.drawRect(x, y, szerPola, wysPola);
            }
            if (MRPole[i][j]==2) {
                painter.setBrush(QBrush(Qt::red));
                painter.drawRect(x, y, szerPola, wysPola);
            }

            switch(plansza[i+2][j+2]) {
            case 1: {
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case 2: {
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case 11: {
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case 12: {
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case -1: {
                    painter.setBrush(QBrush(Qt::yellow));
                    painter.drawRect(x, y, szerPola, wysPola);
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case -2: {
                    painter.setBrush(QBrush(Qt::yellow));
                    painter.drawRect(x, y, szerPola, wysPola);
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                } break;
            case -11: {
                    painter.setBrush(QBrush(Qt::yellow));
                    painter.drawRect(x, y, szerPola, wysPola);
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            case -12: {
                    painter.setBrush(QBrush(Qt::yellow));
                    painter.drawRect(x, y, szerPola, wysPola);
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawEllipse(x+7, y+7, szerPola-14, wysPola-14);
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawEllipse(x+20, y+20, szerPola-40, wysPola-40);
                } break;
            default: {}
            }
            x=x+szerPola;
        }
        y=y+wysPola;
  }
}
