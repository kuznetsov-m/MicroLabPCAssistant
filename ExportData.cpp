#include "ExportData.h"

void ExportData::exportTimeRangeData(const QDate &from, const QDate &to, const QString &filePath)
{
	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		// We're going to streaming text to the file
		QTextStream stream(&file);

		stream << buildTimeRangeData(from, to);

		file.close();
//		qDebug() << "Writer: text writing finished. File:" << reseachFile.fileName();
	}
	else
	{
//		qDebug() << "Writer: writing error. File:" << reseachFile.fileName();
	}
}

QString ExportData::getDirectory() const
{
	return directory;
}

void ExportData::setDirectory(const QString &value)
{
	directory = value;
}

QString ExportData::buildTimeRangeData(const QDate &from, const QDate &to)
{
	QString data;

//	for(const auto &label : labels)
//	{
//		data += label;
//		data += ";";
//	}
//	data += "\n";

	QDir dir(directory);
	if (!dir.exists())
	{
		qDebug() << "ExportData: dirrectory:" << directory << "is not exist.";
		return data;
	}

	QStringList currentFiles = dir.entryList(QStringList() << "*." + EXTENTION, QDir::Files);
	for (QString fileName : currentFiles)
	{
		const QString format = "yyyy-MM-dd";
		auto fileData = QDate::fromString(fileName.left(10), format);

		if (from.daysTo(fileData) >= 0 && fileData.daysTo(to) >= 0)
		{
			QFile file(directory + "/" + fileName);
			if(!file.open(QIODevice::ReadOnly))
			{
				qDebug() << "ExportData: read error. File:" << fileName << ". String:" << file.errorString();
				continue;
			}

			QTextStream in(&file);

			QString text;
			while(!in.atEnd()) {
				text += in.readLine();
			}

			file.close();

			auto object = jsonObjectFromString(text);
			for(auto key : object.keys())
			{
				data += object[key].toString();
				data += ";";
			}
			data += "\n";
		}
	}


	return data;
}

QJsonObject ExportData::jsonObjectFromString(const QString &in)
{
	QJsonObject obj;

	QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

	// check validity of the document
	if (!doc.isNull())
	{
		if (doc.isObject())
		{
			obj = doc.object();
		}
		else
		{
			qDebug() << "Document is not an object" << endl;
		}
	}
	else
	{
		qDebug() << "Invalid JSON...\n" << in << endl;
	}

	return obj;
}

QStringList ExportData::getKeys() const
{
	return keys;
}

void ExportData::setKeys(const QStringList &value)
{
	keys = value;
}

QStringList ExportData::getLabels() const
{
	return labels;
}

void ExportData::setLabels(const QStringList &value)
{
	labels = value;
}
