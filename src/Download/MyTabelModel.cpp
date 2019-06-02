#include "MyTabelModel.h"

MyTabelModel::MyTabelModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

MyTabelModel::~MyTabelModel()
{
}

int MyTabelModel::rowCount(const QModelIndex & parent) const
{
	return m_datas.size();
}

int MyTabelModel::columnCount(const QModelIndex & parent) const
{
	return 5;
}

QVariant MyTabelModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	int row = index.row();
	int col = index.column();
	QVariant var;
	switch (role)
	{
		case Qt::DisplayRole: 
			var = m_datas[row][col]; 
			break;
		case Qt::TextAlignmentRole: 
			var = QVariant(Qt::AlignLeft | Qt::AlignVCenter); 
			break;
	}
	return var;
}

bool MyTabelModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid())
	{
		return false;
	}

	int row = index.row();
	int col = index.column();
	QVariant var;
	switch (role)
	{
		case Qt::EditRole:
			m_datas[row][col] = value.toString();
			return true;
			break;
	}
	return false;
}

QVariant MyTabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	QVariant var;
	if(role == Qt::DisplayRole && orientation == Qt::Orientation::Horizontal)
	{
		switch (section)
		{
			case 0: var = "File Name"; break;
			case 1: var = "Size"; break;
			case 2: var = "Status"; break;
			case 3: var = "Transfer rate"; break;
			case 4: var = "Time left"; break;
		}
	}
	return var;
}

bool MyTabelModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row + count - 1);
	endInsertRows();
	return true;
}

bool MyTabelModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for (int i = row+count-1; i >= row; i--)
	{
		m_datas.removeAt(i);
	}
	endRemoveRows();
	return false;
}

void MyTabelModel::addRowData(QStringList data)
{
	beginInsertRows(QModelIndex(), rowCount(), 1);
	m_datas.append(data);
	endInsertRows();
}
