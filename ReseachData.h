#pragma once

#define VARNAME(Variable) (#Variable)

#include <QString>
#include <QDate>
#include <QUuid>
#include <QJsonObject>

struct ReseachData
{
	ReseachData();

	QJsonObject toJson();

	QUuid uuid;
	QString brand;
	QString company;
	QDate manufactureDate;
	QString samplePreparationUser;
	QDate samplePreparationDate;
	QString analyzeUser;
	QDate analyzeDate;
	QString scanResultFileName;
	QString scanResult;
};
