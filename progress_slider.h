#ifndef PROGRESSSLIDER_H
#define PROGRESSSLIDER_H

#include <QSlider>

class ProgressSlider  : public QSlider
{
    Q_OBJECT
public:
    int duration = 0;
    ProgressSlider() : QSlider(Qt::Horizontal){
        connect(this, SIGNAL(sliderReleased()), this, SLOT (progressChanged()));
        connect(this, SIGNAL(sliderPressed()), this, SLOT(sliderBeenPressed()));
    }

private slots:
    void progressChanged();
    void sliderBeenPressed();

public slots:
    void assignDuration(int);
    void receivePosition(int);

signals:
    void updatePosition(int);
    void sendSliderPressed();

};

#endif // PROGRESSSLIDER_H
