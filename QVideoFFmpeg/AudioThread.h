#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include <QAudioFormat>
#include <QAudioOutput>

class AudioThread
{
public:
    AudioThread();
    bool InitAudioThread();
};

#endif // AUDIOTHREAD_H
