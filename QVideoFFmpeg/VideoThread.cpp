#include "VideoThread.h"
Q_DECLARE_METATYPE(QImage)

VideoThread::VideoThread(AVFrameQueue *frame_queue,int frame_to_width, int frame_to_height)
    :video_frame_queue(frame_queue)
{
    InitRunnable(&VideoThread::loopRunnable,this,frame_to_width,frame_to_height,AV_PIX_FMT_RGB32);
}


VideoThread::~VideoThread()
{


}


void VideoThread::loopRunnable(int frame_to_width,int frame_to_height,enum AVPixelFormat frame_to_format)
{
    QImage image(frame_to_width,frame_to_height, QImage::Format_RGB32);

    while (true) {
      //  qDebug() << "frame_to_width:" << frame_to_width << "frame_to_height:" << frame_to_height << "frame_to_format:" <<frame_to_format;
        AVFrame *frame = NULL;
        frame = video_frame_queue->Front();
        if(frame) {
            frame = video_frame_queue->Pop(1);
            if(frameToQImage(image,frame)){
                  av_frame_free(&frame);
                emit valueChanged(image.copy());

            }
        }

    }

}


bool VideoThread::frameToQImage(QImage &image,AVFrame *frame)
{
    uint8_t* frame_to_data[1] = { reinterpret_cast<uint8_t*>(image.bits()) };
    int frame_to_linesize[1] = { static_cast<int>(image.bytesPerLine()) };
    int frame_to_width={ static_cast<int>(image.width()) };
    int frame_to_height= { static_cast<int>(image.height()) };
    int  ret =-1;
    /* create scaling context */
    struct SwsContext * img_convert_ctx = sws_getContext(
                frame->width,
                frame->height,
                static_cast<AVPixelFormat>(frame->format),
                frame_to_width,
                frame_to_height,
                AV_PIX_FMT_RGB32,
                SWS_BILINEAR,
                nullptr,
                nullptr,
                nullptr);

    if (img_convert_ctx==nullptr) {
        qDebug("Impossible to create scale context for the conversion "
               "fmt:%s s:%dx%d -> fmt:%s s:%dx%d\n",
               av_get_pix_fmt_name( static_cast<AVPixelFormat>(frame->format)), frame->width, frame->height,
               av_get_pix_fmt_name(static_cast<AVPixelFormat>(AV_PIX_FMT_RGB32)), frame_to_width, frame_to_height);
        ret = AVERROR(EINVAL);
        return  false;
    }
    /* buffer is going to be written to rawvideo file, no alignment */
    //    if (av_image_alloc(frame_to_data, frame_to_linesize,
    //    frame_to_width, frame_to_height, frame_to_format, 1) < 0) {
    //        qDebug( "Could not allocate destination image\n");
    //        sws_freeContext(img_convert_ctx);
    //        img_convert_ctx=nullptr;
    //        return false;
    //    }

    /* convert to destination format */
    if( sws_scale(img_convert_ctx, (const uint8_t * const*)frame->data,
                  frame->linesize, 0, frame->height, frame_to_data, frame_to_linesize)<0){
        qDebug( ) << "Could not sws_scale destination format\n";
        sws_freeContext(img_convert_ctx);
        img_convert_ctx=nullptr;
        return false;
    }
    sws_freeContext(img_convert_ctx);
    img_convert_ctx=nullptr;
    return true;
}


