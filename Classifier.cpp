#include "Classifier.h"

QString Classifier::resultTypeToString(const Classifier::ResultType &resultType)
{
	switch (resultType)
	{
		case ResultType::UNKNOWN:
			return "UNKNOWN";

		case ResultType::POSITIVE:
			return "POSITIVE";

		case ResultType::CHECK:
			return "CHECK";

		case ResultType::CLEAR:
			return "CLEAR";

		default:
			return "???";
	}
}

Classifier::ResultType Classifier::stringToResultType(const QString &string)
{
	if (string == resultTypeToString(ResultType::POSITIVE))
		return ResultType::POSITIVE;
	else if (string == resultTypeToString(ResultType::CHECK))
		return ResultType::CHECK;
	else if (string == resultTypeToString(ResultType::CLEAR))
		return ResultType::CLEAR;
	else
		return ResultType::UNKNOWN;
}

Classifier::Classifier(QObject *parent) : QObject(parent)
{
	path = DEFAULT_PATH;
}

Classifier::~Classifier()
{
	if (process != nullptr)
	{
		delete process;
	}
}

void Classifier::start(const QStringList &arguments)
{
	QString program = path;
	process = new QProcess(this);

	connect(process, QOverload<int>::of(&QProcess::finished), this, &Classifier::processFinishedSlot);
	process->setProcessChannelMode(QProcess::MergedChannels);
	process->start(program, arguments);
//	process.waitForFinished(); // sets current thread to sleep and waits for process end ( lacks check)

	qDebug() << "Classifier: process started";
}

QString Classifier::getPath() const
{
	return path;
}

void Classifier::setPath(const QString &value)
{
	path = value;
}

void Classifier::processFinishedSlot(int exitCode)
{
	qDebug() << "Classifier: processFinishedSlot exitCode =" << exitCode;

	ResultType resultType = ResultType::UNKNOWN;
	if (process != nullptr)
	{
		QString output(process->readAllStandardOutput());
		qDebug() << "Classifier: output:" << output;

		delete process;
		process = nullptr;

		resultType = stringToResultType(output);
	}

	emit classified(resultType);
}
