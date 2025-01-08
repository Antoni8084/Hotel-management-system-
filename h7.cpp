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

struct Customer {
    string name;
    string phone;
    int roomNumber;
    int nights; // Added number of nights
};

vector<Room> rooms = {
    {101, "Single", 100.0, true},
    {102, "Single", 100.0, true},
    {201, "Double", 150.0, true},
    {202, "Double", 150.0, true},
    {301, "Suite", 300.0, true},
    {302, "Suite", 300.0, true}
};

vector<Customer> customers;

void displayRooms() {
    cout << "\n--- Room Details ---\n";
    for (const auto &room : rooms) {
        cout << "Room " << room.roomNumber << " (" << room.roomType 
             << ") - $" << room.pricePerNight << " per night. Available: " 
             << (room.isAvailable ? "Yes" : "No") << "\n";
    }
}

void bookRoom() {
    int roomNumber, nights;
    string customerName, customerPhone;

    cout << "Enter room number to book: ";
    cin >> roomNumber;
    cin.ignore();

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (!room.isAvailable) {
                cout << "Room already booked.\n";
                return;
            }
            cout << "Enter customer name: ";
            getline(cin, customerName);
            cout << "Enter customer phone number: ";
            getline(cin, customerPhone);
            cout << "Enter number of nights: ";
            cin >> nights;

            room.isAvailable = false;
            customers.push_back({customerName, customerPhone, roomNumber, nights});
            cout << "Room " << room.roomNumber << " booked successfully.\n";
            return;
        }
    }
    cout << "Invalid room number.\n";
}

void checkoutRoom() {
    int roomNumber;
    cout << "Enter room number to checkout: ";
    cin >> roomNumber;

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (room.isAvailable) {
                cout << "Room is not currently booked.\n";
                return;
            }
            room.isAvailable = true;

            // Ondoa mteja aliyekodisha
            customers.erase(remove_if(customers.begin(), customers.end(),
                [roomNumber](Customer &customer) {
                    return customer.roomNumber == roomNumber;
                }),
                customers.end());
            cout << "Checkout successful for room " << room.roomNumber << ".\n";
            return;
        }
    }
    cout << "Invalid room number.\n";
}

void displayCustomerDetails() {
    if (customers.empty()) {
        cout << "No customers have booked rooms.\n";
        return;
    }
    cout << "\n--- Customer Details ---\n";
    for (const auto &customer : customers) {
        cout << "Name: " << customer.name << ", Phone: " << customer.phone
             << ", Room: " << customer.roomNumber 
             << ", Nights: " << customer.nights << "\n";
    }
}

void calculateTotalCost() {
    if (customers.empty()) {
        cout << "No customers have booked rooms.\n";
        return;
    }

    cout << "\n--- Total Cost Per Customer ---\n";
    for (const auto &customer : customers) {
        for (const auto &room : rooms) {
            if (room.roomNumber == customer.roomNumber) {
                double totalCost = room.pricePerNight * customer.nights;
                cout << "Customer: " << customer.name 
                     << ", Room: " << customer.roomNumber 
                     << ", Total Cost: $" << totalCost << "\n";
                break;
            }
        }
    }
}

void searchRoom() {
    int roomNumber;
    cout << "Enter room number to search: ";
    cin >> roomNumber;

    for (const auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            cout << "\n--- Room Details ---\n";
            cout << "Room " << room.roomNumber << " (" << room.roomType 
                 << ") - $" << room.pricePerNight << " per night. Available: " 
                 << (room.isAvailable ? "Yes" : "No") << "\n";
            return;
        }
    }
    cout << "Room not found.\n";
}

int main() {
    int choice;
    do {
        cout << "--- Hotel Management System ---\n";
        cout << "1. Display Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Checkout Room\n";
        cout << "4. Display Customer Details\n";
        cout << "5. Calculate Total Cost\n";
        cout << "6. Search Room\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayRooms();
        } else if (choice == 2) {
            bookRoom();
        } else if (choice == 3) {
            checkoutRoom();
        } else if (choice == 4) {
            displayCustomerDetails();
        } else if (choice == 5) {
            calculateTotalCost();
        } else if (choice == 6) {
            searchRoom();
        }

    } while (choice != 7);

    return 0;
}