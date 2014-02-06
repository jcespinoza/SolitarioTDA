#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "cardlabel.h"
#include <QDebug>
#include "listPointer.h"

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
    ListP families;
    void deal();
    void reorderZ();

    QLabel* card_Labels[52];

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
