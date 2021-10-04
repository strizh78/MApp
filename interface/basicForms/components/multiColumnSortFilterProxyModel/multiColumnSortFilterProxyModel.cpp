#include "multiColumnSortFilterProxyModel.h"

bool MultiColumnSortFilterProxyModel::filterAcceptsRow(
        int sourceRow,
        const QModelIndex& sourceParent) const
{
    QRegExp regExp = filterRegExp();

    if (regExp.isEmpty()) {
        return true;
    }

    for (int col = 0; col < sourceModel()->columnCount(); ++col) {
        QModelIndex curIdx = sourceModel()->index(sourceRow, col);
        QString data = curIdx.data().toString();

        if (data.contains(regExp)) {
            return true;
        }
    }
    return false;
}
