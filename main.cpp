#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>
#include <QMessageBox>
#include "main_window.h"

MainWindow* w = NULL;
QString start_file;

class Application : public QApplication
{
public:
	Application(int &argc, char **argv) : 
		QApplication(argc, argv) 
	{
		w = new MainWindow;
		w->show();

		if(argc > 1 && argv[1])
			w->open_db(QString(argv[1]));
		else if (start_file.size() > 0)
			w->open_db(start_file);
	}

	bool event(QEvent *event) {
		if (event->type() == QEvent::FileOpen) {
			QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
			if (openEvent) {
				if (w != NULL)
					w->open_db(QString(openEvent->file()));
				else
					start_file = openEvent->file();
			}
		}
		return QApplication::event(event);
	}

private:
};

int main(int argc, char *argv[])
{
	Application a(argc, argv);
//	MainWindow w;
//	w.show();

	return a.exec();
}
