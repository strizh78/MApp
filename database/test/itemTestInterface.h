#pragma once

#include "database/itemDatabaseInterface.h"

template <class BaseItem>
class ItemDBTestInterface : public ItemDBInterface<BaseItem> {
public:
    ItemDBTestInterface() = default;

    int nextCode() override {
        return ++code_;
    }

    void list(std::vector<BaseItem>& receiver) override {
        receiver = list_;
    }
    void add(BaseItem& item) override {
        ItemDBInterface<BaseItem>::setCode(item);
        list_.push_back(item);
    }
    void edit(const BaseItem& oldItem, BaseItem& newItem) override {
        auto it = std::find(list_.begin(), list_.end(), oldItem);

        if (it != list_.end()) {
            ItemDBInterface<BaseItem>::setCodeToEdit(newItem, oldItem.code());
            *it = newItem;
        }
    }

protected:
    static std::vector<BaseItem> list_;
    static int code_;
};
