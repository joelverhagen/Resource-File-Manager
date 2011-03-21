#include "WriteWidget.h"

WriteWidget::WriteWidget(QWidget * parent) : QWidget(parent)
{
	QStringList modelHeaderData;
	modelHeaderData << "File Name" << "File Path";
	tableModel = new TableModel(modelHeaderData, true, this);

    // entire page layout
    pageLayout = new QVBoxLayout(this);

    // layout for table view and table buttons
    tableLayout = new QHBoxLayout();
    pageLayout->addLayout(tableLayout);

    // add the table view
	tableView = new TableView();
	tableView->setModel(tableModel);
    tableLayout->addWidget(tableView);

    // layout for the table buttons
    tableControlsLayout = new QVBoxLayout();
    tableLayout->addLayout(tableControlsLayout);

    tableControlsLayout->addStretch();

    // add the table buttons
	addButton = new QPushButton();
	addButton->setText("Add Files");
	tableControlsLayout->addWidget(addButton);

    deleteButton = new QPushButton();
    deleteButton->setText("Delete");
    tableControlsLayout->addWidget(deleteButton);

    moveUpButton = new QPushButton();
    moveUpButton->setText("Move Up");
    tableControlsLayout->addWidget(moveUpButton);

    moveDownButton = new QPushButton();
    moveDownButton->setText("Move Down");
    tableControlsLayout->addWidget(moveDownButton);

    tableControlsLayout->addStretch();

    // layout for the save controls
    saveLayout = new QHBoxLayout();
    pageLayout->addLayout(saveLayout);

	// line edit for the save path
    saveLocation = new QLineEdit();
	saveLocation->setReadOnly(true);
    saveLayout->addWidget(saveLocation);

	// save button
    saveButton = new QPushButton();
    saveButton->setText("Save Resource File");
    saveLayout->addWidget(saveButton);

	// connect actions
	connect(addButton, SIGNAL(clicked()), this, SLOT(addFiles()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelected()));
	connect(moveUpButton, SIGNAL(clicked()), this, SLOT(moveSelectedUp()));
	connect(moveDownButton, SIGNAL(clicked()), this, SLOT(moveSelectedDown()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
}

void WriteWidget::handleDrag(QDragEnterEvent * event)
{
	if (event->mimeData()->hasUrls())
	{
		event->acceptProposedAction();
	}
}

void WriteWidget::handleDrop(QDropEvent * event)
{
	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> urlList = event->mimeData()->urls();
		for(int i = 0; i < urlList.size(); i++)
		{
			addFile(urlList[i].toLocalFile());
		}
	}
}

void WriteWidget::dragEnterEvent(QDragEnterEvent * event)
{
	handleDrag(event);
}

void WriteWidget::dropEvent(QDropEvent * event)
{
	handleDrop(event);
}

void WriteWidget::addFile(QString filePath)
{
	QFileInfo fileInfo(filePath);

	if(fileInfo.isFile())
	{
		QStringList values;
		values << fileInfo.fileName();
		values << filePath;

		tableModel->appendRow(values);
		tableView->resizeColumnsToContents();
	}
}

void WriteWidget::addFiles()
{
	QStringList files = QFileDialog::getOpenFileNames(this, tr("Select one or more files to add."), ".", tr("All files (*)"));
	for(int i = 0; i < files.size(); i++)
	{
		addFile(files[i]);
	}
}

void WriteWidget::deleteSelected()
{
	tableView->deleteSelected();
}

void WriteWidget::moveSelectedUp()
{
	tableView->moveSelectedUp();
}

void WriteWidget::moveSelectedDown()
{
	tableView->moveSelectedDown();
}

void WriteWidget::save()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Select a save loction."), ".", tr("Resource files (*.dat);;All files (*)"));

	if(fileName.size() == 0)
	{
		return;
	}

	saveLocation->setText(fileName);

	if(saveLocation->text().size() == 0)
	{
		QMessageBox messageBox;
		messageBox.setText(QString(tr("You must select a save location for the resource file.")));
		messageBox.exec();

		return;
	}

	QFileInfo fileInfo(saveLocation->text());

	if(fileInfo.exists() && !fileInfo.isWritable())
	{
		QMessageBox messageBox;
		messageBox.setText(QString(tr("The save location you chose is not writable.")));
		messageBox.exec();

		return;
	}


	ResourceFileWriter writer(saveLocation->text().toStdString());

	QStringList values;
	for(int i = 0; i < tableModel->rowCount(); i++)
	{
		values = tableModel->rowValues(i);
		writer.addEntry(values[0].toStdString(), values[1].toStdString());
	}

	writer.write();

	QMessageBox messageBox;
	messageBox.setText(QString(tr("Your resource file has been written. The final size of the resource file was ")) + QString::number(fileInfo.size()) + QString(tr(" bytes.")));
	messageBox.exec();
}
