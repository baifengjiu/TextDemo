#pragma once

#include <QWidget>

class QToolBox;
class QToolButton;
// spinbox  | dbspinbox | combobox | text
//ֵ��(����)   ֵ��(����)   ��ѡ��     �ı�
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
    * @brif:    ������ type == text : regx
    * @Param:   QString & name ����
    * @Param:   QString value Ĭ��ֵ
    * @Param:   QString regx ������֤
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, QString regx);

    /****************************************
    * @brif:    ������ type == spinbox : min | max
    * @Param:   QString & name ����
    * @Param:   QString value Ĭ��ֵ
    * @Param:   int min ��Сֵ
    * @Param:   int max ���ֵ
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, int min, int max);

    /****************************************
    * @brif:    ������ type == dbspinbox : min | max
    * @Param:   QString & name ����
    * @Param:   QString value Ĭ��ֵ
    * @Param:   double min ��Сֵ
    * @Param:   double max ���ֵ
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, double min, double max);

    /****************************************
    * @brif:    ������ type == combobox : <comboValue></comboValue>
    * @Param:   QString & name ����
    * @Param:   QString value Ĭ��ֵ
    * @Param:   QStringList values comboboxѡ��
    * @ret:     void
    ****************************************/
    void createRow(QString & name, QString value, QStringList values);

    /****************************************
    * @brif:    ����Action
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
