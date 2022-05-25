#include "dailyTimeline.h"

#include "widgets/dailyTimelineForm.h"
#include "widgets/dailyTimelineLine.h"

#include <QVBoxLayout>

DailyTimeline::DailyTimeline(QWidget *parent)
    : QWidget(parent)
    , line_(new DailyTimelineLine(this))
    , selectedEventForm_(new DailyTimelineForm(this))
{
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    auto lay = new QVBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(20);

    lay->insertWidget(lay->count(), line_);
    lay->insertWidget(lay->count(), selectedEventForm_);


    connect (line_, &DailyTimelineLine::elementSelected, selectedEventForm_, &DailyTimelineForm::setTimetableEvent);
    connect (line_, &DailyTimelineLine::elementSelected, parentWidget(), [&]() { parentWidget()->setFixedHeight(236); } );

    connect(selectedEventForm_->declinedButton, &QPushButton::clicked, line_, &DailyTimelineLine::unselect);
    connect (selectedEventForm_->declinedButton, &QPushButton::clicked, parentWidget(), [&]() { parentWidget()->setFixedHeight(152); } );

    connect(selectedEventForm_->acceptedButton, &QPushButton::clicked, line_, &DailyTimelineLine::unselect);
    connect (selectedEventForm_->acceptedButton, &QPushButton::clicked, parentWidget(), [&]() { parentWidget()->setFixedHeight(152); } );

    setLayout(lay);
}

void DailyTimeline::updateData(const std::vector<TimetableEvent> &tevents) {
    line_->updateData(tevents);
}

void DailyTimeline::setDate(QDate date) {
    line_->setDate(date);

    line_->unselect();
    selectedEventForm_->hide();
    parentWidget()->setFixedHeight(152);
}

void DailyTimeline::setDatabase(DatabasePtr database) {
    line_->setDatabase(database);
}
