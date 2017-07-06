#include "widget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_progress = new QProgressBar; /*创建一个进度条对象*/
    layout->addWidget(m_progress, 0, Qt::AlignCenter); /*进度条居中对齐*/
    qDebug() << tr("Widget::Widget");
    DownloadThread *t = new DownloadThread(m_progress); /*创建一个自定义线程对象*/
    qDebug() << tr("t->start");
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater())); /*连接信号finished和槽deleteLater,在完成后,删除对象*/
    t->start(); /*启动线程*/
    qDebug() << tr("quit widget constractor");
}

Widget::~Widget()
{

}


DownloadThread::DownloadThread(QObject *receiver, QObject *parent)
    :QThread(parent), m_receiver(receiver)
{
}

DownloadThread::~DownloadThread()
{
    qDebug() << "DownloadThread::~DownloadThread";
}

void DownloadThread::run()
{
    Worker *worker = new Worker;
    qDebug() << tr("DownloadThread::run");
    connect(worker, SIGNAL(progressChanged(int)),
            m_receiver, SLOT(setValue(int)));
    exec();
}


Worker::Worker(QObject *parent)
{
    connect(&m_timer, SIGNAL(timeout()),
            this, SLOT(onTimeOut()));
    m_timer.start(100);
}

Worker::~Worker()
{
    qDebug() << "Worker::~Worker";
}

void Worker::onTimeOut()
{
    if (m_progress < 100) {
        m_progress++;
        qDebug() << tr("m_progress=%1").arg(m_progress);
        emit progressChanged(m_progress);
    } else {
        m_timer.stop();
        qDebug() << tr("m_timer stop");
        QThread::currentThread()->quit();
        delete this;
    }
}
