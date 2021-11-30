#include "play_pause.h"
#include <QMediaPlayer>

void PlayPause::buttonPressed(){
    if(currentlyPlaying){
        currentlyPlaying = false;
    }
    else {
        currentlyPlaying = true;
    }
    emit sendButtonPressed(currentlyPlaying);
}

void PlayPause::receivePlayState(QMediaPlayer::State state){
    qDebug() << "state " <<state;
    if(state == QMediaPlayer::PausedState){
        setIcon(QIcon(":/play.png"));
    }
    else {
        setIcon(QIcon(":/pause.png"));
    }
}