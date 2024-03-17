#include "CameraWidget.h"
#include <QString>
#include <QVBoxLayout>
#include <QVideoFFmpeg/QVideoFFmpeg.h>
#include <QLabel>

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
    QString str1 = "C:/Users/wangyonglin/Videos/hd(2).mp4";
    QString str2 = "C:/Users/wangyonglin/Videos/hd(1).mp4";

    //创建垂直布局管理器
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->setContentsMargins(0, 0 , 0, 0);
    //设置布局管理器中所有控件从下往上依次排列
    //  layout->setDirection(QBoxLayout::TopToBottom);

    QVideoFFmpeg * video_ffmpeg =new  QVideoFFmpeg(this,width(),height());

    video_ffmpeg->InitVideoConfig(str2,true);
    layout->addWidget(video_ffmpeg);
    video_ffmpeg->show();
    setLayout(layout);
}
