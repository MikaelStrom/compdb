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

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "main_window.h"
#include "ui_main_window.h"
#include "dialog_category.h"
#include "dialog_type.h"
#include "dialog_footprint.h"
#include "dialog_temp.h"
#include "dialog_component.h"

const char *sql_create[] = {
	"CREATE TABLE \"category\" ("
	"	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"	`name`				TEXT NOT NULL"
	");",

	"CREATE TABLE \"mounting\" ("
	"	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"	`name`				TEXT NOT NULL"
	");",

	"CREATE TABLE \"temp\" ("
	"	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"	`name`				TEXT NOT NULL,"
	"	`description`		TEXT"
	");",

	"CREATE TABLE \"footprint\" ("
	"	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"	`name`				TEXT NOT NULL,"
	"	`mounting`			INTEGER,"
	"	`description`		TEXT,"
	"	FOREIGN KEY(`mounting`) REFERENCES `mounting`(`id`)"
	");",

	"CREATE TABLE \"component\" ("
	"	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"	`category`			INTEGER NOT NULL,"
	"	`part_no`			TEXT,"
	"	`footprint`			INTEGER,"
	"	`value`				TEXT,"
	"	`voltage`			TEXT,"
	"	`tolerance`			INTEGER,"
	"	`temp`				INTEGER,"
	"	`count`				INTEGER,"
	"	`suppl`				TEXT,"
	"	`suppl_part_no`		TEXT,"
	"	`price`				REAL,"
	"	`price_vol`			INTEGER,"
	"	`design_item_id`	TEXT,"
	"	`description`		TEXT,"
	"	FOREIGN KEY(`category`) REFERENCES `category`(`id`),"
	"	FOREIGN KEY(`footprint`) REFERENCES `footprint`(`id`),"
	"	FOREIGN KEY(`temp`) REFERENCES `temp`(`id`)"
	");",

	"INSERT INTO `category` (name) VALUES ('Resistor');",
	"INSERT INTO `category` (name) VALUES ('Capacitor');",
	"INSERT INTO `category` (name) VALUES ('Diode');",
	"INSERT INTO `category` (name) VALUES ('BJT');",
	"INSERT INTO `category` (name) VALUES ('JFET');",
	"INSERT INTO `category` (name) VALUES ('Voltage regulator');",

	"INSERT INTO `mounting` (name) VALUES ('N/A');",
	"INSERT INTO `mounting` (name) VALUES ('SMT');",
	"INSERT INTO `mounting` (name) VALUES ('Through Hole');",
	"INSERT INTO `mounting` (name) VALUES ('Chassi');",

	"INSERT INTO `temp` (name, description) VALUES ('N/A', 'N/A');",
	"INSERT INTO `temp` (name, description) VALUES ('NP0/C0G', 'Zero drift');",
	"INSERT INTO `temp` (name, description) VALUES ('X8R', '−55/+150, ΔC/C0 = ±15%');",
	"INSERT INTO `temp` (name, description) VALUES ('X7R', '−55/+125 °C, ΔC/C0 = ±15%');",
	"INSERT INTO `temp` (name, description) VALUES ('X5R', '−55/+85 °C, ΔC/C0 = ±15%');",
	"INSERT INTO `temp` (name, description) VALUES ('X7S', '−55/+125, ΔC/C0 = ±22%');",
	"INSERT INTO `temp` (name, description) VALUES ('Y5V', '−30/+85 °C, ΔC/C0 = +22/−82%');",
	"INSERT INTO `temp` (name, description) VALUES ('Z5U', '+10/+85 °C, ΔC/C0 = +22/−56%');",

	"INSERT INTO `footprint` (name, mounting, description) VALUES ('None', 1, 'None');",
	"INSERT INTO `footprint` (name, mounting, description) VALUES ('0402', 2, 'Metric 1005');",
	"INSERT INTO `footprint` (name, mounting, description) VALUES ('0603', 2, 'Metric 1608');",
	"INSERT INTO `footprint` (name, mounting, description) VALUES ('0805', 2, 'Metric 2012');",
	"INSERT INTO `footprint` (name, mounting, description) VALUES ('1206', 2, 'Metric 3216');"
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	model(NULL)
{
	ui->setupUi(this);
	setCentralWidget(ui->centralWidget);

	db = QSqlDatabase::addDatabase("QSQLITE");

	update_controls();
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::selection_changed(const QItemSelection &, const QItemSelection &)
{
	update_controls();
}

void MainWindow::on_action_open_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open component database"), "", tr("Database files (*.compdb)"));

	if (fileName.size() > 0)
		open_db(fileName);
}

void MainWindow::on_action_new_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("New component database"), "", tr("Database files (*.compdb)"));

	if (fileName.size() > 0) {
		if (! fileName.endsWith(".compdb"))
			fileName.append(".compdb");

		QFile file(fileName);
		if (file.exists() && !file.remove()) {
			QMessageBox::critical(this, "compdb", "Can't remove " + file.fileName());
			return;
		}
		create_db(fileName);
	}
}

