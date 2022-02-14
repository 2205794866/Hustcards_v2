#include "cardmanager.h"


CardManager::CardManager()
{
    this->start_ID = "12346";
    this->nums = 0;
}

int CardManager::get_check_code(std::string ID)
{
    int sum;
    for(int i = 0; i<6; i++)
    {
        sum += ID[i] - '0';
    }
    return (9- sum%10);
}


std::string CardManager::get_card_ID()
{
    std::string stu_ID = "3";
    int num = std::stoi(this->start_ID) + this->nums;
    stu_ID += std::to_string(num);
    stu_ID += std::to_string(get_check_code(stu_ID));
    return stu_ID;


}

bool CardManager::open_account(std::string stu_ID, std::string name)
{
    std::unordered_map<std::string, Person *>::iterator iter = Map_IDtoPerson.find(stu_ID);
    if(iter != Map_IDtoPerson.end())
    {
        return false;
    }
    Person *one = new Person(stu_ID, name);
    this->personlist.push_back(one);
    Map_IDtoPerson.insert(std::make_pair(stu_ID, one));
    return true;
}

bool CardManager::issue_card()
{
    for(int i = 0; i<this->personlist.size(); i++)
    {
        if(personlist[i]->get_cardlist()->size() == 0)
        {
            std::string card_ID = get_card_ID();
            Card* newone = new Card(personlist[i], card_ID, "8888");
            this->cardlist.push_back(newone);
            Map_CIDtoCard.insert(std::make_pair(card_ID, newone));
            personlist[i]->add_card(newone);
        }
    }
    return true;
}