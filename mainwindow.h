#ifndef MAINWINDOW_H
#define MAINWINDOW_H


// QT headers
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include "std.h"
#include "cardmanager.h"

QT_BEGIN_NAMESPACE


namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_search_person_triggered();

private:
    Ui::MainWindow *ui;
    CardManager *CM;

    //QTableView model
    QStandardItemModel *stu_model = new QStandardItemModel();

};
#endif // MAINWINDOW_H
