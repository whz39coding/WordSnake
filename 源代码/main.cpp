#include "mainsense.h"
#include <QApplication>
#include<QMediaPlayer>
#include<QMediaPlaylist>
int main(int argc, char *argv[])
{
    //加载界面

    //音效实现

    QApplication a(argc, argv);
    QMediaPlayer *player = new QMediaPlayer();
    //添加音乐列表
    QMediaPlaylist *musicList = new QMediaPlaylist;
    //添加音乐列表
    //musicList->addMedia(QMediaContent(QUrl("qrc:/music/background_music.mp3")));
   musicList->addMedia(QMediaContent(QUrl("qrc:/r1/sorce/backMusic.mp3")));
    musicList->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(musicList);
    player->setVolume(30);  //音量
    player->play();
    Mainsense  w;
    w.show();
    return a.exec();
}

