#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H
#include <QWidget>
#include <QVideoFFmpeg/RunnableBase.h>
#include <QVideoFFmpeg/AVFrameQueue.h>
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libavutil/time.h>
#include <libswresample/swresample.h>
}
#include <QDebug>
#include <QImage>

class VideoThread :public QWidget,RunnableBase
{
    Q_OBJECT
public:
    VideoThread(AVFrameQueue * frame_queue,int frame_to_width, int frame_to_height);
    ~VideoThread();

    void loopRunnable(
    int frame_to_width,
    int frame_to_height,
    enum AVPixelFormat frame_to_format);

signals:
    void valueChanged(QImage image);

private:
    QImage convertToQImage(const AVFrame *frame);
    bool frameToQImage(QImage &image,AVFrame *frame);
    AVFrameQueue * video_frame_queue=nullptr;
private:
    AVFrame *dst_frame;

};

#endif // VIDEOTHREAD_H
