#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "succeed.h"
#include "stu_info.h"
#include "fail.h"
#include "search_stu.h"




// QT headers
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include "stu_info.h"

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

private:
    Ui::MainWindow *ui;
    CardManager *CM;

    //QTableView model
    QStandardItemModel *stu_model = new QStandardItemModel();



    //func
    void insert_data(unsigned int row_num, std::string stu_ID, std::string name, int money);
};
#endif // MAINWINDOW_H
