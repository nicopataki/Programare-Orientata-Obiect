#pragma once
#include <QAbstractTableModel>
#include <vector>
using std::vector;
#include <QAbstractItemView>
#include <iostream>
#include "service.h"


class MyTableModel :public QAbstractTableModel {
	std::vector<Locatar> locatari;
public:
	MyTableModel(const vector<Locatar>& loc) : locatari(loc) {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatari.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Locatar locatar = locatari[index.row()];
			if (index.column() == 0) {
				return QString::number(locatar.get_apartament());
			}
			if (index.column() == 1) {
				return QString::fromStdString(locatar.get_nume());
			}
			if (index.column() == 2) {
				return QString::number(locatar.get_suprafata());
			}
			if (index.column() == 3) {
				return QString::fromStdString(locatar.get_tip());
			}
		}
		return QVariant{};
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (orientation == Qt::Horizontal) {
			if(role == Qt::DisplayRole)
				switch (section) {
				case 0: 
					return "Apartament";
					break;
				case 1:
					return "Nume";
					break;
				case 2:
					return "Suprafata";
					break;
				case 3:
					return "Tip";
					break;
				default:
					return QString("Column %1").arg(section + 1);
					break;
				}
		}
		else if (orientation == Qt::Vertical) {
			if (role == Qt::DisplayRole)
				return section + 1;
		}
		return QVariant();
	}

	Locatar getloc(const QModelIndex &index) {
		return locatari[index.row()];
	}
	void setLocatari(const vector<Locatar>& locatar) {
		this->locatari = locatar;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};