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

#include <QtSql>
#include <QSqlError>
#include <QMessageBox>
#include "ui_dialog_component.h"
#include "dialog_component.h"
#include "dialog_category.h"
#include "dialog_footprint.h"
#include "dialog_temp.h"
#include "dialog_suppl.h"
#include "db_defs.h"

DialogComponent::DialogComponent(int edit_id, int clone_id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogComponent),
	update_id(-1)
{
	ui->setupUi(this);

	Q_ASSERT(!(edit_id != -1 && clone_id != -1));

#ifdef __APPLE__
	const int marg_left = 6;
	ui->le_part_no->setTextMargins(marg_left, 0, 0, 0);
	ui->le_value->setTextMargins(marg_left, 0, 0, 0);
	ui->le_voltage->setTextMargins(marg_left, 0, 0, 0);
	ui->le_amp->setTextMargins(marg_left, 0, 0, 0);
	ui->le_power->setTextMargins(marg_left, 0, 0, 0);
	ui->le_tolerance->setTextMargins(marg_left, 0, 0, 0);
	ui->le_supplier_part_no->setTextMargins(marg_left, 0, 0, 0);
	ui->le_design_item_id->setTextMargins(marg_left, 0, 0, 0);
	ui->le_description->setTextMargins(marg_left, 0, 0, 0);
	ui->sp_count->setContentsMargins(marg_left, 0, 0, 0);
	ui->sp_price->setContentsMargins(marg_left, 0, 0, 0);
	ui->sp_volume->setContentsMargins(marg_left, 0, 0, 0);
#endif

	setup_combos();

	if (edit_id != -1) {
		update_id = edit_id;
		setWindowTitle("Edit component");
	} else if (clone_id != -1)
		setWindowTitle("Clone component");
	else
		setWindowTitle("Add component");

	if (clone_id != -1 || edit_id != -1) {
		QSqlQuery query;
		query.prepare("SELECT * FROM component WHERE id = :id");
		query.bindValue(":id", clone_id != -1 ? clone_id : edit_id);

		if (!query.exec() || !query.next())
			QMessageBox::critical(this, "compdb", "Can't read component data: " + query.lastError().text());
		else {
			ui->cb_category->setCurrentIndex(ui->cb_category->findData(query.value(COLUMN_CATEGORY).toInt()));
			ui->le_part_no->setText(query.value(COLUMN_PART_NO).toString());
			ui->cb_footprint->setCurrentIndex(ui->cb_footprint->findData(query.value(COLUMN_FOOTPRINT).toInt()));
			ui->le_value->setText(query.value(COLUMN_VALUE).toString());
			ui->le_voltage->setText(query.value(COLUMN_VOLTAGE).toString());
			ui->le_amp->setText(query.value(COLUMN_AMP).toString());
			ui->le_power->setText(query.value(COLUMN_POWER).toString());
			ui->le_tolerance->setText(query.value(COLUMN_TOLERANCE).toString());
			ui->cb_temp->setCurrentIndex(ui->cb_temp->findData(query.value(COLUMN_TEMP).toInt()));
			ui->sp_count->setValue(query.value(COLUMN_COUNT).toInt());
			ui->cb_supplier->setCurrentIndex(ui->cb_supplier->findData(query.value(COLUMN_SUPPL).toInt()));
			ui->le_supplier_part_no->setText(query.value(COLUMN_SUPPL_PART_NO).toString());
			ui->sp_price->setValue(query.value(COLUMN_PRICE).toFloat());
			ui->sp_volume->setValue(query.value(COLUMN_PRICE_VOL).toInt());
			ui->le_design_item_id->setText(query.value(COLUMN_DESIGN_ITEM_ID).toString());
			ui->le_description->setText(query.value(COLUMN_DESCRIPTION).toString());
		}
	}

	ui->cb_category->setFocus();
}

DialogComponent::~DialogComponent()
{
	delete ui;
}

