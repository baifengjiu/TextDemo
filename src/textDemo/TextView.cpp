#include "TextView.h"
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar> 

struct TextView::Imp
{
    Imp():interval(8){}

    QWidget* lineNumberArea;
    QWidget* columnNumber;
    int length;
    int row;
    int col;
    int interval;
    int hScrollOffset;
    int vScrollOffset;
    //QVector<QString> data;
};

TextView::TextView(QWidget *parent) 
    : QPlainTextEdit(parent)
    , imp(new Imp)
{
    imp->lineNumberArea = new LineNumberArea(this);
    imp->columnNumber = new ColumnNumber(this);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    this->setWordWrapMode(QTextOption::NoWrap);
    this->setFont(QFont("Consolas", 12, 0));
    
    this->setReadOnly(true);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &TextView::onHScrollBarChanged);
    //connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &TextView::onVScrollBarChanged);
}

int TextView::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void TextView::setRowAndCol(int row, int col)
{
    imp->row = row;
    imp->col = col;
    update();
}

void TextView::setLength(int length)
{
    imp->length = length;
    update();
}

void TextView::setInterval(int interval)
{
    imp->interval = interval - 1; 
    update();
}

void TextView::setData(QVector<QString>& data)
{
    this->setPlainText("");
    QString text;
    int size = 0;

    setUpdatesEnabled(false);
    for (int i = 0; i < imp->row; i++)
    {
        text = "";
        for (int j = 0; j < imp->col; j++)
        {
            if (size >= data.size())
            {
                QString str = QString("%1").arg('-', imp->length, QLatin1Char('-'));
                text += (j == imp->row - 1) ? str : str + " ";
            }
            else
            {
                text += (j == imp->row-1) ? data.at(size) : data.at(size) + " ";
            }
            ++size;
        }
        this->appendPlainText(text);
        //this->insertPlainText("\n"+text);
    }
    setUpdatesEnabled(true);
    this->update();
}

void TextView::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth()+1, fontMetrics().height() + 5, 0, 0);
}

void TextView::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        imp->lineNumberArea->scroll(0, dy);
    else
        imp->lineNumberArea->update(0, rect.y(), imp->lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void TextView::onVScrollBarChanged(int value)
{
    imp->vScrollOffset = value;
}

void TextView::onHScrollBarChanged(int value)
{
    imp->hScrollOffset = value;
    update();
}

void TextView::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    imp->lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    imp->columnNumber->setGeometry(QRect(cr.left() + lineNumberAreaWidth(), cr.top(), cr.width(), fontMetrics().height() + 5));
}

void TextView::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(Qt::yellow).lighter(160);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    setExtraSelections(extraSelections);
}

void TextView::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(imp->lineNumberArea);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(event->rect(), Qt::lightGray);
    painter.setPen(QPen(QColor(0, 160, 230)));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.drawText(
                0, 
                top+ fontMetrics().height()+5, 
                imp->lineNumberArea->width(), 
                fontMetrics().height(),
                Qt::AlignRight, 
                number
            );
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void TextView::ColumnNumberAreaPaintEvent(QPaintEvent * event)
{
    QPainter painter(imp->columnNumber);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(event->rect(), Qt::lightGray);
    painter.setPen(QPen(QColor(0, 160, 230)));
    QTextBlock block = firstVisibleBlock();
    int y = (int)blockBoundingGeometry(block).translated(contentOffset()).top();

    for (size_t i = 0; i < imp->col; i += imp->interval)
    {
        QString number = QString::number(i);
        int width = fontMetrics().width("9");
        int x = (width * (imp->length + 1))*i + 5;
        int xText = x + (width * imp->length / 2) - fontMetrics().width(number) / 2 - imp->hScrollOffset;
        painter.drawText(
            xText,
            y,
            fontMetrics().width(number),
            fontMetrics().height(),
            Qt::AlignCenter,
            number
        );
        painter.drawLine(
            x + (width * imp->length / 2) - imp->hScrollOffset,
            y + fontMetrics().height(),
            x + (width * imp->length / 2) - imp->hScrollOffset,
            event->rect().height() + event->rect().y()
        );
    }
    painter.drawLine(
        0,
        y + fontMetrics().height(),
        rect().width(),
        y + fontMetrics().height()
    );
}