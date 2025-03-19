//
// Created by Alessandro Mazzetti on 26/08/24.
//

#include <QTest>
#include <QVBoxLayout>
#include "mainwindow.h"

class TestMainWindow : public QObject {
Q_OBJECT

private slots:
    void testAddActivity();
    void testRemoveActivity();
};

void TestMainWindow::testAddActivity() {
    mainwindow mainWindow;
    mainWindow.show();
    Registry registry = mainWindow.getRegistry();
    QDate date(2024, 10, 11);
    Activity activity("Lunch", QTime(12, 0), QTime(13, 0));
    registry.addActivity(date, activity);

    auto activities = registry.getActivities(date);
    QVERIFY(activities.size() == 1);
    QCOMPARE(activities[0].getDescription(), "Lunch");
    QCOMPARE(activities[0].getStartTime(), QTime(12, 0));
    QCOMPARE(activities[0].getEndTime(), QTime(13, 0));
}

void TestMainWindow::testRemoveActivity() {
    mainwindow mainWindow;
    mainWindow.show();
    Registry registry = mainWindow.getRegistry();
    QDate date(2024, 10, 11);
    Activity activity("Lunch", QTime(12, 0), QTime(13, 0));
    registry.addActivity(date, activity);

    QVERIFY(registry.removeActivity(date, "Lunch"));
    auto activities = registry.getActivities(date);
    QVERIFY(activities.empty());
}

QTEST_MAIN(TestMainWindow)
#include "tst_mainwindow.moc"