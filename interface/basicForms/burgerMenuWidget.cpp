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

        setMinimumHeight(50);
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
            if (action_->isChecked()) {
                painter.setPen(CHECKED_COLOR);
                painter.setBrush(CHECKED_COLOR);

                QFont f(font());
                f.setBold(true);
                painter.setFont(f);

                painter.drawRoundedRect(width() - higlightWidth, 0,
                                        higlightWidth, height(),
                                        higlightRadius, higlightRadius);
            }

            auto textRect = contentsRect.adjusted(iconSize_.width(), iconSize_.height() / 2., 0, 0);
            painter.drawText(textRect, 0, action_->text());
        } else {
            QIcon icon = (action_->isChecked()) ? checkedIcon : uncheckedIcon;
            auto iconRect = contentsRect.adjusted(0,
                                                  iconSize_.height() / 4,
                                                  -width() + iconSize_.width() / 2,
                                                  -height() + iconSize_.height() / 2);

            painter.drawPixmap(iconRect, icon.pixmap(iconSize_));
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
    , menuWidth_(0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    menuExpandButton_->setFlat(true);
    menuExpandButton_->setCheckable(true);
    menuExpandButton_->setIconSize(QSize(32, 32));
    menuExpandButton_->setFixedSize(32, 32);
    menuExpandButton_->setCursor(Qt::PointingHandCursor);

    menuExpandButton_->setStyleSheet("""QPushButton:checked{ \
                                            border: none;    \
                                        }                    \
                                        QPushButton:hover{   \
                                            border: none;    \
                                        }""");

    menuActionsGroup_->setExclusive(true);


    auto burgerLay = new QHBoxLayout();
    burgerLay->setContentsMargins(0, 0, 0, /* space between expandButton and menu buttons */ 50);
    burgerLay->setSpacing(0);
    burgerLay->addWidget(menuExpandButton_);
    burgerLay->addWidget(new QWidget(this));

    auto lay = new QVBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    lay->addLayout(burgerLay);
    lay->addStretch();

    setFixedWidth(40);
    setLayout(lay);

    connect(menuExpandButton_, &QPushButton::toggled, this, &BurgerMenuWidget::setExpanded);
}

void BurgerMenuWidget::setExpanded(bool expanded) {
    isExpanded = expanded;

    auto anim = new QPropertyAnimation(this, "minimumWidth", this);
    anim->setDuration(150);
    anim->setStartValue(menuExpandButton_->width());
    anim->setEndValue(menuExpandButton_->width() + menuWidth_);
    anim->setDirection(expanded ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BurgerMenuWidget::addMenuAction(QAction* action) {
    auto iconSize = QSize(20, 20);

    QFont currentFont = font();
    currentFont.setBold(true);
    auto texpPixelsLengths = QFontMetrics(currentFont).boundingRect(action->text()).width();

    int extraPixels = iconSize.width() + /* for highlight-line, when action activated */ 10;
    menuWidth_ = std::max(menuWidth_,
                          texpPixelsLengths + extraPixels);

    menuActionsGroup_->addAction(action);

    auto button = new BurgerMenuElementButton(action, iconSize, this);
    auto lay = static_cast<QVBoxLayout*>(layout());
    lay->insertWidget(lay->count() - 1, button);
}

void BurgerMenuWidget::setBurgerIcons(const QIcon& compressedStateIcon,
                                      const QIcon& expandedStateIcon)
{
    expandedStateIcon_ = changeIconColor(expandedStateIcon, Qt::black, UNCHECKED_COLOR);
    compressedStateIcon_ = changeIconColor(compressedStateIcon, Qt::black, UNCHECKED_COLOR);
}

void BurgerMenuWidget::paintEvent(QPaintEvent*) {
    menuExpandButton_->setIcon(isExpanded ? expandedStateIcon_ : compressedStateIcon_);
}
