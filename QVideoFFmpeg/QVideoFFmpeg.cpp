#include "QVideoFFmpeg.h"
#include <QMessageBox>


QVideoFFmpeg::QVideoFFmpeg(QWidget *parent, int width, int height)
    : QWidget(parent)
{
    resize(width,height);
    audio_packet_queue= new AVPacketQueue();
    video_packet_queue= new AVPacketQueue();

    audio_frame_queue= new AVFrameQueue();
    video_frame_queue= new AVFrameQueue();
    root_demux_thread= new DemuxThread(audio_packet_queue,video_packet_queue);

    audio_decode_thread=new DecodeThread(audio_packet_queue, audio_frame_queue);
    video_decode_thread=new DecodeThread(video_packet_queue, video_frame_queue);
    video_thread= new VideoThread(video_frame_queue,width,height);
//    mainQHBoxLayout = new QHBoxLayout;//水平布局
//    mainQHBoxLayout->setAlignment(Qt::AlignHCenter);
//    mainQHBoxLayout->addStretch();//添加伸缩
//    mainQHBoxLayout->setMargin(0);//设置外边距

//    openFilesButton=new QPushButton("",this);

//    mainQHBoxLayout->addWidget(openFilesButton);//靠下和左

//    openFilesButton->setIcon(QIcon(":images/icon_kjiaii37s5c/wenjian.png"));
//    openFilesButton->setIconSize(QSize(256,256));
//    openFilesButton->setStyleSheet("QPushButton {"
//                                    "background-color: green;" // 按钮背景色
//                                    "font: bold 20px;"	// 按钮字体
//                                    "border-width: 1px;"	// 按钮边框线宽
//                                    "border-radius: 40px;" // 按钮边框圆角半径
//                                    "color: white;"      // 按钮文字颜色
//                                    "}");
//    openFilesButton->show();
//mainQHBoxLayout->addStretch();//添加伸缩
//    pauseQPushButton=new QPushButton("",this);
//    mainQHBoxLayout->addWidget(pauseQPushButton);//靠下和左
//    pauseQPushButton->setIcon(QIcon(":images/icon_kjiaii37s5c/wenjian.png"));
//    pauseQPushButton->setIconSize(QSize(256,256));
//    pauseQPushButton->setStyleSheet("QPushButton {"
//                                    "background-color: green;" // 按钮背景色
//                                    "font: bold 20px;"	// 按钮字体
//                                    "border-width: 1px;"	// 按钮边框线宽
//                                    "border-radius: 40px;" // 按钮边框圆角半径
//                                    "color: white;"      // 按钮文字颜色
//                                    "}");



//   pauseQPushButton->hide();

//    //mainQHBoxLayout->addSpacing(10);//设置离右边框的距离
//    setLayout(mainQHBoxLayout);

//    connect(openFilesButton,SIGNAL(clicked(bool)),this,SLOT(openFiles()));
//    connect(pauseQPushButton,SIGNAL(clicked(bool)),this,SLOT(Pause()));

}

QVideoFFmpeg::~QVideoFFmpeg()
{

  //  delete pauseQPushButton;
   // delete mainQHBoxLayout;
    delete audio_packet_queue;
    delete video_packet_queue;
    delete audio_frame_queue;
    delete video_frame_queue;
}

void QVideoFFmpeg::InitVideoConfig(const QString & url, bool flag)
{

    dstImageflag=flag;

    root_demux_thread->InitURL(url);
    root_demux_thread->Start();


    audio_decode_thread->InitDecode(root_demux_thread->AudioCodecParameters());
    audio_decode_thread->Start();


    video_decode_thread->InitDecode(root_demux_thread->VideoCodecParameters());
    video_decode_thread->Start();


     connect(video_thread, &VideoThread::valueChanged, this, &QVideoFFmpeg::updateValue, Qt::BlockingQueuedConnection);
}

void QVideoFFmpeg::Play()
{

    root_demux_thread->Start();

    audio_decode_thread->Start();

    video_decode_thread->Start();

}

void QVideoFFmpeg::Stop()
{
    root_demux_thread->Stop();
    audio_decode_thread->Stop();

    video_decode_thread->Stop();
}

void QVideoFFmpeg::Pause()
{
   // pauseQPushButton->setIcon(QIcon(":images/icon_kjiaii37s5c/zanting.png"));
    // QMessageBox::information(NULL, "DoubleClick", "double click", QMessageBox::Yes);
   // root_demux_thread->PauseDemux();
    audio_decode_thread->Pause();
    video_decode_thread->Pause();
}

void QVideoFFmpeg::openFiles()
{
 //   openFilesButton->hide();
   //  audio_decode_thread->PauseDecodeThread();
  //   video_decode_thread->PauseDecodeThread();
}

void QVideoFFmpeg::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下
      if(event->button() == Qt::LeftButton)
      {
           // qDebug()<<"################################";
           //  QMessageBox::information(NULL, "DoubleClick", "double click", QMessageBox::Yes);
        if((audio_decode_thread->State()==ThreadRunnable::Running)&&(video_decode_thread->State()==ThreadRunnable::Running) ){
            root_demux_thread->Pause();
            audio_decode_thread->Pause();
            video_decode_thread->Pause();
       }else if((audio_decode_thread->State()==ThreadRunnable::Paused)&&(video_decode_thread->State()==ThreadRunnable::Paused) ){
              root_demux_thread->Resume();
            audio_decode_thread->Resume();
            video_decode_thread->Resume();
       }
      }else if(event->button() == Qt::RightButton)
       {
          // 如果是鼠标右键按下
            //qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
       }
        event->accept();

}


void QVideoFFmpeg::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    /* 实例化画家对象 this指定的是绘图设备 */
            QPainter painter(this);

//            /* 设置画笔 */
//            QPen pen(QColor(255, 0, 0));
//            pen.setWidth(2);
//            pen.setStyle(Qt::DotLine); //设置画笔风格
//            painter.setPen(pen); //让画家使用这个笔

//            /* 设置画刷 */
//            QBrush brush(Qt::green);
//            brush.setStyle(Qt::Dense2Pattern); //设置画刷风格
//            painter.setBrush(brush); //让画家使用画刷

//            /* 画线 */
//            painter.drawLine(QPoint(0, 0), QPoint(100, 100));
//            /* 画圆 */
//            painter.drawEllipse(QPoint(100, 100), 50, 50);
//            /* 画矩形 */
//            painter.drawRect(QRect(150, 150, 50, 50));
//            /* 画文字 */
//            painter.drawText(QPoint(0, 250), "hello furong");


    if(!dstImageflag){

         //QImage image(dstImageData[0], dstImageWidth, dstImageHeight, QImage::Format_RGBA8888);

             painter.drawImage(rect(), dstQImageSlot);
    }else{
         //QImage image(dstImageData[0], dstImageWidth, dstImageHeight, QImage::Format_RGB888);
             painter.drawImage(rect(), dstQImageSlot);
    }
   //  painter.drawPixmap(rect(),QPixmap(":images/icon_kjiaii37s5c/zanting.png"));
}



void QVideoFFmpeg::updateValue(QImage image)
{
     dstQImageSlot =image;
    update();
}




