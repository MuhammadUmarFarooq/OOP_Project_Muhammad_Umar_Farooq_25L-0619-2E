#include "Student.h"
#include <iostream>
#include <string>

Student::Student(string ID="", string name="", string email="", string Type=""):AcademicEntity(ID, name, email) {
    this->Type = Type;
}
