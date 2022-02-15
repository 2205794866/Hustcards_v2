#ifndef SEARCH_STU_H
#define SEARCH_STU_H

#include <QDialog>

namespace Ui {
class search_stu;
}

class search_stu : public QDialog
{
    Q_OBJECT

public:
    explicit search_stu(QWidget *parent = nullptr);
    ~search_stu();

private:
    Ui::search_stu *ui;
};

#endif // SEARCH_STU_H
