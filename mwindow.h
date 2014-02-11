#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "cardlabel.h"
#include <QDebug>
#include "listPointer.h"
#include "listpointert.h"

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
    enum family{CUP, DIAMOND, HEART, CLOVER};
    void generateLabels();
    ListPointerT<QString> family_names;
    void deal();
    void reorderZ();

    ListPointerT<QLabel*> img_labels;

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
