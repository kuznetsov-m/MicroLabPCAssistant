#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
	monitor = new Monitor(this);
	monitor->setDirectory("C:\\Users\\User\\Program Files(x86)\\Agilent\\MicroLabPC\\results");
	monitor->setExtention("asp");
	connect(monitor, &Monitor::foundNewFile, this, &MainWidget::foundFileSlot);

	classifier = new Classifier(this);
	classifier->setPath("python ExpressSystems.py");
	connect(classifier, &Classifier::classified, this, &MainWidget::classifiedSlot);

	auto vl = new QVBoxLayout(this);
	vl->setMargin(0);

	vl->addLayout(createMonitorLayout());

	auto flo = new QFormLayout();
	vl->addLayout(flo);

	lbStatus = new QLabel("");
	flo->addRow("Статус:", lbStatus);

	auto hl = new QHBoxLayout();
	hl->setMargin(0);
	vl->addLayout(hl);

	auto vs = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	hl->addItem(vs);

	reportWidget = new ReportWidget(this);
	connect(reportWidget, &ReportWidget::writeResult, this, &MainWidget::writeAndNextSampleSlot);
	connect(reportWidget, &ReportWidget::writeResultAndNextSample, this, &MainWidget::writeAndNextSampleSlot);
	hl->addWidget(reportWidget);

	writer = new Writer(this);
	writer->setReseachFileSourceDirectory(monitor->getDirectory());

	exportData = new ExportData(this);
	exportDataWidget = new ExportDataWidget(exportData, this);
	vl->addWidget(exportDataWidget);

	connect(&uiTimer, &QTimer::timeout, this, &MainWidget::tikTimerSlot);
	const int UI_INTERVAL = 100;
	uiTimer.setInterval(UI_INTERVAL);

	tikTimerSlot();

	uiTimer.start();

	startClickedSlot();
}

MainWidget::~MainWidget()
{
	uiTimer.stop();

	if (monitor != nullptr)
	{
		if (monitor->isStarted())
			monitor->stop();
		delete monitor;
		monitor = nullptr;
	}

	if (classifier != nullptr)
	{
		delete classifier;
		classifier = nullptr;
	}

	if (writer != nullptr)
	{
		delete writer;
		writer = nullptr;
	}

	if (exportData != nullptr)
	{
		delete exportData;
		exportData = nullptr;
	}

	if (exportDataWidget != nullptr)
	{
		delete exportDataWidget;
		exportDataWidget = nullptr;
	}

	if (reseachData != nullptr)
	{
		delete reseachData;
		reseachData = nullptr;
	}
}

QString MainWidget::statusToString(const MainWidget::Status &status)
{
	switch (status)
	{
		case MainWidget::Status::idle:
			return "Ожидание запуска монитора...";

		case MainWidget::Status::waitingMonitorSignal:
			return "Ожидание нового измерения...";

		case MainWidget::Status::waitingClassifierSignal:
			return "Ожидание результатов работы классификатора...";

		case MainWidget::Status::waitingReport:
			return "Заполнение полей для измерения";

		default:
			return "???";
	}
}

void MainWidget::startClickedSlot()
{
	monitor->updateFiles();
	monitor->start();

	status = MainWidget::Status::waitingMonitorSignal;
}

void MainWidget::stopClickedSlot()
{
	monitor->stop();
}

void MainWidget::tikTimerSlot()
{
	bool isStarted = monitor->isStarted();

	if(isStarted == false)
		status = MainWidget::Status::idle;

	pbMonitorStart->setEnabled(!isStarted);
	pbMonitorStop->setEnabled(isStarted);

	lbStatus->setText(statusToString(status));

	if(status == MainWidget::Status::idle ||
	   status == MainWidget::Status::waitingMonitorSignal ||
	   status == MainWidget::Status::waitingClassifierSignal)
	{
		if (reportWidget->isVisible())
			reportWidget->setVisible(false);
	}
	else if(status == MainWidget::Status::waitingReport)
	{
		if (!reportWidget->isVisible())
			reportWidget->setVisible(true);

	}
}

void MainWidget::foundFileSlot(const QString &path)
{
	status = MainWidget::Status::waitingClassifierSignal;
	reseachData = new ReseachData();
	QFile scanResultFile(path);
	QFileInfo fileInfo(scanResultFile.fileName());
	reseachData->scanResultFileName = fileInfo.fileName();
	classifier->start({path});
}

void MainWidget::classifiedSlot(const Classifier::ResultType &resultType)
{
	reseachData->scanResult = Classifier::resultTypeToString(resultType);

	reportWidget->setReseachData(reseachData);
	reportWidget->update();


	status = MainWidget::Status::waitingReport;
}

void MainWidget::writeAndNextSampleSlot()
{
	writer->writeSlot(reseachData);

	status = MainWidget::Status::waitingMonitorSignal;
}

QVBoxLayout *MainWidget::createMonitorLayout()
{
	auto vl = new QVBoxLayout();

	auto flo = new QFormLayout();
	vl->addLayout(flo);

	flo->addRow("Папка для мониторинга:", new QLabel(monitor->getDirectory()));

	auto hl = new QHBoxLayout();
	vl->addLayout(hl);

	hl->addWidget(new QLabel("Мониторинг:"));

	pbMonitorStart = new QPushButton("Старт");
	connect(pbMonitorStart, &QPushButton::clicked, this, &MainWidget::startClickedSlot);
	hl->addWidget(pbMonitorStart);

	pbMonitorStop = new QPushButton("Стоп");
	connect(pbMonitorStop, &QPushButton::clicked, this, &MainWidget::stopClickedSlot);
	hl->addWidget(pbMonitorStop);

	return vl;
}
