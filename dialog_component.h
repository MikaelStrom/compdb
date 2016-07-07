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

#ifndef DIALOG_COMPONENT_H
#define DIALOG_COMPONENT_H

#include <QDialog>

namespace Ui {
class DialogComponent;
}

class DialogComponent : public QDialog
{
	Q_OBJECT

public:
	explicit DialogComponent(int edit_id = -1, int clone_id = -1, QWidget *parent = 0);
	~DialogComponent();

public Q_SLOTS:
	virtual void accept();

private slots:
	void on_btn_category_clicked();
	void on_btn_footprint_clicked();
	void on_btn_temp_clicked();

private:
	Ui::DialogComponent *ui;
	int update_id;

	void setup_combos();
};

#endif // DIALOG_COMPONENT_H
