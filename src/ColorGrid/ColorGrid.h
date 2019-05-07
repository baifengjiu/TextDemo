#ifndef COLORGRID_H
#define COLORGRID_H

#include "colorgrid_global.h"
#include <QWidget>

class COLORGRID_EXPORT ColorGrid : public QWidget
{
public:
    ColorGrid(QWidget *parent = Q_NULLPTR);

protected:
    virtual void paintEvent(QPaintEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    //virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    int m_row;
    int m_col; 
    int m_cellSize;
    int m_canSeeRow;
    int m_canSeeCol;
};

#endif // !COLORGRID_H