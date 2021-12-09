//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QImageReader>
#include <QDebug>


void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    //setIconSize(QSize(1000,1000));
    info =  i;
}

void TheButton::clicked() {
    emit jumpTo(info);
}

std::vector<TheButtonInfo> TheButton::getInfoIn (std::string loc) {
    qDebug() << QString::fromStdString(loc);
    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files
        qDebug() << "File";
        QString f = it.next();

        if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

                QString thumb = f.left( f .length() - 4) +".png";
                if (QFile(thumb).exists()) { // if a png thumbnail exists
                    QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
                }
                else
                    qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
            }
    }

    return out;
}

void TheButton::friendClicked(){
    std::vector<TheButtonInfo> videos;
    //videos = getInfoIn("C:\\Users\\ahojj\\Desktop\\Leeds\\Modules\\2nd year\\User Interfaces\\UI-CW3");
    //init(&videos.at(0));
    setIcon(QIcon(":/friend-modified.png"));
}
