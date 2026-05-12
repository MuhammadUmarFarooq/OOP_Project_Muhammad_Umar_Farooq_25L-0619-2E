#include "Venue.h"
#include <iostream>
using namespace std;

const string Venue::FILE_PATH = "venues.txt";

void Venue::display() const {
    cout << "Room: " << roomID
         << "  |  Capacity: " << capacity
         << "  |  Computers: " << (hasComputers ? "Yes" : "No") << "\n";
}
string Venue::serialize() const {
    // Format: RoomID|Capacity|HasComputers(1/0)
    return roomID + "|" + to_string(capacity) + "|" + (hasComputers ? "1" : "0");
}