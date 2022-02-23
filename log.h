#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "logger.h"
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class log;
}

class log : public QDialog
{
    Q_OBJECT

public:
    explicit log(QWidget *parent = nullptr);
    ~log();

private:
    Ui::log *ui;
    QStandardItemModel *operation_model;
    QStandardItemModel *consume_model;


    void insert_operation_record(operation_record *);
    void insert_consume_record(consume_record *);
};

#endif // LOG_H
