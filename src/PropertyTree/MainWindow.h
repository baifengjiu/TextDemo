#pragma once

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include "ui_MainWindow.h"

class PropertyTree;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*) override;

private Q_SLOTS:
    void onShowPropertyTree();
    void onShowPropertyTreeWithValue();
    void onShowValue();
private:
    Ui::MainWindow ui;
    PropertyTree *m_tree;
};
