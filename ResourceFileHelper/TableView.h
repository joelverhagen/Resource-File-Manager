#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

#include <QList>
#include <QHeaderView>
#include "TableModel.h"

class TableView : public QTableView
{
    Q_OBJECT

public:
	TableView(QWidget * parent = 0);

	QList<int> getSelectedRows();
	bool setSelectedRows(QList<int> rows);

	bool deleteSelected();
	bool moveSelectedUp();
	bool moveSelectedDown();
};

#endif // TABLEVIEW_H
