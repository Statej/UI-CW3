#include "friend_button.h"
#include <QDebug>

void FriendButton::buttonPressed(){
    qDebug() << "Not there";
    emit sendFriendButtonPressed();
}
