#include <QMessageBox>
#include "dialog_type.h"
#include "ui_dialog_type.h"

DialogType::DialogType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogType)
{
    ui->setupUi(this);

//	connect(view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));

	model = new QSqlTableModel(this);
	model->setTable("mounting");
	model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);
	ui->tableView->hideColumn(0);

    if (!model->select())
        QMessageBox::critical(this, "compdb", "Can't open table mounting: " + model->lastError().text());
}

DialogType::~DialogType()
{
    delete ui;
}

void DialogType::on_pb_new_clicked()
{
	QSqlQuery query;
    query.prepare("INSERT INTO mounting (name) VALUES ('<Mount>')");
	query.exec();
	model->select();
	
	QModelIndex index = model->index(model->rowCount() - 1, 1);
	ui->tableView->scrollToBottom();
	ui->tableView->edit(index);
}

void DialogType::on_pb_delete_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.count() > 0) {
        QModelIndex index = model->index(selected.at(0).row(), 0);
        int dbIndex = index.data().toInt();
   
		QSqlQuery query; 
		query.prepare("DELETE FROM mounting WHERE id = :id");
		query.bindValue(":id", dbIndex);
		if (!query.exec())
            QMessageBox::critical(this, "compdb", "Can't delete mounting: " + query.lastError().text());

		model->select();
	}
}

void DialogType::on_pb_close_clicked()
{
	close();
}
