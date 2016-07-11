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

#ifndef SORT_PROXY_H
#define SORT_PROXY_H

#include <QSortFilterProxyModel>
#include <QMap>

class SortProxy : public QSortFilterProxyModel
{
	Q_OBJECT

 public:
	SortProxy(QObject *parent = 0) : QSortFilterProxyModel(parent) {};
	void update_tables();

 protected:
	bool lessThan(const QModelIndex &left_index, const QModelIndex &right_index) const;

 private:
	typedef QMap<int, QString> Map;

	bool compare_relation(const QModelIndex &left_index, const QModelIndex &right_index, const Map& map) const;
	double interpret_value(QString s, bool& valid) const;
	void load_map(QString sql, Map& map);

	Map map_category;
	Map map_footprint;
	Map map_temp;
	Map map_suppl;
};

#endif
