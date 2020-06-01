#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "ExportData.h"

class ExportDataWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ExportDataWidget(ExportData *_exportData, QWidget *parent = nullptr);

signals:

public slots:
	void exportSlot();

private:
	ExportData *exportData = nullptr;

	QDateEdit *deFrom = nullptr;
	QDateEdit *deTo = nullptr;

	QHBoxLayout *getDateRangeLayout();
};
