#pragma once

#include <QWidget>

#include "Monitor.h"
#include "MonitorWidget.h"
#include "Classifier.h"
#include "ClassifierWidget.h"

class TesterWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TesterWidget(QWidget *parent = nullptr);
	~TesterWidget();

signals:

public slots:

private:
	Monitor *monitor = nullptr;
	MonitorWidget *monitorWidget = nullptr;

	Classifier *classifier = nullptr;
	ClassifierWidget *classifierWidget = nullptr;
};
