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
AcademicEntity(string ID="", string name="", string email="") {
    
}
virtual void displayProfile() = 0;

string getID() const { return ID; }
string getName() const { return name; }
string getEmail() const { return email; }
   
};

#endif // ACADEMICENTITY_H