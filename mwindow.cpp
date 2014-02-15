#include "mwindow.h"
#include "ui_mwindow.h"
#include <algorithm>
#include <ctime>

using namespace std;

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    piles = new CardPile[14];
    pileArray = ListPointerT<CardPile>();
    family_names = ListPointerT<QString>();
    family_names.insert(0, "cups");
    family_names.insert(1, "diam");
    family_names.insert(2, "heart");
    family_names.insert(3, "clov");

    mainOne = CardPile(this);
    mainOne.setCorner(QPoint(20,20));
    generateLabels();
    initializePiles();
    deal();
}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::showHideCard(CardLabel *card, bool v)
{
    if(v){
        QString ins("background-image: url(:/cards/card_pngs/");
        int famin = card->getFamily();
        QString fam(family_names.get( famin ));

        ins.append( fam );
        ins.append("_");
        ins.append(QString::number( card->getCardNumber() ));
        ins.append(".png);  background-repeat: none;");
        card->setStyleSheet(ins);
    }else{
        card->setStyleSheet("background-image: url(:/cards/card_pngs/card_back.png); background-repeat: none;");
    }
}

void MWindow::generateLabels(){
    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            CardLabel* lCard = new CardLabel(this);
            //lCard->setProperty("faceup", true);
            //lCard->setProperty("cardid", index);
            connect(lCard, SIGNAL(showHide(CardLabel*,bool)), this, SLOT(showHideCard(CardLabel*,bool)));
            connect(lCard, SIGNAL(mousePressed(QMouseEvent*,CardLabel*)), this, SLOT(cardPressed(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseDoubleClick(QMouseEvent*,CardLabel*)), this, SLOT(cardDoubleClick(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseReleased(QMouseEvent*,CardLabel*)), this, SLOT(cardReleased(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseMoved(QMouseEvent*,CardLabel*)), this, SLOT(cardMoved(QMouseEvent*,CardLabel*)));
            lCard->setCardID(index);
            lCard->setFamily( i );
            lCard->setCardNumber(j);
            lCard->setOwnerID( 0 );
            lCard->show();
            lCard->setOnTop(index == 51);
            lCard->raise();

            mainOne.insert(index,lCard);
            lCard->setGeometry(20,20, 135, 201);
            index++;
        }
    }
    srand ( unsigned ( time(0) ) );
    for(int i = 0; i < mainOne.getCount(); i++)
        mainOne.shuffleItems();
}

void MWindow::initializePiles()
{
    //pileArray.insert(0, mainOne); //mainOne has index 0
    piles[0] = mainOne;
    mainOne.setPileID(0);

    pile1 = CardPile(this); //pileArray.insert(pile1); //piles get their digit as index
    pile1.setCorner(QPoint(20,235));
    pile1.setPileID(1);
    piles[1] = pile1;

    pile2 = CardPile(this); //pileArray.insert(2, pile2);
    pile2.setCorner(QPoint(160,235));
    pile2.setPileID(2);
    piles[2] = pile2;

    pile3 = CardPile(this); //pileArray.insert(3, pile3);
    pile3.setCorner(QPoint(300,235));
    pile3.setPileID(3);
    piles[3] = pile3;

    pile4 = CardPile(this); //pileArray.insert(4, pile4);
    pile4.setCorner(QPoint(440,235));
    pile4.setPileID(4);
    piles[4] = pile4;

    pile5 = CardPile(this); //pileArray.insert(5, pile5);
    pile5.setCorner(QPoint(580,235));
    pile5.setPileID(5);
    piles[5] = pile5;

    pile6 = CardPile(this); //pileArray.insert(6, pile6);
    pile6.setCorner(QPoint(720,235));
    pile6.setPileID(6);
    piles[6] = pile6;

    pile7 = CardPile(this); //pileArray.insert(7, pile7); //piles get their digit as index
    pile7.setCorner(QPoint(860,235));
    pile7.setPileID(7);
    piles[7] = pile7;

    temp_Store = CardPile(this); //pileArray.insert(8, temp_Store); //index 8
    temp_Store.setCorner(QPoint(174,20));
    temp_Store.setPileID(8);
    piles[8] = temp_Store;

    foundCups = CardPile(this); //pileArray.insert(9, foundCups); //index 9
    foundCups.setCorner(QPoint(384,20));
    foundCups.setPileID(9);
    piles[9] = foundCups;

    foundClovs = CardPile(this); //pileArray.insert(10, foundClovs); //index 10
    foundClovs.setCorner(QPoint(538,20));
    foundClovs.setPileID(10);
    piles[10] = foundClovs;

    foundHearts = CardPile(this); //pileArray.insert(11, foundHearts); //index 11
    foundHearts.setCorner(QPoint(692,20));
    foundHearts.setPileID(11);
    piles[11] = foundHearts;

    foundDiams = CardPile(this); //pileArray.insert(12, foundDiams); //index 12
    foundDiams.setCorner(QPoint(846,20));
    foundDiams.setPileID(12);
    piles[12] = foundDiams;

    aero = CardPile(this); //pileArray.insert(13, aero); //index 13
    aero.setPileID(13);
    piles[13] = aero;
}

void MWindow::deal()
{
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= i; j++){
            NodeT<CardLabel*>* mCard = mainOne.disconnectLast();
            pileArray.get(i).append(mCard);
            CardLabel* temp = mCard->value;
            temp->setOwnerID(i);
            temp->move(piles[i].getCorner());
            temp->hide();
            temp->raise();
            if(j == i)
                temp->show();
        }
    }
}


void MWindow::cardPressed(QMouseEvent *, CardLabel *)
{

}

void MWindow::cardMoved(QMouseEvent *, CardLabel *)
{

}

void MWindow::cardReleased(QMouseEvent *, CardLabel *)
{

}

void MWindow::cardDoubleClick(QMouseEvent *, CardLabel *card)
{
    int wPile = card->getOwnerID();
    if(wPile != 0)
        return;
}
