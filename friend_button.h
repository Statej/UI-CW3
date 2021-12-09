#ifndef FRIENDBUTTON_H
#define FRIENDBUTTON_H

#include <QObject>
#include <QPushButton>

class FriendButton : public QPushButton
{
    Q_OBJECT
public:
    FriendButton() : QPushButton(){
        connect(this, SIGNAL(released()), this, SLOT(buttonPressed()));
    };

private slots:
    void buttonPressed();
signals:
    void sendFriendButtonPressed();
};

#endif // FRIENDBUTTON_H
