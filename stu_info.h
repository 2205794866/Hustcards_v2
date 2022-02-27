#ifndef STU_INFO_H
#define STU_INFO_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include "std.h"
#include "cardmanager.h"
#include "succeed.h"
#include "fail.h"


namespace Ui {
class stu_info;
}

class stu_info : public QDialog
{
    Q_OBJECT

public:
    explicit stu_info(CardManager *CM, int func_num, std::string stu_ID,QWidget *parent = nullptr);
    ~stu_info();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::stu_info *ui;
    QStandardItemModel *card_model;

    CardManager *CM;
    int func_num;
    std::string stu_ID;
};

#endif // STU_INFO_H
