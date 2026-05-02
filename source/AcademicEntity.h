#ifndef ACADEMICENTITY_H
#define ACADEMICENTITY_H


#include <string>
#include<iostream>
using namespace std;    

class AcademicEntity {
private:
string ID;
string name;    
string email;

public:
AcademicEntity(string ID, string name, string email) {
    this->ID = ID;
    this->name = name;
    this->email = email;
}
virtual void displayProfile() = 0;


};

#endif // ACADEMICENTITY_H