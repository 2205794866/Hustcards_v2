#ifndef REGEX_SEARCH_H
#define REGEX_SEARCH_H

#include <QDialog>
#include "cardmanager.h"
#include "search_result.h"


namespace Ui {
class regex_search;
}

class regex_search : public QDialog
{
    Q_OBJECT

public:
    explicit regex_search(CardManager*CM, int func_num,QWidget *parent = nullptr);
    ~regex_search();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::regex_search *ui;
    CardManager *CM;
    std::string str;
    int func_num;
};

#endif // REGEX_SEARCH_H
