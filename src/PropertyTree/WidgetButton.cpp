#include "WidgetButton.h"

#include <QHBoxLayout>

WidgetButton::WidgetButton(Positon pos, QWidget *parent)
	: QWidget(parent), m_position(pos)
{
	QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
	m_addBton = new QPushButton(this);
    m_delBton = new QPushButton(this);
	auto spacer = new QSpacerItem(this->width(), this->height(), QSizePolicy::Expanding);

	if (pos == Left)
	{
		layout->addWidget(m_addBton);
        layout->addWidget(m_delBton);
		layout->addSpacerItem(spacer);
	}
	else
	{
		layout->addSpacerItem(spacer);
        layout->addWidget(m_delBton);
		layout->addWidget(m_addBton);		
	}
	m_addBton->setObjectName("AddButton");
    m_addBton->setObjectName("DelButton");

	this->setLayout(layout);
}

WidgetButton::WidgetButton(const QString &text1, const QString &text2, Positon pos, QWidget *parent)
	: QWidget(parent), m_position(pos)
{
	QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
	m_addBton = new QPushButton(this);
    m_addBton->setText(text1);
    m_delBton = new QPushButton(this);
    m_addBton->setText(text2);
	auto spacer = new QSpacerItem(this->width(), this->height(), QSizePolicy::Expanding);

	if (pos == Left)
	{
        layout->addWidget(m_addBton);
        layout->addWidget(m_delBton);
		layout->addSpacerItem(spacer);
	}
	else
	{
		layout->addSpacerItem(spacer);
        layout->addWidget(m_delBton);
        layout->addWidget(m_addBton);
	}
    m_addBton->setObjectName("AddButton");
    m_addBton->setObjectName("DelButton");

	this->setLayout(layout);
}

WidgetButton::~WidgetButton()
{
}
void WidgetButton::setText(const QString &addText, const QString &delText)
{
	m_addBton->setText(addText);
    m_delBton->setText(delText);
}

void WidgetButton::setIcon(const QIcon &addIcon, const QIcon &delIcon)
{
	m_addBton->setIcon(addIcon);
    m_delBton->setIcon(delIcon);
}

void WidgetButton::setToolTip(const QString &addTip, const QString &delTip)
{
	m_addBton->setToolTip(addTip);
    m_delBton->setToolTip(delTip);
}

WidgetButton::Positon WidgetButton::position() const
{
	return m_position;
}

void WidgetButton::setPositon(const Positon &pos)
{
	QHBoxLayout *layout = static_cast<QHBoxLayout*>(this->layout());
	if (m_position != pos)
	{
		auto spacer = new QSpacerItem(this->width(), this->height(), QSizePolicy::Expanding);
		switch (m_position)
		{
		case WidgetButton::Left:
		{		
			layout->takeAt(1);
			layout->insertSpacerItem(0, spacer);
		}
		break;
		case WidgetButton::Right:
		{
			layout->takeAt(0);
			layout->addSpacerItem(spacer);
		}
		break;
		default: break;
		}
		m_position = pos;
	}
}

QPushButton* WidgetButton::getAddBton() const
{
	return m_addBton;
}

QPushButton * WidgetButton::getDelBton() const
{
    return m_delBton;
}

