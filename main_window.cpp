#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "progress_slider.h"
#include "play_pause.h"
#include "volume_button.h"
#include "volume_slider.h"
#include <QSlider>
#include <QDebug>
#include <QLabel>
#include <QScrollArea>
#include "main_window.h"

void MainWindow::changeLayout(){
    qDebug() << "Here";

    parentWidget->widget(1)->hide();
    parentWidget->widget(0)->show();
    //setLayout(mainWindowLayout);

}

MainWindow::MainWindow(std::vector<TheButtonInfo> &videos){
    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);
    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);



    for ( int i = 0; i < (int)videos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        QWidget *widget = new QWidget();
        QGridLayout *buttonOverlap = new QGridLayout();
        QLabel *durationLabel = new QLabel();
        durationLabel->setText("DURATION");
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        button->setMinimumWidth(150);
        button->setMinimumHeight(150);
        button->setMaximumWidth(150);
        button->setMaximumHeight(150);
        buttonOverlap->addWidget(button, 0 , 0 , Qt::AlignLeft);
        buttonOverlap->addWidget(durationLabel, 0 , 0 , Qt::AlignCenter);
        widget->setLayout(buttonOverlap);
        layout->addWidget(widget);
        button->init(&videos.at(i));

    }
    QWidget *buttonGridWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttonsInGrid;
    // the buttons are arranged horizontally
    QGridLayout *gridButtonLayout = new QGridLayout();
    buttonGridWidget->setLayout(gridButtonLayout);



    for ( int i = 0; i < (int)videos.size()/4; i++ ) {
        for (int j = 0; j < 4; j++){
            TheButton *button = new TheButton(buttonGridWidget);
            QWidget *widget = new QWidget();
            QGridLayout *buttonOverlap = new QGridLayout();
            QLabel *durationLabel = new QLabel();
            durationLabel->setText("DURATION");
            button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
            button->connect(button, SIGNAL(released()), this, SLOT(changeLayout()));
            buttonsInGrid.push_back(button);
            /*
            button->setMinimumWidth(150);
            button->setMinimumHeight(150);
            button->setMaximumWidth(150);
            button->setMaximumHeight(150);
            */
            buttonOverlap->addWidget(button, 0 , 0 , Qt::AlignCenter);
            buttonOverlap->addWidget(durationLabel, 0 , 0 , Qt::AlignCenter);
            widget->setLayout(buttonOverlap);
            gridButtonLayout->addWidget(widget, i , j , 1 ,1);
            button->init(&videos.at(i*4 + j));

        }
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);
    // setup controls panel
    QHBoxLayout* controlsLayout = new QHBoxLayout();
    QHBoxLayout* volumeControlsLayout = new QHBoxLayout();
    QWidget* volumeControlsWidget = new QWidget();
    ProgressSlider* videoProgress = new ProgressSlider();
    QPushButton* playButton = new QPushButton();
    playButton = new PlayPause();
    playButton->setIcon(QIcon(":/volume_off.png"));
    VolumeButton* volumeButton = new VolumeButton();
    VolumeSlider* volumeSlider = new VolumeSlider();
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(videoProgress);
    controlsLayout->addWidget(volumeControlsWidget);
    volumeControlsLayout->addWidget(volumeButton);
    volumeControlsLayout->addWidget(volumeSlider);
    volumeControlsWidget->setLayout(volumeControlsLayout);
    volumeControlsWidget->setMaximumWidth(250);

    // VIDEO PROGRESS SLIDER
    videoProgress->setRange(0, player->duration.toInt());
    //videoProgress->setTickPosition(QSlider::TicksBelow);
    videoProgress->setTickInterval(1);
    videoProgress->setPageStep(1);
    videoProgress->connect(videoProgress, SIGNAL(updatePosition(int)), player, SLOT (updatePosition(int)));
    videoProgress->connect(videoProgress, SIGNAL(sendSliderPressed()), player, SLOT(receiveSliderPressed()));
    player->connect(player, SIGNAL(updateDuration(int)), videoProgress, SLOT(assignDuration(int)));
    player->connect(player, SIGNAL(sendVideoPosition(int)), videoProgress, SLOT(receivePosition(int)));
    player->connect(player, SIGNAL(sendPlayState(QMediaPlayer::State)), playButton, SLOT(receivePlayState(QMediaPlayer::State)));
    volumeSlider->connect(volumeSlider, SIGNAL(sendVolumeValue(int)), player, SLOT(receiveVolumeVal(int)));
    // PLAY PAUSE BUTTON
    playButton->setIcon(QIcon(":/pause.png"));
    playButton->connect(playButton, SIGNAL(sendButtonPressed(bool)), player, SLOT(receivePlayButtonPressed(bool)));

    // VOLUME BUTTON
    volumeButton->setIcon(QIcon(":/volume_on"));
    volumeButton->connect(volumeButton, SIGNAL(sendButtonPressed()), player, SLOT(receiveVolumeButtonPressed()));
    // VOLUME SLIDER
    volumeSlider->setRange(0,100);
    volumeSlider->setSliderPosition(100);

    // create the main window and lay
    initialWindowLayout = new QHBoxLayout();
    mainWindowLayout = new QHBoxLayout();
    QVBoxLayout *vidControlsLayout = new QVBoxLayout();
    vidControlsLayout ->addWidget(videoWidget);
    vidControlsLayout ->addLayout(controlsLayout);
    //window.setLayout(top);
    //setLayout(initialWindowLayout);
    setWindowTitle("tomeo");
    setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget

    //top->addWidget(buttonWidget);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setMinimumHeight(200);
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    scrollArea->setMinimumWidth(200);
    scrollLayout->addWidget(scrollArea);

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(buttonWidget);
    mainWindowLayout->addLayout(vidControlsLayout);
    mainWindowLayout->addLayout(scrollLayout);


    QScrollArea* scrollArea2 = new QScrollArea();
    scrollArea2->setMinimumHeight(200);
    QVBoxLayout *scrollLayout2 = new QVBoxLayout();
    scrollArea2->setMinimumWidth(200);
    scrollLayout2->addWidget(scrollArea2);

    scrollArea2->setWidgetResizable(true);
    scrollArea2->setWidget(buttonGridWidget);

    initialWindowLayout->addLayout(scrollLayout2);

    parentWidget = new QStackedWidget();
    QWidget* initialWindow = new QWidget();
    QWidget* mainWindow = new QWidget();

    initialWindow->setMinimumSize(1670, 900);
    initialWindow->setLayout(initialWindowLayout);
    mainWindow->setLayout(mainWindowLayout);

    parentWidget->addWidget(mainWindow);
    parentWidget->addWidget(initialWindow);

    QVBoxLayout *parentLayout = new QVBoxLayout();
    parentLayout->addWidget(parentWidget);
    setLayout(parentLayout);

    parentWidget->widget(0)->hide();
    parentWidget->widget(1)->show();
    //    widget(2)->show();
}

