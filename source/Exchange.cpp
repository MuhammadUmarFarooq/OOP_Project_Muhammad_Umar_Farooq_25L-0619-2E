#include "Exchange.h"
#include <iostream>
#include <string>
#include "Student.h"
Exchange::Exchange(string ID="", string name="", string email="", bool Semester=false):Student(ID, name, email, "Exchange") {
        this->Semester = Semester;
    }
Exchange::~Exchange() {
}