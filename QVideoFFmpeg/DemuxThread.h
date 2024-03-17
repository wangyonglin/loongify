#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H

#include <QVideoFFmpeg/ThreadRunnable.h>
#include <QVideoFFmpeg/RunnableBase.h>
#include <QVideoFFmpeg/ThreadBase.h>
#include <QVideoFFmpeg/AVPacketQueue.h>
#include <QDebug>
#include <QString>
#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}
#endif


class DemuxThread : private ThreadRunnable
{
public:
    DemuxThread(AVPacketQueue *audio_queue, AVPacketQueue *video_queue);
    ~DemuxThread();
    bool InitURL(const QString & url);
    void Start() ;
    void Stop() ;
    void Pause();
    void Resume();
    virtual void process() override;
    AVCodecParameters *AudioCodecParameters();
    AVCodecParameters *VideoCodecParameters();
    AVRational AudioStreamTimebase();
    AVRational VideoStreamTimebase();

private:
    bool ReadFrameFinish();
    char err2str[256] = {0};
    AVPacketQueue *audio_queue_ = NULL;
    AVPacketQueue *video_queue_ = NULL;
    AVFormatContext *ifmt_ctx_ = NULL;
    int audio_index_ = -1;
    int video_index_ = -1;
    bool finish=false;
};

#endif // DEMUXTHREAD_H
