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

#include <QtGui>
#include <QSqlQuery>
#include <QSqlError>
#include "sort_proxy.h"
#include "db_defs.h"

bool SortProxy::lessThan(const QModelIndex &left_index, const QModelIndex &right_index) const
 {
	if (left_index.column() != right_index.column())
		return QSortFilterProxyModel::lessThan(left_index, right_index);

	QVariant left_q = sourceModel()->data(left_index);
	QVariant right_q = sourceModel()->data(right_index);

	if (!left_q.isValid() || left_q.isNull())
		return false;
	if (!right_q.isValid() || right_q.isNull())
		return true;

	QString left = left_q.toString().trimmed();
	QString right = right_q.toString().trimmed();

	if (left.isEmpty())
		return false;
	if (right.isEmpty())
		return true;

	switch (left_index.column()) {
		case COLUMN_CATEGORY:
			return compare_relation(left_index, right_index, map_category);
		case COLUMN_FOOTPRINT:
			return compare_relation(left_index, right_index, map_footprint);
		case COLUMN_TEMP:
			return compare_relation(left_index, right_index, map_temp);
		case COLUMN_SUPPL:
			return compare_relation(left_index, right_index, map_suppl);
		case COLUMN_VALUE:
		case COLUMN_AMP:
		case COLUMN_VOLTAGE:
		case COLUMN_POWER:
		case COLUMN_TOLERANCE:
		{
			bool lok, rok, less;
			less = interpret_value(left, lok) < interpret_value(right, rok);
			if (lok && rok)
				return less;
			return QString::compare(left, right) < 0;
		}
		default:
			return QSortFilterProxyModel::lessThan(left_index, right_index);
	}
}

bool SortProxy::compare_relation(const QModelIndex &left_index, const QModelIndex &right_index, const Map& map) const
{
	int id_left = left_index.data().toInt();
	int id_right = right_index.data().toInt();

	if (! map.isEmpty()) {
		if (!map.contains(id_left))
				return true;
		if (!map.contains(id_right))
				return false;;

		return map[id_left] < map[id_right];
	}
	return QSortFilterProxyModel::lessThan(left_index, right_index);
}

double SortProxy::interpret_value(QString s, bool& valid) const
{
	int i = 0;
	bool inv = false;
	bool neg = false;
	bool dec = false;
	QString val;
	double mul;

	valid = false;

	if (s.size() > 2 && s[0] == '1' && s[1] == '/') {	// 1/10W
		inv = true;
		i = 2;
	} else if (s[i] == '-') {
		neg = true;
		++i;
	} else if (s[i] == QChar(177)) {	// ±
		while (i < s.size() && !s[i].isNumber())
			++i;
		if (i == s.size() || !s[i].isNumber())
			return 0.0;
	}

	for (; i < s.size(); ++i) {
		if (s[i].isNumber())
			val += s[i];
		else if (s[i] == ',')
			continue;
		else if (s[i] == '.') {
			if (dec)
				return 0.0;
			dec = true;
			val += s[i];
        } else
			break;
	}

	if (s.contains("fS", Qt::CaseInsensitive))
		mul = 1e-15;
	else if (s.contains("ppm", Qt::CaseInsensitive))
		mul = 1e-6;
	else if (s.contains("%"))
		mul = 1e-2;
	else if (s[i] == 'p' || s[i] == 'P')
		mul = 1e-12;
	else if (s[i] == 'n' || s[i] == 'N')
		mul = 1e-9;
	else if (s[i] == 'u' || s[i] == 'U' || s[i] == QChar(181))	// µ
		mul = 1e-6;
	else if (s[i] == 'm')
		mul = 1e-3;
	else if (s[i] == 'k' || s[i] == 'K')
		mul = 1e3;
	else if (s[i] == 'M')
		mul = 1e6;
	else if (s[i] == 'g' || s[i] == 'G')
		mul = 1e9;
	else
		mul = 1.0;

	double n = val.toDouble(&valid);
//	double n = val.toDouble(&valid) * (neg ? -1.0 : 1.0);	// might want this as option?

	return inv ? 1.0 / n * mul : n * mul;
}

void SortProxy::update_tables()
{
	load_map("SELECT id, name FROM category", map_category);
	load_map("SELECT id, name FROM footprint", map_footprint);
	load_map("SELECT id, name FROM temp", map_temp);
	load_map("SELECT id, name FROM suppl", map_suppl);
}

void SortProxy::load_map(QString sql, Map& map)
{
	map.clear();

	QSqlQuery query;

	if(query.exec(sql)) {
		while (query.next())
			map[query.value(0).toInt()] = query.value(1).toString();
	} else
		qDebug() << "SortProxy failed to read table: " << sql << ": " << query.lastError().text();
}
