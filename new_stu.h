#ifndef NEW_STU_H
#define NEW_STU_H

#include <QDialog>
#include "std.h"
#include "succeed.h"
#include "fail.h"
#include "cardmanager.h"

namespace Ui {
class new_stu;
}

class new_stu : public QDialog
{
    Q_OBJECT

public:
    explicit new_stu(CardManager *CM, QWidget *parent = nullptr);
    ~new_stu();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::new_stu *ui;
    CardManager *CM;
};

#endif // NEW_STU_H
