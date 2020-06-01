#include "ClassifierWidget.h"

ClassifierWidget::ClassifierWidget(Classifier *_classifier, QWidget *parent) :
	QWidget(parent), classifier(_classifier)
{
	auto vl = new QVBoxLayout(this);

	auto lb = new QLabel("ClassifierWidget");
	vl->addWidget(lb);

	lePath = new QLineEdit();
	lePath->setText(classifier->getPath());
	vl->addWidget(lePath);

	auto pbSetDirectory = new QPushButton("Задать путь до программы");
	connect(pbSetDirectory, &QPushButton::clicked, this, [this]
	{
		classifier->setPath(lePath->text());
	});
	vl->addWidget(pbSetDirectory);

	leArguments = new QLineEdit();
	QString tempFilePath = "C:\\TestFolder\\file.txt";
	leArguments->setText(tempFilePath);
	vl->addWidget(leArguments);

	auto pbStart = new QPushButton("Старт");
	connect(pbStart, &QPushButton::clicked, this, &ClassifierWidget::startClickedSlot);
	vl->addWidget(pbStart);

}

void ClassifierWidget::setArguments(const QString &value)
{
	leArguments->setText(value);
}

void ClassifierWidget::startClickedSlot()
{
	QStringList arguments;
	arguments << leArguments->text();
	classifier->start(arguments);
}
