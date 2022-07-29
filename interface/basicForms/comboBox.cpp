#include "comboBox.h"

#include <QPainter>

ComboBox::ComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setBackgroundRole(QPalette::Base);
}

void ComboBox::SetAlignment(Qt::Alignment a) {
    align_ = a;
}

void ComboBox::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);

    QPixmap pix(":/icons/bottom_arrow_violet.png");
    pix = pix.scaledToWidth(10);

    auto textRect = contentsRect();
    textRect.setRight(textRect.right() - 10 - pix.width());

    auto pixRect = contentsRect();
    int textWidth = fontMetrics().horizontalAdvance(currentText());
    pixRect.setLeft(pixRect.left()  + textWidth + 10);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    style()->drawItemText(&painter, textRect, align_, palette(), true, currentText(), QPalette::Text);
    style()->drawItemPixmap(&painter, pixRect, align_, pix);

    painter.end();
}
