#include "timetableEntry.h"

#include "timetable/event.h"
#include "appointment/appointment.h"

#include "interface/utils.h"
#include "timetable/timetableUtils.h"

TimetableEntryDrawer::TimetableEntryDrawer(const Appointment &appointment, const TimetableDrawSettings& settings)
    : begin(appointment.date.time())
    , duration(appointment.service.duration)
    , entryTitle("Приём " + appointment.patient.nameInfo.initials)
    , entryExtraComment(appointment.service.name)
    , settings_(settings)
{
    QColor baseColor = Qt::gray;
    baseColor.setAlphaF(0.1);

    QColor extraColor = getAppointmentColor(appointment);

    setColors(baseColor, extraColor);
    setRects();

    QFont boldFont = QFont();
    boldFont.setBold(true);
    setFonts(boldFont, QFont());
}

TimetableEntryDrawer::TimetableEntryDrawer(const Event &event, const TimetableDrawSettings& settings)
    : begin(event.dateTime.time())
    , duration(event.duration)
    , entryTitle(event.title)
    , entryExtraComment(event.comment)
    , settings_(settings)
{
    QColor baseColor = Qt::gray;
    baseColor.setAlphaF(0.1);

    setColors(baseColor, {80, 172, 242});
    setRects();

    QFont boldFont = QFont();
    boldFont.setBold(true);
    setFonts(boldFont, QFont());
}

void TimetableEntryDrawer::draw(QPainter& painter) const {
    drawBackground(painter);
    drawText(painter);
}

void TimetableEntryDrawer::drawBackground(QPainter& painter) const {
    auto oldBrush = painter.brush();
    auto oldPen = painter.pen();

    painter.setPen(Qt::transparent);

    painter.setBrush(backgroundColor);
    painter.drawRoundedRect(backgroundRect, settings_.roundEntryRectRadius, settings_.roundEntryRectRadius);

    painter.setBrush(extraColor);
    painter.drawRoundedRect(extraBackRect, settings_.roundEntryRectRadius, settings_.roundEntryRectRadius);

    painter.setBrush(oldBrush);
    painter.setPen(oldPen);
}

void TimetableEntryDrawer::drawText(QPainter & painter) const {
    auto oldPen = painter.pen();
    auto oldFont = painter.font();

    painter.setPen(textColor);

    painter.setFont(titleFont);
    painter.drawText(textRect, entryTitle);

    painter.setFont(extraTextFont);
    if (textRect.height() <= settings_.oneHourHeight * 0.6) {
        QRect extraTextRect = textRect;
        QFontMetrics metrics(titleFont);
        extraTextRect.setBottomLeft(QPoint(textRect.bottomLeft().x() + metrics.horizontalAdvance(entryTitle),
                                           textRect.bottomLeft().y()));

        painter.drawText(extraTextRect, " [ " + entryExtraComment + " ]");
    } else {
        painter.drawText(textRect, "\n" + entryExtraComment);
    }



    painter.setFont(oldFont);
    painter.setPen(oldPen);
}

void TimetableEntryDrawer::setColors(QColor baseColor, QColor extColor) {
    extraColor = extColor;
    backgroundColor = baseColor;

    textColor = QWidget().palette().text().color();
}

void TimetableEntryDrawer::setRects() {
    int hoursDelta = begin.hour() - settings_.firstTimetableHour;
    int yBeg = settings_.startYCoordinate + settings_.oneHourHeight * hoursDelta + settings_.oneHourHeight * (begin.minute() / 60.) - 2;
    int yDur = settings_.oneHourHeight * (duration.hour()) + settings_.oneHourHeight * (duration.minute() / 60.) - 2;

    backgroundRect = QRect(settings_.startXCoordinate + 3, yBeg, settings_.width - settings_.startXCoordinate - 5, yDur);
    extraBackRect = QRect(backgroundRect.x(), backgroundRect.y(), settings_.extraRectWidth, backgroundRect.height());

    textRect = QRect(settings_.startXCoordinate + 9, yBeg, settings_.width - settings_.startXCoordinate, yDur);
}

void TimetableEntryDrawer::setFonts(QFont mainFont, QFont extraFont) {
    titleFont = mainFont;
    extraTextFont = extraFont;
}

void TimetableEntry::draw(QPainter& painter) const {
    drawer.draw(painter);
}

bool TimetableEntry::rectContainsPoint(const QPoint &point) const{
    return drawer.rect().contains(point);
}

