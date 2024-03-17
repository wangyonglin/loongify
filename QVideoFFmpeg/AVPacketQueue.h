#ifndef AVPACKETQUEUE_H
#define AVPACKETQUEUE_H
#include <QVideoFFmpeg/QueueBase.h>
#include <QDebug>
#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
//#include "libavutil/avutil.h"
//#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}
#endif


class AVPacketQueue
{
public:
    AVPacketQueue();
    ~AVPacketQueue();
    void Abort();

    int Size();
    int Push(AVPacket *val);
    AVPacket *Pop(const int timeout);
private:
    void release();
    QueueBase<AVPacket *> queue_;
};

#endif // AVPACKETQUEUE_H
