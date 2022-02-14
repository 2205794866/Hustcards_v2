#ifndef PERSON_H
#define PERSON_H
#include "std.h"

class Card;

class Person
{
public:
    Person(std::string stu_ID, std::string name);

    std::string get_name();
    std::string get_stu_ID();
    std::vector<Card*> * get_cardlist();

    Card *get_valid_one();
    bool Person::add_card(Card *one);
    int get_money();

    bool is_valid();
    bool add_money(int x);
private:
    std::string name;
    std::string stu_ID;
    std::vector <Card *> *cardlist;
    Card *valid_one;
    bool valid;

    int money;

};

#endif // PERSON_H
