#include "dailyTimelineLine.h"

#include "interface/interfaceUtils.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QApplication>

DailyTimelineLine::DailyTimelineLine(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(65);
    setMouseTracking(true);
    updateUIParams();
}

void DailyTimelineLine::setDate(QDate date) {
    date_ = date;
}

void DailyTimelineLine::setDatabase(DatabasePtr database) {
    database_ = database;
}

void DailyTimelineLine::updateData(const std::vector<TimetableEvent>& tevents) {
    events_ = tevents;
    lastHour_ = std::max(
        20,
        events_.empty() ? -1 : events_.back().end.hour() + 1 * (events_.back().end.minute() != 0)
    );
    numberOfHours_ = lastHour_ - firstHour_;

    repaint();
}

void DailyTimelineLine::unselect() {
    selected_ = nullptr;
}

void DailyTimelineLine::mousePressEvent(QMouseEvent *event) {
    auto* timetableEvent = tryFindEventByPoint(event->pos());
    selected_ = timetableEvent;
    hovered_ = nullptr;

    if (selected_) {
        emit elementSelected(*selected_);
    }

    repaint();
    QWidget::mousePressEvent(event);
}

void DailyTimelineLine::mouseMoveEvent(QMouseEvent *event) {
    auto* timetableEvent = tryFindEventByPoint(event->pos());
    hovered_ = timetableEvent;
    repaint();

    QWidget::mouseMoveEvent(event);
}

void DailyTimelineLine::paintEvent(QPaintEvent *e) {
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    updateUIParams();

    drawBasicTimeline(painter);

    // рисуем события
    for (auto& event : events_) {
        if (selected_ && *selected_ == event) {
            painter.setPen(QPen(QColor(136, 79, 207), 2));
        } else {
            if (date_ < QDate::currentDate() ||
                (QDate::currentDate() == date_ && event.end < QTime::currentTime()))
            {
                event.color.setAlphaF(0.5);
            }
            painter.setPen(QPen(event.color, 2));
        }

        painter.drawLine(getXCoordByTime(event.begin), timelineY_,
                         getXCoordByTime(event.end),   timelineY_);
    }

    for (size_t i = 0; i < events_.size(); ++i) {
        if (selected_ && *selected_ == events_[i]) {
            painter.setPen(QPen(QColor(136, 79, 207), 2));
        } else {
            painter.setPen(QPen(events_[i].color, 2));
        }

        drawTicks(events_[i].begin, events_[i].end, painter);

        if (i == 0 || events_[i - 1].end != events_[i].begin) {
            drawTick(events_[i].begin, painter);
        }

        drawTick(events_[i].end, painter);
    }


    if (date_ == QDate::currentDate() && QTime::currentTime().hour() < lastHour_) {
        drawCurrentTime(painter);
    }

    drawInfoPopUp(painter);

    painter.end();
}

void DailyTimelineLine::leaveEvent(QEvent *event) {
    hovered_ = nullptr;
    repaint();

    QWidget::leaveEvent(event);
}

void DailyTimelineLine::updateUIParams() {
    int lastHourTextWidth = fontMetrics().horizontalAdvance(QString::number(lastHour_));
    int workWidth = width() - lastHourTextWidth;

    oneMinuteSize_ = workWidth / numberOfHours_ / 60.;
    xShift_ = toSeconds(QTime(firstHour_, 0)) / 60. * oneMinuteSize_;

    timelineY_ = height() - 20;
}

TimetableEvent* DailyTimelineLine::tryFindEventByPoint(QPoint pos) {
    if (abs(pos.y() - timelineY_) >= 7) {
        return nullptr;
    }

    for (auto& x : events_) {
        double start = getXCoordByTime(x.begin);
        double end = getXCoordByTime(x.end);

        if (start <= pos.x() && pos.x() <= end) {
            return &x;
        }
    }

    return nullptr;
}

void DailyTimelineLine::drawBasicTimeline(QPainter& painter) {
    // рисуем часы
    auto hourColor = QColor(128, 128, 128);
    hourColor.setAlphaF(0.5);
    painter.setPen(hourColor);

    changeFont(&painter, 14, QFont::Normal); // предположительно это Regular

    QTime time(firstHour_, 0);

    for (int i = 0; i <= numberOfHours_; ++i) {
        if (date_ < QDate::currentDate() ||
            (QDate::currentDate() == date_ && time >= QTime::currentTime()))
        {
            hourColor.setAlphaF(1.);
            painter.setPen(hourColor);
        }

        int coordX = getXCoordByTime(time);
        painter.drawText(coordX, timelineY_ - 12, time.toString("h"));

        time = time.addSecs(/*1 hour*/ 60 * 60);
    }

    // рисуем таймлайн
    painter.setPen(QPen(QColor(209, 211, 217), 2));

    painter.drawLine(getXCoordByTime(QTime(firstHour_, 0)),
                     timelineY_,
                     getXCoordByTime(QTime(lastHour_, 0)),
                     timelineY_);

    // рисуем тики
    drawTicks(QTime(firstHour_, 0), QTime(lastHour_, 1), painter);
}

