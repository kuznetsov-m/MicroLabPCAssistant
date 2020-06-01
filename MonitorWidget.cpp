#include "MonitorWidget.h"

MonitorWidget::MonitorWidget(Monitor *_monitor, QWidget *parent) :
	QWidget(parent), monitor(_monitor)
{
	auto vl = new QVBoxLayout(this);

	auto lb = new QLabel("MonitorWidget");
	vl->addWidget(lb);

	leDirectory = new QLineEdit();
	leDirectory->setText(monitor->getDirectory());
	vl->addWidget(leDirectory);

	auto pbSetDirectory = new QPushButton("Задать директорию");
	connect(pbSetDirectory, &QPushButton::clicked, this, [this]
	{
		monitor->setDirectory(leDirectory->text());
	});
	vl->addWidget(pbSetDirectory);

	chb = new QCheckBox("Выводить уведомление при обнаружении нового файла");
	chb->setChecked(false);
	vl->addWidget(chb);

	auto pbStart = new QPushButton("Старт");
	connect(pbStart, &QPushButton::clicked, this, &MonitorWidget::startClickedSlot);
	vl->addWidget(pbStart);

	auto pbStop = new QPushButton("Стоп");
	connect(pbStop, &QPushButton::clicked, this, &MonitorWidget::stopClickedSlot);
	vl->addWidget(pbStop);

	connect(monitor, &Monitor::foundNewFile, this, [this](const QString fileName)
	{
		if (chb->isChecked())
			QMessageBox::information(this, "Уведомление", "Обнаружен новый файл: " + fileName);
	});
}

void MonitorWidget::startClickedSlot()
{
	monitor->updateFiles();
	monitor->start();
}

void MonitorWidget::stopClickedSlot()
{
	monitor->stop();
}
