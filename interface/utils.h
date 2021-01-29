#pragma once

#include <QString>
#include <QLabel>

#include <vector>

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields);
}
