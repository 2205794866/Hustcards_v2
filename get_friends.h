#ifndef GET_FRIENDS_H
#define GET_FRIENDS_H

#include <QDialog>
#include "analyser.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include "stu_info.h"
#include "cardmanager.h"
#include "std.h"

namespace Ui
{
    class get_friends;
}

class get_friends : public QDialog
{
    Q_OBJECT

public:
    explicit get_friends(Analyser *AL, CardManager *CM, QWidget *parent = nullptr);
    ~get_friends();

private slots:
    // 查询
    void on_pushButton_clicked();

    // 显示信息
    void on_stu_table_doubleClicked(const QModelIndex &index);

private:
    Ui::get_friends *ui;
    QStandardItemModel *stu_model;
    // 分析
    Analyser *AL;
    // CM
    CardManager *CM;
};

#endif // GET_FRIENDS_H
