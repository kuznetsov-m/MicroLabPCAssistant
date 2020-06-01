#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>

#include "Monitor.h"

class MonitorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MonitorWidget(Monitor *_monitor, QWidget *parent = nullptr);

signals:

public slots:
	void startClickedSlot();
	void stopClickedSlot();

private:
	Monitor *monitor = nullptr;

	QLineEdit *leDirectory;
	QCheckBox *chb;
};