void DailyTimelineLine::drawTicks(QTime start, QTime end, QPainter& painter) {
    int startInMinutes = toSeconds(start) / 60;
    int endInMinutes = toSeconds(end) / 60;

    for (int j = startInMinutes / 30 * 30; j < endInMinutes; j += 30) {
        if (j < startInMinutes) {
            continue;
        }

        drawTick(QTime(j / 60, j % 60), painter);
    }
}

void DailyTimelineLine::drawTick(QTime time, QPainter& painter, int tickHeightRedefine) {
    int x = getXCoordByTime(time);

    int tickHeight;
    switch (time.minute()) {
    case 0:
        tickHeight = 5;
        break;
    case 30:
        tickHeight = 3;
        break;
    default:
        tickHeight = 2;
    }
    if (tickHeightRedefine) {
        tickHeight = tickHeightRedefine;
    }

    painter.drawRoundedRect(x, timelineY_ - tickHeight, 1, tickHeight, 1, 1);
    painter.drawLine(x, timelineY_ - 1, x, timelineY_);
}

void DailyTimelineLine::drawInfoPopUp(QPainter& painter) {
    if (!hovered_ || !underMouse()) {
        return;
    }

    double start = toSeconds( hovered_->begin ) / 60.;
    double end = toSeconds( hovered_->end ) / 60.;

    int mid = (start + (end - start) / 2) * oneMinuteSize_ - xShift_;

    // рисуем треугольничек
    QRectF rect = QRectF(mid - 9, timelineY_ - 12 - 2, 18, 9);

    QPainterPath path;
    path.moveTo(rect.left(), rect.top());
    path.lineTo(rect.right(), rect.top());
    path.lineTo(rect.left() + 18 / 2, rect.bottom());
    path.lineTo(rect.left(), rect.top());

    painter.fillPath(path, QBrush(QColor ("white")));

    // настраиваем шрифть и вычисляем длину текста
    QString time = hovered_->begin.toString("hh:mm") + " " + "—" + " " + hovered_->end.toString("hh:mm");

    int minimumTextWidth = 21 + 21 * 2 + 21;

    changeFont(&painter, 12, QFont::Normal);
    minimumTextWidth += painter.fontMetrics().horizontalAdvance(time);
    minimumTextWidth += painter.fontMetrics().horizontalAdvance(hovered_->comment);

    changeFont(&painter, 12, QFont::Medium);
    minimumTextWidth += painter.fontMetrics().horizontalAdvance(hovered_->shortName);


    // рисуем овальчик
    int lastHourTextWidth = fontMetrics().horizontalAdvance(QString::number(lastHour_));
    int workWidth = width() - lastHourTextWidth;

    int startXCoord = mid - minimumTextWidth / 2;
    if (startXCoord < 0) {
        startXCoord = 0;
    }  else if (startXCoord > workWidth - minimumTextWidth) {
        startXCoord = workWidth - minimumTextWidth;
    }

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    painter.drawRoundedRect(startXCoord,
                            timelineY_ - 12 /* размер треугольничка + отступа */ - 32 /* толщина комментика */,
                            minimumTextWidth, 32 /* толщина комментика */,
                            16, 16);

    // текст
    changeFont(&painter, 12, QFont::Normal);
    painter.setPen(QPen(QColor(128, 128, 128), 1));
    painter.drawText(startXCoord + 21,
                     timelineY_ - 16 - painter.fontMetrics().height() / 2,
                     time);

    changeFont(&painter, 12, QFont::Medium);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(startXCoord + 21 + painter.fontMetrics().horizontalAdvance(time) + 21,
                     timelineY_ - 16 - painter.fontMetrics().height() / 2,
                     hovered_->shortName);

    changeFont(&painter, 12, QFont::Normal);
    painter.drawText(startXCoord + 21 + painter.fontMetrics().horizontalAdvance(time) + 21 +
                         painter.fontMetrics().horizontalAdvance(hovered_->shortName) + 21,
                     timelineY_ - 16 - painter.fontMetrics().height() / 2,
                     hovered_->comment);
}

void DailyTimelineLine::drawCurrentTime(QPainter& painter) {
    changeFont(&painter, 14, QFont::Medium);

    QColor timeColor;
    if (palette().window().color() == Qt::white) {
        timeColor = QColor(136, 79, 207);
    } else {
        timeColor = Qt::white;
    }
    painter.setPen(QPen(timeColor, 2));
    painter.setBrush(timeColor);

    drawTick(QTime::currentTime(), painter, 6);

    int h = painter.fontMetrics().height();
    int w = painter.fontMetrics().horizontalAdvance(QTime::currentTime().toString("hh:mm"));

    painter.drawText(QPoint(getXCoordByTime(QTime::currentTime()) - w / 2,
                            timelineY_ + 8 + h / 2),
                     QTime::currentTime().toString("hh:mm"));
}

int DailyTimelineLine::getXCoordByTime(QTime time) {
    return toSeconds( time ) / 60. * oneMinuteSize_ - xShift_;
}
