#include "PropertyTree.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QStringList>
#include <limits>
#include "WidgetButton.h"

//QTreeWidgetItem setData中 UserRole 介绍
//Qt::UserRole        //编辑类型
//Qt::UserRole + 1    //提示信息

PropertyTree::PropertyTree(QWidget *parent)
    : QTreeWidget(parent)
{
    m_parameter.id =0;
    m_parameter.code = "";
    m_parameter.name = "";
    m_parameter.unit = "";

    //extraction
    m_parameter.extractionType = "Com";	//提取类型：com,subcom,supercom,free,split
    //com,free,subcom,supercom
    m_parameter.position = "";		//split只有这个
    m_parameter.positions = "";
    m_parameter.format = "Int";			//类型
    m_parameter.inversion = "Yes";		//是否反转
    m_parameter.NbWords = 0;
    m_parameter.NbWords = 0;
    m_parameter.NbBits = 0;
    m_parameter.LsbPosBit = 0;

    //只有欠采和超采的参数
    m_parameter.recurence = 0;		//subcom,supercom
    m_parameter.majorPos = 0;		//subcom

    //calibrationtFunc校准函数
    m_parameter.calibrationtFuncName = "test1";					//校准函数名

    //processingFunc处理函数
    m_parameter.processingFuncName = "test1";					//处理函数名
    std::map<std::string, double> 	processParam;	//处理函数参数

    //range范围
    m_parameter.range.push_back("[3-10]");
    m_parameter.range.push_back("[2-9]");
    m_parameter.range.push_back("[4-10]");
    

    //physicsDescription物理描述
    std::map<std::string, std::string>	physicsDes;	//物理描述

    //description
    m_parameter.description = "Click here to edit.";	//描述

    initUI();
}

PropertyTree::PropertyTree(parameter parameter, QWidget * parent)
{
    m_parameter = parameter;
    initUI();
}

PropertyTree::~PropertyTree()
{
}

void PropertyTree::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
    {
        retranslateUi();//在此处刷新语言的  
    }
    break;
    default:
        break;
    }
}

void PropertyTree::retranslateUi()
{
}

parameter PropertyTree::getParameter()
{
    //获取genneral
    m_parameter.id = m_genneral->child(0)->text(1).toInt();
    m_parameter.code = m_genneral->child(1)->text(1).toStdString();
    m_parameter.name = m_genneral->child(2)->text(1).toStdString();
    m_parameter.unit = m_genneral->child(3)->text(1).toStdString();
    
    //获取extraction
    m_parameter.extractionType = m_extraction->child(0)->text(1).toStdString();	//提取类型：com,subcom,supercom,free,split
    //com,free,subcom,supercom
    m_parameter.position = m_extraction->child(1)->text(1).toStdString();		//split只有这个
    m_parameter.positions = m_extraction->child(2)->text(1).toStdString();		//free
    m_parameter.format = m_extraction->child(3)->text(1).toStdString();			//类型
    m_parameter.inversion = m_extraction->child(4)->text(1).toStdString();		//是否反转
    m_parameter.NbWords = m_extraction->child(5)->text(1).toInt();
    m_parameter.NbBits = m_extraction->child(6)->text(1).toInt();
    m_parameter.LsbPosBit = m_extraction->child(7)->text(1).toInt();

    //只有欠采和超采的参数
    m_parameter.recurence = m_extraction->child(8)->text(1).toInt();		//subcom,supercom
    m_parameter.majorPos = m_extraction->child(9)->text(1).toInt();		//subcom

    //获取calibration
    m_parameter.calibrationtParam.clear();
    m_parameter.calibrationtFuncName = m_calibrationtFuncItem->text(1).toStdString();					//校准函数名
    for (size_t i = 0; i < m_calibration->childCount(); i++)
    {
        if (m_calibration->child(i) != m_calibrationtFuncItem)
        {
            m_parameter.calibrationtParam.insert(std::make_pair(
                m_calibration->child(i)->text(0).toStdString(), 
                m_calibration->child(i)->text(1).toDouble()
            ));
        }
    }

    //获取processing
    m_parameter.processingFuncName == m_processingFunc->text(1).toStdString();					//处理函数名

    m_parameter.processParam.clear();
    /*for (size_t i = 1; i < m_processingModulus->childCount(); i++)
    {
      m_parameter.processParam.insert(std::make_pair(
            m_processingModulus->child(i)->text(0).toStdString(),
            m_processingModulus->child(i)->text(1).toDouble()
        ));
    }*/

    for (size_t i = 1; i < m_processingParam->childCount(); i++)
    {
        m_parameter.processParam.insert(std::make_pair(
            m_processingParam->child(i)->text(0).toStdString(),
            m_processingParam->child(i)->text(1).toDouble()
        ));
    }

    //获取range
    m_parameter.range.clear();
    for (size_t i = 0; i < m_range->childCount(); i++)
    {
        m_parameter.range.push_back(
            m_range->child(i)->text(0).toStdString()
        );
    }

    //获取physicsDes
    m_parameter.physicsDes.clear();
    for (size_t i = 0; i < m_physicsDes->childCount(); i++)
    {
        m_parameter.physicsDes.insert(std::make_pair(
            m_physicsDes->child(i)->text(0).toStdString(),
            m_physicsDes->child(i)->text(1).toStdString()
        ));
    }

    //获取description
    m_parameter.description = m_description->child(0)->text(0).toStdString();	//描述
    return m_parameter;
}

