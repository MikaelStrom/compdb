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
