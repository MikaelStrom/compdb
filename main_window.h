#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QtCore>
#include <QtSql>
#include <QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void open_db(QString fname);

public slots:
	void selection_changed(const QItemSelection &, const QItemSelection &);

private slots:
	void on_action_open_triggered();
	void on_action_new_triggered();
	void on_action_close_triggered();
	void on_action_exit_triggered();
	void on_action_add_triggered();
	void on_action_clone_triggered();
	void on_action_edit_triggered();
	void on_action_delete_triggered();
	void on_action_category_triggered();
	void on_action_type_triggered();
	void on_action_footprint_triggered();
	void on_action_temp_triggered();
	void on_group_filter_toggled(bool arg1);
    void on_cb_category_currentIndexChanged(int index);
    void on_cb_footprint_currentIndexChanged(int index);
    void on_le_part_no_textChanged(const QString &arg1);
	void on_le_value_textChanged(const QString &arg1);
    void on_le_description_textChanged(const QString &arg1);

private:
	Ui::MainWindow *ui;
	QSqlDatabase db;
	QSqlRelationalTableModel *model;

	void update_controls();
	void update_view();
	void create_db(QString fname);
	void setup_category();
	void setup_footprint();
};

#endif // MAINWINDOW_H
