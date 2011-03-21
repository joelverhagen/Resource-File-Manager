#include "MainWindow.h"

MainWindow::MainWindow(QWidget * parent) : QTabWidget(parent)
{
    setWindowTitle("Resource File Helper");

    resize(600, 400);

    readTab = new ReadWidget();
    writeTab = new WriteWidget();
    aboutTab = new AboutWidget();

    addTab(readTab, "Read");
    addTab(writeTab, "Write");
    addTab(aboutTab, "About");
}

void MainWindow::dragEnterEvent(QDragEnterEvent * event)
{
	if(currentWidget() == readTab)
	{
		readTab->handleDrag(event);
	}
	else if (currentWidget() == writeTab)
	{
		writeTab->handleDrag(event);
	}
}

void MainWindow::dropEvent(QDropEvent * event)
{
	if(currentWidget() == readTab)
	{
		readTab->handleDrop(event);
	}
	else if (currentWidget() == writeTab)
	{
		writeTab->handleDrop(event);
	}
}
