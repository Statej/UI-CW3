#ifndef PLAYPAUSE_H
#define PLAYPAUSE_H

#include <QPushButton>
#include <QMediaPlayer>

class PlayPause : public QPushButton
{
    Q_OBJECT
public:
    bool currentlyPlaying = true;
    PlayPause() : QPushButton(0){
        setIconSize(QSize(35,35));
        connect(this, SIGNAL(clicked()), this, SLOT(buttonPressed()));
    }

private slots:
    void buttonPressed();
public slots:
    void receivePlayState(QMediaPlayer::State state);

signals:
    void sendButtonPressed(bool);
};

#endif // PLAYPAUSE_H
