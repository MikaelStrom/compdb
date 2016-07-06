#include <QMessageBox>
#include "dialog_category.h"
#include "ui_dialog_category.h"

DialogCategory::DialogCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCategory)
{
    ui->setupUi(this);

//	connect(view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));

	model = new QSqlTableModel(this);
	model->setTable("category");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);

    if (!model->select())
        QMessageBox::critical(this, "compdb", "Can't open table categories: " + model->lastError().text());
}

DialogCategory::~DialogCategory()
{
    delete ui;
}

void DialogCategory::on_pb_new_clicked()
{
	QSqlQuery query;
    query.prepare("INSERT INTO category (name) VALUES ('<Category>')");
	query.exec();
	model->select();
	
	QModelIndex index = model->index(model->rowCount() - 1, 1);
	ui->tableView->scrollToBottom();
	ui->tableView->edit(index);
}

void DialogCategory::on_pb_delete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.count() == 1) {
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
	close();
}

