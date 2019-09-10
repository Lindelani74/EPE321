#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class UI;
}

class UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit UI(QWidget *parent = 0);
    ~UI();

private:
    Ui::UI *ui;

    /** \brief Window widget, that will display the GUI elements*/
   QGraphicsScene * scene;

   /** \brief Container Widget to hold all Widgets that will be displayed on the GUI Window*/
   QGraphicsView * view;

   /** \brief Variable to hold the view*/
   QGraphicsRectItem * item;

};

#endif // UI_H
