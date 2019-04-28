#include "fswExterior.h"

#include <QMainWindow>
#include <QLayout>
#include <QPainter>
#include <QDebug>

#if defined(Q_OS_WIN)
#include <qt_windows.h>
#include <windowsx.h>
#endif

fswExterior::fswExterior(QWidget* parent)
	: QObject(parent)
{
}

void fswExterior::setExterior(QWidget* widget, bool hasFrame, int shadow, bool resize)
{
	m_widget = widget;
	m_hasFrame = hasFrame;
	m_shadow = shadow;
	m_resize = resize;

	if (m_widget != nullptr)
	{
		if (resize)
		{
			widget->setParent(nullptr, Qt::FramelessWindowHint);
		}
		else
		{
			widget->setWindowFlags(m_widget->windowFlags() | Qt::FramelessWindowHint);
		}
		if (!hasFrame)
		{
			m_widget->setAttribute(Qt::WA_TranslucentBackground);
		}
		if (m_shadow > 0)
		{
			QMainWindow* mw = qobject_cast<QMainWindow*>(m_widget);
			if (mw != nullptr)
			{
				mw->centralWidget()->layout()->setMargin(m_shadow);
			}
			else
			{
				m_widget->layout()->setMargin(m_shadow);
			}
		}
	}
}

void fswExterior::doPaintShadow(QPaintEvent*)
{

    if (m_widget != nullptr && m_shadow > 0)
    {
        if (m_widget->windowState() & Qt::WindowMaximized)
        {
        }
        else if (m_hasFrame)
        {
            QPainter painter(m_widget);
			QPen pen;
			pen.setStyle(Qt::SolidLine);
			pen.setWidth(m_shadow);
			pen.setBrush(QColor(153, 153, 153));
			pen.setCapStyle(Qt::SquareCap);
			pen.setJoinStyle(Qt::MiterJoin);
			painter.setPen(pen);
			painter.drawRect(0, 0, m_widget->width() - m_shadow, m_widget->height() - m_shadow);
        }
        else
        {
            QPainter painter(m_widget);
            QColor color(0, 0, 0, 250);
            for (int i = 0; i < m_shadow; ++i)
            {
                QPainterPath path;
                path.addRoundedRect(m_shadow - i,
                    m_shadow - i,
                    m_widget->width() - (m_shadow - i) * 2,
                    m_widget->height() - (m_shadow - i) * 2,
                    0, 0, Qt::AbsoluteSize);
                color.setAlpha((m_shadow - i + 1) * (m_shadow - i + 1) / 2 + 1);
                painter.setPen(color);
                painter.drawPath(path);
            }
        }
	}
}

bool fswExterior::doNativeEvent(const QByteArray&, void* msg, long* result)
{
	bool ret = false;
#if defined(Q_OS_WIN)
	if (m_widget != nullptr)
	{
		MSG* message = (MSG*)msg;
		switch (message->message)
		{
		case WM_NCLBUTTONDBLCLK:
			{
				int xPos = GET_X_LPARAM(message->lParam) - m_widget->geometry().x();
				int yPos = GET_Y_LPARAM(message->lParam) - m_widget->geometry().y();
				if (m_captions.indexOf(m_widget->childAt(xPos, yPos)) > -1)
				{
					if (m_widget->isMaximized())
					{
						m_widget->showNormal();
					}
					else
					{
						m_widget->showMaximized();
					}
					ret = true;
				}
			}
			break;

		case WM_NCHITTEST:
			int xPos = GET_X_LPARAM(message->lParam) - m_widget->geometry().x();
			int yPos = GET_Y_LPARAM(message->lParam) - m_widget->geometry().y();
			if (m_sysMenus.indexOf(m_widget->childAt(xPos, yPos)) > -1)
			{
				*result = HTSYSMENU;
				ret = true;
			}
			else if (m_moveBars.indexOf(m_widget->childAt(xPos, yPos)) > -1)
			{
				*result = HTCAPTION;
				ret = true;
			}
			else if (m_resize && (m_widget->windowState() & Qt::WindowMaximized) != Qt::WindowMaximized)
			{
				ret = true;
				if (abs(xPos - m_shadow) <= 5 && abs(yPos - m_shadow) <= 5)
				{
					*result = HTTOPLEFT;
				}
				else if (abs(xPos - m_widget->geometry().width() + m_shadow) <= 5 && abs(yPos - m_shadow) <= 5)
				{
					*result = HTTOPRIGHT;
				}
				else if (abs(xPos - m_shadow) <= 5 && abs(yPos - m_widget->geometry().height() + m_shadow) <= 5)
				{
					*result = HTBOTTOMLEFT;
				}
				else if (abs(xPos - m_widget->geometry().width() + m_shadow) <= 5
					&& abs(yPos - m_widget->geometry().height() + m_shadow) <= 5)
				{
					*result = HTBOTTOMRIGHT;
				}
				else if (abs(xPos - m_shadow) <= 3)
				{
					*result = HTLEFT;
				}
				else if (abs(xPos - m_widget->geometry().width() + m_shadow) <= 3)
				{
					*result = HTRIGHT;
				}
				else if (abs(yPos - m_shadow) <= 3)
				{
					*result = HTTOP;
				}
				else if (abs(yPos - m_widget->geometry().height() + m_shadow) <= 3)
				{
					*result = HTBOTTOM;
				}
				else
				{
					ret = false;
				}
			}
			break;
		}
	}
#else
    Q_UNUSED(msg);
    Q_UNUSED(result);
#endif
	return ret;
}

void fswExterior::addMoveBar(QWidget* w, bool isCaption)
{
	m_moveBars.append(w);
	if (isCaption)
	{
		m_captions.append(w);
	}
}
