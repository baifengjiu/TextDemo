#pragma once

#include <QAbstractTableModel>

class MyTabelModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	MyTabelModel(QObject *parent);
	~MyTabelModel();

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

	void addRowData(QStringList data);

private:
	QList<QStringList> m_datas;
};
