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

    ui->main_deck->installEventFilter(this);

    piles = new CardPile[14];
    pileArray = ListPointerT<CardPile>();
    family_names = ListPointerT<QString>();
    family_names.insert(0, "cups");
    family_names.insert(1, "diam");
    family_names.insert(2, "heart");
    family_names.insert(3, "clov");

    mainOne = CardPile(this);
    mainOne.setCorner(QPoint(20,20));
    initializePiles();
    generateLabels();
    deal();
}

MWindow::~MWindow()
{
    delete ui;
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

void MWindow::transferCards(CardPile &to, NodeT<CardLabel*>* first, bool showPrevious)
{
    if(first != 0){
        QPoint newCoords = to.getCorner();
        NodeT<CardLabel*>* ls = to.last();
        if(ls != 0 && showPrevious)
            newCoords = ls->value->pos() + QPoint(0, 27);
        first->value->move(newCoords);
        to.append(first);
        first->value->setOwnerID(to.getPileID());
        to.makeLastOnTop();
        to.fixIndexes();
    }
}

void MWindow::resetMain()
{
    //Method to reset the main pile here
    NodeT<CardLabel*>* nCard = piles[8].disconnectLast();
    while(nCard != 0){
        nCard->value->hide();
        transferCards(mainOne, nCard, false);
        nCard = piles[8].disconnectLast();
    }
    piles[8].makeLastOnTop();
    piles[8].fixIndexes();
}

int MWindow::getDistance(QPoint p1, QPoint p2)
{
    int x1 = p1.x();
    int y1 = p1.y();
    int x2 = p2.x();
    int y2 = p2.y();
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dx2 = pow(dx, 2);
    int dy2 = pow(dy, 2);
    int distance = sqrt(dx2+dy2);
    return distance;
}

bool MWindow::moveIsValid(CardLabel *card, int dest_pile)
{
    int cFamily = card->getFamily();
    int cNumber = card->getCardNumber();
    CardPile dest = piles[dest_pile];
    //Check the foundations first
    if(dest_pile > 8){
        if(piles[13].getPointer(card)->next != 0)
            return false;
        if(dest.isEmpty() && cNumber != 1)
            return false;
        if(!dest.isEmpty() && dest.getLast()->getFamily() != cFamily)
            return false;
        if(!dest.isEmpty() && dest.getLast()->getCardNumber() != cNumber-1)
            return false;
        return true;
    }else{
        if(dest.isEmpty() && cNumber != 13)
            return false;
        if(!dest.isEmpty() && (dest.getLast()->isRed() == card->isRed()))
            return false;
        if(!dest.isEmpty() && (dest.getLast()->getCardNumber() != cNumber+1))
            return false;
        return true;
    }
    //test pile Type
    //testing emptyness
    //check the last card
    return true;
}

void MWindow::generateLabels(){
    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            CardLabel* lCard = new CardLabel(this);
            connect(lCard, SIGNAL(showHide(CardLabel*,bool)), this, SLOT(showHideCard(CardLabel*,bool)));
            connect(lCard, SIGNAL(mouseDragged(QMouseEvent*,CardLabel*)), this, SLOT(cardDragged(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseDoubleClick(QMouseEvent*,CardLabel*)), this, SLOT(cardDoubleClick(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseReleased(QMouseEvent*,CardLabel*)), this, SLOT(cardReleased(QMouseEvent*,CardLabel*)));
            connect(lCard, SIGNAL(mouseMoved(QMouseEvent*,CardLabel*)), this, SLOT(cardMoved(QMouseEvent*,CardLabel*)));
            lCard->setCardID(index);
            lCard->setFamily( i );
            lCard->setCardNumber(j);
            lCard->setOwnerID( 0 );
            lCard->hide();
            lCard->setOnTop(false);
            lCard->raise();

            mainOne.insert(index,lCard);
            lCard->setGeometry(20,20, CardLabel::CARD_WIDTH, CardLabel::CARD_HEIGHT);
            index++;
        }
    }
    srand ( unsigned ( time(0) ) );
    for(int i = 0; i < mainOne.getCount(); i++)
        mainOne.shuffleItems();
    mainOne.fixIndexes();
}


void MWindow::deal()
{

    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= i; j++){
            NodeT<CardLabel*>* mCard = mainOne.disconnectLast();
            //pileArray.get(i).append(mCard);
            piles[i].append(mCard);
            CardLabel* temp = mCard->value;
            temp->setOwnerID(i);
            temp->move(piles[i].getCorner());
            temp->hide();
            temp->setOnTop(false);
            if(j == i){
                temp->show();
                temp->setOnTop(true);
            }
        }
        piles[i].fixIndexes();
    }
    mainOne.fixIndexes();
    mainOne.updateCount();
    mainOne.last()->value->setOnTop(true);
}

void MWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    /*This is a MWindow's Event to handle the emptyness of the main deck*/
    if(childAt(e->pos()) == ui->main_deck){
        resetMain();
    }
}


void MWindow::cardDragged(QMouseEvent *, CardLabel *card)
{
    card->setOldOwnerID(card->getOwnerID());
    int oldpid = card->getOwnerID();
    if(oldpid == 0)
        return; //cards in mainOne cannot be dragged
    int indexF = piles[oldpid].getIndex(card);
    NodeT<CardLabel*>* first = piles[oldpid].disconnectFrom(indexF);
    transferCards(piles[13], first, false);
    qDebug() << "I'm being dragged";
}

void MWindow::cardMoved(QMouseEvent *, CardLabel *card)
{
    int pileid = card->getOwnerID();
    piles[pileid].updatePosFrom(card);
}

void MWindow::cardReleased(QMouseEvent *, CardLabel *card)
{
    int oldpid = card->getOldOwnerID();
    //at this point the oldOwner ID is the id of the Pile
    //where the card was before being transferred to the aero pile

    QPoint center = card->getCenter();
    int distance = -1;
    int indexFound = -1;

    //Check the piles first. All except mainOne (0)  and aero (13)
    for(int i = 1; i < 13; i++){
        distance = getDistance(center, piles[i].getCenter());
        //distance must be greater than -1 and less than half the width of a card
        //i must not be 8 (temp_store)
        if(distance > -1 && distance < CardLabel::CARD_WIDTH/1.5 && i != 8){
            indexFound = i;
            break;
        }
    }

    int indexOfCard = piles[13].getIndex(card);
    NodeT<CardLabel*>* first = 0;
    card->setOnAir(false);
    if(indexFound != -1 && moveIsValid(card, indexFound)){
        //validate the movement
        qDebug() << "it is fine to move";
        //Move the card to wherever the calculations
        first = piles[13].disconnectFrom(indexOfCard);
        transferCards(piles[indexFound], first, indexFound < 8);
        piles[indexFound].updatePosFrom(card);
        piles[oldpid].unconverLast();
    }else{
        first = piles[13].disconnectFrom(indexOfCard);
        transferCards(piles[oldpid], first, false);
        piles[oldpid].updatePosFrom(card);
    }
}

void MWindow::cardDoubleClick(QMouseEvent *, CardLabel *card)
{
    int wPile = card->getOwnerID();
    if(wPile != 0 || !card->isOnTop())
        return;

    NodeT<CardLabel*>* nCard = mainOne.disconnectLast();
    nCard->value->show();
    transferCards(piles[8], nCard, false);

    NodeT<CardLabel*>* nCard2 = mainOne.disconnectLast();
    nCard2->value->show();
    transferCards(piles[8], nCard2, false);
    NodeT<CardLabel*>* nCard3 = mainOne.disconnectLast();
    nCard3->value->show();
    transferCards(piles[8], nCard3, false);

    mainOne.makeLastOnTop();
    mainOne.fixIndexes();
}
