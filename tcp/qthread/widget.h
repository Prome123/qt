#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QThread>
#include <QTimer>

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject *parent = 0);
    ~Worker();

signals:
    void progressChanged(int progress);


protected slots:
    void onTimeOut();

public:
    QTimer m_timer;
    int m_progress;
};

class DownloadThread : public QThread
{
public:
    DownloadThread(QObject *receiver, QObject *parent = 0);
    ~DownloadThread();

    void run();

protected:
    QObject *m_receiver;
};

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
protected:
    QProgressBar *m_progress;

};

#endif // WIDGET_H
