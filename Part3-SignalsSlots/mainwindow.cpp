#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenActionTriggered()));
}

void MainWindow::onOpenActionTriggered()
{
	// open a file dialog
	auto selected_file = QFileDialog::getOpenFileName(this, tr("Open a file"), QApplication::applicationDirPath());
	
	if(!selected_file.isNull())
	{
		std::cout << selected_file.toStdString() << std::endl;
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}
