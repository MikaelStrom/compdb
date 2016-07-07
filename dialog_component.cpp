#include <QtSql>
#include <QSqlError>
#include <QMessageBox>
#include "ui_dialog_component.h"
#include "dialog_component.h"
#include "dialog_category.h"
#include "dialog_footprint.h"
#include "dialog_temp.h"

DialogComponent::DialogComponent(int edit_id, int clone_id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogComponent),
	update_id(-1)
{
	ui->setupUi(this);

	Q_ASSERT(!(edit_id != -1 && clone_id != -1));

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
		query.prepare("SELECT category, part_no, footprint, value, voltage, tolerance, temp, count, "
					  "  suppl, suppl_part_no, price, price_vol, design_item_id, description "
					  "FROM component WHERE id = :id");
		query.bindValue(":id", clone_id != -1 ? clone_id : edit_id);

		if (!query.exec() || !query.next())
			QMessageBox::critical(this, "compdb", "Can't read component data: " + query.lastError().text());
		else {
			ui->cb_category->setCurrentIndex(ui->cb_category->findData(query.value(0).toInt()));
			ui->le_part_no->setText(query.value(1).toString());
			ui->cb_footprint->setCurrentIndex(ui->cb_footprint->findData(query.value(2).toInt()));
			ui->le_value->setText(query.value(3).toString());
			ui->le_voltage->setText(query.value(4).toString());
			ui->sp_tolerance->setValue(query.value(5).toInt());
			ui->cb_temp->setCurrentIndex(ui->cb_temp->findData(query.value(6).toInt()));
			ui->sp_count->setValue(query.value(7).toInt());
			ui->le_supplier->setText(query.value(8).toString());
			ui->le_supplier_part_no->setText(query.value(9).toString());
			ui->sp_price->setValue(query.value(10).toFloat());
			ui->sp_volume->setValue(query.value(11).toInt());
			ui->le_design_item_id->setText(query.value(12).toString());
			ui->le_descrtion->setText(query.value(13).toString());
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

	int category_index = ui->cb_category->currentIndex();;
	int footprint_index = ui->cb_footprint->currentIndex();;
	int temp_index = ui->cb_temp->currentIndex();;

	ui->cb_category->clear();
	ui->cb_footprint->clear();
	ui->cb_temp->clear();

	query.exec("SELECT id, name FROM category");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_category->addItem(name, QVariant(id));
	}

	query.exec("SELECT footprint.id, footprint.name, mounting.name FROM footprint, mounting "
			   "WHERE footprint.mounting = mounting.id");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString() + " (" + query.value(2).toString() + ")";
		ui->cb_footprint->addItem(name, QVariant(id));
	}

	query.exec("SELECT id, name, description FROM temp");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString() + " (" + query.value(2).toString() + ")";
		ui->cb_temp->addItem(name, QVariant(id));
	}

	if (category_index != -1)
		ui->cb_category->setCurrentIndex(category_index);
	if (footprint_index != -1)
		ui->cb_footprint->setCurrentIndex(footprint_index);
	if (temp_index != -1)
		ui->cb_temp->setCurrentIndex(temp_index);
}

void DialogComponent::accept()
{
	QSqlQuery query;

	if (update_id != -1) {
		query.prepare(
			"UPDATE component SET "
			"  category = :category, part_no = :part_no, footprint = :footprint, value = :value, voltage = :voltage, "
			"  tolerance = :tolerance, temp = :temp, count = :count, suppl = :suppl, suppl_part_no = :suppl_part_no, "
			"  price = :price, price_vol = :price_vol, design_item_id = :design_item_id, description = :design_item_id "
			"WHERE id = :id");
		query.bindValue(":id", update_id);
	} else {
		query.prepare(
			"INSERT INTO component "
			"  (category, part_no, footprint, value, voltage, tolerance, temp, count, "
			"  suppl, suppl_part_no, price, price_vol, design_item_id, description) "
			"VALUES (:category, :part_no, :footprint, :value, :voltage, :tolerance, :temp, :count, "
			"  :suppl, :suppl_part_no, :price, :price_vol, :design_item_id, :description)");
	}

	query.bindValue(":category", ui->cb_category->currentData().toInt());
	query.bindValue(":part_no", ui->le_part_no->text());
	query.bindValue(":footprint", ui->cb_footprint->currentData().toInt());
	query.bindValue(":value", ui->le_value->text());
	query.bindValue(":voltage", ui->le_voltage->text());
	query.bindValue(":tolerance", ui->sp_tolerance->value());
	query.bindValue(":temp", ui->cb_temp->currentData().toInt());
	query.bindValue(":count", ui->sp_count->value());
	query.bindValue(":suppl", ui->le_supplier->text());
	query.bindValue(":suppl_part_no", ui->le_supplier_part_no->text());
	query.bindValue(":price", ui->sp_price->value());
	query.bindValue(":price_vol", ui->sp_volume->value());
	query.bindValue(":design_item_id", ui->le_design_item_id->text());
	query.bindValue(":description", ui->le_descrtion->text());

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
