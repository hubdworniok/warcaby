/*
 * Plik nag?�wkowy gra.h
*/

#pragma once

#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

#include <fstream>


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

                void sprawdzMRpionek(int kolor);
                void sprawdzMBpionek(int kolor);
                void sprawdzMRpole(int x, int y, int pionek);
                void sprawdzMBpole(int x, int y, int pionek);

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

                int poz_x;
                int poz_y;

                int planszagry[12][12];
                int zbite_pionki[12][12];
                int MRpionek[8][8];
                int MRpole[8][8];

                int temp;
                int etap;
                int zbijanie;
                int nast_zbijanie;
};
