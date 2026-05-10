#include "DatabaseManager.h"
#include "Regular.h"
#include "Scholarship.h"
#include "Exchange.h"
#include "WeightageConfig.h"


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


void DatabaseManager::loadWeightages(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        // Manual parsing without stringstream [cite: 1591, 1592]
        int p1 = (int)line.find('|');
        int p2 = (int)line.find('|', p1 + 1);
        int p3 = (int)line.find('|', p2 + 1);

        if (p1 != -1 && p2 != -1 && p3 != -1) {
            // Populate the static vectors in WeightageConfig directly
            WeightageConfig::types.push_back(line.substr(0, p1));
            WeightageConfig::examPcts.push_back(std::stod(line.substr(p1 + 1, p2 - p1 - 1)));
            WeightageConfig::assignPcts.push_back(std::stod(line.substr(p2 + 1, p3 - p2 - 1)));
            WeightageConfig::quizPcts.push_back(std::stod(line.substr(p3 + 1)));
        }
    }
}