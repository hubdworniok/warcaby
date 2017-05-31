#include "interfejs.h"
#include "gra.h"

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

    pbKONIEC_GRY = new QPushButton(tr("&KONIEC"), this);

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
