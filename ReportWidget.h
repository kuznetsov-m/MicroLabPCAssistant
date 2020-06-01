#pragma once

#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>

#include "ReseachData.h"


class ReportWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ReportWidget(QWidget *parent = nullptr);

	ReseachData *getReseachData() const;
	void setReseachData(ReseachData *value);

	void update();

signals:
	void writeResult();
	void writeResultAndNextSample();

private:
	QLineEdit *leUuid = nullptr;
	QLineEdit *leBrand = nullptr;
	QLineEdit *leCompany = nullptr;
	QDateEdit *deManufactureDate = nullptr;
	QLineEdit *leSamplePreparationUser = nullptr;
	QDateEdit *deSamplePreparationDate = nullptr;
	QLineEdit *leAnalyzeUser = nullptr;
	QDateEdit *deAnalyzeDate = nullptr;
	QLineEdit *leScanResult = nullptr;

	QTableWidget *tbw = nullptr;
	const QStringList labels = {"Идентификатор", "Марка продукта", "Производитель",
								"Дата производства", "Пробу подготовил(а)",
								"Дата подготовки пробы", "Анализ выполнил(а)",
								"Дата анализа", "Результат"
							   };

					  ReseachData *reseachData = nullptr;
};
