#include "ColorGrid.h"
#include <QToolTip>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QScrollArea>

struct Impl
{
    Impl()
        :interval(8)
        , row(10)
        , col(10)
        , isShowTopCursor(true)
        , isShowLeftCursor(true)
        , hScrollOffset(0)
        , vScrollOffset(0)
    {}

    int row;//行
    int col;//列
    bool isShowTopCursor; //列号
    bool isShowLeftCursor; //行号
    int interval;//间隔
    int hScrollOffset;//偏移量
    int vScrollOffset;//便移量
};

ColorGrid::ColorGrid(QWidget * parent)
    : QWidget(parent)
    , m_row(1024)
    , m_col(1024)
    , m_cellSize(12)
    //, m_canSeeRow(0)
    //, m_canSeeCol(0)
{
    setMouseTracking(true);
}

void ColorGrid::paintEvent(QPaintEvent * event)
{
    int c = m_cellSize;
    int h = m_col * c;
    int w = m_row * c;;
    //获取表格宽高，计算当前视野
    //m_canSeeRow = this->width() / c;
    //m_canSeeCol = this->height() / c;

    QPainter p(this);
    p.setBrush(palette().base());
    p.setPen(palette().shadow().color());
    p.drawRect(0, 0, w + 2, h + 2);

    int x = 1, y = 1;
    for (int j = 0; j < m_row; j++, y += c)
    {
        x = 1;
        for (int i = 0; i < m_col; i++, x += c)
        {
            auto color = Qt::lightGray;
            color = (i + j) % 2 ? Qt::lightGray : Qt::white;
            p.fillRect(QRect(x, y, m_cellSize, m_cellSize), color);
        }
    }
}

void ColorGrid::mouseMoveEvent(QMouseEvent * event)
{
    QPoint pos = event->pos();

    int c = m_cellSize;
    int row = pos.y() / c;
    int col = pos.x() / c;

    QString message = QString("Row:%1\nCol:%2").arg(row).arg(col);
    QToolTip::showText(event->globalPos(), message, this);

    QWidget::mouseMoveEvent(event);
}

void ColorGrid::mousePressEvent(QMouseEvent * event)
{


}

void ColorGrid::wheelEvent(QWheelEvent * event)
{
    QPoint pos = QCursor::pos();

    m_cellSize += event->delta() / 8 / 15;

    repaint();
    QWidget::wheelEvent(event);
}
