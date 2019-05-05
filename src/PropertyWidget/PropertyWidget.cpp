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
        QDomElement xmlRoot = doc->documentElement(); //返回根节点
       
        //获取当前语言 
        if (false)
        {
            m_xmlRoot = xmlRoot.firstChildElement(); //返回根节点
        }
        else
        {
            m_xmlRoot = xmlRoot.lastChildElement(); //返回根节点
        }
        qDebug() << m_xmlRoot.attribute("Language");
    }
}

void PropertyWidget::initUI(QDomNode & elem, QWidget * parent)
{
    if (elem.isNull()) return;

    QDomElement e = elem.toElement();
    //打印键值对，tagName和nodeName是一个东西
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
        //遍历子元素  
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
    //遍历子元素  
    for (int i = 0; i < list.count(); i++)
    {
        QDomNode n = list.at(i);
        initUI(n, group);
    }

    //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    elem = elem.nextSibling();
}
