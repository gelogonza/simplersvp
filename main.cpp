/* Program name: Restaurant Management System
*  Author: Angelo
*  Date last updated: 12/12/2023
* Purpose: Allows user to input reservations, food orders, table numbers, paying bills,
tracking tables, and closing the restaurant once all reservations are satisfied.
*/




#include <iostream>
#include <string>

// Constants for array sizes
const int MAX_RESERVATIONS = 50;
const int MAX_ORDERS = 50;
const int MAX_TABLES = 20;

struct Reservation {
    std::string customerName;
    std::string time;
    int numberOfPeople;
    bool isCheckedIn;
};

struct Table {
    int tableNumber;
    int size;
    int currentOccupancy;
    bool isOccupied;
};

struct Order {
    int tableNumber;
    int menuItems[10]; // Assuming a max of 10 items per order
    int numItems;
    bool isComplete;
    bool isPaid;
};

// Enum for Menu Items
enum MenuItem {
    VeggieBurger = 35,
    Hamburger = 45,
    FriedChickenSliders = 38,
    HamburgerSliders = 38,
    VeggieSliders = 38,
    HaddockSandwich = 38,
    BLT = 42,
    FauxBLT = 42,
    ChickenBurrito = 42,
    FalafelWrap = 42,
    CheesePizza = 59,
    PepperoniPizza = 59,
    FauxMeatAndChips = 77,
    FishAndChips = 77
};

// Arrays for managing data
Reservation reservations[MAX_RESERVATIONS];
Order orders[MAX_ORDERS];
Table tables[MAX_TABLES];

void initializeTables() {
    for (int i = 0; i < MAX_TABLES; ++i) {
        tables[i].tableNumber = i + 1; // Table numbers start from 1
        tables[i].isOccupied = false;
        tables[i].currentOccupancy = 0;

        // Assign sizes to tables (example logic, adjust as needed)
        if (i < 8) tables[i].size = 2;  // First 8 tables are for 2 people
        else if (i < 10) tables[i].size = 10; // Next 2 tables are for 10 People
        else if (i < 14) tables[i].size = 6;  // Next 4 tables are for 6 people
        else tables[i].size = 4;  // Remaining 6 tables are for 4 people
    }
}

void makeReservation() {
    // Find an available spot in the reservations array
    int availableIndex = -1;
    for (int i = 0; i < MAX_RESERVATIONS; ++i) {
        if (reservations[i].customerName.empty()) { // assuming an empty name means unused spot
            availableIndex = i;
            break;
        }
    }

    if (availableIndex == -1) {
        std::cout << "Sorry, we're fully booked!" << std::endl;
        return;
    }

    // Input reservation details
    Reservation newReservation;
    std::cout << "Enter customer name: ";
    std::cin.ignore(); // Clears the newline character from the buffer
    std::getline(std::cin, newReservation.customerName);
    
    std::cout << "Enter time for the reservation in HH:MM AM/PM: ";
    std::getline(std::cin, newReservation.time); // Now time includes AM/PM

    std::cout << "Enter number of people: ";
    std::cin >> newReservation.numberOfPeople;

    if (newReservation.numberOfPeople > 10) {
        std::cout << "Sorry, we cannot accommodate more than 10 people per reservation.\n";
        return;
    }

    newReservation.isCheckedIn = false;

    // Add the new reservation to the array
    reservations[availableIndex] = newReservation;
    std::cout << "Reservation made successfully for " << newReservation.customerName << " at " << newReservation.time << std::endl;
}


void checkInReservation() {
    std::string customerName;
    std::cout << "Enter customer name for check-in: ";
    std::cin.ignore();
    std::getline(std::cin, customerName);

    // Find the reservation
    int resIndex = -1;
    for (int i = 0; i < MAX_RESERVATIONS; ++i) {
        if (reservations[i].customerName == customerName && !reservations[i].isCheckedIn) {
            resIndex = i;
            break;
        }
    }

    if (resIndex == -1) {
        std::cout << "Reservation not found or already checked in." << std::endl;
        return;
    }

    // Find a suitable table
    int tableIndex = -1;
    for (int i = 0; i < MAX_TABLES; ++i) {
        if (!tables[i].isOccupied && tables[i].size >= reservations[resIndex].numberOfPeople) {
            tableIndex = i;
            break;
        }
    }

    if (tableIndex == -1) {
        std::cout << "No suitable table available." << std::endl;
        return;
    }

    // Update reservation and table status
    reservations[resIndex].isCheckedIn = true;
    tables[tableIndex].isOccupied = true;
    tables[tableIndex].currentOccupancy = reservations[resIndex].numberOfPeople;

    std::cout << "Reservation for " << customerName << " checked in at table " << tables[tableIndex].tableNumber << std::endl;
}

