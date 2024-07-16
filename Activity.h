//
// Created by Alessandro Mazzetti on 16/07/24.
//

#ifndef REGISTRY_ACTIVITY_H
#define REGISTRY_ACTIVITY_H

#include "QString"
#include "QTime"

class Activity{
public:
    Activity(const QString& d, const QTime& s, const QTime& e) : description(d), startTime(s), endTime(e) {}

    const QString& getDescription() const {
        return description;
    }

    void setDescription(QString& toSet) {
        this->description = toSet;
    }

    const QTime& getStartTime() const {
        return startTime;
    }

    const void setStartTime(QTime& toSet) {
        this->startTime = toSet;
    }

    const QTime& getEndTime() const {
        return endTime;
    }

    void setEndTime(QTime& toSet) {
        this->endTime = toSet;
    }

private:
    QString description;
    QTime startTime;
    QTime endTime;
};

#endif //REGISTRY_ACTIVITY_H
