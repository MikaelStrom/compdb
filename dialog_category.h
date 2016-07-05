#ifndef DIALOG_CATEGORY_H
#define DIALOG_CATEGORY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogCategory;
}

class DialogCategory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCategory(QWidget *parent = 0);
    ~DialogCategory();

private slots:
    void on_pb_new_clicked();
    void on_pb_delete_clicked();
    void on_pb_close_clicked();
	void on_row_select();

private:
	QSqlTableModel *model;
    Ui::DialogCategory *ui;
};

#endif // DIALOG_CATEGORY_H
