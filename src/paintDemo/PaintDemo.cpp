#include "PaintDemo.h"
#include "PaintWidget.h"
#include <QVector>
#include <QString>
#include <QTimer>
#include <QScrollArea>
#include <QLayout>
#include <QToolBar>
#include <QAction>
#include <math.h>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QSizePolicy>

#define ROW 1024
#define COL 1024
#define DIFFERENCE 0

PaintDemo::PaintDemo(QWidget *parent)
    : QWidget(parent)
    , m_length(2)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    QToolBar* bar = new QToolBar(this);
    vlayout->addWidget(bar);

    w = new PaintWidget(this);
    w->setRowAndCol(ROW, COL);
    w->setInterval(5);
    w->refresh();
    w->setMinimumSize(1200, 800);
    vlayout->addWidget(w);

    srand((unsigned)time(0));

    QVector<uchar> data;
    uchar value;
   
    for (int i = 0; i < ROW * COL - DIFFERENCE; i++) {
        value = uchar(rand() % 256);
        data.append(value);
    }
    w->setData(data);

    //刷新
    QAction* dataRefresh = new QAction("Data Refresh", this);
    bar->addAction(dataRefresh);
    QTimer* timer = new QTimer(this);
    dataRefresh->setCheckable(true);
    connect(timer, &QTimer::timeout, this, &PaintDemo::onRefresh);

    connect(dataRefresh, &QAction::toggled, [=](bool checked)
    {
        if (checked)
        {
            timer->start(5);
        }
        else
        {
            timer->stop();
        }

    });

    //选择显示位数
    QAction* bin = new QAction("BIN", this);
    bar->addAction(bin);
    connect(bin, &QAction::triggered, [=]()
    {
        m_length = 8;
        w->setJinzhi(RADIX::BINARY);
    });
    QAction* decimal = new QAction("DECIMAL", this);
    bar->addAction(decimal);
    connect(decimal, &QAction::triggered, [=]()
    {
        m_length = 3;
        w->setJinzhi(RADIX::DECIMAL);
    });
    QAction* hex = new QAction("HEX", this);
    bar->addAction(hex);
    connect(hex, &QAction::triggered, [=]()
    {
        m_length = 2;
        w->setJinzhi(RADIX::HEXADECIMAL);
    });

    //显示隐藏游标 顶部
    QAction* top = new QAction("top", this);
    bar->addAction(top);
    bool topChecked = false;
    connect(top, &QAction::triggered, [=,&topChecked]()
    {
        w->isShowTopCursor(topChecked);
        topChecked = !topChecked;
    });

    //显示隐藏游标 底部
    bool leftChecked = false;
    QAction* left = new QAction("left", this);
    bar->addAction(left);
    connect(left, &QAction::triggered, [=, &leftChecked]()
    {
        w->isShowLeftCursor(leftChecked);
        leftChecked = !leftChecked;
    });

    //设置行列显示数
    QLabel* rowLabel = new QLabel("row:", this);
    bar->addWidget(rowLabel);
    QSpinBox* rowEdit = new QSpinBox(this);
    rowEdit->setMaximumWidth(50);
    rowEdit->setRange(0, 1024);
    rowEdit->setValue(ROW);
    bar->addWidget(rowEdit);

    QLabel* colLabel = new QLabel("col:", this);
    bar->addWidget(colLabel);
    QSpinBox* colEdit = new QSpinBox(this);
    colEdit->setMaximumWidth(50);
    colEdit->setRange(0, 1024);
    colEdit->setValue(COL);
    bar->addWidget(colEdit);

    connect(rowEdit, &QSpinBox::editingFinished, [=]() {
        w->setRow(rowEdit->text().toInt());
    });
    connect(colEdit, &QSpinBox::editingFinished, [=]() {
        w->setCol(colEdit->text().toInt());
    });

    //设置列游标间隔
    QLabel* intervalLabel = new QLabel("top interval:", this);
    bar->addWidget(intervalLabel);
    QSpinBox* intervalEdit = new QSpinBox(this);
    intervalEdit->setMaximumWidth(50);
    intervalEdit->setRange(0, 1024);
    intervalEdit->setValue(5);
    bar->addWidget(intervalEdit);

    connect(intervalEdit, &QSpinBox::editingFinished, [=]() {
        w->setInterval(intervalEdit->text().toInt());
    });


}

PaintDemo::~PaintDemo()
{
}

void PaintDemo::onRefresh()
{
    QVector<uchar> data;
    uchar value;
    data.clear();
   
    for (int i = 0; i < ROW * COL - DIFFERENCE; i++) {
        value = uchar(rand() % 256);
        data.append(value);
    }
    w->setData(data);
}
