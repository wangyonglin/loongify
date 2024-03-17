#include "AudioThread.h"

AudioThread::AudioThread()
{

}

bool AudioThread::InitAudioThread()
{
    QAudioFormat fmt;
        fmt.setSampleRate(44100);//样本率
        fmt.setSampleSize(16);  //样本大小 S16
        fmt.setChannelCount(2); //双通道
        fmt.setCodec("audio/pcm"); //设置pcm编码器
        fmt.setByteOrder(QAudioFormat::LittleEndian);//这是字节序
        fmt.setSampleType(QAudioFormat::UnSignedInt);//设置样本类型
        QAudioOutput *out = new QAudioOutput(fmt);//创建QAudioOutput
        QIODevice *io = out->start(); //开始播放

}
