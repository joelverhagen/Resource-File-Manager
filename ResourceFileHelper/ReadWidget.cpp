#include "ReadWidget.h"

ReadWidget::ReadWidget(QWidget * parent) : QWidget(parent)
{
	// resource file reader
	reader = 0;

	// table model
	QStringList modelHeaderData;
	modelHeaderData << "Index" << "File Name" << "File Size";
	tableModel = new TableModel(modelHeaderData, false, this);

	// entire page layout
    pageLayout = new QVBoxLayout(this);

	// layout for the load controls
    loadLayout = new QHBoxLayout();
    pageLayout->addLayout(loadLayout);

	// line edit for file path
    loadLocation = new QLineEdit();
	loadLocation->setReadOnly(true);
    loadLayout->addWidget(loadLocation);

	// button to load open the file selection dialog
    loadButton = new QPushButton();
    loadButton->setText("Load Resource File");
    loadLayout->addWidget(loadButton);

	// layout to hold the table and controls
    tableLayout = new QHBoxLayout();
    pageLayout->addLayout(tableLayout);

	// table view
	tableView = new TableView();
	tableView->setModel(tableModel);
    tableLayout->addWidget(tableView);

	// layout to hold the table controls
    tableControlsLayout = new QVBoxLayout();
    tableLayout->addLayout(tableControlsLayout);

    tableControlsLayout->addStretch();

	// export button
    exportButton = new QPushButton();
    exportButton->setText("Export");
    tableControlsLayout->addWidget(exportButton);

    tableControlsLayout->addStretch();

	// connect actions
	connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
	connect(exportButton, SIGNAL(clicked()), this, SLOT(exportFile()));
}

ReadWidget::~ReadWidget()
{
	if(reader != 0)
	{
		delete reader;
	}
}

void ReadWidget::loadResourceFile()
{
	QFileInfo fileInfo(loadLocation->text());

	if(loadLocation->text().size() == 0 || !fileInfo.exists())
	{
		QMessageBox messageBox;
		messageBox.setText(QString(tr("You must select a resource file.")));
		messageBox.exec();

		return;
	}

	tableModel->clear();

	if(reader != NULL)
	{
		delete reader;
	}

	reader = new ResourceFileReader(loadLocation->text().toStdString());
	reader->read();

	vector<string> entryNames = reader->getEntryNames();

	for(unsigned int i = 0; i < entryNames.size(); i++)
	{
		QStringList values;
		values << QString::number(i) << QString(entryNames[i].c_str()) << QString::number(reader->getEntryFileSize(entryNames[i]));

		tableModel->appendRow(values);
	}

	tableView->resizeColumnsToContents();
}

void ReadWidget::handleDrag(QDragEnterEvent * event)
{
	if (event->mimeData()->hasUrls())
	{
		event->acceptProposedAction();
	}
}

void ReadWidget::handleDrop(QDropEvent * event)
{
	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> urlList = event->mimeData()->urls();
		if(urlList.size() > 0)
		{
			loadLocation->setText(urlList[0].toLocalFile());

			loadResourceFile();
		}
	}
}

void ReadWidget::dragEnterEvent(QDragEnterEvent * event)
{
	handleDrag(event);
}

void ReadWidget::dropEvent(QDropEvent * event)
{
	handleDrop(event);
}

void ReadWidget::load()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Select a resource file."), ".", tr("Resource files (*.dat);;All files (*)"));

	if(fileName.size() == 0)
	{
		return;
	}

	loadLocation->setText(fileName);

	loadResourceFile();
}

void ReadWidget::exportFile()
{
	if(reader == 0)
	{
		QMessageBox messageBox;
		messageBox.setText(QString(tr("You must load a resource file.")));
		messageBox.exec();

		return;
	}

	QList<int> rows = tableView->getSelectedRows();
	if(rows.size() == 0)
	{
		QMessageBox messageBox;
		messageBox.setText(QString(tr("You must select at least one file to export.")));
		messageBox.exec();

		return;
	}

	QStringList names;
	for(int i = 0; i < rows.size(); i++)
	{
		names << tableModel->data(tableModel->index(rows[i], 1)).toString();
	}

	QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Select a destination directory."), ".", 0);

	if(directoryPath.size() == 0) // the user hit cancel
	{
		return;
	}

	if(!directoryPath.endsWith('/') && !directoryPath.endsWith('\\'))
	{
		directoryPath.append('/');
	}

	for(int i = 0; i < names.size(); i++)
	{
		string name = names[i].toStdString();
		QString path = directoryPath + names[i];

		QFile destinationFile(path);

		if(destinationFile.exists())
		{
			QMessageBox replaceConfirm;
			replaceConfirm.setText("A file \""+destinationFile.fileName()+"\" already exists.");
			replaceConfirm.setInformativeText("Do you want to replace this file?");
			replaceConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			replaceConfirm.setDefaultButton(QMessageBox::Yes);
			if(replaceConfirm.exec() == QMessageBox::No)
			{
				continue;
			}
		}

		char * fileDataRaw = reader->getFile(name);

		destinationFile.open(QIODevice::WriteOnly);
		QDataStream output(&destinationFile);
		output.writeRawData(fileDataRaw, reader->getEntryFileSize(name));
		destinationFile.close();

		delete fileDataRaw;
	}
}
