#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "cardlabel.h"
#include <QDebug>

namespace Ui {
class MWindow;
}

class MWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = 0);
    ~MWindow();
    void showCard(QLabel*);
    void hideCard(QLabel*);
    enum family{CUP, DIAMOND, HEART, CLOVER};
    void generateLabels();
    void deal();
    void reorderZ();
    QLabel* card_Labels[52];

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
