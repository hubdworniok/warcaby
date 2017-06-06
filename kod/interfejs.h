#pragma once

#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

#include <fstream>
#include "gra.h"

class Interfejs : public QWidget {
  Q_OBJECT
  public:
        Interfejs();
        ~Interfejs();
  public slots:
        void Zapisz();
        void Niezapisuj();
  private:
        Gra *gra;

        QPushButton *pbNOWA_GRA;
        QPushButton *pbZAPISZ;
        QPushButton *pbWCZYTAJ;
        QPushButton *pbKONIEC_GRY;
        QLabel *infoLabel;
        QLabel *autorLabel;
};
