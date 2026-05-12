#ifndef VENUE_H
#define VENUE_H
#include <string>
using namespace std;

class Venue {
    string roomID;        // e.g. "A101", "LAB-3"
    int    capacity;      // max students that can sit in this room
    bool   hasComputers;  // true if room has computer workstations

public:
    static const string FILE_PATH;  // "venues.txt"

    Venue(const string& id, int cap, bool comp)
        : roomID(id), capacity(cap), hasComputers(comp) {}

    string getRoomID()   const { return roomID;       }
    int    getCapacity() const { return capacity;     }
    bool   getHasComp()  const { return hasComputers; }

    void   display()   const;
    string serialize() const;
};

#endif // VENUE_H