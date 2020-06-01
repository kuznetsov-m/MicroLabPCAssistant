#include "TesterWidget.h"

TesterWidget::TesterWidget(QWidget *parent) : QWidget(parent)
{
	auto vl = new QVBoxLayout(this);

	monitor = new Monitor(this);
	monitorWidget = new MonitorWidget(monitor, this);
	vl->addWidget(monitorWidget);

	classifier = new Classifier(this);
	classifierWidget = new ClassifierWidget(classifier, this);
	vl->addWidget(classifierWidget);

	connect(monitor, &Monitor::foundNewFile, this, [this](const QString &path)
	{
		classifierWidget->setArguments(path);
	});
}

TesterWidget::~TesterWidget()
{
	if (monitor != nullptr)
	{
		if (monitor->isStarted())
			monitor->stop();
		delete monitor;
	}

	if (classifier != nullptr)
	{
		delete classifier;
	}
}
