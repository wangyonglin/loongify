#include "MainWidget.h"
#include <VideoWidget.h>
#include <CameraWidget.h>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1080,1920);
    qDebug() << "##################" << width() << ":" << height();
    QVBoxLayout * layout = new QVBoxLayout(this);
    QPushButton * button =  new QPushButton();
    button->setText("Loongify 王永林");

    layout->setContentsMargins(0, 0 , 0, 0);
    VideoWidget * video_widget= new VideoWidget();
    CameraWidget * camera_widget = new CameraWidget();
    video_widget->resize(width(),height());
    camera_widget->resize(width(),height());
    layout->addWidget(button);
    layout->addWidget(video_widget);
    layout->addWidget(camera_widget);
    video_widget->show();
    camera_widget->show();
    setLayout(layout);
}

MainWidget::~MainWidget()
{

}

//bool MainWidget::eventFilter(QObject *obj, QEvent *event)
//{
//    //mouse button pressed
//    if (event->type() == QEvent::MouseButtonPress){
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//        if(mouseEvent->button() == Qt::LeftButton){
//            if(obj ==video_ffmpeg_a){
//                qDebug()<<"在这里写点击事件 video_ffmpeg_a";
//                return true;
//            }else if(obj ==video_ffmpeg_b){
//                qDebug()<<"在这里写点击事件 video_ffmpeg_b";
//                return true;
//            }else{
//                return false;
//            }
//        }else{
//            return false;
//        }
//    }else{
//        return QObject::eventFilter(obj, event);
//    }


//}

