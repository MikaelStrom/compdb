/*	This file is part of compdb.

	compdb - Cross plattform Electronic Component Database
	Copyright (C) 2016  Mikael Ström
	
	compdb is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	compdb is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with compdb.  If not, see <http://www.gnu.org/licenses/>. 
*/

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
