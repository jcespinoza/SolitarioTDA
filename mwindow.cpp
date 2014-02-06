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
    generateLabels();
    families = ListP(4);
}

MWindow::~MWindow()
{
    for(int i = 0; i < 52; i++){
        delete card_Labels[i];
    }
    delete ui;
}

void MWindow::showCard(QLabel *label)
{
    label->setProperty("faceup", true);
    int index = label->property("cardid").toInt();
    //get the card details from the item with this index in the list
    //Use this code to set the style
    /*
    QString ins("background-image: url(:/cards/card_pngs/");
    ins.append(names[i-1]);
    ins.append("_");
    ins.append(QString::number(j));
    ins.append(".png);  background-repeat: none;");
    lCard->setStyleSheet(ins);
    */
}

void MWindow::hideCard(QLabel *label)
{
    label->setProperty("faceup", false);
    QString cs = QString("Prop: ").append(label->property("faceup").toString());
    label->setStyleSheet("background-image: url(:/cards/card_pngs/card_back.png); background-repeat: none;");
}

void MWindow::generateLabels()
{
    families.insert(0, "cups");
    families.insert(1, "diam");
    families.insert(2, "heart");
    families.insert(3, "clov");
    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            QLabel* lCard = new CardLabel(this);
            lCard->setProperty("faceup", true);
            lCard->setProperty("cardid", index);
            card_Labels[index] = lCard;

            lCard->setGeometry(20,20, 135, 201);

            //hideCard(lCard);
            QString ins("background-image: url(:/cards/card_pngs/");
            ins.append(families.get(i));
            ins.append("_");
            ins.append(QString::number(j));
            ins.append(".png);  background-repeat: none;");
            lCard->setStyleSheet(ins);
            index++;
        }
    }
    srand ( unsigned ( time(0) ) );
    random_shuffle(begin(card_Labels),end(card_Labels));
    reorderZ();
}

void MWindow::deal()
{

}

void MWindow::reorderZ()
{
    for(int i = 0; i < 52; i++){
        QLabel *card = card_Labels[i];
        int index = card->property("cardid").toInt();
        for(int z = 0; z <= index; z++)
            card->raise();
        qDebug() << i << ":" << " cardid: " << index;
    }
}
