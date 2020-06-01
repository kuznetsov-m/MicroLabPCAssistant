#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Classifier.h"

class ClassifierWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ClassifierWidget(Classifier *_classifier, QWidget *parent = nullptr);

	void setArguments(const QString &value);

private slots:
	void startClickedSlot();

private:
	Classifier *classifier = nullptr;

	QLineEdit *lePath = nullptr;

	QLineEdit *leArguments = nullptr;
};
