//
// Created by Alessandro Mazzetti on 16/07/24.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDateEdit"
#include "Registry.h"
#include "QTableWidget"
#include "QPushButton"
#include "QInputDialog"
#include "QMessageBox"
#include "QTime"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    activitiesList = ui->activitiesList;

    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &mainwindow::on_dateEdit_dateChanged);
    connect(ui->addActivity, &QPushButton::clicked, this, &mainwindow::on_addActivityButton_clicked);
    connect(ui->removeActivity, &QPushButton::clicked, this, &mainwindow::on_removeActivityButton_clicked);
    ui->dateEdit->setDate(QDate::currentDate());
}

mainwindow::~mainwindow() {
    delete ui;
}

Registry mainwindow::getRegistry() const {
    return registry;
}

void mainwindow::on_dateEdit_dateChanged(const QDate &date) {
    activitiesList->setRowCount(0);
    int row = 0;
    for( const auto& activity : registry.getActivities(date) ) {
        activitiesList->insertRow(row);
        activitiesList->setItem(row, 0, new QTableWidgetItem(activity.getDescription()));
        activitiesList->setItem(row, 1, new QTableWidgetItem(activity.getStartTime().toString("hh:mm")));
        activitiesList->setItem(row, 2, new QTableWidgetItem(activity.getEndTime().toString("hh:mm")));
    }
}

void mainwindow::on_addActivityButton_clicked() {
    QDate currentDate = ui->dateEdit->date();

    QString description = QInputDialog::getText(this, " ", "Enter activity: ");
    QTime startTime = QTime::fromString(QInputDialog::getText(this, " ", "Enter start time (hh:mm): "));
    try{
        if (!startTime.isValid())
            throw std::out_of_range("Start time not valid.");
    }
    catch (std::exception& e) {
        QMessageBox::information(this, "Error", "Start time is not valid!");
        return;
    }

    QTime endTime = QTime::fromString(QInputDialog::getText(this, " ", "Enter end time (hh:mm): "));
    try{
        if (!endTime.isValid() || endTime < startTime)
            throw std::out_of_range("Start time not valid.");
    }catch (std::exception& e) {
        QMessageBox::information(this, "Error", "End time is not valid!");
        return;
    }

    Activity activity(description, startTime, endTime);

    registry.addActivity(currentDate, activity);

    on_dateEdit_dateChanged(currentDate);
}

void mainwindow::on_removeActivityButton_clicked() {
    QDate currentDate = ui->dateEdit->date();
    QString activityName = QInputDialog::getText(this, "Remove Activity", "Enter activity name to remove: ");

    if (activityName.isEmpty()) {
        return;
    }

    // method to actually remove an activity. returns a boolean so the compiler can decide
    // whether refreshing the page or not
    bool activityRemoved = registry.removeActivity(currentDate, activityName);

    // refresh the display after the removal so it's visible
    if (activityRemoved) {
        QMessageBox::information(this, " ", "Activity removed successfully!");
        on_dateEdit_dateChanged(currentDate);
    } else {
        QMessageBox::information(this, "Error", "Activity not found!");
    }
}
