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

    void removeActivity(const QDate& targetDate, const QString& targetAct) {
        auto date = activities.find(targetDate);
        if( date != activities.end() ) {
            auto activity = date.value();
            for(auto it = activity.begin(); it != activity.end(); it++) {
                if( it->getDescription() == targetAct ) {
                    activity.erase(it);
                }
            }
        }
    }

    QList<Activity> getActivities(const QDate& date) const {
        return activities.value(date);
    }

private:

    // There can be more activities in the same day
    QMap<QDate, QList<Activity>> activities;
};

#endif //REGISTRY_REGISTRY_H
