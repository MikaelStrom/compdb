/*	This file is part of compdb.

	compdb - Cross plattform Electronic Component Database
	Copyright (C) 2016  Mikael Ström

	compdb is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	compdb is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with compdb.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DIALOG_SUPPL_H
#define DIALOG_SUPPL_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogSuppl;
}

class DialogSuppl : public QDialog
{
	Q_OBJECT

public:
	explicit DialogSuppl(QWidget *parent = 0);
	~DialogSuppl();

private slots:
	void on_pb_new_clicked();
	void on_pb_delete_clicked();
	void on_pb_close_clicked();

private:
	QSqlTableModel *model;
	Ui::DialogSuppl *ui;
};

#endif // DIALOG_SUPPL_H
