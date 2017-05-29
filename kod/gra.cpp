
#include "gra.h"

using namespace std;

Interfejs::Interfejs() {

    gra = new Gra();

    setWindowTitle("Witaj w grze warcaby!");
    setFixedSize(572,492);

    pbNOWA_GRA = new QPushButton(tr("&NOWA GRA"), this);
    pbZAPISZ = new QPushButton(tr("&ZAPISZ GRE"), this);
    pbZAPISZ->setDisabled(true);
    connect(gra, SIGNAL(saveOn()), this, SLOT(FsaveOn()));
    connect(gra, SIGNAL(saveOff()), this, SLOT(FsaveOff()));

    pbWCZYTAJ = new QPushButton(tr("&WCZYTAJ GRE"), this);

    pbWyjscie = new QPushButton(tr("&KONIEC"), this);

        infoLabel = new QLabel(tr("<br>ROZPOCZNIJ<br><b>NOWA GRE</b><br>"));
        infoLabel->setFrameStyle(QFrame::WinPanel | QFrame::Raised/*Sunken*/);
        infoLabel->setAlignment(Qt::AlignCenter);
        connect(gra, SIGNAL(zmianaetapu(QString)), infoLabel, SLOT(setText(QString)));


        QVBoxLayout *lPrzyciski = new QVBoxLayout();
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(pbNOWA_GRA);
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(infoLabel);
        lPrzyciski->addStretch(1);
        lPrzyciski->addWidget(pbZAPISZ);
        lPrzyciski->addWidget(pbWCZYTAJ);
        lPrzyciski->addWidget(pbKONIEC_GRY);
        lPrzyciski->addStretch(10);

        QHBoxLayout *lPlansza = new QHBoxLayout();
        lPlansza->addLayout(lPrzyciski);
        lPlansza->addWidget(gra);
        lPlansza->setStretch(1,1);

        this->setLayout(lPlansza);

        connect(pbNOWA_GRA, SIGNAL(clicked()), gra, SLOT(nowagra()));
        connect(pbZAPISZ, SIGNAL(clicked()), gra, SLOT(zapiszgra()));
        connect(pbWCZYTAJ, SIGNAL(clicked()), gra, SLOT(wczytajgre()));
        connect(pbKONIEC_GRY, SIGNAL(clicked()), this, SLOT(close()));
}
Interfejs::~Interfejs() {}

void Interfejs::Zapisz() {
    pbZAPISZ->setDisabled(false);
}

void Interfejs::Niezapisuj() {
    pbZAPISZ->setDisabled(true);
}

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
            MRPionek[i][j] = 0;
}

void Gra::wyzerujMRPole() {

    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            MRPole[i][j] = 0;
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

    wyzerujMRPole();
    nast_zbijanie = 0;

    etap = 1;
    emit zmianaetapu("<br>TERAZ<br><b>BIALE<br></b>");
    emit saveOn();

    repaint();
}

void Game::saveGame() {

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

void Game::wczytajgre() {

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

void Game::sprawdzMRpionek(int kolor) {

    wyzerujMRpionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(planszagry[i][j]){
            case 1: {
                if (kolor==1)
                    if(planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -1: {
                if (kolor==1)
                    if(planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 2: {
                if (kolor==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -2: {
                if (kolor==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 11: {
                if (kolor==1)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -11: {
                if (kolor==1)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case 12: {
                if (kolor==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            case -12: {
                if (kolor==2)
                    if(planszagry[i+1][j-1]==0 || planszagry[i+1][j+1]==0 || planszagry[i-1][j-1]==0 || planszagry[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
            } break;
            default: {}
        }
    }
}

void Gra::mouseMoveEvent(QMouseEvent *event) {
    poz_x = event->y();
    poz_y = event->x();
    repaint();
}

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
                        if(((planszagry[poz_x+2][poz_y+2]==1 || planszagry[poz_x+2][poz_y+2]==11) && MRpionek[poz_x][poz_y]==1) && nast_zbijanie==0)
                            {
                            for (i=2; i<10; i++)
                                for (j=2; j<10; j++)
                                    if(planszagry[i][j]<0)
                                        planszagry[i][j] = -planszagry[i][j];

                            planszagry[poz_x+2][poz_y+2] = -planszagry[poz_x+2][poz_y+2];

                            if(zbijanie==0)
                                sprawdzMRpole(poz_x+2, poz_y+2, -planszagry[poz_x+2][poz_y+2]);
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

                                if(zbijane>0)
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

                                if(nast_zbijanie->0)
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
// FUNKCJA KINGI mousePressEvent
