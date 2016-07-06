#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "main_window.h"
#include "ui_main_window.h"
#include "dialog_category.h"
#include "dialog_type.h"
#include "dialog_footprint.h"
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
	"INSERT INTO `category` (name) VALUES ('Transistor');",
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

	open_db("/Users/mike/c/compdb/components.compdb");
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open component database"), "", tr("Database files (*.compdb)"));

	if (fileName.size() > 0)
		open_db(fileName);
}

void MainWindow::on_actionNew_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("New component database"), "", tr("Database files (*.compdb)"));

	if (fileName.size() > 0) {
		QFile f(fileName);
		if (f.exists() && !f.remove()) {
			QMessageBox::critical(this, "compdb", "Can't remove " + f.fileName());
			return;
		}
		create_db(fileName);
	}
}

void MainWindow::open_db(QString fname)
{
    RelTabModel *old = model;

	if (db.open())
		db.close();

	db.setDatabaseName(fname);
	if (! db.open()) {
		QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + db.lastError().text());
		return;
	}

	QSqlQuery foreign_keys ("PRAGMA foreign_keys = ON");

    model = new RelTabModel(this);
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
	model->setHeaderData(model->fieldIndex("tolerance"), Qt::Horizontal, tr("Tolerance"));
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
		QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + model->lastError().text());
		return;
	}

	if (old)
		delete old;

	setup_category();
	setup_footprint();
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

void MainWindow::update_view()
{
    int selection = ui->tableView->selectionModel()->currentIndex().row();

    model->select();

    if (selection != -1)
        ui->tableView->selectRow(selection);
}

void MainWindow::on_actionCategory_triggered()
{
	DialogCategory dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_actionType_triggered()
{
	DialogType dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_actionFootprint_triggered()
{
	DialogFootprint dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_pb_add_clicked()
{
	DialogComponent dialog;
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_pb_clone_clicked()
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

void MainWindow::on_pb_edit_clicked()
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

void MainWindow::on_pb_delete_clicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedIndexes();

    if (selection.count() > 0) {
		int id = model->index(selection.at(0).row(), 0).data().toInt();

		QSqlQuery query;
		query.prepare("DELETE FROM component WHERE id = :id");
		query.bindValue(":id", id);

		if (!query.exec())
			QMessageBox::critical(this, "compdb", "Can't delete component: " + query.lastError().text());
		update_view();
	}
}

void MainWindow::on_group_filter_toggled(bool enabled)
{
	if (enabled) {
	}
}

void MainWindow::on_le_value_textChanged(const QString &arg1)
{
	qDebug() << arg1;
}

