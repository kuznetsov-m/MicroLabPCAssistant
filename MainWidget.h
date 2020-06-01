#pragma once

#include <QWidget>
#include <QTimer>
#include <QPushButton>

#include "Monitor.h"
#include "Classifier.h"
#include "ClassifierWidget.h"
#include "ReportWidget.h"
#include "ReseachData.h"
#include "Writer.h"
#include "ExportData.h"
#include "ExportDataWidget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget *parent = nullptr);
	~MainWidget();

	enum Status
	{
		idle,
		waitingMonitorSignal,
		waitingClassifierSignal,
		waitingReport
	};
	Q_ENUM(Status)

	static QString statusToString(const MainWidget::Status &status);

signals:

public slots:
	void startClickedSlot();
	void stopClickedSlot();

private slots:
	void tikTimerSlot();
	void foundFileSlot(const QString &path);
	void classifiedSlot(const Classifier::ResultType &resultType);
	void writeAndNextSampleSlot();

private:
	Monitor *monitor = nullptr;

	Classifier *classifier = nullptr;
	ClassifierWidget *classifierWidget = nullptr;

	QTimer uiTimer;

	QVBoxLayout *createMonitorLayout();

	QPushButton *pbMonitorStart;
	QPushButton *pbMonitorStop;

	QLabel *lbStatus = nullptr;

	ReportWidget *reportWidget = nullptr;

	Status status = Status::idle;

	Writer *writer = nullptr;

	ReseachData *reseachData = nullptr;

	ExportData *exportData = nullptr;
	ExportDataWidget *exportDataWidget = nullptr;
};
