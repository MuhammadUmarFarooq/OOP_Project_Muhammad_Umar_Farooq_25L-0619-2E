#include "DatabaseManager.h"
#include "Regular.h"
#include "Scholarship.h"
#include "Exchange.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

std::vector<Student*> DatabaseManager::loadStudents(const std::string& filePath) {
    std::vector<Student*> students;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, type, email, extra;
        
        // Parsing the format: ID | Name | Type | Email | ExtraParam
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, email, '|');
        std::getline(ss, extra, '|');

        // Polymorphic instantiation based on 'Type' 
        if (type == "Regular") {
            students.push_back(new Regular(id, name, email));
        } else if (type == "Scholarship") {
            // Scholarship logic requires a bool for selection status 
            students.push_back(new Scholarship(id, name,email,extra == "1"));
        } else if (type == "Exchange") {
            students.push_back(new Exchange(id,name,email,extra == "1"));
        }
    }
    return students;
}