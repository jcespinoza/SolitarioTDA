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

    pile1 = CardPile(this, 20); pileArray.insert(pile1); //piles get their digit as index
    pile1.setCorner(QPoint(20,235));
    pile1.setX(20);
    pile1.setY(165);
    //qDebug() << "OK PRINT: " << pileArray.get(1).getCorner();
    qDebug() << "PILE1 " << pile1.getCorner();
    pile2 = CardPile(this, 20); pileArray.insert(2, pile2);
    pile2.setCorner(QPoint(160,235));
    pile3 = CardPile(this, 20); pileArray.insert(3, pile3);
    pile3.setCorner(QPoint(300,235));
    pile4 = CardPile(this,20); pileArray.insert(4, pile4);
    pile4.setCorner(QPoint(440,235));
    pile5 = CardPile(this,20); pileArray.insert(5, pile5);
    pile5.setCorner(QPoint(580,235));
    pile6 = CardPile(this, 20); pileArray.insert(6, pile6);
    pile6.setCorner(QPoint(720,235));
    pile7 = CardPile(this, 20); pileArray.insert(7, pile7); //piles get their digit as index
    pile7.setCorner(QPoint(860,235));

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
    qDebug () << "\n HOW MANY? " << pileArray.getCount();
}

void MWindow::deal()
{

    for(int i = 1; i <= 7; i++){
        for(int j = 0; j <= i; j++){
            NodeT<CardLabel*>* mCard = mainOne.disconnectLast();
            pileArray.get(i).append(mCard);
            CardLabel* temp = mCard->value;
            temp->setOwnerID(i);
            temp->move(pile1.getCorner());
            //qDebug() << "\nOn ta bebe? Aki ta: " << temp->pos();
            if(j == i)
                temp->show();
        }
    }
    qDebug() << "CORNER on P1 " << pile1.getCorner();
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
