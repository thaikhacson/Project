// RoomManager.hpp

#ifndef ROOM_MANAGER_HPP
#define ROOM_MANAGER_HPP

#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

struct Room {
    int roomID;
    std::string name;
    bool isOccupied;

    Room(int id, std::string name, bool occupied = false) : roomID(id), name(name), isOccupied(occupied) {}
};

class RoomManager {
private:
    list<Room> rooms; // A vector to store rooms

public:
    // Add a new room
    void addRoom(int roomID);

    // Remove a room
    void removeRoom(int roomID);

    // View the status of a room
    void viewRoomStatus(int roomID);

    // List all rooms
    void listRooms();
};

#endif  // ROOM_MANAGER_HPP
