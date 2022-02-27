#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include "stu_info.h"
#include "cardmanager.h"
#include "std.h"



namespace Ui {
class search_result;
}

class search_result : public QDialog
{
    Q_OBJECT

public:
    explicit search_result(CardManager *CM, std::string str, int func_num, QWidget *parent = nullptr);
    ~search_result();

private slots:
    void on_result_table_doubleClicked(const QModelIndex &index);

private:
    Ui::search_result *ui;
    QStandardItemModel *stu_model;

    CardManager *CM;
    std::string str;
    int func_num;

    bool match_0(std::string , std::string);
    bool match_1(std::string,  std::string);
};

#endif // SEARCH_RESULT_H
