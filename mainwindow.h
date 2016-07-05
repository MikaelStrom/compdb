#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QtCore>
#include <QtSql>
#include <QSqlError>


class MyModel : public QSqlRelationalTableModel
{
public:
    explicit MyModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase())
		: QSqlRelationalTableModel(parent, db) {};

//    virtual Qt::ItemFlags flags(const QModelIndex& index) const // override
//    {
//       Qt::ItemFlags result = QSqlRelationalTableModel::flags(index);
//       if (index.column() != 6)
//           result &= ~Qt::ItemIsEditable;
//       return result;
//    }
};

// ***

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionCategory_triggered();
    void on_actionType_triggered();
    void on_actionFootprint_triggered();
    void on_pb_add_clicked();
    void on_pb_clone_clicked();
    void on_pb_edit_clicked();
    void on_pb_delete_clicked();
    void on_group_filter_toggled(bool arg1);
    void on_le_value_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
	QSqlDatabase db;
	MyModel *model;

	void open_db(QString fname);
	void setup_category();
	void setup_type();
	void setup_footprint();
	void update_view();
};

#endif // MAINWINDOW_H
