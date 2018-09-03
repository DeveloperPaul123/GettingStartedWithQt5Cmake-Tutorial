#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QImageReader>
#include <QStandardPaths>

#include <iostream>

inline void initializeImageFileDialog(QFileDialog &dialog)
{
	static bool first_dialog = true;

	if (first_dialog) {
		first_dialog = false;
		const QStringList pictures_locations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
		dialog.setDirectory(pictures_locations.isEmpty() ? QDir::currentPath() : pictures_locations.last());
	}

	auto image_types_array = QImageReader::supportedMimeTypes();
	QStringList mime_type_filters;
	for (const auto type : image_types_array)
	{
		mime_type_filters.append(type);
	}
	mime_type_filters.sort();

	dialog.setMimeTypeFilters(mime_type_filters);
	dialog.selectMimeTypeFilter("image/jpeg");
}

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
	QFileDialog file_dialog(this, tr("Open Image"));
	initializeImageFileDialog(file_dialog);
	const auto result = file_dialog.exec();
	if(result == QDialog::Accepted)
	{
		// load the file
		auto path = file_dialog.selectedFiles().first();
		QImageReader image_reader(path);
		const QImage image = image_reader.read();
		if(!image.isNull())
		{
			ui->label->setPixmap(QPixmap::fromImage(image));
			ui->label->resize(ui->label->pixmap()->size());
		}
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}