#include "PaintWidget.h"
#include <QLayout>
#include <QScrollArea>
#include <QPainter>
#include <QScrollBar>

struct Imp
{
    Imp()
        :interval(8)
        , length(8)
        , row(10)
        , col(10)
        , isShowTopCursor(true)
        , isShowLeftCursor(true)
        , hScrollOffset(0)
        , vScrollOffset(0)
        , radix(RADIX::BINARY)
    {
    }

    int row;//行
    int col;//列
    bool isShowTopCursor; //列号
    bool isShowLeftCursor; //行号
    int length; //每个字符串长度
    RADIX radix;//进制
    int interval;//间隔
    int hScrollOffset;//偏移量
    int vScrollOffset;//便移量
    QVector<uchar> data; //数据
};

/*
    class PaintWidget
*/
PaintWidget::PaintWidget(QWidget * parent)
    : QAbstractScrollArea(parent)
    , impPtr(new Imp)
{
    this->setContentsMargins(0, 0, 0, 0);
    this->setFont(QFont("Consolas", 12, 0));

    m_topCursor = new TopCursor(impPtr,this);
    m_leftCursor = new LeftCursor(impPtr,this);
    
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &PaintWidget::onHScrollBarChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &PaintWidget::onVScrollBarChanged); 
}

PaintWidget::~PaintWidget()
{
    if (impPtr != nullptr)
    {
        delete impPtr;
        impPtr = nullptr;
    }
}

void PaintWidget::setRowAndCol(int row, int col)
{
    impPtr->row = row;
    impPtr->col = col;
    m_topCursor->repaint();
    m_leftCursor->repaint();
    viewport()->repaint();
    setHScollValue();
    setVScollValue();
}

void PaintWidget::setRow(int row)
{
    impPtr->row = row;
    m_leftCursor->repaint();
    viewport()->repaint();
    setVScollValue();
}

void PaintWidget::setCol(int col)
{
    impPtr->col = col;
    m_topCursor->repaint();
    viewport()->repaint();
    setHScollValue();
}

void PaintWidget::isShowTopCursor(bool isShow)
{
    impPtr->isShowTopCursor = isShow;
    if (impPtr->isShowTopCursor)
    {
        m_topCursor->show();
    }
    else
    {
        m_topCursor->hide();
    }
}

void PaintWidget::isShowLeftCursor(bool isShow)
{
    impPtr->isShowLeftCursor = isShow;
    if (impPtr->isShowLeftCursor)
    {
        m_leftCursor->show();
    }
    else
    {
        m_leftCursor->hide();
    }
}

void PaintWidget::setJinzhi(RADIX radix)
{
    impPtr->radix =radix;
    switch (radix) {
    case RADIX::HEXADECIMAL:
        impPtr->length = 2;
        break;
    case RADIX::DECIMAL:
        impPtr->length = 3;
        break;
    case RADIX::OCTAL:
        impPtr->length = 3;
        break;
    case RADIX::BINARY:
        impPtr->length = 8;
        break;
    }
    m_topCursor->repaint();
    setHScollValue();
}

void PaintWidget::setInterval(int interval)
{
    impPtr->interval = interval;
    m_topCursor->repaint();
}

void PaintWidget::setData(QVector<uchar>& data)
{
    impPtr->data.clear();
    impPtr->data = data;
    viewport()->repaint();
}

void PaintWidget::refresh()
{
    m_leftCursor->update();
    m_topCursor->update();
    setHScollValue();
    setVScollValue();
}

void PaintWidget::resizeEvent(QResizeEvent * e)
{
    QWidget::resizeEvent(e);
    int x = impPtr->row, n = 0;
    for (n = 0; x > 0; n++)
    {
        x /= 10;
    }

    setViewportMargins(fontMetrics().width(QString::number(impPtr->row)) + 2, fontMetrics().height() + 6, 0, 0);

    QRect cr = contentsRect();
    m_leftCursor->setGeometry(QRect(
        cr.left(),
        cr.top() + fontMetrics().height() + 6,
        fontMetrics().width(QString::number(impPtr->row)) + 5,
        cr.height() - fontMetrics().height() - 6
    ));
    m_topCursor->setGeometry(QRect(
        cr.left() + fontMetrics().width(QString::number(impPtr->row)) + 5,
        cr.top(),
        cr.width() - fontMetrics().width(QString::number(impPtr->row)) - 5,
        fontMetrics().height() + 6
    ));

    setHScollValue();
    setVScollValue();
}

void PaintWidget::setHScollValue()
{
    int fontWidth = fontMetrics().width("0");
    int width = impPtr->col*fontWidth*impPtr->length + (impPtr->col-1)*fontWidth;
    horizontalScrollBar()->setValue(impPtr->hScrollOffset);
    horizontalScrollBar()->setRange(0, width - viewport()->rect().width());
    horizontalScrollBar()->setPageStep(viewport()->rect().width());
}

