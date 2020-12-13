#include "homeopathicprep.h"

HomeopathicPrep::HomeopathicPrep(QObject *parent) : QObject(parent){
}

QString HomeopathicPrep::name() const {
    return name_;
}

void HomeopathicPrep::setName(QString name) {
    name_ = name;
}

QString HomeopathicPrep::nameLat() const {
    return nameLat_;
}

void HomeopathicPrep::setNameLat(QString nameLat) {
    nameLat_ = nameLat;
}

GroupsOfHomeoPrep HomeopathicPrep::group() const {
    return group_;
}

void HomeopathicPrep::setGroup(GroupsOfHomeoPrep group) {
    group_ = group;
}

std::vector<DilutionsOhHomeoPrep> HomeopathicPrep::availableDilutions() const {
    return availableDilutions_;
}

void HomeopathicPrep::setAvailableDilutions(std::vector<DilutionsOhHomeoPrep> availableDilutions) {
    availableDilutions_ = availableDilutions;
}

QString HomeopathicPrep::view() const {
    QString homeoPrepView = name_;

    if (nameLat_.size())
        homeoPrepView += " (" + nameLat_ + ")";

    return homeoPrepView;
}
