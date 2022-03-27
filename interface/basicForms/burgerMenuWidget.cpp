#include "burgerMenuWidget.h"

#include <QLayout>
#include <QBitmap>
#include <QPainter>
#include <QStyleOption>
#include <QPropertyAnimation>

namespace {
QIcon changeIconColor(const QIcon& icon, QColor oldColor, QColor newColor) {
    auto pixmap = icon.pixmap(QSize(512, 512));
    auto mask = pixmap.createMaskFromColor(oldColor, Qt::MaskOutColor);

    QPainter painter(&pixmap);
    painter.setPen(newColor);
    painter.setBrush(newColor);
    painter.drawPixmap(pixmap.rect(), mask, mask.rect());
    painter.end();

    return QIcon(pixmap);
}
}

const QColor CHECKED_COLOR(136, 79, 207);
const QColor UNCHECKED_COLOR(196, 196, 196);

bool isExpanded = false;

class BurgerMenuElementButton : public QPushButton {
public:
    BurgerMenuElementButton(QAction* action, QSize iconSize, QWidget* parent)
        : QPushButton(parent)
        , action_(action)
        , iconSize_(iconSize)
    {
        action_->setCheckable(true);
        action_->setChecked(false);

        checkedIcon = changeIconColor(action_->icon(), Qt::black, CHECKED_COLOR);
        uncheckedIcon = changeIconColor(action_->icon(), Qt::black, UNCHECKED_COLOR);

        connect(action, &QAction::destroyed, this, &BurgerMenuElementButton::deleteLater);
        connect(action_, SIGNAL(changed()), this, SLOT(update()));
        connect(this, &BurgerMenuElementButton::clicked, action_, &QAction::trigger);

        setFixedHeight(65);
        setMinimumWidth(50);
        setCursor(Qt::PointingHandCursor);
    }

    void paintEvent(QPaintEvent*) override {
        const int higlightWidth = 3;
        const int higlightRadius = 5;

        QPainter painter(this);
        QStyleOptionButton opt;
        opt.initFrom(this);

        const QRect contentsRect = style()->subElementRect(QStyle::SE_PushButtonContents, &opt, this);

        if (isExpanded) {
            QFont f(font());
            f.setPixelSize(18);

            if (action_->isChecked()) {
                painter.setPen(CHECKED_COLOR);
                painter.setBrush(CHECKED_COLOR);

                painter.drawRoundedRect(width() - higlightWidth, 0,
                                        higlightWidth, height(),
                                        higlightRadius, higlightRadius);

                f.setWeight(QFont::Bold);
            } else {
                f.setWeight(QFont::Normal);

                QColor textColor(140, 140, 140);
                painter.setPen(textColor);
                painter.setBrush(textColor);
            }
            painter.setFont(f);
            auto textRect = contentsRect.adjusted(iconSize_.width(), iconSize_.height() / 2., 0, 0);
            textRect.setLeft(50);
            painter.drawText(textRect, 0, action_->text());
        } else {
            QIcon icon = (action_->isChecked()) ? checkedIcon : uncheckedIcon;
            painter.drawPixmap(contentsRect.center().x() - iconSize_.width() / 2,
                               contentsRect.center().y() - iconSize_.height() / 2,
                               icon.pixmap((iconSize_)));
        }
    }

private:
    QAction* action_;
    QSize iconSize_;

    QIcon checkedIcon;
    QIcon uncheckedIcon;
};


BurgerMenuWidget::BurgerMenuWidget(QWidget* parent)
    : QWidget(parent)
    , menuExpandButton_(new QPushButton(this))
    , menuActionsGroup_(new QActionGroup(this))
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    menuExpandButton_->setCheckable(true);
    menuExpandButton_->setCursor(Qt::PointingHandCursor);
    menuExpandButton_->setStyleSheet("border: none;");

    menuActionsGroup_->setExclusive(true);

    burgerLay_ = new QHBoxLayout();
    burgerLay_->addWidget(menuExpandButton_);
    burgerLay_->addStretch();

    auto lay = new QVBoxLayout();
    lay->setContentsMargins(0, 35, 0, 0);
    lay->setSpacing(25);
    lay->addLayout(burgerLay_);
    lay->addStretch();

    setLayout(lay);

    setMinimumWidth(50);
    setMaximumWidth(50);

    setExpanded(false);

    connect(menuExpandButton_, &QPushButton::toggled, this, &BurgerMenuWidget::setExpanded);
}

void BurgerMenuWidget::setExpanded(bool expanded) {
    isExpanded = expanded;

    auto anim = new QPropertyAnimation(this, "minimumWidth", this);
    anim->setDuration(150);
    anim->setStartValue(50);
    anim->setEndValue(400);
    anim->setDirection(expanded ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    if (isExpanded) {
        burgerLay_->setContentsMargins(45, 0, 0, 65);
        menuExpandButton_->setIconSize(QSize(19, 19));
        menuExpandButton_->setFixedSize(19, 19);
    } else {
        burgerLay_->setContentsMargins(7, 0, 0, 65);
        menuExpandButton_->setIconSize(QSize(24, 19));
        menuExpandButton_->setFixedSize(24, 19);
    }
}

void BurgerMenuWidget::addMenuAction(QAction* action) {
    auto iconSize = QSize(20, 20);

    menuActionsGroup_->addAction(action);

    auto button = new BurgerMenuElementButton(action, iconSize, this);
    auto lay = static_cast<QVBoxLayout*>(layout());
    lay->insertWidget(lay->count() - 1, button);
}

void BurgerMenuWidget::setBurgerIcons(const QIcon& compressedStateIcon,
                                      const QIcon& expandedStateIcon)
{
    expandedStateIcon_ = expandedStateIcon;
    compressedStateIcon_ = compressedStateIcon;
}

void BurgerMenuWidget::paintEvent(QPaintEvent*) {
    menuExpandButton_->setIcon(isExpanded ? expandedStateIcon_ : compressedStateIcon_);
}
