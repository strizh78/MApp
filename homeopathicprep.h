#ifndef HOMEOPATHICPREP_H
#define HOMEOPATHICPREP_H

#include <QObject>
#include <QString>
#include <vector>

enum class GroupsOfHomeoPrep {
    MINERALS,
    PLANTS,
    ANIMALS,
    IMMATERIAL
};

enum class DilutionsOhHomeoPrep {
    D6,
    D12,
    C3,
    C6,
    C12,
    C30,
    C200,
    C1000 = 1000,
    M1 = 1000,
    M10,
    M50,
    LM1,
    LM2,
    LM3,
    LM4,
    LM5,
    LM6,
    LM7,
    LM8,
    LM9,
    LM10,
    LM11,
    LM12
};

class HomeopathicPrep : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName);
    Q_PROPERTY(QString nameLat READ nameLat WRITE setNameLat);
    Q_PROPERTY(GroupsOfHomeoPrep group READ group WRITE setGroup);
    Q_PROPERTY(std::vector<DilutionsOhHomeoPrep> availableDilutions READ availableDilutions WRITE setAvailableDilutions);

public:
    explicit HomeopathicPrep(QObject *parent = nullptr);
    QString name() const;
    void setName(QString);
    QString nameLat() const;
    void setNameLat(QString);
    GroupsOfHomeoPrep group() const;
    void setGroup(GroupsOfHomeoPrep);
    std::vector<DilutionsOhHomeoPrep> availableDilutions() const;
    void setAvailableDilutions(std::vector<DilutionsOhHomeoPrep>);

    QString view() const;

private:
    QString name_;
    QString nameLat_;
    GroupsOfHomeoPrep group_;
    std::vector<DilutionsOhHomeoPrep> availableDilutions_;

};

#endif // HOMEOPATHICPREP_H