void enterOrder() {
    int tableNumber;
    std::cout << "Enter table number for order: ";
    std::cin >> tableNumber;

    // Find the table
    int tableIndex = -1;
    for (int i = 0; i < MAX_TABLES; ++i) {
        if (tables[i].tableNumber == tableNumber && tables[i].isOccupied) {
            tableIndex = i;
            break;
        }
    }

    if (tableIndex == -1) {
        std::cout << "Table not found or not occupied." << std::endl;
        return;
    }

    // Find an available spot in the orders 
    int orderIndex = -1;
    for (int i = 0; i < MAX_ORDERS; ++i) {
        if (orders[i].numItems == 0) { // assuming an empty order has 0 items
            orderIndex = i;
            break;
        }
    }

    if (orderIndex == -1) {
        std::cout << "Cannot place more orders, capacity reached." << std::endl;
        return;
    }

    // Enter order details
    Order newOrder;
    newOrder.tableNumber = tableNumber;
    newOrder.isComplete = false;
    newOrder.isPaid = false;
    newOrder.numItems = 0;

    std::cout << "Enter menu item numbers (0 to 13), -1 to finish:" << std::endl;
    int menuItemNumber;
    while (std::cin >> menuItemNumber && menuItemNumber != -1) {
        if (menuItemNumber >= 0 && menuItemNumber <= 13) {
            if (newOrder.numItems < 10) {
                newOrder.menuItems[newOrder.numItems++] = menuItemNumber;
            } else {
                std::cout << "Maximum number of items reached. Cannot add more." << std::endl;
                break;
            }
        } else {
            std::cout << "Invalid menu item number. Please try again." << std::endl;
        }
    }

    orders[orderIndex] = newOrder;
    std::cout << "Order placed for table " << tableNumber << std::endl;
}

void completeOrder() {
    int tableNumber;
    std::cout << "Enter table number to complete order: ";
    std::cin >> tableNumber;

    // Find the order for the given table
    int orderIndex = -1;
    for (int i = 0; i < MAX_ORDERS; ++i) {
        if (orders[i].tableNumber == tableNumber && !orders[i].isComplete) {
            orderIndex = i;
            break;
        }
    }

    if (orderIndex == -1) {
        std::cout << "Order not found or already completed for table " << tableNumber << "." << std::endl;
        return;
    }

    // Mark the order as completed
    orders[orderIndex].isComplete = true;
    std::cout << "Order for table " << tableNumber << " marked as completed." << std::endl;
}

void calculateAndPayBill() {
    int tableNumber;
    std::cout << "Enter table number to calculate and pay bill: ";
    std::cin >> tableNumber;

    // Find the completed but unpaid order for the table
    int orderIndex = -1;
    for (int i = 0; i < MAX_ORDERS; ++i) {
        if (orders[i].tableNumber == tableNumber && orders[i].isComplete && !orders[i].isPaid) {
            orderIndex = i;
            break;
        }
    }

    if (orderIndex == -1) {
        std::cout << "Order not found, not complete, or already paid for table " << tableNumber << "." << std::endl;
        return;
    }

    // Calculate the bill
    double subtotal = 0.0;
    for (int i = 0; i < orders[orderIndex].numItems; ++i) {
        subtotal += static_cast<double>(MenuItem(orders[orderIndex].menuItems[i]));
    }
    double tax = subtotal * 0.10; // 10% tax
    double tip = subtotal * 0.20; // 20% tip
    double total = subtotal + tax + tip;

    // Display and mark order as paid
    std::cout << "Bill for table " << tableNumber << ":\n";
    std::cout << "Subtotal: $" << subtotal << "\n";
    std::cout << "Tax: $" << tax << "\n";
    std::cout << "Tip: $" << tip << "\n";
    std::cout << "Total: $" << total << "\n";

    orders[orderIndex].isPaid = true;
    std::cout << "Bill paid. Thank you!" << std::endl;
}

void closeRestaurant() {
    // Check for pending reservations
    for (int i = 0; i < MAX_RESERVATIONS; ++i) {
        if (!reservations[i].customerName.empty() && !reservations[i].isCheckedIn) {
            std::cout << "There are pending reservations. Cannot close the restaurant." << std::endl;
            return;
        }
    }

    // Check for outstanding orders
    for (int i = 0; i < MAX_ORDERS; ++i) {
        if (orders[i].numItems > 0 && (!orders[i].isComplete || !orders[i].isPaid)) {
            std::cout << "There are outstanding orders. Cannot close the restaurant." << std::endl;
            return;
        }
    }

    std::cout << "Closing the restaurant." << std::endl;
    // The program can now proceed to shut down operations.
}

int main() {
    initializeTables(); //Initializes the tables at the start.
    
    int choice;
    bool isRestaurantOpen = true;

    // Initialize tables here (if needed)

    while (isRestaurantOpen) {
        std::cout << "1. Make Reservation\n";
        std::cout << "2. Check-in for Reservation\n";
        std::cout << "3. Enter Order\n";
        std::cout << "4. Complete Order\n";
        std::cout << "5. Calculate and Pay Bill\n";
        std::cout << "6. Close the Restaurant\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                makeReservation();
                break;
            case 2:
                checkInReservation();
                break;
            case 3:
                enterOrder();
                break;
            case 4:
                completeOrder();
                break;
            case 5:
                calculateAndPayBill();
                break;
            case 6:
                closeRestaurant();
                isRestaurantOpen = false;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }

    return 0;
}

