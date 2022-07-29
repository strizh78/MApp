#include "timetableTop.h"

#include "dailyTimeline/dailyTimeline.h"

#include "interface/basicForms/comboBox.h"
#include "interface/appointment/appointmentForm.h"
#include "interface/timetable/event/eventForm.h"

#include "interface/interfaceUtils.h"
#include "timetable/timetableUtils.h"

#include <QPainter>
#include <QVBoxLayout>

TimetableTop::TimetableTop(QWidget* parent)
    : QWidget(parent)
    , title_(new QLabel(this))
    , timeline_(new DailyTimeline(this))
{
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    auto lay = new QVBoxLayout();
    lay->setContentsMargins(25, 25, 18, 0);
    lay->setSpacing(10);
    setLayout(lay);

    auto titleLay = new QHBoxLayout();
    titleLay->setContentsMargins(0, 0, 0, 0);

    titleLay->insertWidget(titleLay->count(), title_);
    title_->setFixedHeight(27);
    titleLay->addStretch();

    createEventBox_ = new ComboBox(this);
    createEventBox_->setPlaceholderText("Создать событие");
    createEventBox_->addItem("Приём");
    createEventBox_->addItem("Событие");
    createEventBox_->setCurrentIndex(-1);

    createEventBox_->SetAlignment(Qt::AlignCenter);
    changeFont(createEventBox_, 16, QFont::Normal);
    createEventBox_->setContentsMargins(15, 0, 15, 0);
    createEventBox_->setMinimumWidth(createEventBox_->fontMetrics().horizontalAdvance(createEventBox_->currentText()) + 50);
    createEventBox_->setStyleSheet("background: palette(window); height: 35px; border-radius: 15px;");
    connect(createEventBox_, QOverload<int>::of(&ComboBox::activated), this, &TimetableTop::processCreateEventBox);

    titleLay->insertWidget(titleLay->count(), createEventBox_);

    lay->insertLayout(lay->count(), titleLay);
    lay->insertWidget(lay->count(), timeline_);
    lay->addStretch();

    setFixedHeight(minimizedHeight_);
}

void TimetableTop::setDate(QDate date) {
    timeline_->setDate(date);

    QString titleText;

    changeFont(this, 24, QFont::DemiBold);
    titleText += QString("<span style=\"font-size:24px;font-weight:500;font-family:%1\">%2 </span>")
                     .arg(font().family(), date.toString("d MMMM yyyy").toLower());

    changeFont(this, 18, QFont::Medium);
    titleText += QString("<span style=\"color:%1;font-size:18px;font-weight:400;\"> / </span>")
                     .arg(QColor(209, 211, 217).name());
    titleText += QString("<span style=\"color:%1;font-size:18px;font-weight:400;\">%2</span>")
                     .arg(QColor(128, 130, 135).name(), date.toString("dddd"));

    title_->setText(titleText);
}

void TimetableTop::setDatabase(DatabasePtr database) {
    database_ = database;
    timeline_->setDatabase(database);
}

void TimetableTop::updateData(const std::vector<TimetableEvent>& tevents) {
    timeline_->updateData(tevents);
}

void TimetableTop::processCreateEventBox() {
    if (createEventBox_->currentIndex() == -1) {
        return;
    } else if (createEventBox_->currentText() == "Приём") {
        auto* viewForm = new AppointmentForm(database_);

        viewForm->setAttribute(Qt::WA_DeleteOnClose, true);
        viewForm->show();
    } else if (createEventBox_->currentText() == "Событие") {
        auto* viewForm = new EventForm(database_);

        viewForm->setAttribute(Qt::WA_DeleteOnClose, true);
        viewForm->show();
    }

    createEventBox_->setCurrentIndex(-1);
}

void TimetableTop::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QColor backgroundColor = palette().base().color();
    painter.setPen(backgroundColor);
    painter.setBrush(backgroundColor);

    painter.drawRoundedRect(contentsRect(), 20, 20);

    if (height() <= minimizedHeight_) {
        painter.drawRect(contentsRect().left(),
                         contentsRect().center().y(),
                         contentsRect().width(),
                         contentsRect().height() - contentsRect().center().y());
    }
}
