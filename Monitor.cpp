#include "Monitor.h"

Monitor::Monitor(QObject *parent) : QObject(parent)
{
	directory = DEFAULT_DIRECTORY;
	extention = DEFAULT_EXTENTION;

	const int INTERVAL = 1000;
	timer.setInterval(INTERVAL);
	connect(&timer, &QTimer::timeout, this, &Monitor::tikTimerSlot);
}

void Monitor::start()
{
	timer.start();

	qDebug() << "Monitor: started";
}

void Monitor::stop()
{
	timer.stop();

	qDebug() << "Monitor: stoped";
}

bool Monitor::isStarted()
{
	return timer.isActive();
}

void Monitor::updateFiles()
{
	QDir directory(DEFAULT_DIRECTORY);
	files = directory.entryList(QStringList()
								<< "*." + extention.toLower()
								<< "*." + extention.toUpper(),
								QDir::Files);
}

QString Monitor::getDirectory() const
{
	return directory;
}

void Monitor::setDirectory(const QString &value)
{
	directory = value;
}

void Monitor::tikTimerSlot()
{
	qDebug() << "Monitor: tikTimerSlot()";

	QDir dir(directory);
	if (!dir.exists())
	{
		qDebug() << "Monitor: dirrectory:" << directory << "is not exist.";
		return;
	}

	QStringList currentFiles = dir.entryList(QStringList()
											 << "*." + extention.toLower()
											 << "*." + extention.toUpper(),
											 QDir::Files);
	for (QString fileName : currentFiles)
	{
		if (!files.contains(fileName))
		{
			emit foundNewFile(dir.path() + "/" + fileName);
		}
	}

	updateFiles();
}

QString Monitor::getExtention() const
{
	return extention;
}

void Monitor::setExtention(const QString &value)
{
	extention = value;
}
