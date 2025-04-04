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

// implementation for findActivity that iterates firstly through all the dates and then
// over the activitiesList in each day
QList<Activity> Registry::findActivity(const QString &name) const {

    // activities with the same name will be pushed into targetList
    QList<Activity> targetList;
    int currentYear = QDate::currentDate().year();

    for (auto i = activities.begin(); i != activities.end(); ++i) {

        const QDate& date = i.key();
        if(date.year() != currentYear)
            continue;

        const QList<Activity>& list = i.value();

        for (auto j = list.begin(); j != list.end(); ++j) {
            if (j->getDescription() == name) {
                targetList.push_back(*j);
            }
        }
    }

    return targetList;

}