void PropertyTree::onItemEditFilterChanged(QTreeWidgetItem* item, int column)
{
    QString tip = item->data(0, Qt::UserRole + 1).toString();
    emit signalTip(tip);

    int type = item->data(column, Qt::UserRole).toInt();
    //type = 0；的时候，不是编辑项
    if (!type)
    {
        return;
    }

    m_currentEditItem = item;
    m_currentEditItemColumn = column;

    switch (type)
    {
    case PropertyTree::INT:
    {
        QSpinBox *dspin_box = new QSpinBox();
        dspin_box->setMaximum(std::numeric_limits<int>::max());
        dspin_box->setMinimum(std::numeric_limits<int>::min());
        dspin_box->setValue(item->text(column).toInt());
        this->setItemWidget(item, column, dspin_box);
        connect(dspin_box, SIGNAL(editingFinished()), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::UINT:
    {
        QLineEdit *lineEdit = new  QLineEdit();
        QRegExp regExp("^[0-9]+$");
        lineEdit->setValidator(new  QRegExpValidator(regExp));
        this->setItemWidget(item, column, lineEdit);
        lineEdit->setText(item->text(column));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::DOUBLE:
    {
        QDoubleSpinBox *dspin_box = new QDoubleSpinBox();
        dspin_box->setMaximum(std::numeric_limits<double>::max());
        dspin_box->setMinimum(std::numeric_limits<double>::min());
        dspin_box->setValue(item->text(column).toDouble());
        this->setItemWidget(item, column, dspin_box);
        connect(dspin_box, SIGNAL(editingFinished()), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::BOOL:
    {
        QComboBox *combox = new  QComboBox();
        QStringList lists;
        lists << "YES" << "No";
        combox->addItems(lists);
        combox->setCurrentText(item->text(column));
        this->setItemWidget(item, column, combox);
        connect(combox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::FORMAT:
    {
        QComboBox *combox = new  QComboBox();
        QStringList lists;
        lists << "Int" << "UInt" << "Float" << "Double" << "BCD" << "Gray";
        combox->addItems(lists);
        combox->setCurrentText(item->text(column));
        this->setItemWidget(item, column, combox);
        connect(combox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::EXTRACTIONTYPE:
    {
        QComboBox *combox = new QComboBox();
        QStringList lists;
        lists << "Com" << "SubCom" << "SuperCom" << "Free" << "Split";
        combox->addItems(lists);
        combox->setCurrentText(item->text(column));
        this->setItemWidget(item, column, combox);
        connect(combox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::PROCESSINGFUNC:
    {
        QComboBox *combox = new QComboBox();
        QStringList lists;
        lists << "test1" << "test2" << "test3";
        combox->addItems(lists);
        combox->setCurrentText(item->text(column));
        this->setItemWidget(item, column, combox);
        connect(combox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::CALIBRATIONFUNC:
    {
        QComboBox *combox = new QComboBox();
        QStringList lists;
        lists << "test1" << "test2" << "test3";
        combox->addItems(lists);
        combox->setCurrentText(item->text(column));
        this->setItemWidget(item, column, combox);
        connect(combox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::DISCRIPTION:
    {
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setText(item->text(column));
        lineEdit->selectAll();
        lineEdit->setMinimumHeight(120);
        setItemWidget(item, column, lineEdit);
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onFinishEdit()));
    }
        break;
    case PropertyTree::TEXT:
    {
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setText(item->text(column));
        lineEdit->selectAll();
        setItemWidget(item, column, lineEdit);
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onFinishEdit()));
    }
        break;
    default:
        break;
    }
}

void PropertyTree::drawRow(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QStyleOptionViewItemV3 opt = option;
    QTreeWidgetItem *item = static_cast<QTreeWidgetItem*>(index.internalPointer());
    painter->save();
    if (item->parent() != nullptr && !((index.row() + 1) % 2))
    {
        int leftWidth = fontMetrics().width("0");
        painter->fillRect(
            QRect(
                option.rect.x() + leftWidth,
                option.rect.y(),
                width() - leftWidth,
                option.rect.height()
            ),
            QColor("#FFFFFF"));
    }
    painter->restore();

    //根节点
    if (item->parent() == nullptr) {
        item->setTextAlignment(0, Qt::AlignVCenter);
        painter->fillRect(
            QRect(
                option.rect.x(),
                option.rect.y() + 1,
                width(),
                option.rect.height() - 2
            ),
            QColor("#FFFFFF"));
        painter->setPen(QPen(QColor("#C0C0C0")));
        int width = fontMetrics().width(item->text(0));
        painter->drawLine(
            opt.rect.x() + this->indentation() + width + 10,
            opt.rect.bottom() - opt.rect.height() / 2,
            opt.rect.right(),
            opt.rect.bottom() - opt.rect.height() / 2
        );
    }
    //没有子节点
    else if (item->childCount() == 0) {
        item->setTextAlignment(0, Qt::AlignHCenter | Qt::AlignVCenter);
        item->setTextAlignment(1, Qt::AlignHCenter | Qt::AlignVCenter);
    }
    //既有父节点也有子节点
    else 
    {
        item->setTextAlignment(0, Qt::AlignVCenter);
        painter->fillRect(
            QRect(
                option.rect.x(),
                option.rect.y(),
                width(),
                option.rect.height()
            ),
            QColor("#d9d9d9"));
    }

    painter->restore(); 
    QTreeWidget::drawRow(painter, opt, index);
}

void PropertyTree::onItemClicked(QTreeWidgetItem *item, int column)
{
    //如果当前点击的是同一个item，不做任何操作
    if (item == m_currentEditItem && column == m_currentEditItemColumn)
    {
        return;
    }

    //是否显示range的删除按钮
    if (item->parent() == m_range)
    {
        qobject_cast<WidgetButton*>(itemWidget(m_range, 1))->getDelBton()->show();
    }
    else
    {
        qobject_cast<WidgetButton*>(itemWidget(m_range, 1))->getDelBton()->hide();
    }

    //是否显示physics Descripte的删除按钮
    if (item->parent() == m_physicsDes)
    {
        qobject_cast<WidgetButton*>(itemWidget(m_physicsDes, 1))->getDelBton()->show();
    }
    else
    {
        qobject_cast<WidgetButton*>(itemWidget(m_physicsDes, 1))->getDelBton()->hide();
    }

    //删除界面上出现的编辑框
    QTreeWidgetItemIterator it(this);
    while (*it) {
        for (size_t i = 0; i < (*it)->columnCount(); ++i)
        {
            QWidget *widget = itemWidget(*it, i);
            if (widget)
            {
                m_currentEditItem = *it;
                m_currentEditItemColumn = i;
                onFinishEdit();
                removeItemWidget(*it, i);
            }
        }
        ++it;
    }
}

void PropertyTree::onFinishEdit()
{
    QObject *obj = sender();
    QWidget *widget = itemWidget(m_currentEditItem, m_currentEditItemColumn);
    if (widget)
    {
        QString text = getEidtString(widget);
        if (text != m_currentEditItem->text(0) && text != "")
        {
            m_currentEditItem->setText(m_currentEditItemColumn, text);

        }
        removeItemWidget(m_currentEditItem, m_currentEditItemColumn);
    } 
}

void PropertyTree::onAddRange()
{
    //range增加一行
    QTreeWidgetItem* item = new QTreeWidgetItem(m_range);
    item->setData(0, Qt::UserRole, Type::TEXT);
    item->setData(0, Qt::UserRole + 1, tr("tip message"));
    item->setFirstColumnSpanned(true);
}

void PropertyTree::onDelRange()
{
    QTreeWidgetItem * currentItem = this->currentItem();
    m_range->removeChild(currentItem);
}

void PropertyTree::onAddPhysicsDes()
{
    //PhysicsDes增加一行
    QTreeWidgetItem* tree = new QTreeWidgetItem(m_physicsDes);
    tree->setData(0, Qt::UserRole, Type::TEXT);
    tree->setData(0, Qt::UserRole + 1, tr("tip message"));
    tree->setData(1, Qt::UserRole, Type::TEXT);
}

void PropertyTree::onDelPhysicsDes()
{
    QTreeWidgetItem * currentItem = this->currentItem();
    m_physicsDes->removeChild(currentItem);
}

void PropertyTree::initUI()
{
    setFixedWidth(347);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setAcceptDrops(true);
    this->setFrameShape(QFrame::NoFrame);
    this->setColumnCount(2);
    this->setHeaderHidden(true);
    this->setColumnWidth(0, 135);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setIndentation(15);
    
    initGenneral();
    initExtraction();
    initCalibration();
    initProcessing();
    initRange();
    initPhysicsDes();
    initDescription();   
   
    this->expandAll();
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemEditFilterChanged(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemClicked(QTreeWidgetItem*, int)));
   
}

void PropertyTree::initGenneral()
{
    m_genneral = new QTreeWidgetItem(this);
    m_genneral->setText(0, tr("Genneral"));
    m_genneral->setFirstColumnSpanned(true);

    QTreeWidgetItem* id = new QTreeWidgetItem(m_genneral);
    id->setText(0, tr("ID"));
    id->setData(0, Qt::UserRole + 1, tr("tip message"));
    id->setText(1, QString::number(m_parameter.id));
    QTreeWidgetItem* code = new QTreeWidgetItem(m_genneral);
    code->setText(0, tr("Code"));
    code->setData(0, Qt::UserRole + 1, tr("tip message"));
    code->setData(1, Qt::UserRole, Type::TEXT);
    code->setText(1, m_parameter.code.c_str());
    QTreeWidgetItem* name = new QTreeWidgetItem(m_genneral);
    name->setText(0, tr("Name"));
    name->setData(0, Qt::UserRole + 1, tr("Parameter Ident, must be unique in whole project.")  );
    name->setData(1, Qt::UserRole, Type::TEXT);
    name->setText(1, m_parameter.name.c_str());
    QTreeWidgetItem* unit = new QTreeWidgetItem(m_genneral);
    unit->setText(0, tr("Unit"));
    unit->setData(0, Qt::UserRole + 1, tr("Parameter quantities unit."));
    unit->setData(1, Qt::UserRole, Type::TEXT);
    unit->setText(1, m_parameter.unit.c_str());
}

void PropertyTree::initExtraction()
{
    m_extraction = new QTreeWidgetItem(this);
    m_extraction->setFirstColumnSpanned(true);
    m_extraction->setText(0, tr("Extraction"));
    QTreeWidgetItem* extractionType = new QTreeWidgetItem(m_extraction);
    extractionType->setText(0, tr("Extraction Type"));
    extractionType->setData(0, Qt::UserRole + 1, tr("Parameter position type."));
    extractionType->setData(1, Qt::UserRole, Type::EXTRACTIONTYPE);
    extractionType->setText(1, m_parameter.extractionType.c_str());
    QTreeWidgetItem* position = new QTreeWidgetItem(m_extraction);
    position->setText(0, tr("Position"));
    position->setData(0, Qt::UserRole + 1, tr("Parameter position offset in minor frame. Must be greater than 0."));
    position->setData(1, Qt::UserRole, Type::UINT);
    position->setText(1, m_parameter.position.c_str());
    QTreeWidgetItem* positions = new QTreeWidgetItem(m_extraction);
    positions->setText(0, tr("Positions"));
    positions->setData(0, Qt::UserRole + 1, tr("Parameter position offset in minor frame. Must be greater than 0."));
    positions->setData(1, Qt::UserRole, Type::UINT);
    positions->setText(1, m_parameter.positions.c_str());
    QTreeWidgetItem* format = new QTreeWidgetItem(m_extraction);
    format->setText(0, tr("Format"));
    format->setData(0, Qt::UserRole + 1, tr("Parameter coding type."));
    format->setData(1, Qt::UserRole, Type::FORMAT);
    format->setText(1, m_parameter.format.c_str());
    QTreeWidgetItem* inversion = new QTreeWidgetItem(m_extraction);
    inversion->setText(0, tr("Inversion"));
    inversion->setData(0, Qt::UserRole + 1, tr("Bytes inversion."));
    inversion->setData(1, Qt::UserRole, Type::BOOL);
    inversion->setText(1, m_parameter.inversion.c_str());
    QTreeWidgetItem* NbBytes = new QTreeWidgetItem(m_extraction);
    NbBytes->setText(0, tr("Nb Bytes"));
    NbBytes->setData(0, Qt::UserRole + 1, tr("Number of Bytes."));
    NbBytes->setData(1, Qt::UserRole, Type::UINT);
    NbBytes->setText(1, QString::number(m_parameter.NbWords));
    QTreeWidgetItem* NbBits = new QTreeWidgetItem(m_extraction);
    NbBits->setText(0, tr("Nb Bits"));
    NbBits->setData(0, Qt::UserRole + 1, tr("Number of bits."));
    NbBits->setData(1, Qt::UserRole, Type::UINT);
    NbBits->setText(1, QString::number(m_parameter.NbBits));
    QTreeWidgetItem* LsbPosBit = new QTreeWidgetItem(m_extraction);
    LsbPosBit->setText(0, tr("Lsb Position Bit"));
    LsbPosBit->setData(0, Qt::UserRole + 1, tr("LSB bit."));
    LsbPosBit->setData(1, Qt::UserRole, Type::UINT);
    LsbPosBit->setText(1, QString::number(m_parameter.LsbPosBit));
    QTreeWidgetItem* recurence = new QTreeWidgetItem(m_extraction);
    recurence->setText(0, tr("Recurence"));
    recurence->setData(0, Qt::UserRole + 1, tr("Recurence."));
    recurence->setData(1, Qt::UserRole, Type::UINT);
    recurence->setText(1, QString::number(m_parameter.recurence));
    QTreeWidgetItem* majorPos = new QTreeWidgetItem(m_extraction);
    majorPos->setText(0, tr("MajorPos"));
    majorPos->setData(0, Qt::UserRole + 1, tr("Major Positon."));
    majorPos->setData(1, Qt::UserRole, Type::UINT);
    majorPos->setText(1, QString::number(m_parameter.majorPos));

    changeExtractionType(m_parameter.extractionType.c_str());
}

void PropertyTree::initCalibration()
{
    m_calibration = new QTreeWidgetItem(this);
    m_calibration->setText(0, tr("Calibration"));
    m_calibration->setFirstColumnSpanned(true);
    m_calibrationtFuncItem = new QTreeWidgetItem(m_calibration);
    m_calibrationtFuncItem->setText(0, tr("CalibrationFunc"));
    m_calibrationtFuncItem->setData(0, Qt::UserRole + 1, tr("tip message"));
    m_calibrationtFuncItem->setData(1, Qt::UserRole, Type::CALIBRATIONFUNC);
    m_calibrationtFuncItem->setText(1, m_parameter.calibrationtFuncName.c_str());

    changeCalibrationtFunc(m_calibrationtFuncItem->text(1));
}

void PropertyTree::initProcessing()
{
    QTreeWidgetItem* processing = new QTreeWidgetItem(this);
    processing->setText(0, tr("Processing"));
    processing->setFirstColumnSpanned(true);
    m_processingFunc = new QTreeWidgetItem(processing);
    m_processingFunc->setText(0, tr("ProcessingFunc"));
    m_processingFunc->setData(0, Qt::UserRole + 1, tr("tip message"));
    m_processingFunc->setData(1, Qt::UserRole, Type::PROCESSINGFUNC);
    m_processingFunc->setText(1, m_parameter.processingFuncName.c_str());

    m_processingParam = new QTreeWidgetItem(processing);
    m_processingParam->setText(0, tr("Param"));
    m_processingParam->setFirstColumnSpanned(true);    

    m_processingModulus = new QTreeWidgetItem(processing);
    m_processingModulus->setText(0, tr("Modulus"));
    m_processingModulus->setFirstColumnSpanned(true);

    changeProcessingFunc(m_processingFunc->text(1));
}

void PropertyTree::initRange()
{
    m_range = new QTreeWidgetItem(this);
    m_range->setText(0, tr("Range"));
    WidgetButton *addRange = new WidgetButton(WidgetButton::Positon::Right);
    addRange->setObjectName("TreeAddItem");
    addRange->setToolTip("add range", "delete range");
    addRange->setIcon(QIcon(":/PropertyTree/Resources/addItem.png"), QIcon(":/PropertyTree/Resources/deleteItem.png"));
    this->setItemWidget(m_range, 1, addRange);
    
    for (auto iter = m_parameter.range.begin(); iter != m_parameter.range.end(); ++iter)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(m_range);
        item->setText(0, iter->c_str());
        item->setData(0, Qt::UserRole, Type::TEXT);
        item->setData(0, Qt::UserRole + 1, tr("tip message"));
        item->setFirstColumnSpanned(true);
    }

     addRange->getDelBton()->setHidden(true);
    connect(addRange->getAddBton(), &QPushButton::clicked,this, &PropertyTree::onAddRange);
    connect(addRange->getDelBton(), &QPushButton::clicked, this, &PropertyTree::onDelRange);
}

void PropertyTree::initPhysicsDes()
{
    m_physicsDes = new QTreeWidgetItem(this);
    m_physicsDes->setText(0, tr("PhysicsDes"));
    WidgetButton *addPhysicsDes = new WidgetButton(WidgetButton::Positon::Right);
    addPhysicsDes->setObjectName("TreeAddItem");
    addPhysicsDes->setToolTip("add physics description", "delete physics description");
    addPhysicsDes->setIcon(QIcon(":/PropertyTree/Resources/addItem.png"), QIcon(":/PropertyTree/Resources/deleteItem.png"));
    this->setItemWidget(m_physicsDes, 1, addPhysicsDes);
    for (auto iter = m_parameter.physicsDes.begin(); iter != m_parameter.physicsDes.end(); ++iter)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(m_physicsDes);
        item->setText(0, (iter->first).c_str());
        item->setData(0, Qt::UserRole, Type::TEXT);
        item->setData(0, Qt::UserRole + 1, tr("tip message"));
        item->setData(1, Qt::UserRole, Type::TEXT);
        item->setText(1, (iter->second).c_str());
    }

    addPhysicsDes->getDelBton()->setHidden(true);
    connect(addPhysicsDes->getAddBton(), &QPushButton::clicked, this, &PropertyTree::onAddPhysicsDes);
    connect(addPhysicsDes->getDelBton(), &QPushButton::clicked, this, &PropertyTree::onDelPhysicsDes);
}

void PropertyTree::initDescription()
{
    m_description = new QTreeWidgetItem(this);
    m_description->setText(0, tr("Description"));
    QTreeWidgetItem* des = new QTreeWidgetItem(m_description);
    des->setData(0, Qt::UserRole, Type::DISCRIPTION);
    des->setData(0, Qt::UserRole + 1, tr("tip message"));
    des->setText(0, m_parameter.description.c_str());
    QWidget *widget = new QWidget;
    widget->setFixedHeight(120); //撑高此item高度
    this->setItemWidget(des, 0, widget);
    des->setFirstColumnSpanned(true);
}

QString PropertyTree::getEidtString(QWidget* widget)
{
    QString text;
    if (QComboBox *combo_box = dynamic_cast<QComboBox*>(widget))
    {
        text = combo_box->currentText();
        int type = m_currentEditItem->data(m_currentEditItemColumn, Qt::UserRole).toInt();
        switch (type)
        {
        case PropertyTree::EXTRACTIONTYPE:
            changeExtractionType(text);
            break;
        case PropertyTree::PROCESSINGFUNC:
            changeProcessingFunc(text);
            break;
        case PropertyTree::CALIBRATIONFUNC:
            changeCalibrationtFunc(text);
            break;
        default:
            break;
        } 
    }

    if (QSpinBox *spin_box = dynamic_cast<QSpinBox*>(widget))
    {
        text = spin_box->text();
    }

    if (QDoubleSpinBox *dspin_box = dynamic_cast<QDoubleSpinBox*>(widget))
    {
        text = dspin_box->text();
    }

    if (QLineEdit *line_edit = dynamic_cast<QLineEdit*>(widget))
    {
        text = line_edit->text();
    }
    return text;
}

void PropertyTree::changeExtractionType(const QString text)
{ 
    //"Com" << "SubCom" << "SuperCom" << "Free" << "Split";
    if (text == "Split")
    {
        //只保留postion
        m_extraction->child(1)->setHidden(false);
        for (size_t i = 2; i < m_extraction->childCount(); ++i)
        {
            m_extraction->child(i)->setHidden(true);
        }
    }
    else if (text == "SubCom")
    {
        //全部显示,隐藏positions
        for (size_t i = 1; i < m_extraction->childCount(); ++i)
        {
            if (m_extraction->child(i)->text(0) == "Positions")
            {
                m_extraction->child(i)->setHidden(true);
            }
            else
            {
                m_extraction->child(i)->setHidden(false);
            }
        }
    }
    else if (text == "SuperCom")
    {
        //隐藏 majorPos ,隐藏positions
        for (size_t i = 1; i < m_extraction->childCount(); ++i)
        {
            if (m_extraction->child(i)->text(0) == "MajorPos" || m_extraction->child(i)->text(0) == "Positions")
            {
                m_extraction->child(i)->setHidden(true);
            }
            else
            {
                m_extraction->child(i)->setHidden(false);
            }
        }
    }
    else if (text == "Free")
    {
        //隐藏 majorPos和recurence,position
        for (size_t i = 1; i < m_extraction->childCount(); ++i)
        {
            if (m_extraction->child(i)->text(0) == "Recurence" || m_extraction->child(i)->text(0) == "MajorPos" || m_extraction->child(i)->text(0) == "Position")
            {
                m_extraction->child(i)->setHidden(true);
            }
            else
            {
                m_extraction->child(i)->setHidden(false);
            }
        }
    }
    else
    {
        //隐藏 majorPos和recurence,隐藏positions
        for (size_t i = 1; i < m_extraction->childCount(); ++i)
        {
            if (m_extraction->child(i)->text(0) == "Recurence" || m_extraction->child(i)->text(0) == "MajorPos" || m_extraction->child(i)->text(0) == "Positions")
            {
                m_extraction->child(i)->setHidden(true);

            }
            else
            {
                m_extraction->child(i)->setHidden(false);
            }
        }
    }
}

void PropertyTree::changeCalibrationtFunc(const QString text)
{
    //删除原来的item，添加新的item
    for (size_t i = 0; i < m_calibration->childCount(); i++)
    {
        QTreeWidgetItem* item = m_calibration->child(i);
        if (item != m_calibrationtFuncItem)
        {
            //删除
            m_calibration->removeChild(item);
            delete item;
            i--;
        }
    }
    //添加新的item
    if (text == m_parameter.calibrationtFuncName.c_str())
    {
        for (auto iter = m_parameter.calibrationtParam.begin(); iter != m_parameter.calibrationtParam.end(); iter++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_calibration);
            item->setText(0, (iter->first).c_str());
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, QString::number(iter->second));
        }
    }
    else
    {
        for (size_t i = 0; i < 5; i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_calibration);
            item->setText(0, "text");
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, "");
        }
    }
}

void PropertyTree::changeProcessingFunc(const QString text)
{ 
    //删除原来的item，添加新的item
    for (size_t i = 0; i < m_processingParam->childCount(); i++)
    {
        QTreeWidgetItem* item = m_processingParam->child(i);       
        m_processingParam->removeChild(item);
        delete item;
        i--;
    }

    for (size_t i = 0; i < m_processingModulus->childCount(); i++)
    {
        QTreeWidgetItem* item = m_processingModulus->child(i);
        m_processingModulus->removeChild(item);
        delete item;
        i--;
    }

    if (text == m_parameter.processingFuncName.c_str())
    {
        for (auto iter = m_parameter.processParam.begin(); iter != m_parameter.processParam.end(); iter++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_processingParam);
            item->setText(0, (iter->first).c_str());
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, QString::number(iter->second));
        }
        for (auto iter = m_parameter.processParam.begin(); iter != m_parameter.processParam.end(); iter++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_processingModulus);
            item->setText(0, (iter->first).c_str());
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, QString::number(iter->second));
        }
    }
    else
    {
        for (size_t i = 0; i < 5; i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_processingParam);
            item->setText(0, "text");
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, "");
        }
        for (size_t i = 0; i < 3; i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(m_processingModulus);
            item->setText(0, "text");
            item->setData(0, Qt::UserRole + 1, tr("tip message"));
            item->setData(1, Qt::UserRole, Type::TEXT);
            item->setText(1, "");
        }
    }

}
