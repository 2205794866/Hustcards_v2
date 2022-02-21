#ifndef CANCEL_ACCOUNT_H
#define CANCEL_ACCOUNT_H

#include <QDialog>

namespace Ui {
class cancel_account;
}

class cancel_account : public QDialog
{
    Q_OBJECT

public:
    explicit cancel_account(QWidget *parent = nullptr);
    ~cancel_account();

private:
    Ui::cancel_account *ui;
};

#endif // CANCEL_ACCOUNT_H
