#pragma once

#include <QWidget>

class QToolBox;
class QToolButton;
// spinbox  | dbspinbox | combobox | text
//值域(整数)   值域(复数)   复选框     文本
//- type == spinbox : min | max
//- type == dbspinbox : min | max
//- type == combobox : <comboValue></comboValue>
//- type == text : regx


class ItemGroup : public QWidget
{
    Q_OBJECT

public:
    ItemGroup(QString titleName = "", bool hideTitle = false, QWidget *parent = Q_NULLPTR);
    ~ItemGroup();

    QWidget* getContent();

    /****************************************
    * @brif:    创建行 type == text : regx
    * @Param:   QString & name 名字
    * @Param:   QString value 默认值
    * @Param:   QString regx 正则验证
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, QString regx);

    /****************************************
    * @brif:    创建行 type == spinbox : min | max
    * @Param:   QString & name 名字
    * @Param:   QString value 默认值
    * @Param:   int min 最小值
    * @Param:   int max 最大值
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, int min, int max);

    /****************************************
    * @brif:    创建行 type == dbspinbox : min | max
    * @Param:   QString & name 名字
    * @Param:   QString value 默认值
    * @Param:   double min 最小值
    * @Param:   double max 最大值
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, double min, double max);

    /****************************************
    * @brif:    创建行 type == combobox : <comboValue></comboValue>
    * @Param:   QString & name 名字
    * @Param:   QString value 默认值
    * @Param:   QStringList values combobox选项
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, QStringList values);

    /****************************************
    * @brif:    设置Action
    * @Param:   QAction * action
    * @ret:     void
    ****************************************/
    void setAction(QAction *action);

    enum BoxType
    {
        SPINBOX,
        DBSPINBOX,
        COMBOBOX,
        TEXT,
    };

private Q_SLOTS:
    void onExpand(bool checked);

private:
    bool        m_isHideTitle;
    QToolBox    *m_toolBox;
    QWidget     *m_contentWidget;
    QToolButton *m_btnExpand;
};
