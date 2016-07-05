/********************************************************************************
** Form generated from reading UI file 'dialog_category.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CATEGORY_H
#define UI_DIALOG_CATEGORY_H

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

class Ui_DialogCategory
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_new;
    QPushButton *pb_delete;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_close;

    void setupUi(QDialog *DialogCategory)
    {
        if (DialogCategory->objectName().isEmpty())
            DialogCategory->setObjectName(QStringLiteral("DialogCategory"));
        DialogCategory->resize(367, 434);
        verticalLayout = new QVBoxLayout(DialogCategory);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(DialogCategory);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pb_new = new QPushButton(DialogCategory);
        pb_new->setObjectName(QStringLiteral("pb_new"));

        horizontalLayout_2->addWidget(pb_new);

        pb_delete = new QPushButton(DialogCategory);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));

        horizontalLayout_2->addWidget(pb_delete);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_close = new QPushButton(DialogCategory);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        horizontalLayout_2->addWidget(pb_close);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogCategory);

        QMetaObject::connectSlotsByName(DialogCategory);
    } // setupUi

    void retranslateUi(QDialog *DialogCategory)
    {
        DialogCategory->setWindowTitle(QApplication::translate("DialogCategory", "Component Categories", 0));
        pb_new->setText(QApplication::translate("DialogCategory", "New...", 0));
        pb_delete->setText(QApplication::translate("DialogCategory", "Delete", 0));
        pb_close->setText(QApplication::translate("DialogCategory", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCategory: public Ui_DialogCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CATEGORY_H
