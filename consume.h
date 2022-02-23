#ifndef CONSUME_H
#define CONSUME_H

#include <QDialog>
#include "canteen.h"
#include "std.h"
#include "logger.h"
#include "succeed.h"
#include "fail.h"

extern Logger logger;
namespace Ui {
class consume;
}

class consume : public QDialog
{
    Q_OBJECT

public:
    explicit consume(canteen *CT,QWidget *parent = nullptr);
    ~consume();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::consume *ui;

    canteen *CT;
};

#endif // CONSUME_H
