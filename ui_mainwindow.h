/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionCategory;
    QAction *actionType;
    QAction *actionFootprint;
    QAction *actionNew_database;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *group_filter;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *cb_category;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QComboBox *cb_type;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QComboBox *cb_footprint;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QLineEdit *le_value;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_add;
    QPushButton *pb_clone;
    QPushButton *pb_edit;
    QPushButton *pb_delete;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(775, 429);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionCategory = new QAction(MainWindow);
        actionCategory->setObjectName(QStringLiteral("actionCategory"));
        actionType = new QAction(MainWindow);
        actionType->setObjectName(QStringLiteral("actionType"));
        actionFootprint = new QAction(MainWindow);
        actionFootprint->setObjectName(QStringLiteral("actionFootprint"));
        actionNew_database = new QAction(MainWindow);
        actionNew_database->setObjectName(QStringLiteral("actionNew_database"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(24);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        group_filter = new QGroupBox(centralWidget);
        group_filter->setObjectName(QStringLiteral("group_filter"));
        group_filter->setFocusPolicy(Qt::TabFocus);
        group_filter->setCheckable(true);
        group_filter->setChecked(false);
        horizontalLayout_3 = new QHBoxLayout(group_filter);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        label_2 = new QLabel(group_filter);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        cb_category = new QComboBox(group_filter);
        cb_category->setObjectName(QStringLiteral("cb_category"));

        horizontalLayout_3->addWidget(cb_category);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label = new QLabel(group_filter);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        cb_type = new QComboBox(group_filter);
        cb_type->setObjectName(QStringLiteral("cb_type"));

        horizontalLayout_3->addWidget(cb_type);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        label_3 = new QLabel(group_filter);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        cb_footprint = new QComboBox(group_filter);
        cb_footprint->setObjectName(QStringLiteral("cb_footprint"));

        horizontalLayout_3->addWidget(cb_footprint);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_4 = new QLabel(group_filter);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        le_value = new QLineEdit(group_filter);
        le_value->setObjectName(QStringLiteral("le_value"));

        horizontalLayout_3->addWidget(le_value);

        le_value->raise();
        label_4->raise();
        cb_type->raise();
        label->raise();
        label_3->raise();
        cb_footprint->raise();
        cb_category->raise();
        label_2->raise();

        verticalLayout->addWidget(group_filter);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        tableView = new QTableView(groupBox_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout_2->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(-1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        pb_add = new QPushButton(groupBox_2);
        pb_add->setObjectName(QStringLiteral("pb_add"));

        horizontalLayout_2->addWidget(pb_add);

        pb_clone = new QPushButton(groupBox_2);
        pb_clone->setObjectName(QStringLiteral("pb_clone"));

        horizontalLayout_2->addWidget(pb_clone);

        pb_edit = new QPushButton(groupBox_2);
        pb_edit->setObjectName(QStringLiteral("pb_edit"));

        horizontalLayout_2->addWidget(pb_edit);

        pb_delete = new QPushButton(groupBox_2);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));

        horizontalLayout_2->addWidget(pb_delete);

        horizontalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 775, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionNew_database);
        menuEdit->addAction(actionType);
        menuEdit->addAction(actionCategory);
        menuEdit->addAction(actionFootprint);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "compdb", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open database...", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open component database", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionCategory->setText(QApplication::translate("MainWindow", "Edit Categories", 0));
#ifndef QT_NO_TOOLTIP
        actionCategory->setToolTip(QApplication::translate("MainWindow", "Edit Categories", 0));
#endif // QT_NO_TOOLTIP
        actionCategory->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionType->setText(QApplication::translate("MainWindow", "Edit Types", 0));
#ifndef QT_NO_TOOLTIP
        actionType->setToolTip(QApplication::translate("MainWindow", "Edit Types", 0));
#endif // QT_NO_TOOLTIP
        actionType->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0));
        actionFootprint->setText(QApplication::translate("MainWindow", "Edit Footprints", 0));
#ifndef QT_NO_TOOLTIP
        actionFootprint->setToolTip(QApplication::translate("MainWindow", "Edit Footprints", 0));
#endif // QT_NO_TOOLTIP
        actionFootprint->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0));
        actionNew_database->setText(QApplication::translate("MainWindow", "New database...", 0));
        actionNew_database->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        group_filter->setTitle(QApplication::translate("MainWindow", "Filter", 0));
        label_2->setText(QApplication::translate("MainWindow", "Category", 0));
        cb_category->clear();
        cb_category->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "<All>", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Type", 0));
        cb_type->clear();
        cb_type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "<All>", 0)
        );
        label_3->setText(QApplication::translate("MainWindow", "Footprint", 0));
        cb_footprint->clear();
        cb_footprint->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "<All>", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "Value", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Components", 0));
        pb_add->setText(QApplication::translate("MainWindow", "Add", 0));
        pb_clone->setText(QApplication::translate("MainWindow", "Clone", 0));
        pb_edit->setText(QApplication::translate("MainWindow", "Edit", 0));
        pb_delete->setText(QApplication::translate("MainWindow", "Delete", 0));
        menuFile->setWindowTitle(QApplication::translate("MainWindow", "compdb", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
