#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class EditableWidget; }
QT_END_NAMESPACE

class EditableWidget : public QWidget
{
    Q_OBJECT

public:
    EditableWidget(QWidget *parent = nullptr);
    ~EditableWidget();

public slots:
    void addButtonClicked();

private:
    Ui::EditableWidget *ui;
};
