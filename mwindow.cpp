#include "mwindow.h"
#include "ui_mwindow.h"
#include <algorithm>
#include <ctime>

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    generateLabels();
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

    QString names[4] = {"cups", "diam", "heart", "clov"};
    int index = 0;
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 13; j++){
            QLabel* lCard = new CardLabel(this);
            lCard->setProperty("faceup", false);
            lCard->setProperty("cardid", index);
            card_Labels[index] = lCard;
            //lCard->setGeometry(20+2*index,20+2*index, 135, 201);
            lCard->setGeometry(20,20, 135, 201);
            //hideCard(lCard);
            QString ins("background-image: url(:/cards/card_pngs/");
            ins.append(names[i-1]);
            ins.append("_");
            ins.append(QString::number(j));
            ins.append(".png);  background-repeat: none;");
            lCard->setStyleSheet(ins);
            index++;
        }
    }
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(std::begin(card_Labels), std::end(card_Labels));
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
