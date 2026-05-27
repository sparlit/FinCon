#pragma once
#include <QAbstractTableModel>
#include <QVector>
#include <QJsonObject>

namespace FinConCore {

struct FinConMarketRow {
    QString FinConStr_Symbol;
    double FinConVal_Price;
    double change;
    double pctChange;
};

class FinConMarketModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit FinConMarketModel(QObject* parent = nullptr);
    virtual ~FinConMarketModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& FinConIdx_General, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateQuote(const QJsonObject& quote);

private:
    QVector<FinConMarketRow> data_;
};

}
