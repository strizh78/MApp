#pragma once

#include <QSortFilterProxyModel>

#include <vector>

class MultiColumnSortFilterProxyModel : public QSortFilterProxyModel {
public:
    MultiColumnSortFilterProxyModel() = default;

private:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};
