#ifndef COLORGRID_H
#define COLORGRID_H

#include <QWidget>

class  ColorGrid : public QWidget
{
public:
    ColorGrid(QWidget *parent = Q_NULLPTR);

Q_SIGNALS:
    void postionChanged(bool isSelect, QPair<uint16_t, uint16_t> pos);

protected:
    virtual void paintEvent(QPaintEvent * event) override;
    virtual void mouseMoveEvent(QMouseEvent * event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    //virtual void contextMenuEvent(QContextMenuEvent *event) override;


private:
    int m_row;
    int m_col;
    int m_cellSize;
    int m_canSeeRow;
    int m_canSeeCol;
};

#endif // !COLORGRID_H
