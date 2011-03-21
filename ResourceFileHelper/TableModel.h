#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

#include <QStringList>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
	TableModel(QStringList modelHeaderData, bool editable, QObject * parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex &index) const;

	bool appendRow(QStringList values);
	bool swapRows(int source, int destination);

	bool isValidRow(int row);
	bool isValidColumn(int column);

	QStringList rowValues(int row);
	bool setRowValues(int row, QStringList values);

	void clear();

private:
	QList<QStringList> modelData;
	QStringList modelHeaderData;
	bool editable;
};

#endif // TABLEMODEL_H
