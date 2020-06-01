#include "ReseachData.h"

ReseachData::ReseachData()
{
	uuid = QUuid::createUuid();
	manufactureDate = QDate::currentDate();
	samplePreparationDate = QDate::currentDate();
	analyzeDate = QDate::currentDate();
}

QJsonObject ReseachData::toJson()
{
	QJsonObject jsonObject;
	const QString format = "yyyy.MM.dd";

	jsonObject[VARNAME(uuid)] = uuid.toString();
	jsonObject[VARNAME(brand)] = brand;
	jsonObject[VARNAME(company)] = company;
	jsonObject[VARNAME(manufactureDate)] = manufactureDate.toString(format);
	jsonObject[VARNAME(samplePreparationUser)] = samplePreparationUser;
	jsonObject[VARNAME(samplePreparationDate)] = samplePreparationDate.toString(format);;
	jsonObject[VARNAME(analyzeUser)] = analyzeUser;
	jsonObject[VARNAME(analyzeDate)] = analyzeDate.toString(format);
	jsonObject[VARNAME(scanResultFileName)] = scanResultFileName;
	jsonObject[VARNAME(scanResult)] = scanResult;



	return jsonObject;
}
