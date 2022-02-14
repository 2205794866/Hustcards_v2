#include "card.h"

Card::Card(Person *owner, std::string card_ID, std::string password)
{
    this->owner = owner;
    this->card_ID = card_ID;
    this->password = password;
    this->valid = true;
    
}

bool Card::is_valid()
{
    return this->valid;
}

std::string Card::get_card_ID()
{
    return this->card_ID;
}

Person *Card::get_owner()
{
    return this->owner;
}

bool Card::report_lost()
{
    if(this->valid == true)
    {
        this->valid = false;
        return true;
    }
    return false; 
}

bool Card::remove_lost()
{
    if(this->valid == false)
    {
        this->valid = true;
        return true;
    }
    return false;  
}