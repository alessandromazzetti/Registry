//
// Created by Alessandro Mazzetti on 26/08/24.
//

#include <gtest/gtest.h>
#include "Activity.h"

TEST(ActivityTest, Constructor) {
    Activity activity("Lunch", QTime(12,0), QTime(13,0));

    EXPECT_EQ(activity.getDescription(), "Lunch");
    EXPECT_EQ(activity.getStartTime(), QTime(12, 0));
    EXPECT_EQ(activity.getEndTime(), QTime(13,0));
}

TEST(ActivityTest, GetterAndSetters) {
    Activity activity("Lunch", QTime(12,0), QTime(13,0));

    activity.setDescription("Call");
    EXPECT_EQ(activity.getDescription(), "Call");

    activity.setStartTime(QTime(14,0));
    EXPECT_EQ(activity.getStartTime(), QTime(14, 0));

    activity.setEndTime(QTime(15,0));
    EXPECT_EQ(activity.getEndTime(), QTime(15, 0));
}

TEST(ActivityTest, Valid) {
    Activity activity("Lunch", QTime(12,0), QTime(13,0));
    EXPECT_NO_THROW(activity.setStartTime(QTime(11, 0)));
    EXPECT_NO_THROW(activity.setEndTime(QTime(14, 0)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}