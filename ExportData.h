#pragma once

#include <QObject>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class ExportData : public QObject
{
	Q_OBJECT

public:
	explicit ExportData(QObject *parent = nullptr) : QObject(parent)
	{
		directory = DEFAULT_DIRECTORY;
	}

	void exportTimeRangeData(const QDate &from, const QDate &to, const QString &filePath);

	QString getDirectory() const;
	void setDirectory(const QString &value);

	QStringList getLabels() const;
	void setLabels(const QStringList &value);

	QStringList getKeys() const;
	void setKeys(const QStringList &value);

private:
	const QString DEFAULT_DIRECTORY = "Data";
	const QString EXTENTION = "txt";
	QString directory;

	QString buildTimeRangeData(const QDate &from, const QDate &to);

	QJsonObject jsonObjectFromString(const QString &in);

	QStringList labels;
	QStringList keys;
};
