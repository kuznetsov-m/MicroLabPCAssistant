#pragma once

#include <QObject>
#include <QDir>
#include <QJsonDocument>
#include <QDebug>

#include "ReseachData.h"

class Writer : public QObject
{
	Q_OBJECT
public:
	explicit Writer(QObject *parent = nullptr);

	QString getReseachFileSourceDirectory() const;
	void setReseachFileSourceDirectory(const QString &value);

signals:

public slots:
	void writeSlot(ReseachData *reseachData);

private:
	QString reseachFileSourceDirectory;
	const QString DEFAULT_DIRECTORY = "Data";
	const QString DEFAULT_RESEACH_FILES_DIRECTORY = "ReseachFiles";
	QString directory;
};
