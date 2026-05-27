#include "FinConMarketModel.h"
#include <QColor>

namespace FinConCore {

FinConFinConMarketModel::FinConFinConMarketModel(QObject* parent) : QAbstractTableModel(parent) {}
FinConFinConMarketModel::~FinConFinConMarketModel() {}

int FinConFinConMarketModel::rowCount(const QModelIndex& parent) const {
    return data_.size();
}

int FinConFinConMarketModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant FinConFinConMarketModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= data_.size()) return QVariant();

    const auto& row = data_[index.row()];
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return row.symbol;
            case 1: return QString::number(row.price, 'f', 2);
            case 2: return QString::number(row.change, 'f', 2);
            case 3: return QString::number(row.pctChange, 'f', 2) + "%";
        }
    } else if (role == Qt::ForegroundRole) {
        if (index.column() >= 2) {
            return (row.change >= 0) ? QColor("#10b981") : QColor("#ef4444");
        }
    }
    return QVariant();
}

QVariant FinConFinConMarketModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Symbol";
            case 1: return "Price";
            case 2: return "Change";
            case 3: return "% Change";
        }
    }
    return QVariant();
}

void FinConFinConMarketModel::updateQuote(const QJsonObject& quote) {
    QString symbol = quote["symbol"].toString();
    double price = quote["price"].toDouble();

    for (int i = 0; i < data_.size(); ++i) {
        if (data_[i].symbol == symbol) {
            data_[i].price = price;
            emit dataChanged(index(i, 0), index(i, 3));
            return;
        }
    }

    beginInsertRows(QModelIndex(), data_.size(), data_.size());
    data_.push_back({symbol, price, 0.0, 0.0});
    endInsertRows();
}

}
