#ifndef STU_INFO_FUNC_H
#define STU_INFO_FUNC_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include "std.h"
#include "cardmanager.h"
#include "succeed.h"
#include "fail.h"


namespace Ui {
class stu_info_func;
}

class stu_info_func : public QDialog
{
    Q_OBJECT

public:
    explicit stu_info_func(CardManager *CM,int func_num, Person *one, QWidget *parent = nullptr);
    ~stu_info_func();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::stu_info_func *ui;
    int func_num;
    QStandardItemModel *card_model;
    CardManager *CM;
    Person *one;
};

#endif // STU_INFO_FUNC_H
