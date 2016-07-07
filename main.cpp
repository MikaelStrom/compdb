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
