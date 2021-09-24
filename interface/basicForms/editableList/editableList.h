#pragma once

#include <QWidget>
#include <QRegExpValidator>

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class EditableWidget; }
QT_END_NAMESPACE

class QLineEdit;
class QPushButton;

class EditableList : public QWidget {
    Q_OBJECT

public:
    EditableList(QWidget *parent = nullptr);
    ~EditableList();

    std::vector<QString> getDataList();
    void setDataList(const std::vector<QString>& data);

    void setMinimumWidth(int minWidth);
    void setRegExp(const QRegExp& regExp);

public slots:
    void addButtonClicked();
    void deleteButtonClicked();

private:
    std::pair <QLineEdit*, QPushButton*> createRow();
    void insertRow(QLineEdit* lineEdit, QPushButton* delButton);
private:
    Ui::EditableWidget *ui;

    int minWidth_ = 0;
    QRegExpValidator* validator_;
};
