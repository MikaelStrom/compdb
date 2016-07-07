#ifndef DIALOG_TYPE_H
#define DIALOG_TYPE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogType;
}

class DialogType : public QDialog
{
	Q_OBJECT

public:
	explicit DialogType(QWidget *parent = 0);
	~DialogType();

private slots:
	void on_pb_new_clicked();
	void on_pb_delete_clicked();
	void on_pb_close_clicked();

private:
	QSqlTableModel *model;
	Ui::DialogType *ui;
};

#endif // DIALOG_TYPE_H
