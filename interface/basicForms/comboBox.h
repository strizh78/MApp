#pragma once

#include <QComboBox>

class ComboBox : public QComboBox {
public:
    ComboBox(QWidget *parent = nullptr);

    void SetAlignment(Qt::Alignment a);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    Qt::Alignment align_;
};
