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

private:
	bool mode_update;
    Ui::DialogComponent *ui;

	void setup_combos();
};

#endif // DIALOG_COMPONENT_H