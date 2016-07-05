/********************************************************************************
** Form generated from reading UI file 'dialog_component.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_COMPONENT_H
#define UI_DIALOG_COMPONENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogComponent
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *cb_category;
    QLabel *label;
    QComboBox *cb_type;
    QLabel *label_3;
    QComboBox *cb_footprint;
    QLabel *label_4;
    QLineEdit *le_part_no;
    QLabel *label_5;
    QLineEdit *le_value;
    QLabel *label_6;
    QSpinBox *sp_count;
    QLabel *label_7;
    QLineEdit *le_supplier;
    QLabel *label_9;
    QLineEdit *le_supplier_part_no;
    QLabel *label_8;
    QLineEdit *le_price_volume;
    QLabel *label_12;
    QLabel *label_10;
    QLineEdit *le_design_item_id;
    QLabel *label_11;
    QLineEdit *le_descrtion;
    QSpinBox *sp_volume;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogComponent)
    {
        if (DialogComponent->objectName().isEmpty())
            DialogComponent->setObjectName(QStringLiteral("DialogComponent"));
        DialogComponent->resize(448, 431);
        verticalLayout = new QVBoxLayout(DialogComponent);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(DialogComponent);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        cb_category = new QComboBox(DialogComponent);
        cb_category->setObjectName(QStringLiteral("cb_category"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_category);

        label = new QLabel(DialogComponent);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        cb_type = new QComboBox(DialogComponent);
        cb_type->setObjectName(QStringLiteral("cb_type"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cb_type);

        label_3 = new QLabel(DialogComponent);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cb_footprint = new QComboBox(DialogComponent);
        cb_footprint->setObjectName(QStringLiteral("cb_footprint"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_footprint);

        label_4 = new QLabel(DialogComponent);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        le_part_no = new QLineEdit(DialogComponent);
        le_part_no->setObjectName(QStringLiteral("le_part_no"));

        formLayout->setWidget(3, QFormLayout::FieldRole, le_part_no);

        label_5 = new QLabel(DialogComponent);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        le_value = new QLineEdit(DialogComponent);
        le_value->setObjectName(QStringLiteral("le_value"));

        formLayout->setWidget(4, QFormLayout::FieldRole, le_value);

        label_6 = new QLabel(DialogComponent);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        sp_count = new QSpinBox(DialogComponent);
        sp_count->setObjectName(QStringLiteral("sp_count"));

        formLayout->setWidget(5, QFormLayout::FieldRole, sp_count);

        label_7 = new QLabel(DialogComponent);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        le_supplier = new QLineEdit(DialogComponent);
        le_supplier->setObjectName(QStringLiteral("le_supplier"));

        formLayout->setWidget(6, QFormLayout::FieldRole, le_supplier);

        label_9 = new QLabel(DialogComponent);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_9);

        le_supplier_part_no = new QLineEdit(DialogComponent);
        le_supplier_part_no->setObjectName(QStringLiteral("le_supplier_part_no"));

        formLayout->setWidget(7, QFormLayout::FieldRole, le_supplier_part_no);

        label_8 = new QLabel(DialogComponent);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_8);

        le_price_volume = new QLineEdit(DialogComponent);
        le_price_volume->setObjectName(QStringLiteral("le_price_volume"));

        formLayout->setWidget(8, QFormLayout::FieldRole, le_price_volume);

        label_12 = new QLabel(DialogComponent);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_12);

        label_10 = new QLabel(DialogComponent);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_10);

        le_design_item_id = new QLineEdit(DialogComponent);
        le_design_item_id->setObjectName(QStringLiteral("le_design_item_id"));

        formLayout->setWidget(10, QFormLayout::FieldRole, le_design_item_id);

        label_11 = new QLabel(DialogComponent);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_11);

        le_descrtion = new QLineEdit(DialogComponent);
        le_descrtion->setObjectName(QStringLiteral("le_descrtion"));

        formLayout->setWidget(11, QFormLayout::FieldRole, le_descrtion);

        sp_volume = new QSpinBox(DialogComponent);
        sp_volume->setObjectName(QStringLiteral("sp_volume"));

        formLayout->setWidget(9, QFormLayout::FieldRole, sp_volume);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DialogComponent);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogComponent);
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogComponent, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogComponent, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogComponent);
    } // setupUi

    void retranslateUi(QDialog *DialogComponent)
    {
        DialogComponent->setWindowTitle(QApplication::translate("DialogComponent", "Dialog", 0));
        label_2->setText(QApplication::translate("DialogComponent", "Category", 0));
        label->setText(QApplication::translate("DialogComponent", "Type", 0));
        label_3->setText(QApplication::translate("DialogComponent", "Footprint", 0));
        label_4->setText(QApplication::translate("DialogComponent", "Part No", 0));
        label_5->setText(QApplication::translate("DialogComponent", "Value", 0));
        label_6->setText(QApplication::translate("DialogComponent", "Count", 0));
        label_7->setText(QApplication::translate("DialogComponent", "Supplier", 0));
        label_9->setText(QApplication::translate("DialogComponent", "Supplier Part No", 0));
        label_8->setText(QApplication::translate("DialogComponent", "Price @ volume", 0));
        label_12->setText(QApplication::translate("DialogComponent", "Volume", 0));
        label_10->setText(QApplication::translate("DialogComponent", "Design Item Id", 0));
        label_11->setText(QApplication::translate("DialogComponent", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogComponent: public Ui_DialogComponent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_COMPONENT_H
