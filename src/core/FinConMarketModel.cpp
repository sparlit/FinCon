#include "FinConMarketModel.h"
#include <QColor>

namespace FinConCore {

FinConMarketModel::FinConMarketModel(QObject* parent) : QAbstractTableModel(parent) {}
FinConMarketModel::~FinConMarketModel() {}

int FinConMarketModel::rowCount(const QModelIndex& parent) const {
    return data_.size();
}

int FinConMarketModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant FinConMarketModel::data(const QModelIndex& FinConIdx_General, int role) const {
    if (!FinConIdx_General.isValid() || FinConIdx_General.row() >= data_.size()) return QVariant();

    const auto& row = data_[FinConIdx_General.row()];
    if (role == Qt::DisplayRole) {
        switch (FinConIdx_General.column()) {
            case 0: return row.FinConStr_Symbol;
            case 1: return QString::number(row.FinConVal_Price, 'f', 2);
            case 2: return QString::number(row.change, 'f', 2);
            case 3: return QString::number(row.pctChange, 'f', 2) + "%";
        }
    } else if (role == Qt::ForegroundRole) {
        if (FinConIdx_General.column() >= 2) {
            return (row.change >= 0) ? QColor("#10b981") : QColor("#ef4444");
        }
    }
    return QVariant();
}

QVariant FinConMarketModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void FinConMarketModel::updateQuote(const QJsonObject& quote) {
    QString FinConStr_Symbol = quote["FinConStr_Symbol"].toString();
    double FinConVal_Price = quote["FinConVal_Price"].toDouble();

    for (int i = 0; i < data_.size(); ++i) {
        if (data_[i].FinConStr_Symbol == FinConStr_Symbol) {
            data_[i].FinConVal_Price = FinConVal_Price;
            emit dataChanged(index(i, 0), index(i, 3));
            return;
        }
    }

    beginInsertRows(QModelIndex(), data_.size(), data_.size());
    data_.push_back({FinConStr_Symbol, FinConVal_Price, 0.0, 0.0});
    endInsertRows();
}

}
