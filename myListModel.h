#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>

using std::vector;

class MyListModel :public QAbstractListModel {
private:
	vector<Locatar> locatar;
public:
	MyListModel(const vector<Locatar>& locatar): locatar{locatar} {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatar.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto loc = locatar[index.row()].get_nume();
			return QString::fromStdString(loc);
		}
		return QVariant{};
	}

	void setLoc(vector<Locatar>& locatar) {
		locatar = locatar;
		auto topIndex = createIndex(0, 0);
		auto botIndex = createIndex(rowCount(), 0);
		emit dataChanged(topIndex, botIndex);
		emit layoutChanged();
	}
};