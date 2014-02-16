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
    CardPile* piles;

    void initializePiles();
    void deal();
    void mouseDoubleClickEvent(QMouseEvent*);
    CardPile mainOne;
public slots:
    void cardDragged(QMouseEvent*, CardLabel*);
    void cardMoved(QMouseEvent*, CardLabel *);
    void cardReleased(QMouseEvent*, CardLabel *);
    void cardDoubleClick(QMouseEvent*, CardLabel*);
    void showHideCard(CardLabel*, bool);
    void transferCards(CardPile &to, NodeT<CardLabel*>* first , bool showPrevious);
    void resetMain();
    int getDistance(QPoint, QPoint);
    bool moveIsValid(CardLabel*, int);

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
