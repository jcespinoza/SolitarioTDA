#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "cardlabel.h"
#include <QDebug>
#include "CardPile.h"

namespace Ui{
class MWindow;
}

class MWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = 0);
    ~MWindow();
    void showCard(CardLabel*);
    void hideCard(CardLabel*);
    void generateLabels();
    ListPointerT<QString> family_names;
    CardPile foundCups;
    CardPile foundClovs;
    CardPile foundHearts;
    CardPile foundDiams;
    CardPile temp_Store;
    CardPile pile1;
    CardPile pile2;
    CardPile pile3;
    CardPile pile4;
    CardPile pile5;
    CardPile pile6;
    CardPile pile7;
    CardPile aero;
    ListPointerT<CardPile> pileArray;

    void initializePiles();
    void deal();
    void reorderZ();

    CardPile mainOne;
public slots:
    void cardPressed(QMouseEvent*, CardLabel*);
    void cardMoved(QMouseEvent*, CardLabel *);
    void cardReleased(QMouseEvent*, CardLabel *);
    void cardDoubleClick(QMouseEvent*, CardLabel*);
    void showHideCard(CardLabel*, bool);

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
