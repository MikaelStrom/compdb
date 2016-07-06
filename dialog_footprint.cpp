#include <QMessageBox>
#include "ui_dialog_footprint.h"
#include "dialog_footprint.h"
#include "dialog_type.h"

DialogFootprint::DialogFootprint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFootprint)
{
    ui->setupUi(this);

	model = new QSqlRelationalTableModel(this);
	model->setTable("footprint");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
	model->setRelation(2, QSqlRelation("mounting", "id", "name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Footprint"));
    model->setHeaderData(2, Qt::Horizontal, tr("Mounting"));
    model->setHeaderData(3, Qt::Horizontal, tr("Description"));
    if (!model->select())
        QMessageBox::critical(this, "compdb", "Can't open table footprint: " + model->lastError().text());

    ui->tableView->setModel(model);
	ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
	ui->tableView->hideColumn(0);
}

DialogFootprint::~DialogFootprint()
{
    delete ui;
	delete model;
}

void DialogFootprint::on_pb_new_clicked()
{
	QSqlQuery query;
    query.prepare("INSERT INTO footprint (name, mounting) VALUES ('<Footprint>', 1)");
	if (!query.exec())
		QMessageBox::critical(this, "compdb", "Can't add footprint: " + query.lastError().text());
	else {
		model->select();
		QModelIndex index = model->index(model->rowCount() - 1, 1);
		ui->tableView->selectRow(model->rowCount() - 1);
		ui->tableView->edit(index);
	}
}

void DialogFootprint::on_pb_delete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.count() == 1) {
        QModelIndex index = model->index(selected.at(0).row(), 0);
        int dbIndex = index.data().toInt();
   
		QSqlQuery query; 
		query.prepare("DELETE FROM footprint WHERE id = :id");
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

void DialogFootprint::on_pb_mounting_clicked()
{
    DialogType dialog;
    dialog.setModal(true);
    dialog.exec();
    model->select();
}
