#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "ui_form.h"
#include "the_button.h"
class MainWindow : public QWidget
{
public:
    MainWindow(std::vector<TheButtonInfo> videos);

};

#endif // MAINWINDOW_H