void MainWindow::on_action_close_triggered()
{
	db.close();
	if (model)
		model->clear();
	update_controls();
}

void MainWindow::on_action_exit_triggered()
{
	close();
}

void MainWindow::on_action_add_triggered()
{
	DialogComponent dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_action_clone_triggered()
{
	QModelIndexList selection = ui->tableView->selectionModel()->selectedIndexes();

	if (selection.count() > 0) {
		int id = model->index(selection.at(0).row(), 0).data().toInt();

		DialogComponent dialog(-1, id);
		dialog.setModal(true);
		dialog.exec();
		update_view();
	}
}

void MainWindow::on_action_edit_triggered()
{
	QModelIndexList selection = ui->tableView->selectionModel()->selectedIndexes();

	if (selection.count() > 0) {
		int id = model->index(selection.at(0).row(), 0).data().toInt();
		DialogComponent dialog(id);
		dialog.setModal(true);
		dialog.exec();
		update_view();
	}
}

void MainWindow::on_action_delete_triggered()
{
	QModelIndexList selection = ui->tableView->selectionModel()->selectedIndexes();

	if (selection.count() > 0 && QMessageBox::question(this, "compdb", tr("Delete selected component?")) == QMessageBox::Yes) {
		int id = model->index(selection.at(0).row(), 0).data().toInt();

		QSqlQuery query;
		query.prepare("DELETE FROM component WHERE id = :id");
		query.bindValue(":id", id);

		if (!query.exec())
			QMessageBox::critical(this, "compdb", "Can't delete component: " + query.lastError().text());
		update_view();
	}
}

void MainWindow::on_action_category_triggered()
{
	DialogCategory dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_action_type_triggered()
{
	DialogType dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_action_footprint_triggered()
{
	DialogFootprint dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_action_temp_triggered()
{
	DialogTemp dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_group_filter_toggled(bool)
{
	update_view();
}

void MainWindow::on_cb_category_currentIndexChanged(int)
{
	update_view();
}

void MainWindow::on_cb_footprint_currentIndexChanged(int)
{
	update_view();
}

void MainWindow::on_le_part_no_textChanged(const QString &)
{
	update_view();
}

void MainWindow::on_le_value_textChanged(const QString &)
{
	update_view();
}

void MainWindow::on_le_description_textChanged(const QString &)
{
	update_view();
}

void MainWindow::update_controls()
{
	bool db_open = db.isOpen();
	bool selected = db_open && ui->tableView->selectionModel()->selectedIndexes().count() > 0;

	ui->group_components->setEnabled(db_open);
	ui->group_filter->setEnabled(db_open);
	ui->action_close->setEnabled(db_open);
	ui->action_add->setEnabled(db_open);
	ui->action_clone->setEnabled(selected);
	ui->action_edit->setEnabled(selected);
	ui->action_delete->setEnabled(selected);
	ui->action_category->setEnabled(db_open);
	ui->action_type->setEnabled(db_open);
	ui->action_footprint->setEnabled(db_open);
	ui->action_temp->setEnabled(db_open);
	setWindowTitle(db_open ? "compdb (" + db.databaseName() + ")" : "compdb (No database open)");
}

void MainWindow::update_view()
{
	int selection = ui->tableView->selectionModel()->currentIndex().row();
	int category = ui->cb_category->currentData().toInt();
	int footprint = ui->cb_footprint->currentData().toInt();
	QString part_no = ui->le_part_no->text();
	QString value = ui->le_value->text();
	QString descr = ui->le_description->text();
	QString filter;

	if (ui->group_filter->isChecked()) {
		if (category != -1)
			filter = "category = " + QString::number(category);
		if (footprint != -1) {
			if (!filter.isEmpty())
				filter += " AND ";
			filter += "footprint = " + QString::number(footprint);
		}
		if (part_no.length() > 0) {
			if (!filter.isEmpty())
				filter += " AND ";
			filter += "part_no LIKE '%" + part_no + "%'";
		}
		if (value.length() > 0) {
			if (!filter.isEmpty())
				filter += " AND ";
			filter += "value LIKE '%" + value + "%'";
		}
		if (descr.length() > 0) {
			if (!filter.isEmpty())
				filter += " AND ";
			filter += "component.description LIKE '%" + descr + "%'";
		}
	}
	model->setFilter(filter);
	if (!model->select())
		QMessageBox::critical(this, "compdb", "Can't set filter (" + filter + "): " + model->lastError().text());

	if (selection != -1)
		ui->tableView->selectRow(selection);

	update_controls();
}

void MainWindow::open_db(QString fname)
{
	QSqlRelationalTableModel *old = model;

	if (db.open())
		db.close();

	db.setDatabaseName(fname);
	if (! db.open()) {
		QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + db.lastError().text());
		return;
	}

	QSqlQuery foreign_keys("PRAGMA foreign_keys = ON");

	model = new QSqlRelationalTableModel(this);
	model->setTable("component");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
	model->setRelation(model->fieldIndex("category"), QSqlRelation("category", "id", "name"));
	model->setRelation(model->fieldIndex("footprint"), QSqlRelation("footprint", "id", "name"));
	model->setRelation(model->fieldIndex("temp"), QSqlRelation("temp", "id", "name"));

	model->setHeaderData(1, Qt::Horizontal, tr("Category"));
	model->setHeaderData(3, Qt::Horizontal, tr("Footprint"));
	model->setHeaderData(7, Qt::Horizontal, tr("Temp Coeff"));
	model->setHeaderData(model->fieldIndex("part_no"), Qt::Horizontal, tr("Part No"));
	model->setHeaderData(model->fieldIndex("value"), Qt::Horizontal, tr("Value"));
	model->setHeaderData(model->fieldIndex("voltage"), Qt::Horizontal, tr("Voltage rating"));
	model->setHeaderData(model->fieldIndex("tolerance"), Qt::Horizontal, tr("Tolerance %"));
	model->setHeaderData(model->fieldIndex("count"), Qt::Horizontal, tr("Count"));
	model->setHeaderData(model->fieldIndex("suppl"), Qt::Horizontal, tr("Supplier"));
	model->setHeaderData(model->fieldIndex("suppl_part_no"), Qt::Horizontal, tr("Supplier Part No"));
	model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, tr("Price/pcs"));
	model->setHeaderData(model->fieldIndex("price_vol"), Qt::Horizontal, tr("@ volume"));
	model->setHeaderData(model->fieldIndex("design_item_id"), Qt::Horizontal, tr("Design Item Id"));
	model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("Description"));

	ui->tableView->setModel(model);
	ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
	ui->tableView->hideColumn(0);

	if (!model->select()) {
		QMessageBox::critical(this, "compdb", "Can't open/select " + fname + ": " + model->lastError().text());
		db.close();
		update_controls();
		return;
	}

	connect(ui->tableView->selectionModel(),
			SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
			SLOT(selection_changed(const QItemSelection &, const QItemSelection &)));

	if (old)
		delete old;

	setup_category();
	setup_footprint();
	update_controls();
}

void MainWindow::create_db(QString fname)
{
	if (db.open())
		db.close();

	db.setDatabaseName(fname);

	if (! db.open()) {
		QMessageBox::critical(this, "compdb", "Can't create " + fname + ": " + db.lastError().text());
		return;
	}

	for (unsigned i = 0; i < sizeof(sql_create) / sizeof(sql_create[0]); ++ i) {
		QSqlQuery query;
		if (!query.exec(sql_create[i])) {
			QMessageBox::critical(this, "compdb", "Can't execute sql:\n" + QString(sql_create[i]) + ":\n" + query.lastError().text());
			break;
		}
	}

	db.close();

	open_db(fname);
}

void MainWindow::setup_category()
{
	int cur_index = ui->cb_category->currentIndex();

	while (ui->cb_category->count() > 0)
		ui->cb_category->removeItem(0);

	ui->cb_category->addItem("<All>", QVariant(-1));

	QSqlQuery query;
	query.exec("SELECT id, name FROM category");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_category->addItem(name, QVariant(id));
	}

	if (cur_index != -1)
		ui->cb_category->setCurrentIndex(cur_index);
}

void MainWindow::setup_footprint()
{
	int cur_index = ui->cb_footprint->currentIndex();

	while (ui->cb_footprint->count() > 0)
		ui->cb_footprint->removeItem(0);

	ui->cb_footprint->addItem("<All>", QVariant(-1));

	QSqlQuery query;
	query.exec("SELECT id, name FROM footprint");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_footprint->addItem(name, QVariant(id));
	}

	if (cur_index != -1)
		ui->cb_footprint->setCurrentIndex(cur_index);
}

