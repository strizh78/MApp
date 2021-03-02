#include "utils.h"

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields) {
    if (wrongFields.empty()) {
        return;
    }
    errorText->setVisible(true);
    errorText->setText("Недопустимое значение полей: " + toString(wrongFields, ", "));
}
}

QString toString(const std::vector<QString>& src, std::string sep) {
    QString result;

    for (const auto& x : src) {
        result += x + QString::fromStdString(sep);
    }
    result.resize(result.size() - sep.size());

    return result;
}

namespace Validators {
void SetValidator(const QRegExp& regExp, QLineEdit* lineEdit) {
    QRegExpValidator* regExpValidator = new QRegExpValidator(regExp);
    lineEdit->setValidator(regExpValidator);
}

void setDoubleValidator(QLineEdit* lineEdit) {
    QRegExp regExp("[0-9]*[.]?[0-9]*");
    SetValidator(regExp, lineEdit);
}

void setEnglishValidator(QLineEdit* lineEdit) {
    QRegExp regExp("[a-zA-Z]*");
    SetValidator(regExp, lineEdit);
}
}
