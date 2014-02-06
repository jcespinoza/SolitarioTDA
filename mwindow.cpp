#include "mwindow.h"
#include "ui_mwindow.h"

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
}

void MWindow::hideCard(QLabel *label)
{
    label->setProperty("faceup", false);
    QString cs = QString("Prop: ").append(label->property("faceup").toString());
    label->setStyleSheet("background-image: url(:/cards/card_pngs/card_back.png);");
}

void MWindow::generateLabels()
{

    QString names[4] = {"cups", "diam", "treb", "hearts"};
    int index = 0;
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 13; j++){
            QLabel* lCard = new QLabel(this);
            lCard->setProperty("faceup", false);
            lCard->setProperty("cardid", index);
            card_Labels[index] = lCard;
            lCard->setVisible(true);
            lCard->setGeometry(20,20, 135, 201);
            QString ins("background-image: url(:/cards/card_pngs/");
            ins.append(names[i-1]);
            ins.append("_");
            ins.append(QString::number(j));
            ins.append(".png);");
            lCard->setStyleSheet(ins);
            index++;
        }
    }
}
