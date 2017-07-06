#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    bool event(QEvent *);

private:
    QLabel *m_label;
};

#endif // WIDGET_H
