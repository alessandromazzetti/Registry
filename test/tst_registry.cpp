//
// Created by Alessandro Mazzetti on 26/08/24.
//

#include <gtest/gtest.h>
#include "Registry.h"

TEST(RegistryTest, AddActivity) {
    Registry registry;
    QDate date(2024, 11, 13);
    Activity activity("Lunch", QTime(12,0), QTime(13, 0));

    registry.addActivity(date, activity);

    auto activities = registry.getActivities(date);
    ASSERT_EQ(activities.size(), 1);
    EXPECT_EQ(activities[0].getDescription(), "Lunch");
    EXPECT_EQ(activities[0].getStartTime(), QTime(12, 0));
    EXPECT_EQ(activities[0].getEndTime(), QTime(13, 0));

}

TEST(RegistryTest, GetActivities) {
    Registry registry;
    QDate date1(2024, 11, 13);
    QDate date2(2024, 11, 14);

    registry.addActivity(date1, Activity("Lunch", QTime(12, 0), QTime(13, 0)));
    registry.addActivity(date1, Activity("Call", QTime(14, 0), QTime(15, 0)));
    registry.addActivity(date2, Activity("Lecture", QTime(10, 0), QTime(11, 0)));

    auto activities1 = registry.getActivities(date1);
    ASSERT_EQ(activities1.size(), 2);
    EXPECT_EQ(activities1[0].getDescription(), "Lunch");
    EXPECT_EQ(activities1[1].getDescription(), "Call");

    auto activities2 = registry.getActivities(date2);
    ASSERT_EQ(activities2.size(), 1);
    EXPECT_EQ(activities2[0].getDescription(), "Lecture");

}

TEST(RegistryTest, RemoveActivities) {
    Registry registry;
    QDate date(2024, 11, 13);

    registry.addActivity(date, Activity("Lunch", QTime(12, 0), QTime(13, 0)));
    registry.addActivity(date, Activity("Call", QTime(14, 0), QTime(15, 0)));

    bool removed = registry.removeActivity(date, "Lunch");
    EXPECT_TRUE(removed);

    auto activities = registry.getActivities(date);
    ASSERT_EQ(activities.size(), 1);
    EXPECT_EQ(activities[0].getDescription(), "Call");

    // test for removing non-existent activities
    removed = registry.removeActivity(date, "Workshop");
    EXPECT_FALSE(removed);
}

// test for findActivities method
TEST(RegistryTest, FindActivities) {
    Registry registry;
    QDate date1(2024, 11, 13);
    QDate date2(2025, 04, 04);

    registry.addActivity(date1, Activity("Lunch", QTime(12, 0), QTime(13, 0)));
    registry.addActivity(date1, Activity("Dinner", QTime(19, 0), QTime(20, 0)));

    registry.addActivity(date2, Activity("Lunch", QTime(13, 0), QTime(14, 0)));

    bool found = registry.findActivity("Lunch");
    EXPECT_TRUE(found);

    found = registry.findActivity("Dinner");
    EXPECT_FALSE(found);

    found = registry.findActivity("Workshop");
    EXPECT_FALSE(found);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}