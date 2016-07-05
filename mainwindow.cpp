#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_category.h"
#include "dialog_type.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	model(NULL)
{
	ui->setupUi(this);
	setCentralWidget(ui->tableView);

    db = QSqlDatabase::addDatabase("QSQLITE");

    openDb("/Users/mike/c/compdb/components.db");
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open component database"), "", tr("Database files (*.db)"));

	if (fileName.size() > 0)
		openDb(fileName);
}

void MainWindow::openDb(QString fname)
{
	QSqlTableModel *old = model;

    if (db.open()) {
		db.close();
    }

    db.setDatabaseName(fname);
	if (! db.open()) {
        QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + db.lastError().text());
		return;
	}

	model = new QSqlTableModel(this);
	model->setTable("category");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);

    if (!model->select()) {
        QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + model->lastError().text());
        return;
    }

	if (old) 
		delete old;
}

void MainWindow::on_actionCategory_triggered()
{
    DialogCategory dialog;

    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionType_triggered()
{
    DialogType dialog;

    dialog.setModal(true);
    dialog.exec();
}
