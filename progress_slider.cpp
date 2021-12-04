#include "progress_slider.h"

void ProgressSlider::progressChanged(){
    emit updatePosition(sliderPosition());
}

void ProgressSlider::assignDuration(int dur){
    duration = dur;
    setRange(0, duration/10);
}
void ProgressSlider::receivePosition(int pos){
    setSliderPosition(pos/10);
}

void ProgressSlider::sliderBeenPressed(){
    emit sendSliderPressed();
}
