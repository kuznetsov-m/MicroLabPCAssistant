#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	auto w = new QWidget(this);
	auto hl = new QHBoxLayout(w);
	this->setCentralWidget(w);

	mainWidget = new MainWidget(this);
	hl->addWidget(mainWidget);

//	testerWidget = new TesterWidget(this);
//	hl->addWidget(testerWidget);
}

MainWindow::~MainWindow()
{
	delete ui;
}
