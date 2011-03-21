#ifndef READWIDGET_H
#define READWIDGET_H

#include <QWidget>

#include "TableModel.h"

#include "ResourceFile.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QUrl>
#include "TableView.h"
#include <QMessageBox>
#include <vector>
#include <string>
#include <QList>

#include <QDebug>

class ReadWidget : public QWidget
{
    Q_OBJECT

public:
    ReadWidget(QWidget *parent = 0);
	~ReadWidget();

	void handleDrag(QDragEnterEvent * event);
	void handleDrop(QDropEvent * event);

protected:
	void dragEnterEvent(QDragEnterEvent * event);
	void dropEvent(QDropEvent * event);

private:
	void loadResourceFile();

	ResourceFileReader * reader;

	TableModel * tableModel;

    QVBoxLayout * pageLayout;
    QHBoxLayout * loadLayout;
    QLineEdit * loadLocation;
    QPushButton * loadButton;
    QHBoxLayout * tableLayout;
	TableView * tableView;
    QVBoxLayout * tableControlsLayout;
	QPushButton * exportButton;

private slots:
	void load();
	void exportFile();
};

#endif
