#include "PropertyWidget.h"
#include <QFile>
#include "ItemGroup.h"
#include <qdebug.h>    

PropertyWidget::PropertyWidget(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    m_exterior.setExterior(this, true, 1, false);
    redXml();
    initUI(m_xmlRoot,nullptr);
    connect(ui.closeBtn, &QToolButton::clicked, this, &PropertyWidget::close);
}

void PropertyWidget::redXml()
{
    QFile file(":/Resources/PropertyTree.xml");
    if (file.open(QFile::ReadOnly))
    {
        QDomDocument * doc = new QDomDocument();
        doc->setContent(file.readAll());
        file.close();
        QDomElement xmlRoot = doc->documentElement(); //���ظ��ڵ�
       
        //��ȡ��ǰ���� 
        if (false)
        {
            m_xmlRoot = xmlRoot.firstChildElement(); //���ظ��ڵ�
        }
        else
        {
            m_xmlRoot = xmlRoot.lastChildElement(); //���ظ��ڵ�
        }
        qDebug() << m_xmlRoot.attribute("Language");
    }
    file.close();
}

void PropertyWidget::initUI(QDomNode & elem, QWidget * parent)
{
    if (elem.isNull()) return;

    QDomElement e = elem.toElement();
    //��ӡ��ֵ�ԣ�tagName��nodeName��һ������
    ItemGroup * group = nullptr;
    if (e.attribute("type") == "title")
    {
        group = new ItemGroup(e.attribute("name"), false, this);

        if (parent == nullptr)
        {
            ui.scrollAreaWidgetContents->layout()->addWidget(group);
        }
        else
        {
           QWidget* parentContent = qobject_cast<ItemGroup*>(parent)->getContent();
           parentContent->layout()->addWidget(group);
        }
    }
    else if (e.attribute("type") == "spinbox")
    {
        QString minStr = e.attribute("min");
        QString maxStr = e.attribute("max");
        int min = minStr.toInt();
        int max = maxStr.toInt();
        qobject_cast<ItemGroup*>(parent)->createRow(e.attribute("name"), e.attribute("defaultValue"), min, max);
    }
    else if (e.attribute("type") == "dbspinbox")
    {
        QString minStr = e.attribute("min");
        QString maxStr = e.attribute("max");
        int min = minStr.toDouble();
        int max = maxStr.toDouble();
        qobject_cast<ItemGroup*>(parent)->createRow(e.attribute("name"), e.attribute("defaultValue"), min, max);
    }
    else if (e.attribute("type") == "combobox")
    {
        QStringList values;
        QDomNodeList list = e.childNodes();
        //������Ԫ��  
        for (int i = 0; i < list.count(); i++)
        {
            QDomNode n = list.at(i);
            values.append(n.toElement().text());
        }
        qobject_cast<ItemGroup*>(parent)->createRow(e.attribute("name"), e.attribute("defaultValue"), values);
    }
    else if (e.attribute("type") == "text")
    {
        qobject_cast<ItemGroup*>(parent)->createRow(e.attribute("name"), e.attribute("defaultValue"), e.attribute("regx"));
    }

    QDomNodeList list = e.childNodes();
    //������Ԫ��  
    for (int i = 0; i < list.count(); i++)
    {
        QDomNode n = list.at(i);
        initUI(n, group);
    }

    //��һ���ֵܽڵ�,nextSiblingElement()����һ���ֵ�Ԫ�أ������
    elem = elem.nextSibling();
}
