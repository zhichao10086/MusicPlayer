#ifndef MULTIMUSICFUNC_H
#define MULTIMUSICFUNC_H

#include <QObject>
#include <string>
#include <QDebug>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavdevice/avdevice.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
}
#endif

using namespace std;

class MultiMusicFunc : public QObject
{
    Q_OBJECT
public:
    explicit MultiMusicFunc(QObject *parent = nullptr);
    enum RetMessage{
        error = -1,
        finish = 0,
    };

    static int musicCut(double start,double end,string inFilename,string outFileName);
signals:

public slots:
};

#endif // MULTIMUSICFUNC_H
