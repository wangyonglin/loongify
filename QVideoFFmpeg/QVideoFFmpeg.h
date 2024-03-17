#ifndef QVIDEOFFMPEG_H
#define QVIDEOFFMPEG_H
#include <QString>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include <QVideoFFmpeg/DemuxThread.h>
#include <QVideoFFmpeg/DecodeThread.h>
#include <QVideoFFmpeg/VideoThread.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
class QVideoFFmpeg : public QWidget
{
    Q_OBJECT
public:
    QVideoFFmpeg(QWidget *parent = nullptr, int width=1920, int height=1080);
    ~QVideoFFmpeg();
      void InitVideoConfig(const QString & url,bool flag);
    void Play();
    void Stop();
private slots:
    void Pause();
    void openFiles();
private:
    virtual void mousePressEvent(QMouseEvent *event) override;
    QHBoxLayout *mainQHBoxLayout=nullptr;

    QPushButton *openFilesButton=nullptr;
    QPushButton *pauseQPushButton=nullptr;


    virtual void paintEvent(QPaintEvent *event);
    void updateValue(QImage image);
private:
    std::atomic_bool status;
    QImage dstQImageSlot;
    QString dstUrlFilename;
    AVPacketQueue *video_packet_queue=nullptr;
    AVPacketQueue *audio_packet_queue=nullptr;


    AVFrameQueue *video_frame_queue=nullptr;
    AVFrameQueue *audio_frame_queue=nullptr;

    DemuxThread *root_demux_thread=nullptr;
    DecodeThread *audio_decode_thread=nullptr;
    DecodeThread *video_decode_thread=nullptr;

    VideoThread *video_thread = nullptr;
    bool dstImageflag=true;
};

#endif // QVIDEOFFMPEG_H
