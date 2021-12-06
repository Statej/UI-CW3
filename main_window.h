#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QHBoxLayout>
#include "ui_form.h"
#include "the_button.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(std::vector<TheButtonInfo> &videos);

private:
    bool showingMainWindow = false;
    QHBoxLayout *mainWindowLayout;
    QHBoxLayout *initialWindowLayout;
    QStackedWidget* parentWidget;
private slots:
    void changeLayout();
};

#endif // MAINWINDOW_H
