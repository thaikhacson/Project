// EmployeeManager.h

#ifndef EMPLOYEE_MANAGER_HPP
#define EMPLOYEE_MANAGER_HPP

#include "room_manager.hpp"
#include "menu_manager.hpp"

struct Employee {
    string name;
    int employeeID;
    int phoneNumber;
    string position;
    string shift; // Additional employee information can be added as needed.
};

class EmployeeManager {
private:
    list<Employee> employees; // A vector to store employees

public:
    // Add a new employee
    void addEmployee(string name, int employeeID, int phoneNumber, string position);

    // Edit employee information
    void editEmployee(int employeeID);

    // Remove an employee
    void removeEmployee(int employeeID);

    // Set work shift for an employee
    void setShift(int employeeID, string newShift);

    // List all employees
    void listEmployees();

    // Working hours (implementation can be defined as needed)
    void workHours(int employeeID);
};

#endif  // EMPLOYEE_MANAGER_HPP
