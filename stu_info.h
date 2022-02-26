#ifndef STU_INFO_H
#define STU_INFO_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include "std.h"
#include "cardmanager.h"

namespace Ui {
class stu_info;
}

class stu_info : public QDialog
{
    Q_OBJECT

public:
    explicit stu_info(CardManager *CM, std::string stu_ID,QWidget *parent = nullptr);
    ~stu_info();

private:
    Ui::stu_info *ui;

    QStandardItemModel *card_model;

    CardManager *CM;
    std::string stu_ID;
};

#endif // STU_INFO_H
