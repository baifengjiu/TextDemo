#pragma once

#include <QtWidgets/QWidget>

class TextView;

class TextDemo : public QWidget
{
    Q_OBJECT

public:
    TextDemo(QWidget *parent = Q_NULLPTR);
    void onRefresh();
    
private:
    TextView* m_textView;
    int m_length;
};
