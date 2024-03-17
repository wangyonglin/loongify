#include "DecodeThread.h"

DecodeThread::DecodeThread(AVPacketQueue *packet_queue, AVFrameQueue *frame_queue)
    :packet_queue_(packet_queue), frame_queue_(frame_queue)
{

}

DecodeThread::~DecodeThread()
{
    if(codec_ctx_)
        avcodec_close(codec_ctx_);
}

bool DecodeThread::InitDecode(AVCodecParameters *par)
{
    if(!par) {
        qDebug() << ("Init par is null");
        return false;
    }
    if(codec_ctx_==nullptr)
    codec_ctx_ = avcodec_alloc_context3(NULL);

    int ret = avcodec_parameters_to_context(codec_ctx_, par);
    if(ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        qDebug() << "avcodec_parameters_to_context failed" << err2str;
        return false;
    }
    // h264
    // h264_qsv  AV_CODEC_ID_H264
//    avcodec_find_decoder_by_name()
    AVCodec *codec=nullptr;
//    if(AV_CODEC_ID_H264 == codec_ctx_->codec_id)
//        codec = avcodec_find_decoder_by_name("h264_qsv");
//    else
        codec = avcodec_find_decoder(codec_ctx_->codec_id); //作业： 硬件解码
    if(!codec) {
        qDebug() << "avcodec_find_decoder failed";
        return false;
    }

    ret = avcodec_open2(codec_ctx_, codec, NULL);
    if(ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        qDebug() << "avcodec_open2 failed" << err2str;
        return false;
    }
  //  qInfo() << ("Init finish");
    return true;
}

void DecodeThread::Start()
{
   start();

}

void DecodeThread::Stop()
{
    stop();
}

void DecodeThread::Pause()
{
    pause();
}

void DecodeThread::Resume()
{
    resume();
}

ThreadRunnable::State DecodeThread::State()
{
    return  state();
}


void DecodeThread::process()
{

    if(frame==nullptr){
        frame = av_frame_alloc();
    }
     if(codec_ctx_==nullptr)return;
    while (state()) {

        //        if(frame_queue_->Size() > 10) {
        //            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //            continue;
        //        }


        AVPacket *pkt = packet_queue_->Pop(10);
        if(pkt) {
            int ret = avcodec_send_packet(codec_ctx_, pkt);
            av_packet_free(&pkt);
            //            qInfo() << ("ret = %d", ret);
            if(ret < 0) {
                av_strerror(ret, err2str, sizeof(err2str));
                qDebug() << "avcodec_send_packet failed" << err2str;
                break;
            }
            // 读取解码后的frame
            while (!abort) {
                ret = avcodec_receive_frame(codec_ctx_, frame);
                if(ret == 0) {
                    frame_queue_->Push(frame);
                    //  qInfo() << codec_ctx_->codec->name << " frame queue size " << frame_queue_->Size();
                    continue;
                } else if(AVERROR(EAGAIN) == ret) {
                    break;
                } else {
                    abort = true;
                    av_strerror(ret, err2str, sizeof(err2str));
                    qDebug() << "avcodec_receive_frame failed" << err2str;
                    break;
                }
            }
        }/* else {
//            qInfo() << ("not got packet");
        }*/

    }
    // qInfo() << ("DecodeThread::Run Finish");
    if(frame)
        av_free(frame);
}
