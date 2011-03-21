#include "TableView.h"

TableView::TableView(QWidget * parent) : QTableView(parent)
{
	QHeaderView * header = verticalHeader();
	header->setHidden(true);

	header = horizontalHeader();
	header->setClickable(false);
	header->setDragEnabled(false);
	header->setResizeMode(QHeaderView::Fixed);
}

QList<int> TableView::getSelectedRows()
{
	QItemSelectionModel * currentSelection = selectionModel();

	QModelIndexList indexList = currentSelection->selectedIndexes();
	QList<int> rows;
	for(int i = 0; i < indexList.size(); i++)
	{
		rows << indexList[i].row();
	}

	return rows;
}

bool TableView::setSelectedRows(QList<int> rows)
{
	QItemSelectionModel * selection = selectionModel();
	selection->clear();

	TableModel * currentModel = static_cast<TableModel *>(model());

	QItemSelection totalSelection;
	for(int i = 0; i < rows.size(); i++)
	{
		if(!currentModel->isValidRow(rows[i]))
		{
			continue;
		}

		QModelIndex index = model()->index(rows[i], 0);
		QItemSelection currentSelection(index, index);
		totalSelection.merge(currentSelection, QItemSelectionModel::SelectCurrent);
	}
	selection->select(totalSelection, QItemSelectionModel::ClearAndSelect);
	setSelectionModel(selection);

	return true;
}

bool TableView::deleteSelected()
{
	QList<int> rows = getSelectedRows();
	qSort(rows.begin(), rows.end(), qGreater<int>());

	for(int i = 0; i < rows.size(); i++)
	{
		model()->removeRow(rows[i]);
	}

	resizeColumnsToContents();

	return true;
}

bool TableView::moveSelectedUp()
{
	QList<int> rows = getSelectedRows();
	qSort(rows.begin(), rows.end(), qLess<int>());

	TableModel * currentModel = static_cast<TableModel *>(model());

	for(int i = 0; i < rows.size(); i++)
	{
		if(rows[i] == 0)
		{
			break;
		}

		currentModel->swapRows(rows[i], rows[i] - 1);
		rows[i] -= 1;
	}

	setSelectedRows(rows);

	return true;
}

bool TableView::moveSelectedDown()
{
	QList<int> rows = getSelectedRows();
	qSort(rows.begin(), rows.end(), qGreater<int>());

	TableModel * currentModel = static_cast<TableModel *>(model());

	for(int i = 0; i < rows.size(); i++)
	{
		if(rows[i] == currentModel->rowCount() - 1)
		{
			break;
		}

		currentModel->swapRows(rows[i], rows[i] + 1);
		rows[i] += 1;
	}

	setSelectedRows(rows);

	return true;
}
