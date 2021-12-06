//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include "progress_slider.h"
#include <vector>
#include <QTimer>

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;

public:
    QVariant duration = 0;

    ThePlayer() : QMediaPlayer(NULL) {
        setNotifyInterval(10);
        setVolume(100); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        mTimer->start();
        //connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
        connect(this, SIGNAL(durationChanged(qint64)), this, SLOT(newDuration()));
        connect(this, SIGNAL(positionChanged(qint64)), this, SLOT (changedPosition()));
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

private:
    bool initialising = true;

private slots:

    // change the image and video for one button every one second
    void shuffle();

    void playStateChanged (QMediaPlayer::State ms);

    void newDuration();

    void changedPosition();


public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    //update video position from slider
    void updatePosition(int position);

    void receiveSliderPressed();
    void receivePlayButtonPressed();
    void receiveVolumeButtonPressed();
    void receiveVolumeVal(int);
signals:
    void updateDuration(int);
    void sendVideoPosition(int);
    void sendPlayState(QMediaPlayer::State);
};

#endif //CW2_THE_PLAYER_H
