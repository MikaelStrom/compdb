#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_category.h"
#include "dialog_type.h"
#include "dialog_footprint.h"
#include "dialog_component.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	model(NULL)
{
	ui->setupUi(this);
	setCentralWidget(ui->centralWidget);

	db = QSqlDatabase::addDatabase("QSQLITE");

	open_db("/Users/mike/c/compdb/components.db");
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open component database"), "", tr("Database files (*.db)"));

	if (fileName.size() > 0)
		open_db(fileName);
}

void MainWindow::open_db(QString fname)
{
	QSqlTableModel *old = model;

	if (db.open()) {
		db.close();
	}

	db.setDatabaseName(fname);
	if (! db.open()) {
		QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + db.lastError().text());
		return;
	}

	model = new MyModel(this);
	model->setTable("component");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
	model->setRelation(model->fieldIndex("category"), QSqlRelation("category", "category_id", "name"));
	model->setRelation(model->fieldIndex("type"), QSqlRelation("type", "type_id", "name"));
	model->setRelation(model->fieldIndex("footprint"), QSqlRelation("footprint", "footprint_id", "name"));

	model->setHeaderData(1, Qt::Horizontal, tr("Category"));
	model->setHeaderData(2, Qt::Horizontal, tr("Type"));
	model->setHeaderData(4, Qt::Horizontal, tr("Footprint"));
	model->setHeaderData(model->fieldIndex("part_no"), Qt::Horizontal, tr("Part No"));
	model->setHeaderData(model->fieldIndex("value"), Qt::Horizontal, tr("Value"));
	model->setHeaderData(model->fieldIndex("count"), Qt::Horizontal, tr("Count"));
	model->setHeaderData(model->fieldIndex("suppl"), Qt::Horizontal, tr("Supplier"));
	model->setHeaderData(model->fieldIndex("suppl"), Qt::Horizontal, tr("Supplier"));
	model->setHeaderData(model->fieldIndex("suppl_part_no"), Qt::Horizontal, tr("Supplier Part No"));
	model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, tr("Price/pcs"));
	model->setHeaderData(model->fieldIndex("price_vol"), Qt::Horizontal, tr("@ volume"));
	model->setHeaderData(model->fieldIndex("design_item_id"), Qt::Horizontal, tr("Design Item Id"));
	model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("Description"));

	ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);

	if (!model->select()) {
		QMessageBox::critical(this, "compdb", "Can't open " + fname + ": " + model->lastError().text());
		return;
	}

	if (old)
		delete old;

	setup_category();
	setup_type();
	setup_footprint();

}

void MainWindow::setup_category()
{
	int cur_index = ui->cb_category->currentIndex();

	while (ui->cb_category->count() > 0)
		ui->cb_category->removeItem(0);

	ui->cb_category->addItem("<All>", QVariant(-1));

	QSqlQuery query;
	query.exec("SELECT category_id, name FROM category");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_category->addItem(name, QVariant(id));
	}

	if (cur_index != -1)
		ui->cb_category->setCurrentIndex(cur_index);
}

void MainWindow::setup_type()
{
	int cur_index = ui->cb_type->currentIndex();

	while (ui->cb_type->count() > 0)
		ui->cb_type->removeItem(0);

	ui->cb_type->addItem("<All>", QVariant(-1));

	QSqlQuery query;
	query.exec("SELECT type_id, name FROM type");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		ui->cb_type->addItem(name, QVariant(id));
	}

	if (cur_index != -1)
		ui->cb_type->setCurrentIndex(cur_index);
}

void MainWindow::setup_footprint()
{
	int cur_index = ui->cb_footprint->currentIndex();

	while (ui->cb_footprint->count() > 0)
		ui->cb_footprint->removeItem(0);

	ui->cb_footprint->addItem("<All>", QVariant(-1));

	QSqlQuery query;
	query.exec("SELECT footprint_id, name FROM footprint");
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
	model->select();
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
	int index = 1;
	DialogComponent dialog(-1, index);
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_pb_edit_clicked()
{
	int index = 1;
	DialogComponent dialog(index);
	dialog.setModal(true);
	dialog.exec();
	update_view();
}

void MainWindow::on_pb_delete_clicked()
{
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

