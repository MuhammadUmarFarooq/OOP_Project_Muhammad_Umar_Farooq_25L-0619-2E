#pragma once
#include "Section.h"
#include "Venue.h"
#include "Course.h"
#include "LabCourse.h" // Needed for dynamic_cast check
#include <vector>
#include <string>

using namespace std;

class Scheduler {
    // Custom structure to replace std::map<string, vector<string>>
    struct BookingRecord {
        string venueID;
        vector<string> takenSlots;
    };

    vector<Section*>& sections; // reference — modifies the original list
    vector<Venue*>&   venues;
    vector<Course*>&  courses;

    // Replaced map with a vector of custom structs
    vector<BookingRecord> venueSchedule;

    // Private helpers
    Course* findCourse   (const string& cid)                 const;
    bool    isAvailable  (const string& vid, const string& slot)const;
    Venue* suitableVenue(Course* c, const string& slot)        const;
    
    // Helper to find index in venueSchedule without using <map> or <algorithm>
    int findVenueScheduleIdx(const string& vid) const;

public:
    Scheduler(vector<Section*>& s, vector<Venue*>& v, vector<Course*>& c)
        : sections(s), venues(v), courses(c) {}

    void assignVenues();   // main scheduler
    void detectConflicts()                                  const;
    void saveExamSchedule(const string& fp = "exam_schedule.txt") const;
    void displaySchedule()                                  const;
};