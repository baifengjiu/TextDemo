#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QAbstractScrollArea>

class QPaintEvent;
class QResizeEvent;
class PaintWidget;
class PaintView;

enum RADIX
{
    BINARY=2,
    OCTAL=8,
    DECIMAL=10,
    HEXADECIMAL=16
};

/****************************************
* @brif	TopCursor 顶部游标（列号）
****************************************/
class TopCursor : public QWidget
{
    Q_OBJECT

public:
    TopCursor(struct Imp *impPtr, QWidget* parent = nullptr);
    ~TopCursor() {};

protected:
    void paintEvent(QPaintEvent* event);

private:
    struct Imp *impPtr;
};

/****************************************
* @brif	LeftCursor 左侧游标（行号）
****************************************/
class LeftCursor : public QWidget
{
    Q_OBJECT
public:
    LeftCursor(struct Imp *impPtr, QWidget* parent = nullptr);
    ~LeftCursor() {};

protected:
    void paintEvent(QPaintEvent* event);

private:
    struct Imp *impPtr;
};

/****************************************
* @brif	PaintWidgets 主界面
****************************************/
class PaintWidget : public QAbstractScrollArea
{
    Q_OBJECT
public:
    PaintWidget(QWidget* parent = nullptr);
    ~PaintWidget();

    //设置行列
    void setRowAndCol(int row, int col);

    //设置行
    void setRow(int row);

    //设置列
    void setCol(int col);

    //是否显示顶部游标（列号）
    void isShowTopCursor(bool isShow);

    //是否显示左侧游标（行号）
    void isShowLeftCursor(bool isShow);

    //设置进制
    void setJinzhi(RADIX type);

    //设置游标间隔
    void setInterval(int interval);

    //设置数据
    void setData(QVector<uchar> &data);

    void refresh();

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    //bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    void setHScollValue();
    void setVScollValue();
    //16
    inline QString & toHex(uchar ch, QString &str){
        uchar l(ch & 0b1111);
        uchar h((ch >> 4) & 0b1111);
        str[0] = (h < 10) ? '0' + h : 'A' - 10 + h;
        str[1] = (l < 10) ? '0' + l : 'A' - 10 + l;
        return str;
    }
    //10
    inline QString & toDec(uchar ch, QString &str){
        str[0] = '0' + (ch / 100);
        str[1] = '0' + ((ch / 10) % 10);
        str[2] = '0' + (ch % 10);
        return str;
    }
    //8
    inline QString & toOct(uchar ch, QString &str){
        str[0] = '0' + ((ch >> 6) & 0b111);
        str[1] = '0' + ((ch >> 3) & 0b111);
        str[2] = '0' + (ch & 0b111);
        return str;
    }
//2
inline QString & toBin(uchar ch, QString &str){
    for(int i = 0; i < 4; ++i)
    {
        str[7-i] = '0' + ((ch >> i) & 1);
        str[3-i] = '0' + ((ch >> (i+4)) & 1);
    }
    return str;
}

private slots:
    void onHScrollBarChanged(int value);
    void onVScrollBarChanged(int value);

private:
    TopCursor* m_topCursor;
    LeftCursor* m_leftCursor;
    struct Imp *impPtr;
};

#endif // !PAINTWIDGET_H

