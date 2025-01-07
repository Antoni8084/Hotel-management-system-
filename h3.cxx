#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Room {
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
};

vector<Room> rooms = {
    {101, "Single", 100.0, true},
    {102, "Single", 100.0, true},
    {201, "Double", 150.0, true},
    {202, "Double", 150.0, true},
    {301, "Suite", 300.0, true},
    {302, "Suite", 300.0, true}
};

void displayRooms() {
    cout << "\n--- Room Details ---\n";
    for (const auto &room : rooms) {
        cout << "Room " << room.roomNumber << " (" << room.roomType 
             << ") - $" << room.pricePerNight << " per night. Available: " 
             << (room.isAvailable ? "Yes" : "No") << "\n";
    }
}

void bookRoom() {
    int roomNumber;
    cout << "Enter room number to book: ";
    cin >> roomNumber;

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (!room.isAvailable) {
                cout << "Room already booked.\n";
                return;
            }
            room.isAvailable = false;
            cout << "Room " << room.roomNumber << " booked successfully.\n";
            return;
        }
    }
    cout << "Invalid room number.\n";
}

int main() {
    int choice;
    do {
        cout << "--- Hotel Management System ---\n";
        cout << "1. Display Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Checkout Room\n";
        cout << "4. Display Customer Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayRooms();
        } else if (choice == 2) {
            bookRoom();
        }

    } while (choice != 5);

    return 0;
}