#include "volume_slider.h"

void VolumeSlider:: volumeChanged(){
    emit sendVolumeValue(value());
}
