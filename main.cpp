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

#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>
#include <QMessageBox>
#include "main_window.h"

MainWindow* window = NULL;
QString file;

class Application : public QApplication
{
public:
	Application(int &argc, char **argv) : QApplication(argc, argv)
	{
		window = new MainWindow;
		window->show();

		if(argc > 1)
			window->open_db(QString(argv[1]));
		else if (file.size() > 0)
			window->open_db(file);
	}

	// OSX only: Events can execute BEFORE main is executed.
	bool event(QEvent *event)
	{
		if (event->type() == QEvent::FileOpen) {
			QFileOpenEvent *file_event = static_cast<QFileOpenEvent *>(event);
			if (file_event) {
				if (window != NULL)
					window->open_db(file_event->file());
				else
					file = file_event->file();
			}
		}
		return QApplication::event(event);
	}
};

int main(int argc, char *argv[])
{
	Application app(argc, argv);

	return app.exec();
}
