#include "Writer.h"

Writer::Writer(QObject *parent) : QObject(parent)
{
	directory = DEFAULT_DIRECTORY;
}

void Writer::writeSlot(ReseachData *reseachData)
{
	auto checkAndCreateDirectory = [](const QString &directory)
	{
		QDir dir(directory);
		if (!dir.exists())
		{
			qDebug() << "Writer: dirrectory:" << directory << "is not exist. Try to create.";

			if (QDir().mkdir(directory))
				qDebug() << "Writer: dirrectory:" << directory << "created successfully.";
			else
			{
				qDebug() << "Writer: dirrectory:" << directory << "can not created.";
				return;
			}
		}
	};

	checkAndCreateDirectory(directory);
	checkAndCreateDirectory(directory + "/" + DEFAULT_RESEACH_FILES_DIRECTORY);

	//Копирование результата сканирования в папку
	QFile scanResultFile(reseachFileSourceDirectory + "/" + reseachData->scanResultFileName);
	QFileInfo fileInfo(scanResultFile.fileName());
	QString destinationPath = directory + "/" + DEFAULT_RESEACH_FILES_DIRECTORY + "/" + fileInfo.fileName();
	auto result = QFile::copy(scanResultFile.fileName(), destinationPath);
	qDebug() << "Writer: copy from:" << scanResultFile.fileName()
			 << "to" <<	destinationPath
			 << "result:" << result;

	//Сохранение записи в файл
	const QString format = "yyyy-MM-dd_HH-mm-ss-zzz";
	const QString fileName = QDateTime::currentDateTime().toString(format) + ".txt";

	QFile reseachFile(directory + "/" + fileName);
	if(reseachFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&reseachFile);

		QJsonDocument jsonDocument(reseachData->toJson());
		QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));
		stream << jsonString;

		reseachFile.close();
		qDebug() << "Writer: text writing finished. File:" << reseachFile.fileName();
	}
	else
	{
		qDebug() << "Writer: writing error. File:" << reseachFile.fileName();
	}
}

QString Writer::getReseachFileSourceDirectory() const
{
	return reseachFileSourceDirectory;
}

void Writer::setReseachFileSourceDirectory(const QString &value)
{
	reseachFileSourceDirectory = value;
}
