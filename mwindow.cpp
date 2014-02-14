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
    family_names = ListPointerT<QString>(4);
    family_names.insert(0, "cups");
    family_names.insert(1, "diam");
    family_names.insert(2, "heart");
    family_names.insert(3, "clov");

    mainOne = CardPile(this, 52);
    mainOne.setCorner(QPoint(20,20));
    generateLabels();
    initializePiles();
    deal();

}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::showCard(CardLabel *label)
{


}

void MWindow::hideCard(CardLabel *label)
{

}

void MWindow::showHideCard(CardLabel *card, bool v)
{
    if(v){
        QString ins("background-image: url(:/cards/card_pngs/");
        ins.append( family_names.get( card->getFamily() ) );
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
            lCard->hide();
            lCard->setCardID(index);
            lCard->setFamily( i );
            lCard->setCardNumber(j);
            lCard->setOwnerID( 0 );

            mainOne.insert(index,lCard);
            lCard->setGeometry(20,20, 135, 201);
            index++;
        }
    }
    srand ( unsigned ( time(0) ) );
    for(int i = 0; i < mainOne.getCount(); i++)
        mainOne.shuffleItems();
    reorderZ();
}

void MWindow::initializePiles()
{
    pileArray = ListPointerT<CardPile>(14);
    pileArray.insert(0, mainOne); //mainOne has index 0

    pile1 = CardPile(this, 20); pileArray.insert(1, pile1); //piles get their digit as index
    pile1.setCorner(QPoint(20,165));
    pile2 = CardPile(this, 20); pileArray.insert(2, pile2);
    pile2.setCorner(QPoint(160,165));
    pile3 = CardPile(this, 20); pileArray.insert(3, pile3);
    pile3.setCorner(QPoint(300,165));
    pile4 = CardPile(this,20); pileArray.insert(4, pile4);
    pile4.setCorner(QPoint(440,165));
    pile5 = CardPile(this,20); pileArray.insert(5, pile5);
    pile5.setCorner(QPoint(580,165));
    pile6 = CardPile(this, 20); pileArray.insert(6, pile6);
    pile6.setCorner(QPoint(720,165));
    pile7 = CardPile(this, 20); pileArray.insert(7, pile7); //piles get their digit as index
    pile1.setCorner(QPoint(860,165));

    temp_Store = CardPile(this, 24); pileArray.insert(8, temp_Store); //index 8
    temp_Store.setCorner(QPoint(174,20));
    foundCups = CardPile(this, 13); pileArray.insert(9, foundCups); //index 9
    foundCups.setCorner(QPoint(384,20));
    foundClovs = CardPile(this, 13); pileArray.insert(10, foundClovs); //index 10
    foundClovs.setCorner(QPoint(538,20));
    foundHearts = CardPile(this, 13); pileArray.insert(11, foundHearts); //index 11
    foundHearts.setCorner(QPoint(692,20));
    foundDiams = CardPile(this, 13); pileArray.insert(12, foundDiams); //index 12
    foundDiams.setCorner(QPoint(846,20));

    aero = CardPile(this,13); pileArray.insert(13, aero); //index 13
}

void MWindow::deal()
{

    for(int i = 1; i <= 7; i++){
        for(int j = 0; j <= i; j++){
            //NodeT<CardLabel*>* mCard = mainOne.disconnectLast();
            //qDebug() << "\nDisconnectd " << mCard;
            //pileArray.get(i).append(mCard);
            qDebug() << "\nGot here";
            //CardLabel* temp = mCard->value;
            qDebug() << "\ncreated mCard";
            //temp->setOwnerID(i);
            //temp->move(pileArray.get(i).getCorner());
            //if(j == i)
              //  temp->show();
        }
    }
}

void MWindow::reorderZ()
{
    mainOne.fixIndexes();
    for(int i = 0; i < 52; i++){
        CardLabel *card = mainOne.get(i);
        int index = card->property("cardid").toInt();
        for(int z = 0; z <= index; z++)
            card->raise();
    }

}

void MWindow::cardPressed(QMouseEvent *e, CardLabel *card)
{

}

void MWindow::cardMoved(QMouseEvent *e, CardLabel *card)
{

}

void MWindow::cardReleased(QMouseEvent *e, CardLabel *card)
{

}

void MWindow::cardDoubleClick(QMouseEvent *e, CardLabel *card)
{

}
