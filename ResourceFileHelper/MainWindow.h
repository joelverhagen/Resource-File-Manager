#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTabWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

#include "ReadWidget.h"
#include "WriteWidget.h"
#include "AboutWidget.h"

class MainWindow : public QTabWidget
{
    Q_OBJECT

public:
	MainWindow(QWidget * parent = 0);

protected:
	void dragEnterEvent(QDragEnterEvent * event);
	void dropEvent(QDropEvent * event);

private:
    ReadWidget * readTab;
    WriteWidget * writeTab;
    AboutWidget * aboutTab;
};

#endif // MAINWINDOW_H
