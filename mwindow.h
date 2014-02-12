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
    void showCard(QLabel*);
    void hideCard(QLabel*);
    void generateLabels();
    ListPointerT<QString> family_names;
    ListPointerT<QLabel*> foundCups;
    ListPointerT<QLabel*> foundClovs;
    ListPointerT<QLabel*> foundHearts;
    ListPointerT<QLabel*> foundDiams;

    void deal();
    void reorderZ();

    ListPointerT<QLabel*> mainOne;

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
