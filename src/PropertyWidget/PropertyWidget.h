#pragma once

#include <QtWidgets/QDialog>
#include "ui_PropertyWidget.h"
#include "fswExterior.h"
#include <QDomDocument>

class PropertyWidget : public QDialog
{
    Q_OBJECT

public:
    PropertyWidget(QWidget *parent = Q_NULLPTR);


private:
    virtual void paintEvent(QPaintEvent* pe) override
    {
        m_exterior.doPaintShadow(pe);
    }

    virtual bool nativeEvent(const QByteArray& eventType, void* msg, long* result) override
    {
        return m_exterior.doNativeEvent(eventType, msg, result)
            || QDialog::nativeEvent(eventType, msg, result);
    }

    void redXml();
    void initUI(QDomNode & node, QWidget * parentGroup);

private:
    Ui::PropertyWidgetClass ui;
    fswExterior m_exterior;

    QDomElement m_xmlRoot;
};
