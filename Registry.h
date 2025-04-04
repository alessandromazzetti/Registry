//
// Created by Alessandro Mazzetti on 16/07/24.
//

#ifndef REGISTRY_REGISTRY_H
#define REGISTRY_REGISTRY_H

#include <QDate>
#include <QMap>
#include "Activity.h"

class Registry {
public:
    void addActivity(const QDate& date, const Activity& activity) {
        activities[date].push_back(activity);
    }

    void updateActivities(const QDate& date, const QList<Activity>& activitiesList);

    // date.value().begin() and date.value().end() are used to iterate through QList<Activity>
    bool removeActivity(const QDate& targetDate, const QString& targetAct);

    QList<Activity> getActivities(const QDate& date) const {
        return activities.value(date);
    }

    // added method to find an activity by name
    bool findActivity(const QString& name) const;

private:

    // There can be more activities in the same day
    QMap<QDate, QList<Activity>> activities;
};

#endif //REGISTRY_REGISTRY_H
