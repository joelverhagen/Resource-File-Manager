#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QLabel>

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    AboutWidget(QWidget * parent = 0);

private:
    QVBoxLayout * pageLayout;
    QLabel * label;
};

#endif // ABOUTWIDGET_H
