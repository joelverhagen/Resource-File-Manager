#include "TableModel.h"

TableModel::TableModel(QStringList modelHeaderData, bool editable, QObject * parent) : QAbstractTableModel(parent)
{
	this->editable = editable;
	this->modelHeaderData = modelHeaderData;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
	return modelData.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
	return modelHeaderData.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}

	if(index.row() >= modelData.size() || index.row() < 0)
	{
		return QVariant();
	}

	if(index.column() >= modelHeaderData.size() || index.column() < 0)
	{
		return QVariant();
	}

	if(role == Qt::DisplayRole)
	{
		QList<QString> row = modelData[index.row()];

		return row[index.column()];
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
	{
		return QVariant();
	}

	if(orientation == Qt::Horizontal)
	{
		if(section >= columnCount() || section < 0)
		{
			return QVariant();
		}

		return modelHeaderData[section];
	}

	return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(index.isValid() && role == Qt::EditRole)
	{
		QString stringValue = value.toString();

		// make sure the new entry name is at least one character
		if(stringValue.size() == 0)
		{
			return false;
		}

		// make sure the new entry name is unique
		for(int i = 0; i < rowCount(); i++)
		{
			if(i == index.row())
			{
				continue;
			}

			QStringList row = modelData[i];
			if(stringValue == row[index.column()])
			{
				return false;
			}
		}

		QStringList row = modelData[index.row()];
		row[index.column()] = stringValue;

		modelData[index.row()] = row;

		emit(dataChanged(index, index));

		return true;
	}

	return false;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int row = 0; row < rows; row++) {
		QStringList row;
		for(int column = 0; column < columnCount(); column++)
		{
			row.append(QString(" "));
		}

		modelData.insert(position, row);
	}

	endInsertRows();

	return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for(int row = 0; row < rows; ++row)
	{
		modelData.removeAt(position);
	}

	endRemoveRows();

	return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
	if(index.column() == 0)
	{
		if(editable)
		{
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		}
		else
		{
			return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		}

	}
	return Qt::ItemIsEnabled;
}

bool TableModel::appendRow(QStringList values)
{
	if(values.size() != columnCount())
	{
		return false;
	}

	for(int i = 0; i < rowCount(); i++)
	{
		if(values[0] == data(index(i, 0)).toString())
		{
			return false;
		}
	}

	insertRow(rowCount());

	return setRowValues(rowCount() - 1, values);
}

bool TableModel::swapRows(int source, int destination)
{
	if(!isValidRow(source) || !isValidRow(destination))
	{
		return false;
	}

	if(source == destination)
	{
		return true;
	}

	QStringList sourceValues = rowValues(source);
	QStringList destinationValues = rowValues(destination);

	setRowValues(destination, sourceValues);
	emit(dataChanged(index(destination, 0), index(destination, columnCount() - 1)));

	setRowValues(source, destinationValues);
	emit(dataChanged(index(source, 0), index(source, columnCount() - 1)));

	return true;
}

bool TableModel::isValidRow(int row)
{
	return row >= 0 && row < rowCount();
}

bool TableModel::isValidColumn(int column)
{
	return column >= 0 && column < columnCount();
}

QStringList TableModel::rowValues(int row)
{
	if(isValidRow(row))
	{
		return modelData[row];
	}
	return QStringList();
}

bool TableModel::setRowValues(int row, QStringList values)
{
	if(isValidRow(row))
	{
		modelData[row] = values;
		return true;
	}

	return false;
}

void TableModel::clear()
{
	int currentRowCount = rowCount();
	if(currentRowCount > 0)
	{
		removeRows(0, currentRowCount);
	}
}
