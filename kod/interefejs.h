#include <iostream>
#include <stdlib>

using namespace std;


class Interface : public QWidget
{
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
