#include "PropertyWidget.h"

PropertyWidget::PropertyWidget(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    m_exterior.setExterior(this, true, 1, false);
}
