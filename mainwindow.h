#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "succeed.h"
#include "stu_info.h"
#include "fail.h"
#include "search_stu.h"
#include "new_stu.h"
#include "add_money.h"
#include "logger.h"
#include "canteen.h"
#include "consume.h"
#include "operation.h"
#include "analyser.h"


// QT headers
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>



#include "regex_search.h"
#include "time_set.h"
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

    void on_consume_triggered();

    void on_operate_all_triggered();

    void on_to_begin_clicked();

    void on_to_end_clicked();

    void on_sub_one_clicked();

    void on_add_one_clicked();

    void on_canteen_ID_valueChanged(int arg1);

    void on_tabWidget_tabBarClicked(int index);

    void on_search_person_triggered();

    void on_recover_account_triggered();

    void on_pushButton_clicked();

    void on_regex_ID_search_triggered();

    void on_regex_name_search_triggered();

    void on_summary_triggered();

private:
    Ui::MainWindow *ui;
    CardManager *CM;
    canteen *CT;
    Analyser *AL;
    //QTableView model
    QStandardItemModel *stu_model;
    QStandardItemModel *record_model;

    //func
    void insert_data(unsigned int row_num, std::string stu_ID, std::string name, int money);
    Operation *get_operation(std::string);
    Operation *get_consume_operation(std::string, int);
    void insert_record(unsigned int ,record *);
    void execute(Operation *);
};
#endif // MAINWINDOW_H
