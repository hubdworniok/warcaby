/*
  Name: Warcaby
  Version: 1.1
  Copyright: GPL GNU
  Author: Bartosz 'Orange' Owczarek
*/

#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

#include <fstream>

#ifndef WARCABY_H_
#define WARCABY_H_

class Game : public QWidget {

        Q_OBJECT;

        public:
                Game();
                ~Game();

                void zerujPlansza();
                void zerujZbite();
                void zerujMRPionek();
                void zerujMRPole();

                void sprawdzMRPionek(int kolor);
                void sprawdzMBPionek(int kolor);
                void sprawdzMRPole(int x, int y, int pionek);
                void sprawdzMBPole(int x, int y, int pionek);

                void mouseMoveEvent(QMouseEvent *event);
                void mousePressEvent(QMouseEvent *event);
                void paintEvent(QPaintEvent*);

        public slots:
                void newGame();
                void saveGame();
                void loadGame();
        signals:
                void zmianaEtap(QString info);
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

class Interface : public QWidget {
  Q_OBJECT
  public:
        Interface();
        ~Interface();
  public slots:
        void FsaveOn();
        void FsaveOff();
  private:
        Game *game;

        QPushButton *pbNowa_gra;
        QPushButton *pbZapisz_gre;
        QPushButton *pbWczytaj_gre;
        QPushButton *pbWyjscie;
        QLabel *infoLabel;
        QLabel *autorLabel;
};

#endif
