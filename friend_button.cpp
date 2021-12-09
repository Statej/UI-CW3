#include "friend_button.h"

void FriendButton::buttonPressed(){
    emit sendFriendButtonPressed();
}
