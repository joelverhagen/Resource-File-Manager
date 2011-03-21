#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>

#include "TableModel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "TableView.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QUrl>
#include "ResourceFile.h"
#include <QMessageBox>

class WriteWidget : public QWidget
{
    Q_OBJECT

public:
    WriteWidget(QWidget * parent = 0);

	void handleDrag(QDragEnterEvent * event);
	void handleDrop(QDropEvent * event);

protected:
	void dragEnterEvent(QDragEnterEvent * event);
	void dropEvent(QDropEvent * event);

private:
	void addFile(QString filePath);

	TableModel * tableModel;

    QVBoxLayout * pageLayout;
    QHBoxLayout * tableLayout;
	TableView * tableView;
    QVBoxLayout * tableControlsLayout;
	QPushButton * addButton;
    QPushButton * deleteButton;
    QPushButton * moveUpButton;
    QPushButton * moveDownButton;
    QHBoxLayout * saveLayout;
	QLineEdit * saveLocation;
    QPushButton * saveButton;

private slots:
	void addFiles();
	void deleteSelected();
	void moveSelectedUp();
	void moveSelectedDown();
	void save();
};

#endif // WRITEWIDGET_H
