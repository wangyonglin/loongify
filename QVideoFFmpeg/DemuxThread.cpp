#include "DemuxThread.h"

DemuxThread::DemuxThread(AVPacketQueue *audio_queue, AVPacketQueue *video_queue)
    :audio_queue_(audio_queue), video_queue_(video_queue)
{


}

DemuxThread::~DemuxThread()
{


}

bool DemuxThread::InitURL(const QString & url)
{
    int ret = 0;
   // ifmt_ctx_ = avformat_alloc_context();
    ret = avformat_open_input(&ifmt_ctx_, url.toStdString().data(), NULL, NULL);
    if(ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        qDebug() << "avformat_open_input failed" <<  err2str;
        return false;
    }

    ret = avformat_find_stream_info(ifmt_ctx_, NULL);
    if(ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        qDebug() << "avformat_find_stream_info failed" << err2str;
        return false;
    }
    av_dump_format(ifmt_ctx_, 0, url.toStdString().data(), 0);

    audio_index_ = av_find_best_stream(ifmt_ctx_, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    video_index_ = av_find_best_stream(ifmt_ctx_, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
   // qInfo() << "audio_index_:" << audio_index_ << "video_index_:" << video_index_ ;
    if(audio_index_ < 0 || video_index_ < 0) {
        qDebug() << "no audio or no video";
        return false;
    }

  //  qInfo() << ("Init leave");
    return true;
}

void DemuxThread::Start()
{
    start();
}

void DemuxThread::Stop()
{
    stop();
    avformat_close_input(&ifmt_ctx_);
}

void DemuxThread::Pause()
{
    pause();
}

void DemuxThread::Resume()
{
    resume();
}

void DemuxThread::process()
{
   // qInfo() << ("DemuxThread process in");
    if(ifmt_ctx_==nullptr)return;
    int ret = 0;
    AVPacket pkt;

    while (state()==Running) {

        if(audio_queue_->Size() > 100 || video_queue_->Size() > 100) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        ret = av_read_frame(ifmt_ctx_, &pkt);
        if(ret < 0) {
            av_strerror(ret, err2str, sizeof(err2str));
            qDebug() << "av_read_frame failed"  << err2str;
            pause();
            break;
        }
        if(pkt.stream_index == audio_index_) {
            ret = audio_queue_->Push(&pkt);
            av_packet_unref(&pkt);
            qInfo() << "audio pkt queue size:" << audio_queue_->Size();
        } else if(pkt.stream_index == video_index_) {
            ret = video_queue_->Push(&pkt);
            av_packet_unref(&pkt);
            qInfo() << "video pkt queue size:"<< video_queue_->Size();
        } else {
            av_packet_unref(&pkt);
        }
    }
   // qInfo() << ("DemuxThread process finish");
}



AVCodecParameters *DemuxThread::AudioCodecParameters()
{
    if(audio_index_ != -1) {
        return ifmt_ctx_->streams[audio_index_]->codecpar;
    } else {
        return NULL;
    }
}

AVCodecParameters *DemuxThread::VideoCodecParameters()
{
    if(video_index_ != -1) {
        return ifmt_ctx_->streams[video_index_]->codecpar;
    } else {
        return NULL;
    }
}

AVRational DemuxThread::AudioStreamTimebase()
{
    if(audio_index_ != -1) {
        return ifmt_ctx_->streams[audio_index_]->time_base;
    } else {
        return AVRational{0, 0};
    }
}

AVRational DemuxThread::VideoStreamTimebase()
{
    if(video_index_ != -1) {
        return ifmt_ctx_->streams[video_index_]->time_base;
    } else {
        return AVRational{0, 0};
    }
}

bool DemuxThread::ReadFrameFinish()
{
     avformat_close_input(&ifmt_ctx_);
}

