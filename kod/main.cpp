/*
  Name: Warcaby
  Version: 1.1
  Copyright: GPL GNU
  Author: Bartosz 'Orange' Owczarek
*/

#include <QApplication>
#include "gra.h"
#include "interfejs.h"

using namespace std;

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Interfejs warcaby;
  warcaby.show();
  return app.exec();
}
