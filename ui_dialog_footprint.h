/********************************************************************************
** Form generated from reading UI file 'dialog_footprint.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FOOTPRINT_H
#define UI_DIALOG_FOOTPRINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogFootprint
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_new;
    QPushButton *pb_delete;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_close;

    void setupUi(QDialog *DialogFootprint)
    {
        if (DialogFootprint->objectName().isEmpty())
            DialogFootprint->setObjectName(QStringLiteral("DialogFootprint"));
        DialogFootprint->resize(367, 434);
        verticalLayout = new QVBoxLayout(DialogFootprint);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(DialogFootprint);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->horizontalHeader()->setVisible(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pb_new = new QPushButton(DialogFootprint);
        pb_new->setObjectName(QStringLiteral("pb_new"));

        horizontalLayout_2->addWidget(pb_new);

        pb_delete = new QPushButton(DialogFootprint);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));

        horizontalLayout_2->addWidget(pb_delete);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_close = new QPushButton(DialogFootprint);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        horizontalLayout_2->addWidget(pb_close);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogFootprint);

        QMetaObject::connectSlotsByName(DialogFootprint);
    } // setupUi

    void retranslateUi(QDialog *DialogFootprint)
    {
        DialogFootprint->setWindowTitle(QApplication::translate("DialogFootprint", "Footprints", 0));
        pb_new->setText(QApplication::translate("DialogFootprint", "New...", 0));
        pb_delete->setText(QApplication::translate("DialogFootprint", "Delete", 0));
        pb_close->setText(QApplication::translate("DialogFootprint", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogFootprint: public Ui_DialogFootprint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FOOTPRINT_H
