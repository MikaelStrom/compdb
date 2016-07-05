#include <QMessageBox>
#include "dialog_footprint.h"
#include "ui_dialog_footprint.h"

DialogFootprint::DialogFootprint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFootprint)
{
    ui->setupUi(this);

	model = new QSqlTableModel(this);
	model->setTable("footprint");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Footprint"));
    model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    if (!model->select())
        QMessageBox::critical(this, "compdb", "Can't open table footprint: " + model->lastError().text());

    ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);
}

DialogFootprint::~DialogFootprint()
{
    delete ui;
}

void DialogFootprint::on_pb_new_clicked()
{
	QSqlQuery query;
    query.prepare("INSERT INTO footprint (name) VALUES ('<Footprint>')");
	query.exec();
	model->select();
	
	QModelIndex index = model->index(model->rowCount() - 1, 1);
    ui->tableView->selectRow(model->rowCount() - 1);
    ui->tableView->edit(index);
}

void DialogFootprint::on_pb_delete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.count() == 1) {
        QModelIndex index = model->index(selected.at(0).row(), 0);
        int dbIndex = index.data().toInt();
   
		QSqlQuery query; 
		query.prepare("DELETE FROM footprint WHERE footprint_id = :id");
		query.bindValue(":id", dbIndex);
		if (!query.exec())
            QMessageBox::critical(this, "compdb", "Can't delete footprint: " + query.lastError().text());

		model->select();
	}
}

void DialogFootprint::on_pb_close_clicked()
{
	close();
}
