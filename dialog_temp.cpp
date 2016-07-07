#include <QMessageBox>
#include "dialog_temp.h"
#include "ui_dialog_temp.h"

DialogTemp::DialogTemp(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogTemp)
{
	ui->setupUi(this);

	model = new QSqlTableModel(this);
	model->setTable("temp");
	model->setHeaderData(1, Qt::Horizontal, tr("Temp Rating"));
	model->setHeaderData(2, Qt::Horizontal, tr("Description"));
	if (!model->select())
		QMessageBox::critical(this, "compdb", "Can't open table temp: " + model->lastError().text());

	ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);
}

DialogTemp::~DialogTemp()
{
	delete ui;
	delete model;
}

void DialogTemp::on_pb_new_clicked()
{
	QSqlQuery query;
	query.prepare("INSERT INTO temp (name, description) VALUES ('<Temp Rating>', '')");
	if (!query.exec())
		QMessageBox::critical(this, "compdb", "Can't add temp: " + query.lastError().text());
	else {
		model->select();
		QModelIndex index = model->index(model->rowCount() - 1, 1);
		ui->tableView->selectRow(model->rowCount() - 1);
		ui->tableView->edit(index);
	}
}

void DialogTemp::on_pb_delete_clicked()
{
	QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
	if (selected.count() > 0) {
		QModelIndex index = model->index(selected.at(0).row(), 0);
		int dbIndex = index.data().toInt();

		QSqlQuery query;
		query.prepare("DELETE FROM temp WHERE id = :id");
		query.bindValue(":id", dbIndex);
		if (!query.exec())
			QMessageBox::critical(this, "compdb", "Can't delete temp: " + query.lastError().text());

		model->select();
	}
}

void DialogTemp::on_pb_close_clicked()
{
	close();
}
