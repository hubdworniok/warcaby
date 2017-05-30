/*
 * Plik nag?ówkowy gra.h
*/


#ifndef GRA_H_INCLUDED
#define GRA_H_INCLUDED

#include <iostream>
#include <stdlib>

using namespace std;

class Gra : public QWidget {

        Q_OBJECT;

        public:
                Gra();
                ~Gra();

                void wyzerujplansze();
                void wyzerujzbite();
                void wyzerujMRpionek();
                void wyzerujMRpole();

                void sprawdzMRPionek(int kolor);
                void sprawdzMBPionek(int kolor);
                void sprawdzMRPole(int x, int y, int pionek);
                void sprawdzMBPole(int x, int y, int pionek);

                void mouseMoveEvent(QMouseEvent *event);
                void mousePressEvent(QMouseEvent *event);
                void paintEvent(QPaintEvent*);

        public slots:
                void nowagra();
                void zapiszgra();
                void wczytajgre();
        signals:
                void zmianaetapu(QString info);
                void saveOn();
                void saveOff();
        private:
                int i;
                int j;

                int xPos;
                int yPos;

                int plansza[12][12];
                int zbite[12][12];
                int MRPionek[8][8];
                int MRPole[8][8];

                int tmp;
                int etap;
                int bicie;
                int bicieNext;
};

class Interfejs : public QWidget {
  Q_OBJECT
  public:
        Interfejs();
        ~Interfejs();
  public slots:
        void FsaveOn();
        void FsaveOff();
  private:
        Game *game;

        QPushButton *pbNOWA_GRA;
        QPushButton *pbZAPISZ;
        QPushButton *pbWCZYTAJ;
        QPushButton *pbKONIEC_GRY;
        QLabel *infoLabel;
        QLabel *autorLabel;
};





#endif // GRA_H_INCLUDED
