#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QSlider>

class VolumeSlider : public QSlider
{
    Q_OBJECT
public:
    VolumeSlider() : QSlider(Qt::Horizontal){
        connect(this, SIGNAL(valueChanged(int)), this, SLOT(volumeChanged()));
    }

private slots:
    void volumeChanged();

public slots:

signals:
    void sendVolumeValue(int);
};

#endif // VOLUMESLIDER_H
