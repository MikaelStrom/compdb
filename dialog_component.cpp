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
    ui(new Ui::DialogComponent)
{
    ui->setupUi(this);

	Q_ASSERT(!(edit_id != -1 && clone_id != -1));

	setup_combos();

	if (edit_id != -1) {
		mode_update = true;
        setWindowTitle("Edit Component");
	} else
        setWindowTitle("Add Component");

	if (clone_id != -1) {

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

	query.prepare(
		"INSERT INTO component "
		"  (category, part_no, footprint, value, voltage, tolerance, temp, count, "
		"  suppl, suppl_part_no, price, price_vol, design_item_id, description) "
		"VALUES (:category, :part_no, :footprint, :value, :voltage, :tolerance, :temp, :count, "
		":suppl, :suppl_part_no, :price, :price_vol, :design_item_id, :description)");

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
		QMessageBox::critical(this, "compdb", "Can't add component: " + query.lastError().text());
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
