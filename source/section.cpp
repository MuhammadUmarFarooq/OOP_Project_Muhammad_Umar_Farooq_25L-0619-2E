#include "Section.h"
#include <iostream>
using namespace std;

const string Section::FILE_PATH = "sections.txt";

void Section::display() const {
    cout << "Section : " << sectionID
         << "  |  Course: "  << courseID
         << "  |  Teacher: " << teacherID
         << "  |  Venue: "   << (venueID.empty()  ? "TBD" : venueID)
         << "  |  Slot: "    << (timeSlot.empty() ? "TBD" : timeSlot)
         << "\n";
}
string Section::serialize() const {
    // Format: SectionID|CourseID|TeacherID|VenueID|TimeSlot
    return sectionID + "|" + courseID + "|" + teacherID
         + "|" + venueID + "|" + timeSlot;
}
