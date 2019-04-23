#include "TextDemo.h"
#include "TextView.h"
#include <QLayout>
#include <QToolBar>
#include <QAction>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <QTimer>

TextDemo::TextDemo(QWidget *parent)
    : QWidget(parent)
    , m_length(2)
{
    m_textView = new TextView(this);
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0,0,0,0);
    QToolBar* bar = new QToolBar(this);
    vlayout->addWidget(bar);
    vlayout->addWidget(m_textView);
    
    m_textView->setRowAndCol(1024 , 1024);
    m_textView->setLength(2);
    QVector<QString> data;
    srand((unsigned)time(0));

    data.clear();
    QString value;
    for (int i = 0; i < 1024 * 128; i++) {
        value = "";
        for (size_t i = 0; i < m_length; i++)
        {
            value += QString("%1").arg(rand() % 10);
        }
        data.append(value);
    }
    m_textView->setData(data);

    //刷新
    QAction* dataRefresh = new QAction("Data Refresh", this);
    bar->addAction(dataRefresh);
    QTimer* timer = new QTimer(this);
    dataRefresh->setCheckable(true);
    connect(timer, &QTimer::timeout, this, &TextDemo::onRefresh);

    connect(dataRefresh, &QAction::toggled, [=](bool checked) 
    {
        if (checked)
        {
            timer->start(1);
        }
        else
        {
            timer->stop();
        }
           
    });

    //选择显示位数
    QAction* bin = new QAction("BIN",this);
    bar->addAction(bin);
    connect(bin, &QAction::triggered, [=]()
    {
        m_length = 8;
        m_textView->setLength(8);
    });
    QAction* decimal = new QAction("DECIMAL", this);
    bar->addAction(decimal);
    connect(decimal, &QAction::triggered, [=]()
    {
        m_length = 3;
        m_textView->setLength(3);
    });
    QAction* hex = new QAction("HEX", this);
    bar->addAction(hex);
    connect(hex, &QAction::triggered, [=]()
    {
        m_length = 2;
        m_textView->setLength(2);
    });
}

void TextDemo::onRefresh()
{
    QVector<QString> data;
    QString value;
    for (int i = 0; i < 1024 * 128; i++) {
        value = "";
        for (size_t i = 0; i < m_length; i++)
        {
            value += QString("%1").arg(rand() % 10);
        }
        data.append(value);
    }

    m_textView->setData(data);
}

