/*	This file is part of compdb.

	compdb - Cross plattform Electronic Component Database
	Copyright (C) 2016	Mikael Ström

	compdb is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	compdb is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with compdb.	If not, see <http://www.gnu.org/licenses/>.
*/

#include <QMessageBox>
#include <QInputDialog>
#include "dialog_category.h"
#include "ui_dialog_category.h"

DialogCategory::DialogCategory(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogCategory)
{
	ui->setupUi(this);

	model = new QSqlTableModel(this);
	model->setTable("category");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->setSort(1, Qt::AscendingOrder);
	ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);

	if (!model->select())
		QMessageBox::critical(this, "compdb", "Can't open table category: " + model->lastError().text());
}

DialogCategory::~DialogCategory()
{
	delete ui;
}

void DialogCategory::on_pb_new_clicked()
{
	QSqlQuery query;
	query.prepare("INSERT INTO category (name) VALUES ('<Category>')");
	if (!query.exec())
		QMessageBox::critical(this, "compdb", "Can't add category: " + query.lastError().text());
	else {
		int inserted_id = query.lastInsertId().toInt();

		model->select();
		for (int i = 0; i < model->rowCount(); ++i) {
			QModelIndex index = model->index(i, 0);
			if (model->data(index, Qt::DisplayRole).toInt() == inserted_id) {
				QModelIndex item = model->index(i, 1);
				ui->tableView->selectRow(i);
				ui->tableView->scrollTo(item);
				ui->tableView->edit(item);
				break;
			}
		}
	}
}

void DialogCategory::on_pb_delete_clicked()
{
	QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
	if (selected.count() > 1) {
		QModelIndex index = model->index(selected.at(0).row(), 0);
		int dbIndex = index.data().toInt();

		QSqlQuery query;
		query.prepare("DELETE FROM category WHERE id = :id");
		query.bindValue(":id", dbIndex);
		if (!query.exec())
			QMessageBox::critical(this, "compdb", "Can't delete category: " + query.lastError().text());

		model->select();
	}
}

void DialogCategory::on_pb_close_clicked()
{
	model->submitAll();
	close();
}
