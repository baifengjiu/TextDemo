#ifndef PAINTDEMO_H
#define PAINTDEMO_H

#include <QWidget>

class PaintWidget;
class PaintDemo : public QWidget
{
    Q_OBJECT

public:
    explicit PaintDemo(QWidget *parent = 0);
    ~PaintDemo();

    void onRefresh();

private:
    PaintWidget* w;
    int m_length;
};

#endif // PAINTDEMO_H
