//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <QDebug>
#include <stdio.h>
#include <cmath>
using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
    //        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    qDebug() << ms;
    switch (ms) {
    case QMediaPlayer::State::StoppedState:
        play(); // starting playing again...
        break;
    case QMediaPlayer::State::PausedState:
        emit sendPlayState(ms);
        break;
    case QMediaPlayer::State::PlayingState:
        emit sendPlayState(ms);
        break;
    default:
        break;
    }
}

// PRIVATE SLOTS
void ThePlayer::newDuration(){
    duration = metaData("Duration");
    if(duration.toInt() != 0){
        emit updateDuration(duration.toInt());
    }
    //qDebug() << "duration: " << duration;
}

void ThePlayer::changedPosition(){
    int pos = position();
    //qDebug() <<"current player position = " << pos;
    emit sendVideoPosition(pos);
}

// PUBLIC SLOTS
void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    //    QVariant duration = metaData("Duration");
    //    qDebug() << duration;
    play();
}

void ThePlayer::updatePosition(int position){
    //qDebug() << "Updating Position in player" << position;
    setPosition(position*10);
    play();
}

void ThePlayer::receiveSliderPressed(){
    pause();
}

void ThePlayer::receiveVolumeButtonPressed(){
    if(isMuted()==false){
        setMuted(true);
    }
    else{
        setMuted(false);
    }

}

void ThePlayer::receivePlayButtonPressed(bool currentlyPlaying){
    if(state() == PausedState){
        play();
    }
    else{
        pause();
    }
}

void ThePlayer:: receiveVolumeVal(int volume){
    //float convertedVolume = log(volume)/log(100);
//    qDebug() <<"OVKUME"<< convertedVolume * 100;
    setVolume(volume);
}
