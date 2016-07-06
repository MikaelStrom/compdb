#ifndef DIALOG_FOOTPRINT_H
#define DIALOG_FOOTPRINT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogFootprint;
}

class DialogFootprint : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFootprint(QWidget *parent = 0);
    ~DialogFootprint();

private slots:
    void on_pb_new_clicked();
    void on_pb_delete_clicked();
    void on_pb_close_clicked();

    void on_pb_mounting_clicked();

private:
	QSqlRelationalTableModel *model;
    Ui::DialogFootprint *ui;
};

#endif // DIALOG_FOOTPRINT_H
