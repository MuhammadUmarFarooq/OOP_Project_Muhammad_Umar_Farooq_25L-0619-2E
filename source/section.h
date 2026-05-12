/*
 * CONCEPT: Link/Association Class
 * A Section ties together a Course, a Teacher, a Venue, and a TimeSlot.
 * The Scheduler fills venueID and timeSlot after running its algorithm.
 * Before scheduling, these fields are empty strings.
 */
#pragma once
#include <string>
using namespace std;

class Section {
    string sectionID;   // unique section identifier e.g. "CS101-A"
    string courseID;    // which course this section belongs to
    string teacherID;   // which teacher teaches this section
    string venueID;     // assigned by Scheduler (empty before scheduling)
    string timeSlot;    // assigned by Scheduler (empty before scheduling)

public:
    static const string FILE_PATH;  // "sections.txt"

    Section(const string& sid, const string& cid,
            const string& tid,
            const string& vid = "",   // optional — set by Scheduler later
            const string& ts  = "")   // optional — set by Scheduler later
        : sectionID(sid), courseID(cid), teacherID(tid),
          venueID(vid), timeSlot(ts) {}

    // Getters
    string getSectionID() const { return sectionID; }
    string getCourseID()  const { return courseID;  }
    string getTeacherID() const { return teacherID; }
    string getVenueID()   const { return venueID;   }
    string getTimeSlot()  const { return timeSlot;  }

    // Setters used by Scheduler
    void setVenueID (const string& v) { venueID  = v; }
    void setTimeSlot(const string& t) { timeSlot = t; }

    void   display()   const;
    string serialize() const;
};