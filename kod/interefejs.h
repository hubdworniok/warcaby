#include <iostream>
#include <stdlib>

using namespace std;


class Interfejs : public QWidget
{
  Q_OBJECT
  public:
        Interfejs();
        ~Interfejs();
  public slots:
        void Zapisz();
        void Niezapisuj();
  private:
        Game *game;

        QPushButton *pbNOWA_GRA;
        QPushButton *pbZAPISZ;
        QPushButton *pbWCZYTAJ;
        QPushButton *pbKONIEC_GRY;
        QLabel *infoLabel;
        QLabel *autorLabel;
};
