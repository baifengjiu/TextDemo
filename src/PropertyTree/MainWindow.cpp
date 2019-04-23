#include "MainWindow.h"
#include "PropertyTree.h"
#include <QDockWidget>
#include <utility>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_tree(nullptr)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::onShowPropertyTree);

    connect(ui.pushButton_3, &QPushButton::clicked, this, &MainWindow::onShowPropertyTreeWithValue);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::onShowValue);
}

MainWindow::~MainWindow()
{
    if (m_tree != nullptr)
    {
        delete m_tree;
        m_tree = nullptr;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (m_tree!=nullptr)
    {
        m_tree->setGeometry(this->geometry().x() + width() - m_tree->width(), this->geometry().y(), m_tree->width() - 2, height() - 2);
    }
    QWidget::resizeEvent(event);
}

void MainWindow::onShowPropertyTreeWithValue()
{
    if (m_tree != nullptr)
    {
        delete m_tree;
        m_tree = nullptr;
    }
    setlocale(LC_ALL, "zh_CN.UTF-8");

    parameter parameter;
    parameter.id = 1111;    
    parameter.code = "code";
    parameter.name = "name";
    parameter.unit = "��";

    //extraction
    parameter.extractionType ="Com";	//��ȡ���ͣ�com,subcom,supercom,free,split
    //com,free,subcom,supercom
    parameter.position = "(1:12)(1:33)";		//splitֻ�����
    parameter.positions = "";
    parameter.format = "Int";			//����
    parameter.inversion = "Yes";		//�Ƿ�ת
    parameter.NbWords = 1;
    parameter.NbBits = 2;
    parameter.LsbPosBit = 3;

    //ֻ��Ƿ�ɺͳ��ɵĲ���
    parameter.recurence = 3;		//subcom,supercom
    parameter.majorPos = 4;		//subcom

    //calibrationtFuncУ׼����
    parameter.calibrationtFuncName = "test1";					//У׼������
    //У׼��������
    parameter.calibrationtParam.insert(std::make_pair("test11", 33.2));
    parameter.calibrationtParam.insert(std::make_pair("test12", 11.2));
    parameter.calibrationtParam.insert(std::make_pair("test13", 44));

    //processingFunc������
    parameter.processingFuncName = "test1";					//��������
   //����������
    parameter.processParam.insert(std::make_pair("test11", 33.2));
    parameter.processParam.insert(std::make_pair("test12", 11.2));
    parameter.processParam.insert(std::make_pair("test13", 44));

    //range��Χ
    parameter.range.push_back("[3-10]");
    parameter.range.push_back("[2-9]");
    parameter.range.push_back("[4-10]");

    //physicsDescription��������
    //��������
    parameter.physicsDes.insert(std::make_pair("[30-45]","temperature"));
    parameter.physicsDes.insert(std::make_pair("[55-100]", "temperature"));

    //description
    parameter.description = "this is description whih id = 1111";	//����
    setlocale(LC_ALL, "C");

    m_tree = new PropertyTree(parameter);
    m_tree->setGeometry(this->geometry().x() + width() - m_tree->width(), this->geometry().y(), m_tree->width() - 2, height() - 2);
    m_tree->show();
    connect(m_tree, &PropertyTree::signalTip, [=](QString & text) {
        ui.tip->setText(text);
    });
}

void MainWindow::onShowValue()
{
    if (m_tree != nullptr)
    {
        ui.textEdit->clear();

        parameter parameter = m_tree->getParameter();
        
        ui.textEdit->append("parameter.id:" + QString::number(parameter.id));
        ui.textEdit->append("parameter.code:" + QString(parameter.code.c_str()));
        ui.textEdit->append("parameter.name:" + QString(parameter.name.c_str()));
        ui.textEdit->append("parameter.unit:" + QString(parameter.unit.c_str()));

        //extraction
        ui.textEdit->append("parameter.extractionType:" + QString(parameter.extractionType.c_str()));	//��ȡ���ͣ�com,subcom,supercom,free,split
        //com,free,subcom,supercom
        ui.textEdit->append("parameter.position:" + QString(parameter.position.c_str()));		//splitֻ�����
        ui.textEdit->append("parameter.positions:" + QString(parameter.positions.c_str()));		//free
        ui.textEdit->append("parameter.format:" + QString(parameter.format.c_str()));			//����
        ui.textEdit->append("parameter.inversion:" + QString(parameter.inversion.c_str()));		//�Ƿ�ת
        ui.textEdit->append("parameter.NbWords:" + QString::number(parameter.NbWords));
        ui.textEdit->append("parameter.NbBits:" + QString::number(parameter.NbBits));
        ui.textEdit->append("parameter.LsbPosBit:" + QString::number(parameter.LsbPosBit));

        //ֻ��Ƿ�ɺͳ��ɵĲ���
        ui.textEdit->append("parameter.recurence:" + QString::number(parameter.recurence));		//subcom,supercom
        ui.textEdit->append("parameter.majorPos:" + QString::number(parameter.majorPos));		//subcom

        //calibrationtFuncУ׼����
        ui.textEdit->append("parameter.calibrationtFuncName:" + QString(parameter.calibrationtFuncName.c_str()));				//У׼������
        for (auto iter = parameter.calibrationtParam.begin(); iter != parameter.calibrationtParam.end(); iter++)
        {
            ui.textEdit->append("\t" + QString((iter->first).c_str()) + ":" + QString::number(iter->second));
        }

        //processingFunc������
        ui.textEdit->append("parameter.processingFuncName:" + QString(parameter.processingFuncName.c_str()));					//��������
        for (auto iter = parameter.processParam.begin(); iter != parameter.processParam.end(); iter++)
        {
            ui.textEdit->append("\t" + QString((iter->first).c_str()) + ":" + QString::number(iter->second));
        }

        //range��Χ
        ui.textEdit->append("parameter.range:");
        for (auto iter = parameter.range.begin(); iter != parameter.range.end(); iter++)
        {
            ui.textEdit->append("\t" + QString(iter->c_str()));
        }

        //physicsDescription��������
        ui.textEdit->append("parameter.physicsDes:");
        for (auto iter = parameter.physicsDes.begin(); iter != parameter.physicsDes.end(); iter++)
        {
            ui.textEdit->append("\t" + QString((iter->first).c_str()) + ":" + QString((iter->second).c_str()));
        }

        //description
        ui.textEdit->append("parameter.description:" + QString(parameter.description.c_str()));	//����
    }

}

void MainWindow::onShowPropertyTree()
{
    if (m_tree != nullptr)
    {
        delete m_tree;
        m_tree = nullptr;
    }
    m_tree = new PropertyTree;  
    m_tree->setGeometry(this->geometry().x() + width() - m_tree->width(), this->geometry().y(), m_tree->width() - 2, height() - 2);
    m_tree->show();
    connect(m_tree, &PropertyTree::signalTip, [=](QString & text) {
        ui.tip->setText(text);
    });
}
