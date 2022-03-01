#ifndef GET_FRIENDS_H
#define GET_FRIENDS_H

#include <QDialog>
#include "analyser.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include "stu_info.h"
#include "cardmanager.h"
#include "std.h"




namespace Ui {
class get_friends;
}

class get_friends : public QDialog
{
    Q_OBJECT

public:
    explicit get_friends(Analyser*AL, CardManager *CM,QWidget *parent = nullptr);
    ~get_friends();

private slots:
    void on_pushButton_clicked();

    void on_stu_table_doubleClicked(const QModelIndex &index);

private:
    Ui::get_friends *ui;
    QStandardItemModel *stu_model;
    Analyser *AL;
    CardManager *CM;
};

#endif // GET_FRIENDS_H
