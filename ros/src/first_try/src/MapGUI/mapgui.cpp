#include "mapgui.h"
#include "ui_mapgui.h"

mapGUI::mapGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapGUI)
{
    ui->setupUi(this);
}

mapGUI::~mapGUI()
{
    delete ui;
}