void DialogComponent::setup_combos()
{
	QSqlQuery query;

	int category_id = -1;
	int footprint_id = -1;
	int temp_id = -1;
	int suppl_id = -1;

	if (ui->cb_category->currentData().isValid() && !ui->cb_category->currentData().isNull())
		category_id = ui->cb_category->currentData().toInt();
	if (ui->cb_footprint->currentData().isValid() && !ui->cb_footprint->currentData().isNull())
		footprint_id = ui->cb_footprint->currentData().toInt();
	if (ui->cb_temp->currentData().isValid() && !ui->cb_temp->currentData().isNull())
		temp_id = ui->cb_temp->currentData().toInt();
	if (ui->cb_supplier->currentData().isValid() && !ui->cb_supplier->currentData().isNull())
		suppl_id = ui->cb_supplier->currentData().toInt();

	ui->cb_category->clear();
	ui->cb_footprint->clear();
	ui->cb_temp->clear();
	ui->cb_supplier->clear();

	query.exec("SELECT id, name FROM category ORDER BY name ASC");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_category->addItem(name, QVariant(id));
	}

	query.exec("SELECT footprint.id, footprint.name, mounting.name FROM footprint, mounting "
			   "WHERE footprint.mounting = mounting.id ORDER BY footprint.name ASC");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString() + " (" + query.value(2).toString() + ")";
		ui->cb_footprint->addItem(name, QVariant(id));
	}

	query.exec("SELECT id, name, description FROM temp ORDER BY name ASC");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString() + " (" + query.value(2).toString() + ")";
		ui->cb_temp->addItem(name, QVariant(id));
	}

	query.exec("SELECT id, name FROM suppl ORDER BY name ASC");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_supplier->addItem(name, QVariant(id));
	}

	if (category_id != -1)
		ui->cb_category->setCurrentIndex(ui->cb_category->findData(category_id));
	if (footprint_id != -1)
		ui->cb_footprint->setCurrentIndex(ui->cb_footprint->findData(footprint_id));
	if (temp_id != -1)
		ui->cb_temp->setCurrentIndex(ui->cb_temp->findData(temp_id));
	if (suppl_id != -1)
		ui->cb_supplier->setCurrentIndex(ui->cb_supplier->findData(suppl_id));
}

void DialogComponent::accept()
{
	QSqlQuery query;

	if (update_id != -1) {
		query.prepare(
			"UPDATE component SET "
			"  category = :category, part_no = :part_no, footprint = :footprint, "
			"  value = :value, voltage = :voltage, amp = :amp, power = :power, tolerance = :tolerance, "
			"  temp = :temp, count = :count, suppl = :suppl, suppl_part_no = :suppl_part_no, "
			"  price = :price, price_vol = :price_vol, design_item_id = :design_item_id, description = :description "
			"WHERE id = :id");
		query.bindValue(":id", update_id);
	} else {
		query.prepare(
			"INSERT INTO component "
			"  (category, part_no, footprint, value, voltage, amp, power, tolerance, temp, count, "
			"  suppl, suppl_part_no, price, price_vol, design_item_id, description) "
			"VALUES (:category, :part_no, :footprint, :value, :voltage, :amp, :power, :tolerance, :temp, :count, "
			"  :suppl, :suppl_part_no, :price, :price_vol, :design_item_id, :description)");
	}

	query.bindValue(":category", ui->cb_category->currentData().toInt());
	query.bindValue(":part_no", ui->le_part_no->text());
	query.bindValue(":footprint", ui->cb_footprint->currentData().toInt());
	query.bindValue(":value", ui->le_value->text());
	query.bindValue(":voltage", ui->le_voltage->text());
	query.bindValue(":amp", ui->le_amp->text());
	query.bindValue(":power", ui->le_power->text());
	query.bindValue(":tolerance", ui->le_tolerance->text());
	query.bindValue(":temp", ui->cb_temp->currentData().toInt());
	query.bindValue(":count", ui->sp_count->value());
	query.bindValue(":suppl", ui->cb_supplier->currentData().toInt());
	query.bindValue(":suppl_part_no", ui->le_supplier_part_no->text());
	query.bindValue(":price", ui->sp_price->value());
	query.bindValue(":price_vol", ui->sp_volume->value());
	query.bindValue(":design_item_id", ui->le_design_item_id->text());
	query.bindValue(":description", ui->le_description->text());

	if (!query.exec())
		QMessageBox::critical(this, "compdb", "Can't add/update component: " + query.lastError().text());
	else
		close();
}

void DialogComponent::on_btn_category_clicked()
{
	DialogCategory dialog;
	dialog.setModal(true);
	dialog.exec();
	setup_combos();
}

void DialogComponent::on_btn_footprint_clicked()
{
	DialogFootprint dialog;
	dialog.setModal(true);
	dialog.exec();
	setup_combos();
}

void DialogComponent::on_btn_temp_clicked()
{
	DialogTemp dialog;
	dialog.setModal(true);
	dialog.exec();
	setup_combos();
}

void DialogComponent::on_btn_suppl_clicked()
{
	DialogSuppl dialog;
	dialog.setModal(true);
	dialog.exec();
	setup_combos();
}
