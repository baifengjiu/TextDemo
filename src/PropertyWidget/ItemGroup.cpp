#include "ItemGroup.h"
#include <QLayout>
#include <QLabel>
#include <QToolButton>
#include <QToolBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

#define FIXEDWIDTH 100

ItemGroup::ItemGroup(QString titleName, bool hideTitle, QWidget * parent)
    : QWidget(parent)
    , m_isHideTitle(hideTitle)
    , m_toolBox(nullptr)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    if (!hideTitle)
    {
        QWidget *titleWidget = new QWidget(parent);
        titleWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        QHBoxLayout *hTitleLayout = new QHBoxLayout(titleWidget);
        m_btnExpand = new  QToolButton(titleWidget);
        m_btnExpand->setIcon(QIcon(":/Resources/itemExpansion.png"));
        m_btnExpand->setCheckable(true);
        QLabel * title = new QLabel(titleWidget);
        title->setText(titleName);
        m_toolBox = new QToolBox(titleWidget);

        hTitleLayout->addWidget(m_btnExpand);
        hTitleLayout->addWidget(title);
        hTitleLayout->addStretch();
        hTitleLayout->addWidget(m_toolBox);
        vLayout->addWidget(titleWidget);
        connect(m_btnExpand, &QToolButton::clicked, this, &ItemGroup::onExpand);
    }

    m_contentWidget = new QWidget(parent);
    m_contentWidget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    QVBoxLayout *vContentLayout = new QVBoxLayout(m_contentWidget);
    vContentLayout->setContentsMargins(9,0,9,0);
    vContentLayout->setSpacing(5);
    vLayout->addWidget(m_contentWidget);
}

ItemGroup::~ItemGroup()
{
}

QWidget* ItemGroup::getContent()
{
    return m_contentWidget;
}

void ItemGroup::createRow(QString & name, QString value, QString regx)
{
    QWidget *widget = new QWidget(m_contentWidget);
    widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    if (!name.isEmpty())
    {
        QLabel *nameLabel = new QLabel(widget);
        nameLabel->setText(name);
        nameLabel->setFixedWidth(FIXEDWIDTH);
        hLayout->addWidget(nameLabel);
    }
    QLineEdit *edit = new QLineEdit(widget);
    edit->setText(value);
    hLayout->addWidget(edit);

    m_contentWidget->layout()->addWidget(widget);
}

void ItemGroup::createRow(QString & name, QString value, int min, int max)
{
    QWidget *widget = new QWidget(m_contentWidget);
    widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    if (!name.isEmpty())
    {
        QLabel *nameLabel = new QLabel(widget);
        nameLabel->setText(name);
        nameLabel->setFixedWidth(FIXEDWIDTH);
        hLayout->addWidget(nameLabel);
    }
    QSpinBox *edit = new QSpinBox(widget);
    edit->setRange(min, max);
    edit->setValue(value.toInt());
    hLayout->addWidget(edit);

    m_contentWidget->layout()->addWidget(widget);
}

void ItemGroup::createRow(QString & name, QString value, double min, double max)
{
    QWidget *widget = new QWidget(m_contentWidget);
    widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    if (!name.isEmpty())
    {
        QLabel *nameLabel = new QLabel(widget);
        nameLabel->setText(name);
        nameLabel->setFixedWidth(FIXEDWIDTH);
        hLayout->addWidget(nameLabel);
    }
    QDoubleSpinBox *edit = new QDoubleSpinBox(widget);
    edit->setValue(value.toDouble());
    edit->setRange(min, max);
    hLayout->addWidget(edit);

    m_contentWidget->layout()->addWidget(widget);
}

void ItemGroup::createRow(QString & name, QString value, QStringList values)
{
    QWidget *widget = new QWidget(m_contentWidget);
    widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    if (!name.isEmpty())
    {
        QLabel *nameLabel = new QLabel(widget);
        nameLabel->setText(name);
        nameLabel->setFixedWidth(FIXEDWIDTH);
        hLayout->addWidget(nameLabel);
    }
    QComboBox *edit = new QComboBox(widget);
    edit->addItems(values);
    edit->setEditText(value);
    hLayout->addWidget(edit);

    m_contentWidget->layout()->addWidget(widget);
}

void ItemGroup::setAction(QAction * action)
{
    if (m_isHideTitle)
    {
        m_toolBox->addAction(action);
    }
}

void ItemGroup::onExpand(bool checked)
{
    checked ? m_btnExpand->setIcon(QIcon(":/Resources/itemClose.png")) : m_btnExpand->setIcon(QIcon(":/Resources/itemExpansion.png"));
    m_contentWidget->setHidden(checked);
}

