//
// Created by Alessandro Mazzetti on 16/07/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

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
    QTime endTime = QTime::fromString(QInputDialog::getText(this, " ", "Enter end time (hh:mm): "));

    Activity activity(description, startTime, endTime);

    registry.addActivity(currentDate, activity);

    on_dateEdit_dateChanged(currentDate);
}

void mainwindow::on_removeActivityButton_clicked() {
    QDate currentDate = ui->dateEdit->date();
    QString description = QInputDialog::getText(this, " ", "Enter activity: ");
    if ( registry.removeActivity(currentDate, description) )
        QMessageBox::information(this, " ", "Activity removed succesfully.");
    else
        QMessageBox::information(this, " ", "Activity not found!");
    return;
}