#include "dailyTimetableArchive.h"
#include "dailyTimetableEvent.h"

#include "interface/interfaceUtils.h"

#include <QPainter>
#include <QVBoxLayout>

DailyTimetableArchive::DailyTimetableArchive(DatabasePtr database, QWidget *parent)
    : QAbstractButton(parent)
    , database_(database)
{
    setCheckable(true);
    setChecked(false);

    setMouseTracking(true);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    auto layMain = new QVBoxLayout();
    layMain->setContentsMargins(25, 20, 25, 20);
    layMain->setSpacing(25);
    layMain->addStretch();
    setLayout(layMain);

    auto lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);

    layMain->insertLayout(layMain->count(), lay);

    auto layLabelsV = new QVBoxLayout();
    layLabelsV->setContentsMargins(0, 10 - 3, 0, 10 - 3);

    title_ = new QLabel("Архив прошедших событий за день", this);
    changeFont(title_, 18, QFont::Normal);
    title_->setForegroundRole(QPalette::WindowText);
    title_->setFixedHeight(title_->fontMetrics().height());
    title_->setStyleSheet("color:rgb(180, 180, 180);");
    title_->show();

    layLabelsV->insertWidget(layLabelsV->count(), title_);
    layLabelsV->addStretch();

    lay->insertLayout(lay->count(), layLabelsV);

    auto layButtonsV = new QHBoxLayout();
    layButtonsV->setContentsMargins(0, 0, 0, 0);

    buttonExpand_ = new QPushButton(this);
    buttonExpand_->setObjectName("expandButton");
    buttonExpand_->setIcon(QIcon(":/icons/bottom_arrow.png"));
    buttonExpand_->setFixedSize(18, 18);
    buttonExpand_->setStyleSheet("border: 0; background: transparent;");
    lay->insertWidget(lay->count(), buttonExpand_);

    setMinimumHeight(76);

    connect(this, &QPushButton::toggled, this, &DailyTimetableArchive::update);
}

void DailyTimetableArchive::addEvent(const TimetableEvent &event) {
    auto lay = static_cast<QVBoxLayout*>(layout());

    auto* eventWidget = new DailyTimetableEvent(event, database_, this);
    eventWidget->hide();
    eventWidget->setObjectName("event");
    lay->insertWidget(lay->count(), eventWidget);

}

void DailyTimetableArchive::update() {
    int h = 76;
    for (auto& event : findChildren<DailyTimetableEvent*>()) {
        if (event->objectName() == "event") {
            event->setVisible(isChecked());
            if (isChecked())
                h += event->height() + 25;
        }
    }

    setFixedHeight(h);

    if (isChecked()) {
        buttonExpand_->setIcon(QIcon(":/icons/top_arrow.png"));
    } else {
        buttonExpand_->setIcon(QIcon(":/icons/bottom_arrow.png"));
    }

    QWidget::update();
}

void DailyTimetableArchive::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(palette().color(QPalette::Inactive, QPalette::Window));
    painter.setBrush(palette().color(QPalette::Inactive, QPalette::Window));

    painter.drawRoundedRect(contentsRect(), 20, 20);
    painter.end();
}
