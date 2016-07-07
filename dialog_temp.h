#ifndef DIALOG_TEMP_H
#define DIALOG_TEMP_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogTemp;
}

class DialogTemp : public QDialog
{
	Q_OBJECT

public:
	explicit DialogTemp(QWidget *parent = 0);
	~DialogTemp();

private slots:
	void on_pb_new_clicked();
	void on_pb_delete_clicked();
	void on_pb_close_clicked();

private:
	QSqlTableModel *model;
	Ui::DialogTemp *ui;
};

#endif // DIALOG_TEMP_H
