#include "Scholarship.h"
#include <iostream>
#include <string>
#include "Student.h"
#include "AcademicEntity.h"


Scholarship::Scholarship(string ID, string name, string email, bool selectedForScholarship):Student(ID, name, email, "Scholarship") {
    this->ScholarshipMantained = selectedForScholarship;                                                                          
}

