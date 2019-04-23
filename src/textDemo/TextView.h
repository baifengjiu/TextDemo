#pragma once

#include <QPlainTextEdit>
#include <QObject>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;
class ColumnNumber;

class TextView : public QPlainTextEdit
{
    Q_OBJECT

public:
    TextView(QWidget *parent = 0);
    TextView(int length,QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void ColumnNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    /****************************************
    * @brif	设置行列
    * @Param: int row
    * @Param: int col
    * @ret: void 
    ****************************************/
    void setRowAndCol(int row,int col);
    /****************************************
    * @brif	设置进制长度
    * @Param: int length
    * @ret: void
    ****************************************/
    void setLength(int length);
    /****************************************
    * @brif	设置列数显示间隔
    * @Param: int intereval
    * @ret: void
    ****************************************/
    void setInterval(int interval);
    /****************************************
    * @brif	设置数据
    * @Param: QVector<QString> data
    * @ret: void
    ****************************************/
    void setData(QVector<QString>& data);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void onHScrollBarChanged(int value);
    void onVScrollBarChanged(int value);

private:
    struct Imp;
    std::shared_ptr<Imp> imp;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextView *editor) : QWidget(editor) {
        m_textView = editor;
    }

    QSize sizeHint() const override {
        return QSize(m_textView->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        m_textView->lineNumberAreaPaintEvent(event);
    }

private:
    TextView *m_textView;
};

class ColumnNumber : public QWidget
{
public:
    ColumnNumber(TextView *editor) : QWidget(editor) {
        m_textView = editor;
    }

    QSize sizeHint() const override {
        return QSize(0, m_textView->width());
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        m_textView->ColumnNumberAreaPaintEvent(event);
    }

private:
    TextView *m_textView;
};
