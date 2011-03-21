#include "AboutWidget.h"

AboutWidget::AboutWidget(QWidget * parent) : QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);

	QString version;
	version.sprintf("%1.1f", VERSION);

    label = new QLabel();
	label->setOpenExternalLinks(true);
	label->setWordWrap(true);
	label->setText("<p>This program was written by me, Joel Verhagen, as a tool to manage my custom resource files. For more information about this piece of software and my resource file format, check out my <a href=\"http://www.joelverhagen.com\">website</a>.</p><p>Resource File Helper was written in C++, using Qt 4.7.2. This is version " + version + ".</p><p>Credit for the icon goes to the artist, <a href=\"http://www.a2591.com/2009/09/container-icon-set-3-cargo-boxes.html\">A2591.com</a>.");
    pageLayout->addWidget(label);

	pageLayout->addStretch();
}
