#ifndef CARD_H
#define CARD_H
#include "std.h"
#include "person.h"

class Card
{
public:
    Card(Person *owner, std::string Card_ID, std::string password);

    bool is_valid();
    bool report_lost();
    bool remove_lost();

    std::string get_card_ID();
    Person *get_owner();



private:
    std::string password;
    std::string validTime;
    std::string card_ID;
    bool valid;
    

    Person *owner;
    

};

#endif // CARD_H
