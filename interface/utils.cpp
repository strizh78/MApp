#include "utils.h"

namespace ErrorLog {
QString getWrongFieldsString(const std::vector<QString>& wrongFields) {
    QString result;
    for (auto& x : wrongFields) {
        result += x + ',';
    }
    result.resize(result.size() - 1);
    return result;
}

void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields) {
    if (wrongFields.empty()) {
        return;
    }
    errorText->setVisible(true);
    errorText->setText("Недопустимое значение полей: " + getWrongFieldsString(wrongFields));
}
}
