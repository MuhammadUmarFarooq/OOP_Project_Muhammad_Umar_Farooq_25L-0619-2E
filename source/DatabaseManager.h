#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

// Include necessary headers
#include <iostream>
#include <vector>
#include <string>
#include "AcademicEntity.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Assessment.h"


#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Forward declarations
class Student;
class Course;
class Assessment;
class Regular;
class Scholarship;
class Exchange;
 

class DatabaseManager {
public:
    // Loads all students from Students.txt into a vector of pointers
    static std::vector<Student*> loadStudents(const std::string& filePath);
    
    // Saves the current state of students back to the file
    static void saveStudents(const std::string& filePath, const std::vector<Student*>& students);
};



#endif // DATABASEMANAGER_H