void PaintWidget::setVScollValue()
{
    int fontHight = fontMetrics().height();
    int height = impPtr->row*fontHight;
    verticalScrollBar()->setValue(impPtr->vScrollOffset);
    verticalScrollBar()->setRange(0, height - viewport()->rect().height());
    verticalScrollBar()->setPageStep(viewport()->rect().height());
}

void PaintWidget::onHScrollBarChanged(int value)
{
    impPtr->hScrollOffset = value;
    update();
}

void PaintWidget::onVScrollBarChanged(int value)
{
    impPtr->vScrollOffset = value;
    update();
}
void PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int fontWidth = fontMetrics().width("0");
    int fontHight = fontMetrics().height();

    painter.setPen(QPen(QColor(0, 0, 0)));
    int xoffset = horizontalScrollBar()->value();
    int yoffset = verticalScrollBar()->value();

    QString str;
    QString qStr = QString("%1").arg('-', impPtr->length, QLatin1Char('-'));

    //y轴
    int index = 0;
    for (int i = 0; i < impPtr->row; i++) {//行
        for (int j = 0; j < impPtr->col; j++) {//列
            int x = j * (fontWidth*impPtr->length + fontWidth) - xoffset;
            int y = i * fontHight - yoffset;
            //局部刷新，显示部分刷新
            if (x >= -(fontWidth * impPtr->length) && x < viewport()->width()&& 
                y >= -(fontHight) && y < viewport()->height()) {
                if (index >= impPtr->data.size())
                {
                    painter.drawText(
                        x,
                        y, 
                        fontWidth*impPtr->length,
                        fontHight,
                        Qt::AlignCenter,
                        qStr
                    );
                }
                else
                {
                    //int ch = impPtr->data[index];
                    //str = QString("%1").arg(ch, impPtr->length, impPtr->radix, QLatin1Char('0'));

                    uchar ch = impPtr->data[index];
                    switch (impPtr->radix) {
                    case RADIX::HEXADECIMAL:
                        toHex(ch, str);
                        break;
                    case RADIX::DECIMAL:
                        toDec(ch, str);
                        break;
                    case RADIX::OCTAL:
                        toOct(ch, str);
                        break;
                    case RADIX::BINARY:
                        toBin(ch, str);
                        break;                        
                    }
                    painter.drawText(
                        x,
                        y,
                        fontWidth*impPtr->length,
                        fontHight,
                        Qt::AlignCenter,
                        str
                    );
                }
            }
            ++index;
        }
    }
}

/*
    class LeftCursor
*/
LeftCursor::LeftCursor(struct Imp* impPtr, QWidget * parent)
    : QWidget(parent)
    , impPtr(impPtr)
{
    this->setFont(QFont("Consolas", 12, 0));
}

void LeftCursor::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(QPen(QColor(0, 160, 230)));

    int fontWidth = fontMetrics().width("0");
    int fontHight = fontMetrics().height();

    //y轴
    int index = 0;
    for (int i = 0; i < impPtr->row; i++) {//行
        QString number = QString::number(i);
        painter.drawText(
            0,
            i*fontHight - impPtr->vScrollOffset,
            fontMetrics().width(QString::number(impPtr->row)),
            fontHight, 
            Qt::AlignRight,
            QString().number(i+1)
        );
    }
    int x = fontMetrics().width(QString::number(impPtr->row)) + 2;
    painter.drawLine(x, 0, x, rect().height());
}

/*
    class TopCursor
*/
TopCursor::TopCursor(struct Imp* impPtr, QWidget * parent)
    : QWidget(parent)
    , impPtr(impPtr)
{
    this->setFont(QFont("Consolas", 12, 0));
}

void TopCursor::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(QPen(QColor(0, 160, 230)));

    int fontWidth = fontMetrics().width("0");
    int fontHight = fontMetrics().height();
    //x轴
    for (int i = 0; i < impPtr->col; i += impPtr->interval) {
        QString number = QString::number(i);
        int lineX = i * (fontWidth*impPtr->length + fontWidth) + fontWidth * impPtr->length / 2- impPtr->hScrollOffset;
        painter.drawText(
            lineX-((fontMetrics().width(number))/2),
            0,
            fontMetrics().width(number),
            fontHight, 
            Qt::AlignCenter,
            QString().number(i)
        );
        painter.drawLine(lineX, fontHight + 1, lineX, fontHight + 6);
    }
    painter.drawLine(
        0,
        fontHight,
        rect().width(),
        fontHight
    );
}
