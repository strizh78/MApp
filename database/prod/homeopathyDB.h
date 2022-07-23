#pragma once

#include "itemProdInterface.h"

#include "drugs/homeopathy.h"

class HomeopathyDB : public ItemDBProdInterface<homeopathy::Drug> {
public:
    HomeopathyDB();

protected:
    homeopathy::Drug rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const homeopathy::Drug& item) override;
};
