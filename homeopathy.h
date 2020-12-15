#pragma once

#include <QObject>
#include <QString>

#include <vector>

namespace homeopathy {

enum class Groups {
    MINERALS,
    PLANTS,
    ANIMALS,
    IMMATERIAL
};

enum class Dilutions {
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

class Drug : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName);
    Q_PROPERTY(QString nameLat READ nameLat WRITE setNameLat);
    Q_PROPERTY(Groups group READ group WRITE setGroup);
    Q_PROPERTY(std::vector<Dilutions> availableDilutions READ availableDilutions WRITE setAvailableDilutions);

public:
    explicit Drug(QObject *parent = nullptr);
    QString name() const;
    void setName(const QString&);
    QString nameLat() const;
    void setNameLat(const QString&);
    Groups group() const;
    void setGroup(Groups);
    std::vector<Dilutions> availableDilutions() const;
    void setAvailableDilutions(const std::vector<Dilutions>&);

    QString getFullName() const;

private:
    QString name_;
    QString nameLat_;
    Groups group_;
    std::vector<Dilutions> availableDilutions_;

};

}
