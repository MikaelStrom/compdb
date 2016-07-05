/********************************************************************************
** Form generated from reading UI file 'dialog_type.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_TYPE_H
#define UI_DIALOG_TYPE_H

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

class Ui_DialogType
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_new;
    QPushButton *pb_delete;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_close;

    void setupUi(QDialog *DialogType)
    {
        if (DialogType->objectName().isEmpty())
            DialogType->setObjectName(QStringLiteral("DialogType"));
        DialogType->resize(367, 434);
        verticalLayout = new QVBoxLayout(DialogType);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(DialogType);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pb_new = new QPushButton(DialogType);
        pb_new->setObjectName(QStringLiteral("pb_new"));

        horizontalLayout_2->addWidget(pb_new);

        pb_delete = new QPushButton(DialogType);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));

        horizontalLayout_2->addWidget(pb_delete);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_close = new QPushButton(DialogType);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        horizontalLayout_2->addWidget(pb_close);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogType);

        QMetaObject::connectSlotsByName(DialogType);
    } // setupUi

    void retranslateUi(QDialog *DialogType)
    {
        DialogType->setWindowTitle(QApplication::translate("DialogType", "Component Types", 0));
        pb_new->setText(QApplication::translate("DialogType", "New...", 0));
        pb_delete->setText(QApplication::translate("DialogType", "Delete", 0));
        pb_close->setText(QApplication::translate("DialogType", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogType: public Ui_DialogType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_TYPE_H
