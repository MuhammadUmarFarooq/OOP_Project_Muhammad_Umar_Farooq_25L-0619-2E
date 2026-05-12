#include "Schedular.h"
#include <iostream>
#include <fstream>

using namespace std;

// All available exam time slots in a week
static const int    NUM_SLOTS = 15;
static const string TIME_SLOTS[NUM_SLOTS] = {
    "Mon 08:00", "Mon 11:00", "Mon 14:00",
    "Tue 08:00", "Tue 11:00", "Tue 14:00",
    "Wed 08:00", "Wed 11:00", "Wed 14:00",
    "Thu 08:00", "Thu 11:00", "Thu 14:00",
    "Fri 08:00", "Fri 11:00", "Fri 14:00"
};

// ── Private helpers ───────────────────────────────────────────────────────────

// Replaces map index lookup with manual linear search
int Scheduler::findVenueScheduleIdx(const string& vid) const {
    for (int i = 0; i < (int)venueSchedule.size(); i++) {
        if (venueSchedule[i].venueID == vid) return i;
    }
    return -1;
}

Course* Scheduler::findCourse(const string& cid) const {
    for (int i = 0; i < (int)courses.size(); i++)
        if (courses[i]->getCourseID() == cid) return courses[i];
    return nullptr;
}

bool Scheduler::isAvailable(const string& vid, const string& slot) const {
    int idx = findVenueScheduleIdx(vid);
    if (idx == -1) return true; // No bookings for this room yet

    const vector<string>& taken = venueSchedule[idx].takenSlots;
    // Manual loop replaces std::find from <algorithm>
    for (int i = 0; i < (int)taken.size(); i++) {
        if (taken[i] == slot) return false;
    }
    return true;
}

Venue* Scheduler::suitableVenue(Course* c, const string& slot) const {
    bool needComp = (c->getCourseType() == "Lab");
    for (int i = 0; i < (int)venues.size(); i++) {
        Venue* v = venues[i];
        if (needComp && !v->getHasComp())         continue; // Lab needs computers [cite: 6]
        if (v->getCapacity() < c->getEnrolled()) continue; // Must seat everyone [cite: 6]
        if (!isAvailable(v->getRoomID(), slot))  continue; // Slot must be free
        return v;   // first suitable venue found
    }
    return nullptr;
}

// ── Main Scheduling Algorithm ─────────────────────────────────────────────────
void Scheduler::assignVenues() {
    int assigned = 0, skipped = 0;

    for (int i = 0; i < (int)sections.size(); i++) {
        Section* sec = sections[i];
        Course* c   = findCourse(sec->getCourseID());

        if (c == nullptr) {
            cout << "[WARN] No course found for section " << sec->getSectionID() << "\n";
            continue;
        }
        // Lab courses have no exam — skip
        if (c->getExamDuration() == 0) {
            cout << "[SKIP] " << sec->getSectionID() << " is a Lab (no exam).\n";
            skipped++; continue;
        }
        if (c->getEnrolled() == 0) {
            cout << "[SKIP] " << sec->getSectionID() << " has 0 enrolled students.\n";
            skipped++; continue;
        }

        bool found = false;
        for (int s = 0; s < NUM_SLOTS && !found; s++) {
            string slot = TIME_SLOTS[s];
            Venue* v = suitableVenue(c, slot);
            if (v != nullptr) {
                sec->setVenueID(v->getRoomID()); // [cite: 3]
                sec->setTimeSlot(slot);         // [cite: 3]

                // Manual map logic: find or create booking record
                int idx = findVenueScheduleIdx(v->getRoomID());
                if (idx != -1) {
                    venueSchedule[idx].takenSlots.push_back(slot);
                } else {
                    BookingRecord newRecord;
                    newRecord.venueID = v->getRoomID();
                    newRecord.takenSlots.push_back(slot);
                    venueSchedule.push_back(newRecord);
                }

                cout << "[OK]   " << sec->getSectionID()
                     << " -> Venue: " << v->getRoomID()
                     << " @ " << slot << "\n";
                found = true;
                assigned++;
            }
        }
        if (!found) {
            cout << "[FAIL] No slot found for " << sec->getSectionID()
                 << " (needs " << c->getEnrolled() << " seats)\n";
            skipped++;
        }
    }
    cout << "\nScheduling complete: " << assigned << " assigned, "
         << skipped << " skipped.\n";
}

// ── Conflict Detection ────────────────────────────────────────────────────────
void Scheduler::detectConflicts() const {
    bool anyConflict = false;

    for (int i = 0; i < (int)venueSchedule.size(); i++) {
        const string& vid = venueSchedule[i].venueID;
        const vector<string>& slots = venueSchedule[i].takenSlots;

        // Count occurrences using nested loops since map is removed
        for (int j = 0; j < (int)slots.size(); j++) {
            int count = 0;
            for (int k = 0; k < (int)slots.size(); k++) {
                if (slots[j] == slots[k]) count++;
            }

            if (count > 1) {
                cout << "[CONFLICT] Venue " << vid
                     << " has " << count << " exams at " << slots[j] << "\n";
                anyConflict = true;
                break; // Alert once per venue/slot conflict
            }
        }
    }
    if (!anyConflict) cout << "No scheduling conflicts detected.\n";
}

void Scheduler::saveExamSchedule(const string& fp) const {
    ofstream file(fp);
    file << "SectionID|CourseID|VenueID|TimeSlot\n";
    for (int i = 0; i < (int)sections.size(); i++) {
        Section* s = sections[i];
        if (!s->getTimeSlot().empty())
            file << s->getSectionID() << "|" << s->getCourseID() << "|"
                 << s->getVenueID()   << "|" << s->getTimeSlot() << "\n";
    }
    cout << "Exam schedule saved to " << fp << "\n";
}

void Scheduler::displaySchedule() const {
    cout << "\n=== Current Exam Schedule ===\n";
    bool any = false;
    for (int i = 0; i < (int)sections.size(); i++) {
        if (!sections[i]->getTimeSlot().empty()) {
            sections[i]->display(); // [cite: 3]
            any = true;
        }
    }
    if (!any) cout << "No schedule assigned yet. Run auto-assign first.\n";
}