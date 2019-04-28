#pragma once

#include <QWidget>

class ItemGroup : public QWidget
{
    Q_OBJECT

public:
    ItemGroup(QWidget *parent = Q_NULLPTR);
    ItemGroup(QString & title, QWidget *parent = Q_NULLPTR);
    ~ItemGroup();

private:
    void initTitleWidget(QString & title);
    
};
