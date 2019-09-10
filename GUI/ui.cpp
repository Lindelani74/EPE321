#include "ui.h"
#include "ui_ui.h"

UI::UI(QWidget *parent) : QMainWindow(parent), ui(new Ui::UI)
{
    ui->setupUi(this);
    //Create a scene to hold all items
    scene = new QGraphicsScene();

    //Create view to see/display the scene
    view = new QGraphicsView(scene);

    //Set the background of the windows/widget
    view->setBackgroundBrush(QBrush(QImage(":/Backgrounds/Background.jpg")));

    //make window size 800*600
    view->setFixedSize(800,600);
    view->setSceneRect(0,0,800,600);

    //The initial window is to prompt user to select game mode... frame1()
    //startup_frame();
    view->show();
}

UI::~UI()
{
    delete ui;
}
