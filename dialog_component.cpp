#include <QtSql>
#include <QSqlError>
#include <QMessageBox>
#include "dialog_component.h"
#include "ui_dialog_component.h"

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
}

DialogComponent::~DialogComponent()
{
    delete ui;
}

void DialogComponent::setup_combos()
{
	QSqlQuery query;

	query.exec("SELECT category_id, name FROM category");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_category->addItem(name, QVariant(id));
	}

	query.exec("SELECT type_id, name FROM type");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_type->addItem(name, QVariant(id));
	}

	query.exec("SELECT footprint_id, name FROM footprint");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_footprint->addItem(name, QVariant(id));
	}
}

void DialogComponent::accept()
{
	QSqlQuery query;

	query.prepare(
		"INSERT INTO component "
		"(category, type, part_no, footprint, value, count, "
		"suppl, suppl_part_no, price, price_vol, design_item_id, description) "
		"VALUES (:category, :type, :part_no, :footprint, :value, :count, "
		":suppl, :suppl_part_no, :price, :price_vol, :design_item_id, :description)");

    query.bindValue(":category", ui->cb_category->currentData().toInt());
    query.bindValue(":type", ui->cb_type->currentData().toInt());
    query.bindValue(":part_no", ui->le_part_no->text());
    query.bindValue(":footprint", ui->cb_footprint->currentData().toInt());
    query.bindValue(":value", ui->le_value->text());
    query.bindValue(":count", ui->sp_count->value());
    query.bindValue(":suppl", ui->le_supplier->text());
    query.bindValue(":suppl_part_no", ui->le_supplier_part_no->text());
    query.bindValue(":price", ui->le_price_volume->text().toFloat());
    query.bindValue(":price_vol", ui->sp_volume->value());
    query.bindValue(":design_item_id", ui->le_design_item_id->text());
    query.bindValue(":description", ui->le_descrtion->text());

	if (!query.exec())
		QMessageBox::critical(this, "compdb", "Can't add component: " + query.lastError().text());
	else
		close();
}

