//
// Created by Alessandro Mazzetti on 16/07/24.
//

#ifndef REGISTRY_MAINWINDOW_H
#define REGISTRY_MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <QTableWidget>
#include <QPushButton>
#include "Registry.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

    Registry getRegistry() const;

    void on_dateEdit_dateChanged(const QDate& date);
    void on_addActivityButton_clicked();
    void on_removeActivityButton_clicked();

private:
    Ui::mainwindow *ui;
    Registry registry;
    QTableWidget* activitiesList;
};


#endif //REGISTRY_MAINWINDOW_H
