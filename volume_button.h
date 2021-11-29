#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include <QPushButton>

class VolumeButton : public QPushButton
{
    Q_OBJECT
public:
    bool muted = false;
    VolumeButton() : QPushButton(0){
        connect(this, SIGNAL(clicked()), this, SLOT(buttonPressed()));
    }

private slots:
    void buttonPressed();
public slots:

signals:
    void sendButtonPressed();
};

#endif // SOUNDBUTTON_H
