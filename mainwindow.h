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

private slots:
    void on_actionOpen_triggered();
    void on_actionCategory_triggered();
    void on_actionType_triggered();

private:
    Ui::MainWindow *ui;
	QSqlDatabase db;
	QSqlTableModel *model;

	void openDb(QString fname);
};

#endif // MAINWINDOW_H
