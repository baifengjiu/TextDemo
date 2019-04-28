#ifndef fswExterior_H
#define fswExterior_H

#include <QWidget>

// ժҪ: 
//     �ޱ߿����widget�����ࡣ
class fswExterior : public QObject
{
Q_OBJECT
public:
	explicit fswExterior(QWidget* parent = 0);

	void setExterior(QWidget* widget, bool hasFrame, int shadow, bool resize);

	void doPaintShadow(QPaintEvent*);
	bool doNativeEvent(const QByteArray& eventType, void* msg, long* result);

	int shadow() const { return m_shadow; }

	void addMoveBar(QWidget* w, bool isCaption = false);

private:
	QWidget* m_widget = nullptr;
	bool m_hasFrame = true;
	int m_shadow = 0;
	bool m_resize = false;

	QList<QObject*> m_moveBars;
	QList<QObject*> m_captions;
	QList<QObject*> m_sysMenus;
};

#endif
