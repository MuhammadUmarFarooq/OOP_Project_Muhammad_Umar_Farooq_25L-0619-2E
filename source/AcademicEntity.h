#ifndef ACADEMICENTITY_H
#define ACADEMICENTITY_H


#include <string>
#include<iostream>
using namespace std;    

class AcademicEntity {
protected:// i am using protected access specifier because i want to allow derived classes to access these members directly
string ID;
string name;    
string email;
string file_path; // To store the file path for persistence


public:
virtual ~AcademicEntity() = default;
AcademicEntity(string ID="", string name="", string email="") {
    
}
virtual void displayProfile() = 0;

string getID() const { return ID; }
string getName() const { return name; }
string getEmail() const { return email; }
string getFilePath() const { return file_path; }

virtual string serialize()      const = 0;
};

#endif // ACADEMICENTITY_H