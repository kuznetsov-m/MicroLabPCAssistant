#include "ExportDataWidget.h"

ExportDataWidget::ExportDataWidget(ExportData *_exportData, QWidget *parent) :
	QWidget(parent), exportData(_exportData)
{
	auto vl = new QVBoxLayout(this);

	vl->addLayout(getDateRangeLayout());

	auto pbExport = new QPushButton("Экспорт в csv");
	connect(pbExport, &QPushButton::clicked, this, &ExportDataWidget::exportSlot);
	vl->addWidget(pbExport);
}

void ExportDataWidget::exportSlot()
{
	QString filePath = QFileDialog::getSaveFileName(this, "Выберите путь для экспорта", "AssistantData.csv", "CSV(*.csv)");

	exportData->exportTimeRangeData(deFrom->date(), deTo->date(), filePath);

	QMessageBox::information(this, "Экспорт в CSV", "Данные успешно экспортированы.");
}

QHBoxLayout *ExportDataWidget::getDateRangeLayout()
{
	auto hl = new QHBoxLayout();

	hl->addStretch();

	hl->addWidget(new QLabel("Диапазон дат:"));

	deFrom = new QDateEdit();
	deFrom->setDate(QDate::currentDate().addDays(-1));
	hl->addWidget(deFrom);

	hl->addWidget(new QLabel("-"));

	deTo = new QDateEdit();
	deTo->setDate(QDate::currentDate());
	hl->addWidget(deTo);

	hl->addStretch();

	return hl;
}
