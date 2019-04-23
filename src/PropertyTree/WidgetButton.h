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
	// ��ť�ϵ��ı�
    void setText(const QString &addText, const QString &delText);

	// ��ť�ϵ�ͼ��
	void setIcon(const QIcon &addIcon, const QIcon &delIcon);

	// ��ť�ϵ��ı�
	void setToolTip(const QString &addTip, const QString &delTip);

	// ��ťλ��
	Positon position() const;
	void setPositon(const Positon &pos);

	// ��ȡ��ť����
	QPushButton* getAddBton() const;
    QPushButton* getDelBton() const;
    
signals:
	/*
	* @abstract ����¼�
	* @return 
	*/
	void clicked();

private:
	QPushButton *m_addBton = nullptr;
    QPushButton *m_delBton = nullptr;
	Positon m_position = Left;
	double  m_scale = 0.0;
};
