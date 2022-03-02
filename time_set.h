#ifndef TIME_SET_H
#define TIME_SET_H

#include <QDialog>
#include <QDateTime>

#include "succeed.h"
#include "fail.h"
#include "logger.h"
namespace Ui
{
    class time_set;
}

class time_set : public QDialog
{
    Q_OBJECT

public:
    explicit time_set(QWidget *parent = nullptr);
    ~time_set();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::time_set *ui;
};

#endif // TIME_SET_H
