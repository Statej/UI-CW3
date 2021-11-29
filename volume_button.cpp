#include "volume_button.h"

void VolumeButton::buttonPressed(){
    if(muted){
        muted = false;
        setIcon(QIcon(":/volume_on"));
    }
    else{
        muted = true;
        setIcon(QIcon(":/volume_off"));
    }
    emit sendButtonPressed();
}
