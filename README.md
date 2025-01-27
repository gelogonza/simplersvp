# Restaurant Management System - README

## Overview
The **Restaurant Management System** is a console-based application designed to streamline the operations of a restaurant. The program allows users to manage reservations, food orders, table assignments, bill payments, and closing operations in an efficient and user-friendly manner.

---

## Features
1. **Make Reservations**  
   Users can input customer details, reservation time, and party size. The system ensures table capacity is not exceeded.
   
2. **Check-in Reservations**  
   Allows customers to check in, and the system assigns a suitable table based on the reservation details.

3. **Enter Orders**  
   Accepts food orders for tables, with validation for maximum items per order and availability.

4. **Complete Orders**  
   Marks orders as completed once the food has been served.

5. **Calculate and Pay Bills**  
   Automatically calculates the bill with tax and tip. Bills can be paid to free up the table.

6. **Close the Restaurant**  
   Ensures all reservations are fulfilled, and no outstanding orders or unpaid bills exist before closing.

---

## Technical Details
### Constants and Limits
- **Maximum Reservations**: 50  
- **Maximum Orders**: 50  
- **Maximum Tables**: 20  

### Table Configuration
- **Tables 1-8**: Seats 2 people.  
- **Tables 9-10**: Seats 10 people.  
- **Tables 11-14**: Seats 6 people.  
- **Tables 15-20**: Seats 4 people.

### Menu Items
The system includes a predefined menu with item prices:
- Veggie Burger: $35
- Hamburger: $45
- Cheese Pizza: $59  
(See source code for the full menu.)

### Tax and Tip Calculation
- **Tax**: 10%  
- **Tip**: 20%  

---

## How to Use
1. Run the program in a C++ environment.
2. Use the main menu to navigate the operations:
   - `1`: Make a reservation.
   - `2`: Check in a reservation.
   - `3`: Enter a food order for a table.
   - `4`: Mark an order as completed.
   - `5`: Calculate and pay the bill.
   - `6`: Close the restaurant.
3. Follow on-screen prompts to input required data.

---

## Limitations
- Reservations cannot exceed 10 people.
- A maximum of 50 reservations and 50 orders can be stored simultaneously.
- The system does not persist data after the program ends.

---

## Future Improvements
1. **Data Persistence**: Store reservations and orders in a database or file for future retrieval.
2. **Dynamic Table Configuration**: Allow customization of table sizes and numbers.
3. **User Interface**: Upgrade to a graphical user interface for improved usability.
4. **Order Customization**: Include options for modifying or canceling orders.

---

## Compilation and Execution
### Prerequisites
- C++ Compiler (e.g., GCC, Clang)
- Standard C++ Library

### Compile
```bash
g++ restaurant_management_system.cpp -o restaurant_management_system
```

### Run
```bash
./restaurant_management_system
```

---

## Author
**Angelo**  
_Last Updated_: 12/12/2023  
_For questions or improvements, feel free to contribute._  

---

Enjoy managing your restaurant efficiently! 😊
