#ifndef SEARCH_STU_H
#define SEARCH_STU_H

#include <QDialog>
#include "std.h"
#include "stu_info.h"
#include "cardmanager.h"
#include "succeed.h"
#include "fail.h"

namespace Ui {
class search_stu;
}

class search_stu : public QDialog
{
    Q_OBJECT

public:
    explicit search_stu(CardManager *CM, int func_num,QWidget *parent = nullptr);
    ~search_stu();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::search_stu *ui;
    CardManager *CM;
    int func_num;
};

#endif // SEARCH_STU_H
