#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
    void generateLabels();
    QLabel* card_Labels[52];

private:
    Ui::MWindow *ui;

};

#endif // MWINDOW_H
