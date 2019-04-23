/******************************************************************************
*  @PropertyTree.cpp  : (����)
******************************************************************************
*
******************************************************************************
*  @author	:	fu.xue
*  @date	:	2019/04/17
*  @version	:
******************************************************************************
*  ģ���б� :
*
*  Class       :
*  Description :
*
******************************************************************************
*  Change History
* ----------------------------------------------------------------------------
*    Date    :  Ver. : Author : Description
* ----------------------------------------------------------------------------
* 2019/04/17 :       : fu.xue : Create
*            :       :        :
******************************************************************************/
#ifndef PROPERTYTREE_H
#define PROPERTYTREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <struct.h>

class PropertyTree : public QTreeWidget
{
    Q_OBJECT

public:
    PropertyTree(QWidget *parent = Q_NULLPTR);
    PropertyTree(parameter parameter, QWidget *parent = Q_NULLPTR);
    ~PropertyTree();

    parameter getParameter();

protected:
    /****************************************
   * @brif:    �¼�
   * @Param:   QEvent *event
   * @ret:     void
   ****************************************/
    void changeEvent(QEvent *);

    /****************************************
    * @brif:    ��������������ʽ
    * @Param:   QPainter *painter, 
    * @Param:   const QStyleOptionViewItem &option, 
    * @Param:   const QModelIndex &index
    * @ret:     void
    ****************************************/
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    /****************************************
    * @brif:    ʵʱ����
    * @Param:   
    * @ret:     
    ****************************************/
    void retranslateUi();
Q_SIGNALS:
    /****************************************
    * @brif:    ��ʾ��Ϣ
    * @Param:   QString string
    * @ret:     void
    ****************************************/
    void signalTip(QString string);

private Q_SLOTS:
    /****************************************
    * @brif:    �༭�¼�
    * @Param:   QTreeWidgetItem* ��ǰ�ڵ�
    * @Param:   int ��ǰ��
    * @ret:     
    ****************************************/
    void onItemEditFilterChanged(QTreeWidgetItem*, int);
   
    /****************************************
    * @brif:    ѡ��item
    * @Param:   const QModelIndex &current
    * @Param:   const QModelIndex &previous
    * @ret:     void
    ****************************************/
    void onItemClicked(QTreeWidgetItem*, int);

    /****************************************
    * @brif:    �༭�¼�
    * @Param:   QTreeWidgetItem* ��ǰ�ڵ�
    * @Param:   int ��ǰ��
    * @ret:
    ****************************************/
    void onFinishEdit();

    /****************************************
    * @brif:    ��ӷ�Χ
    * @Param:   
    * @ret:
    ****************************************/
    void onAddRange();
    void onDelRange();

    /****************************************
    * @brif:    �����������
    * @Param:   
    * @ret:
    ****************************************/
    void onAddPhysicsDes();
    void onDelPhysicsDes();

private:
    //��ʼ�����Ա༭���Ļ������Ժܽṹ
    void initUI();
    void initGenneral();
    void initExtraction();
    void initCalibration();
    void initProcessing();
    void initRange();
    void initPhysicsDes();
    void initDescription();

    /****************************************
    * @brif:    ��ȡ�༭���б༭������
    * @Param:   QWidget* widget �༭��
    * @ret:     QString �༭���е�����
    ****************************************/
    QString getEidtString(QWidget* widget);

    /****************************************
    * @brif:    ��extraction type �ı�
    * @Param:   const QString text ��ǰѡ�����
    * @ret:     void
    ****************************************/
    void changeExtractionType(const QString text);

    /****************************************
    * @brif:    ��calibration function�ı�
    * @Param:   const QString text ��ǰѡ���ֵ
    * @ret:     void
    ****************************************/
    void changeCalibrationtFunc(const QString text);

    /****************************************
    * @brif:    ��Processing function �ı�
    * @Param:   const QString text ��ǰѡ���ֵ
    * @ret:     void
    ****************************************/
    void changeProcessingFunc(const QString text);
private:
    //top�ڵ�
    QTreeWidgetItem* m_genneral;
    QTreeWidgetItem* m_extraction;
    QTreeWidgetItem* m_calibration;
    QTreeWidgetItem* m_range;
    QTreeWidgetItem* m_physicsDes;
    QTreeWidgetItem* m_description;

    QTreeWidgetItem* m_calibrationtFuncItem;

    QTreeWidgetItem* m_processingFunc;
    QTreeWidgetItem* m_processingParam;
    QTreeWidgetItem* m_processingModulus;
    
    //��ǰѡ�нڵ�
    QTreeWidgetItem* m_currentEditItem;
    int m_currentEditItemColumn;

    enum Type
    {
        INT = 1,
        UINT,
        DOUBLE,
        BOOL,
        FORMAT,
        EXTRACTIONTYPE,
        PROCESSINGFUNC,
        CALIBRATIONFUNC,
        DISCRIPTION,
        TEXT,
    };

    parameter m_parameter;
};

#endif // !PROPERTYTREE_H

