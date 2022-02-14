#ifndef SUCCEED_H
#define SUCCEED_H

#include <QDialog>

namespace Ui {
class succeed;
}

class succeed : public QDialog
{
    Q_OBJECT

public:
    explicit succeed(QWidget *parent = nullptr);
    ~succeed();

private:
    Ui::succeed *ui;
};

#endif // SUCCEED_H
