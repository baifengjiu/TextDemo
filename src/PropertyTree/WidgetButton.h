#pragma once

#include <QWidget>
#include <QPushButton>

class WidgetButton : public QWidget
{
	Q_OBJECT

public:
	enum Positon
	{
		Left,
		Right,
	};

	explicit WidgetButton(Positon pos = Left, QWidget*parent = nullptr);
	explicit WidgetButton(const QString &text1, const QString &text2, Positon pos = Left, QWidget *parent = nullptr);
	~WidgetButton();

public:
	// 按钮上的文本
    void setText(const QString &addText, const QString &delText);

	// 按钮上的图标
	void setIcon(const QIcon &addIcon, const QIcon &delIcon);

	// 按钮上的文本
	void setToolTip(const QString &addTip, const QString &delTip);

	// 按钮位置
	Positon position() const;
	void setPositon(const Positon &pos);

	// 获取按钮对象
	QPushButton* getAddBton() const;
    QPushButton* getDelBton() const;
    
signals:
	/*
	* @abstract 点击事件
	* @return 
	*/
	void clicked();

private:
	QPushButton *m_addBton = nullptr;
    QPushButton *m_delBton = nullptr;
	Positon m_position = Left;
	double  m_scale = 0.0;
};
