#include "musicplayerview.h"
#include <QApplication>
#include <musicplayercontroller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MusicPlayerController* mpc = MusicPlayerController::newInstance();

    mpc->show();

    return a.exec();
}
