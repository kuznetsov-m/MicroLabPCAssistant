#pragma once

#include <QObject>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

class Classifier : public QObject
{
	Q_OBJECT

public:
	enum ResultType
	{
		UNKNOWN,
		POSITIVE,
		CHECK,
		CLEAR
	};
	Q_ENUM(ResultType)

	static QString resultTypeToString(const ResultType &resultType);
	static ResultType stringToResultType(const QString &string);

	Classifier(QObject *parent = nullptr);
	~Classifier();

	void start(const QStringList &arguments);

	QString getPath() const;
	void setPath(const QString &value);

signals:
	void classified(const ResultType &resultType);

private slots:
	void processFinishedSlot(int exitCode);

private:
//	const QString DEFAULT_PATH = "C:\\Windows\\System32\\notepad.exe";
	const QString DEFAULT_PATH = "notepad";

	QString path;

	QProcess *process = nullptr;
};
