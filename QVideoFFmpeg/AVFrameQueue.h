#ifndef AVFRAMEQUEUE_H
#define AVFRAMEQUEUE_H

#include <QDebug>
#include <QVideoFFmpeg/QueueBase.h>

#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
//#include "libavutil/avutil.h"
//#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}
#endif
class AVFrameQueue
{
public:
    AVFrameQueue();
    ~AVFrameQueue();
    void Abort();
    int Push(AVFrame *val);
    AVFrame *Pop(const int timeout);
    AVFrame *Front();
    int Size();
private:
    void release();
    QueueBase<AVFrame *> queue_;
};
#endif // AVFRAMEQUEUE_H
