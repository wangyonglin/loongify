#ifndef DECODETHREAD_H
#define DECODETHREAD_H
#include <QVideoFFmpeg/ThreadRunnable.h>
#include <QVideoFFmpeg/RunnableBase.h>
#include <QVideoFFmpeg/AVPacketQueue.h>
#include <QVideoFFmpeg/AVFrameQueue.h>
#include <QDebug>

class DecodeThread :  private ThreadRunnable
{
public:
    DecodeThread(AVPacketQueue *packet_queue, AVFrameQueue *frame_queue);
    ~DecodeThread();
    bool InitDecode(AVCodecParameters *par);
    void Start() ;
    void Stop() ;
     void Pause();
     void Resume();
    State State();
     virtual void process() override;
private:
     AVFrame *frame=nullptr;
     bool abort = false;
    char err2str[256] = {0};
    AVCodecContext *codec_ctx_ = NULL;
    AVPacketQueue *packet_queue_ = NULL;
    AVFrameQueue *frame_queue_ = NULL;
};

#endif // DECODETHREAD_H
