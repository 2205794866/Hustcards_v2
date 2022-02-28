#ifndef GET_PASSWORD_H
#define GET_PASSWORD_H

#include <QDialog>

namespace Ui {
class get_password;
}

class get_password : public QDialog
{
    Q_OBJECT

public:
    explicit get_password(std::string &pass_word,QWidget *parent = nullptr);
    ~get_password();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::get_password *ui;
    std::string &pass_word;
};

#endif // GET_PASSWORD_H
