#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "succeed.h"
#include "stu_info.h"
#include "fail.h"
#include "search_stu.h"
#include "new_stu.h"
#include "add_money.h"
#include "logger.h"
#include "log.h"

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



    void on_show_data_clicked();

    void on_Input_all_triggered();

    void on_clear_data_clicked();

    void on_stus_info_doubleClicked(const QModelIndex &index);


    void on_open_account_triggered();

    void on_remove_person_triggered();

    void on_issue_all_card_triggered();

    void on_report_lost_triggered();

    void on_issue_card_triggered();

    void on_remove_lost_triggered();

    void on_add_money_triggered();

    void on_open_log_triggered();

private:
    Ui::MainWindow *ui;
    CardManager *CM;

    //QTableView model
    QStandardItemModel *stu_model;
    QStandardItemModel *operation_model;
    QStandardItemModel *consume_model;


    //func
    void insert_data(unsigned int row_num, std::string stu_ID, std::string name, int money);

    void insert_operation_record(operation_record *);
    void insert_consume_record(consume_record *);
};
#endif // MAINWINDOW_H
