#ifndef MAPGUI_H
#define MAPGUI_H

#include <QMainWindow>

namespace Ui {
class mapGUI;
}

class mapGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapGUI(QWidget *parent = 0);
    ~mapGUI();

private:
    Ui::mapGUI *ui;
};

#endif // MAPGUI_H
