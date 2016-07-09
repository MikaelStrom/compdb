/*	This file is part of compdb.

	compdb - Cross plattform Electronic Component Database
	Copyright (C) 2016	Mikael Ström

	compdb is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	compdb is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with compdb.	If not, see <http://www.gnu.org/licenses/>.
*/

#include <QComboBox>
#include <QSpinBox>
#include <QDebug>
#include <QSqlError>
#include "rel_delegate.h"
#include "db_defs.h"

RelationDelegate::RelationDelegate(QObject *parent) :
	QStyledItemDelegate(parent)
{
}

QWidget* RelationDelegate::createEditor(QWidget *parent,
										const QStyleOptionViewItem &option,
										const QModelIndex &index) const
{
	QWidget* e;

	switch (index.column()) {
		case COLUMN_CATEGORY:
		{
			QComboBox *editor = new QComboBox(parent);
			editor->setFrame(false);

			QSqlQuery query;
			query.exec("SELECT id, name FROM category ORDER BY name ASC");
			while (query.next()) {
				int id = query.value(0).toInt();
				QString name = query.value(1).toString();
				editor->addItem(name, QVariant(id));
			}
			e = editor;
			break;
		}
		case COLUMN_FOOTPRINT:
		{
			QComboBox *editor = new QComboBox(parent);
			editor->setFrame(false);

			QSqlQuery query;
			query.exec("SELECT id, name FROM footprint ORDER BY name ASC");
			while (query.next()) {
				int id = query.value(0).toInt();
				QString name = query.value(1).toString();
				editor->addItem(name, QVariant(id));
			}
			e = editor;
			break;
		}
		case COLUMN_TEMP:
		{
			QComboBox *editor = new QComboBox(parent);
			editor->setFrame(false);

			QSqlQuery query;
			query.exec("SELECT id, name FROM temp ORDER BY name ASC");
			while (query.next()) {
				int id = query.value(0).toInt();
				QString name = query.value(1).toString();
				editor->addItem(name, QVariant(id));
			}
			e = editor;
			break;
		}
		case COLUMN_COUNT:
		case COLUMN_PRICE_VOL:
		{
			QSpinBox *editor = new QSpinBox(parent);
			editor->setFrame(false);
			editor->setMinimum(0);
			editor->setMaximum(10000000);
			e = editor;
			break;
		}
		default:
			e = QStyledItemDelegate::createEditor(parent, option, index);
	}

	return e;
}

void RelationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	switch (index.column()) {
		case COLUMN_CATEGORY:
		case COLUMN_FOOTPRINT:
		case COLUMN_TEMP:
		{
			QComboBox *cb = static_cast<QComboBox*>(editor);
			for (int i = 0 ; i < cb->count(); ++ i)
				if (cb->itemData(i).toInt() == index.model()->data(index, Qt::EditRole).toInt()) {
					cb->setCurrentIndex(i);
					break;
				}
			break;
		}
		case COLUMN_COUNT:
		case COLUMN_PRICE_VOL:
		{
			int value = index.model()->data(index, Qt::EditRole).toInt();
			QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
			spinBox->setValue(value);
			break;
		}
		default:
			QStyledItemDelegate::setEditorData(editor, index);
			break;
	}
}

void RelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
									const QModelIndex &index) const
{
	switch (index.column()) {
		case COLUMN_CATEGORY:
		case COLUMN_FOOTPRINT:
		case COLUMN_TEMP:
		{
			QComboBox *cb = static_cast<QComboBox*>(editor);
			if (cb->currentData().isValid()) {
				int value = cb->currentData().toInt();
				model->setData(index, value, Qt::EditRole);
			} else
				qDebug() << "Invalid combobox data!";
			break;
		}
		case COLUMN_COUNT:
		case COLUMN_PRICE_VOL:
		{
			QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
			spinBox->interpretText();
			int value = spinBox->value();
			model->setData(index, value, Qt::EditRole);
			break;
		}
		default:
			QStyledItemDelegate::setModelData(editor, model, index);
			break;
	}
}

void RelationDelegate::updateEditorGeometry(QWidget *editor,
											const QStyleOptionViewItem &option,
											const QModelIndex &) const
{
   editor->setGeometry(option.rect);
}

void RelationDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
	switch (index.column()) {
		case COLUMN_VALUE:
		case COLUMN_VOLTAGE:
		case COLUMN_AMP:
		case COLUMN_POWER:
		case COLUMN_TOLERANCE:
		case COLUMN_TEMP:
		case COLUMN_COUNT:
		case COLUMN_PRICE:
		case COLUMN_PRICE_VOL:
			option->displayAlignment = Qt::AlignRight;
			break;
	}

	// a bit hackish: let base class prepare and then override text
	QStyledItemDelegate::initStyleOption(option, index);

	QVariant value = index.data(Qt::DisplayRole);

	if(index.column() == COLUMN_CATEGORY || index.column() == COLUMN_FOOTPRINT || index.column() == COLUMN_TEMP) {
		if (value.isValid() && !value.isNull()) {
			int id = index.model()->data(index, Qt::EditRole).toInt();
			QString q;
			switch (index.column()) {
				case COLUMN_CATEGORY:	q = "SELECT name FROM category WHERE id = :id"; break;
				case COLUMN_FOOTPRINT:	q = "SELECT name FROM footprint WHERE id = :id"; break;
				case COLUMN_TEMP:		q = "SELECT name FROM temp WHERE id = :id";	break;
			}
			QSqlQuery query;
			query.prepare(q);
			query.bindValue(":id", id);

			if (!query.exec())
				qDebug() << "sql query failed '" << query.lastQuery() << "': " <<  query.lastError().text();
			else if (query.next())
				option->text = displayText(query.value(0).toString(), option->locale);
		}
	}
}
