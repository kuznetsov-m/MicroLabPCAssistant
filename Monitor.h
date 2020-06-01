#pragma once

#include <QObject>
#include <QString>
#include <QDir>
#include <QTimer>
#include <QDebug>

class Monitor : public QObject
{
	Q_OBJECT

public:
	Monitor(QObject *parent = nullptr);

	void start();
	void stop();

	bool isStarted();

	void updateFiles();

	QString getDirectory() const;
	void setDirectory(const QString &value);

	QString getExtention() const;
	void setExtention(const QString &value);

signals:
	void foundNewFile(QString fileName);

private slots:
	void tikTimerSlot();

private:
	const QString DEFAULT_DIRECTORY = "C:\\TestFolder";
	const QString DEFAULT_EXTENTION = "txt";

	QString directory;
	QString extention;

	QTimer timer;

	QStringList files;
};
