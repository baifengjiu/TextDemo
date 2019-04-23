/******************************************************************************
*  @PropertyTree.cpp  : (描述)
******************************************************************************
*
******************************************************************************
*  @author	:	fu.xue
*  @date	:	2019/04/17
*  @version	:
******************************************************************************
*  模块列表 :
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
   * @brif:    事件
   * @Param:   QEvent *event
   * @ret:     void
   ****************************************/
    void changeEvent(QEvent *);

    /****************************************
    * @brif:    画属性树背景样式
    * @Param:   QPainter *painter, 
    * @Param:   const QStyleOptionViewItem &option, 
    * @Param:   const QModelIndex &index
    * @ret:     void
    ****************************************/
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    /****************************************
    * @brif:    实时翻译
    * @Param:   
    * @ret:     
    ****************************************/
    void retranslateUi();
Q_SIGNALS:
    /****************************************
    * @brif:    提示信息
    * @Param:   QString string
    * @ret:     void
    ****************************************/
    void signalTip(QString string);

private Q_SLOTS:
    /****************************************
    * @brif:    编辑事件
    * @Param:   QTreeWidgetItem* 当前节点
    * @Param:   int 当前列
    * @ret:     
    ****************************************/
    void onItemEditFilterChanged(QTreeWidgetItem*, int);
   
    /****************************************
    * @brif:    选中item
    * @Param:   const QModelIndex &current
    * @Param:   const QModelIndex &previous
    * @ret:     void
    ****************************************/
    void onItemClicked(QTreeWidgetItem*, int);

    /****************************************
    * @brif:    编辑事件
    * @Param:   QTreeWidgetItem* 当前节点
    * @Param:   int 当前列
    * @ret:
    ****************************************/
    void onFinishEdit();

    /****************************************
    * @brif:    添加范围
    * @Param:   
    * @ret:
    ****************************************/
    void onAddRange();
    void onDelRange();

    /****************************************
    * @brif:    添加物理描述
    * @Param:   
    * @ret:
    ****************************************/
    void onAddPhysicsDes();
    void onDelPhysicsDes();

private:
    //初始化属性编辑树的基本属性很结构
    void initUI();
    void initGenneral();
    void initExtraction();
    void initCalibration();
    void initProcessing();
    void initRange();
    void initPhysicsDes();
    void initDescription();

    /****************************************
    * @brif:    获取编辑框中编辑的数据
    * @Param:   QWidget* widget 编辑框
    * @ret:     QString 编辑框中的数据
    ****************************************/
    QString getEidtString(QWidget* widget);

    /****************************************
    * @brif:    当extraction type 改变
    * @Param:   const QString text 当前选择的项
    * @ret:     void
    ****************************************/
    void changeExtractionType(const QString text);

    /****************************************
    * @brif:    当calibration function改变
    * @Param:   const QString text 当前选项的值
    * @ret:     void
    ****************************************/
    void changeCalibrationtFunc(const QString text);

    /****************************************
    * @brif:    当Processing function 改变
    * @Param:   const QString text 当前选项的值
    * @ret:     void
    ****************************************/
    void changeProcessingFunc(const QString text);
private:
    //top节点
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
    
    //当前选中节点
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

