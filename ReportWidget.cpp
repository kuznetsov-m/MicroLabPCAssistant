#include "ReportWidget.h"

/* Поля:
«Марка продукта»,
«Производитель»,
«Дата производства»,
«Пробу подготовил(а)»,
«Дата подготовки пробы» (в этом окне по умолчанию стоит сегодняшняя),
«Анализ выполнил(а)»,
«Дата анализа» (тоже сегодняшняя дата).
И ещё поле id (неизменяемо, уникальный id измерения, генерится программой).
Поле «Результат» (неизменяемо), содержит результат работы классификатора в виде строки “POSITIVE”, “CHECK”, “CLEAR”.

Все поля, начиная с «Пробу подготовил(а)», следует разместить в отдельной строке, поскольку эти данные характеризуют само измерение, а их может быть несколько (обычно 3 повтора для одной марки продукта, каждому повтору измерения соответствует свой файл и свой набор полей).
*/

ReportWidget::ReportWidget(QWidget *parent) : QWidget(parent)
{
	auto flo = new QFormLayout(this);
	flo->setMargin(0);

	leUuid = new QLineEdit();
	leUuid->setEnabled(false);
	flo->addRow(new QLabel("Идентификатор:"), leUuid);

	leBrand = new QLineEdit();
	flo->addRow(new QLabel("Марка продукта:"), leBrand);

	leCompany = new QLineEdit();
	flo->addRow(new QLabel("Производитель:"), leCompany);

	deManufactureDate = new QDateEdit();
	flo->addRow(new QLabel("Дата производства:"), deManufactureDate);

	leSamplePreparationUser = new QLineEdit();
	flo->addRow(new QLabel("Пробу подготовил(а):"), leSamplePreparationUser);

	deSamplePreparationDate = new QDateEdit();
	flo->addRow(new QLabel("Дата подготовки пробы:"), deSamplePreparationDate);

	leAnalyzeUser = new QLineEdit();
	flo->addRow(new QLabel("Анализ выполнил(а):"), leAnalyzeUser);

	deAnalyzeDate = new QDateEdit();
	flo->addRow(new QLabel("Дата анализа:"), deAnalyzeDate);

	leScanResult = new QLineEdit();
	leScanResult->setEnabled(false);
	flo->addRow(new QLabel("Результат:"), leScanResult);

	tbw = new QTableWidget();
	tbw->setColumnCount(labels.size());
	tbw->setHorizontalHeaderLabels(labels);
	for(int i = 0; i < tbw->columnCount(); ++i)
		tbw->setColumnWidth(i, 150);
	flo->addRow(tbw);

	//Сохранить
	auto pbWriteResult = new QPushButton("Сохранить");
	connect(pbWriteResult, &QPushButton::clicked, this, [this]
	{
		reseachData->uuid = QUuid::fromString(leUuid->text());
		reseachData->brand = leBrand->text();
		reseachData->company = leCompany->text();
		reseachData->manufactureDate = deManufactureDate->date();
		reseachData->samplePreparationUser = leSamplePreparationUser->text();
		reseachData->samplePreparationDate = deSamplePreparationDate->date();
		reseachData->analyzeUser = leAnalyzeUser->text();
		reseachData->analyzeDate = deAnalyzeDate->date();
		reseachData->scanResult = leScanResult->text();

		const QString format = "dd.MM.yyyy";
		const int rowCount = tbw->rowCount();
		tbw->insertRow(rowCount);
		tbw->setItem(rowCount, labels.indexOf("Идентификатор"),
					 new QTableWidgetItem(leUuid->text()));
		tbw->setItem(rowCount, labels.indexOf("Марка продукта"),
					 new QTableWidgetItem(leBrand->text()));
		tbw->setItem(rowCount, labels.indexOf("Производитель"),
					 new QTableWidgetItem(leCompany->text()));
		tbw->setItem(rowCount, labels.indexOf("Дата производства"),
					 new QTableWidgetItem(deManufactureDate->date().toString(format)));
		tbw->setItem(rowCount, labels.indexOf("Пробу подготовил(а)"),
					 new QTableWidgetItem(leSamplePreparationUser->text()));
		tbw->setItem(rowCount, labels.indexOf("Дата подготовки пробы"),
					 new QTableWidgetItem(deSamplePreparationDate->date().toString(format)));
		tbw->setItem(rowCount, labels.indexOf("Анализ выполнил(а)"),
					 new QTableWidgetItem(leAnalyzeUser->text()));
		tbw->setItem(rowCount, labels.indexOf("Дата анализа"),
					 new QTableWidgetItem(deAnalyzeDate->date().toString(format)));
		tbw->setItem(rowCount, labels.indexOf("Результат"),
					 new QTableWidgetItem(leScanResult->text()));
		emit writeResult();
	});
	flo->addRow(pbWriteResult);

	//Завершить повторы, следующий образец
	auto pbWriteResultAndNextSample = new QPushButton("Завершить повторы, следующий образец");
	connect(pbWriteResultAndNextSample, &QPushButton::clicked, this, [this]
	{
		reseachData->uuid = QUuid::fromString(leUuid->text());
		reseachData->brand = leBrand->text();
		reseachData->company = leCompany->text();
		reseachData->manufactureDate = deManufactureDate->date();
		reseachData->samplePreparationUser = leSamplePreparationUser->text();
		reseachData->samplePreparationDate = deSamplePreparationDate->date();
		reseachData->analyzeUser = leAnalyzeUser->text();
		reseachData->analyzeDate = deAnalyzeDate->date();
		reseachData->scanResult = leScanResult->text();

		tbw->clearContents();
		tbw->setRowCount(0);

		emit writeResultAndNextSample();
	});
	flo->addRow(pbWriteResultAndNextSample);
}

ReseachData *ReportWidget::getReseachData() const
{
	return reseachData;
}

void ReportWidget::setReseachData(ReseachData *value)
{
	reseachData = value;
}

void ReportWidget::update()
{
	leUuid->setText(reseachData->uuid.toString());
	leBrand->setText(reseachData->brand);
	leCompany->setText(reseachData->company);
	deManufactureDate->setDate(reseachData->manufactureDate);
	leSamplePreparationUser->setText(reseachData->samplePreparationUser);
	deSamplePreparationDate->setDate(reseachData->samplePreparationDate);
	leAnalyzeUser->setText(reseachData->analyzeUser);
	deAnalyzeDate->setDate(reseachData->analyzeDate);
	leScanResult->setText(reseachData->scanResult);
}
