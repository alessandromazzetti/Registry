//
// Created by Alessandro Mazzetti on 16/07/24.
//

#include "Registry.h"

void Registry::updateActivities(const QDate& date, const QList<Activity>& activitiesList) {
    activities[date] = activitiesList;
}

bool Registry::removeActivity(const QDate& date, const QString& activityName) {
    if (!activities.contains(date)) {
        return false;
    }

    QList<Activity>& activitiesList = activities[date];
    for (auto it = activitiesList.begin(); it != activitiesList.end(); ++it) {
        if (it->getDescription() == activityName) {
            activitiesList.erase(it);
            return true;
        }
    }
    return false;
}
