#include "musiccutthread.h"

MusicCutThread::MusicCutThread(double start, double end, QString inFilename, QString outFilename)
{
    this->_start = start;
    this->_end = end;
    this->_inFilename = inFilename;
    this->_outputFilename = outFilename;
}

MusicCutThread::~MusicCutThread()
{

}

void MusicCutThread::run()
{
    int ret = MultiMusicFunc::musicCut(this->_start,this->_end,this->_inFilename.toStdString(),this->_outputFilename.toStdString());

    emit finish(ret);
}
