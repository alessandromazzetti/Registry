//
// Created by Alessandro Mazzetti on 16/07/24.
//

#ifndef REGISTRY_ACTIVITY_H
#define REGISTRY_ACTIVITY_H

#include "QString"
#include "QTime"

class Activity{
public:

    // added check for startTime and endTime
    Activity(const QString& d, const QTime& s, const QTime& e) : description(d),
                                                                 startTime(s),
                                                                 endTime(e) {
        if(!startTime.isValid() || !endTime.isValid())
            throw std::out_of_range("Inserted time is not valid.");

        if( endTime < startTime)
            throw std::out_of_range("End time is not valid.");

    }

    const QString& getDescription() const {
        return description;
    }

    void setDescription(QString toSet) {
        this->description = toSet;
    }

    const QTime& getStartTime() const {
        return startTime;
    }

    // added check for variable toSet
    const void setStartTime(QTime toSet) {
        if(!toSet.isValid() || toSet > endTime)
            return;

        this->startTime = toSet;
    }

    const QTime& getEndTime() const {
        return endTime;
    }

    // added check for variable toSet
    void setEndTime(QTime toSet) {
        if(!toSet.isValid() || toSet < startTime)
            return;

        this->endTime = toSet;
    }

private:
    QString description;
    QTime startTime;
    QTime endTime;
};

#endif //REGISTRY_ACTIVITY_H
