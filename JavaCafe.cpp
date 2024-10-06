#include <iostream>
#include <iomanip>  // for formatting output
#include <string>
#include <algorithm>  // for sorting
using namespace std;

// Base class: Employee
class Employee {
protected:
    string employeeID, employeeName, position, employeeType, startDate;
    double BasicSalary, HourlyWage, WorkingHours, LeaveDays, OvertimeHours;
    double Bonus, OvertimeBonus, NetSalaryBeforeTax, NetSalaryAfterTax, IncomeTax, SocialSecurityTax;

public:
    Employee() : BasicSalary(0), HourlyWage(0), WorkingHours(0), LeaveDays(0), OvertimeHours(0),
                 Bonus(0), OvertimeBonus(0), NetSalaryBeforeTax(0), NetSalaryAfterTax(0), IncomeTax(0), SocialSecurityTax(10) {}

    virtual void inputEmployeeInfo() {
        cout << "Enter Employee ID: "; cin >> employeeID;
        cout << "Enter Employee Name: "; cin.ignore(); getline(cin, employeeName);
        cout << "Enter Position (Barista, Cashier, Kitchen Staff, Cleaner, Waiter/Waitress, Supervisor): ";
        getline(cin, position);
        cout << "Enter Start Date (dd/mm/yyyy): "; 
        cin >> startDate;
        cout << "Enter Leave Days: "; 
        cin >> LeaveDays;
    }

    void displayEmployeeInfoInTable() const {
        cout << left << setw(12) << employeeID 
             << setw(20) << employeeName 
             << setw(15) << position 
             << setw(15) << employeeType 
             << setw(10) << LeaveDays 
             << setw(10) << OvertimeHours 
             << setw(15) << fixed << setprecision(2) << BasicSalary 
             << setw(15) << fixed << setprecision(2) << OvertimeBonus 
             << setw(15) << fixed << setprecision(2) << NetSalaryBeforeTax 
             << setw(10) << fixed << setprecision(2) << IncomeTax 
             << setw(15) << fixed << setprecision(2) << NetSalaryAfterTax 
             << endl;
    }

    virtual void calculateSalary() = 0;  // Pure virtual function for salary calculation

    string getEmployeeName() const {
        return employeeName;
    }

    string getEmployeeType() const {
        return employeeType;
    }
    double getNetSalaryAfterTax() const {
    return NetSalaryAfterTax;
}

};

// Derived class: FullTimeEmployee
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee() {
        employeeType = "Full-Time";
        WorkingHours = 8;
    }

    void inputEmployeeInfo() override {
        Employee::inputEmployeeInfo();  // Reuse the base class's method
        cout << "Enter Overtime Hours: "; 
        cin >> OvertimeHours;
        setDefaultSalary();
    }

    void setDefaultSalary() {
        string lowerPosition = position;  
        for (auto &c : lowerPosition) c = tolower(c);
        
        if (lowerPosition == "barista") {
            BasicSalary = 1920;
        } else if (lowerPosition == "cashier") {
            BasicSalary = 1790;
        } else if (lowerPosition == "kitchen staff") {
            BasicSalary = 1850;
        } else if (lowerPosition == "cleaner") {
            BasicSalary = 1400;
        } else if (lowerPosition == "waiter/waitress") {
            BasicSalary = 1700;
        } else if (lowerPosition == "supervisor") {
            BasicSalary = 2400;
        } else {
            BasicSalary = 0;
        }
        HourlyWage = BasicSalary / 240;  // Assume 240 hours per month
    }

    void calculateSalary() override {
        Bonus = BasicSalary * 0.10;  // 10% of Basic Salary
        OvertimeBonus = OvertimeHours > 0 ? OvertimeHours * HourlyWage * 2 : 0;
        NetSalaryBeforeTax = BasicSalary + OvertimeBonus + Bonus;
        IncomeTax = NetSalaryBeforeTax * 0.02;  // 2% income tax
        NetSalaryAfterTax = NetSalaryBeforeTax - IncomeTax - SocialSecurityTax;
    }
    double getNetSalaryAfterTax() const {
    return NetSalaryAfterTax;
}

};

// Derived class: PartTimeEmployee
class PartTimeEmployee : public Employee {
public:
    PartTimeEmployee() {
        employeeType = "Part-Time";
    }

    void inputEmployeeInfo() override {
        Employee::inputEmployeeInfo();
        cout << "Enter Working Hours: "; 
        cin >> WorkingHours;
        OvertimeHours = 0;
        setDefaultSalary();
    }

    void setDefaultSalary() {
        string lowerPosition = position;
        for (auto &c : lowerPosition) c = tolower(c);
        
        if (lowerPosition == "barista") {
            HourlyWage = 8;
        } else if (lowerPosition == "cashier") {
            HourlyWage = 7.5;
        } else if (lowerPosition == "kitchen staff") {
            HourlyWage = 7.75;
        } else if (lowerPosition == "cleaner") {
            HourlyWage = 5.8;
        } else if (lowerPosition == "waiter/waitress") {
            HourlyWage = 7;
        } else if (lowerPosition == "supervisor") {
            HourlyWage = 10;
        } else {
            HourlyWage = 0;
        }
        BasicSalary = WorkingHours * HourlyWage;
    }

    void calculateSalary() override {
        Bonus = BasicSalary * 0.10;  // 10% of Basic Salary
        NetSalaryBeforeTax = BasicSalary + Bonus;
        IncomeTax = NetSalaryBeforeTax * 0.02;  // 2% income tax
        NetSalaryAfterTax = NetSalaryBeforeTax - IncomeTax - SocialSecurityTax;
    }
    double getNetSalaryAfterTax() const {
    return NetSalaryAfterTax;
}

};

// Sorting function using std::sort
bool compareByName(Employee* a, Employee* b) {
    return a->getEmployeeName() < b->getEmployeeName();
}

// Function to display employee table headers
void displayTableHeader(const string& header) {
    cout << "\n" << header << "\n";
    cout << string(120, '=') << endl;
    cout << left << setw(12) << "Emp ID" 
         << setw(20) << "Name" 
         << setw(15) << "Position" 
         << setw(15) << "Type" 
         << setw(10) << "Leave" 
         << setw(10) << "Overtime" 
         << setw(15) << "Basic Salary" 
         << setw(15) << "Overtime Bonus" 
         << setw(15) << "Gross Salary" 
         << setw(10) << "Income Tax" 
         << setw(15) << "Net Salary" 
         << endl;
    cout << string(120, '-') << endl;
}

// Function to display all employee data
void showAllEmployeeData(Employee* employees[], int employeeCount) {
    // Sort employees by name
    sort(employees, employees + employeeCount, compareByName);

    displayTableHeader("All Employee Data");

    // Loop through and display all employees
    for (int i = 0; i < employeeCount; i++) {
        employees[i]->displayEmployeeInfoInTable();
    }
    cout << string(120, '=') << endl;
}

// Function to show total monthly payment with a breakdown in a table format
void showTotalMonthlyPayment(Employee* employees[], int employeeCount) {
    int fullTimeCount = 0, partTimeCount = 0;
    double fullTimeTotal = 0.0, partTimeTotal = 0.0;

    // Calculate totals and counts for full-time and part-time employees
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i]->getEmployeeType() == "Full-Time") {
            fullTimeCount++;
            fullTimeTotal += employees[i]->getNetSalaryAfterTax(); // Use the getter here
        } else if (employees[i]->getEmployeeType() == "Part-Time") {
            partTimeCount++;
            partTimeTotal += employees[i]->getNetSalaryAfterTax(); // Use the getter here
        }
    }
    
    // Display the table with employee types, counts, and total salaries
    cout << "\nMonthly Payment Summary\n";
    cout << string(60, '=') << endl;
    cout << left << setw(20) << "Employee Type" 
         << setw(10) << "Count" 
         << setw(20) << "Total Net Salary" << endl;
    cout << string(60, '-') << endl;
    
    // Output for Full-time Employees
    cout << left << setw(20) << "Full-time Employees" 
         << setw(10) << fullTimeCount 
         << "$" << fixed << setprecision(2) << fullTimeTotal << endl;

    // Output for Part-time Employees
    cout << left << setw(20) << "Part-time Employees" 
         << setw(10) << partTimeCount 
         << "$" << fixed << setprecision(2) << partTimeTotal << endl;

    cout<< string(60, '-') << endl;
    
    // Display total employees and total salary
    cout << left << setw(20) << "Total Employees" 
         << setw(10) << (fullTimeCount + partTimeCount) 
         << "$" << fixed << setprecision(2) << (fullTimeTotal + partTimeTotal) << endl;
    
    cout << string(60, '=') << endl;
}



int main() {
    Employee* employees[100];
    int employeeCount = 0;
    int choice;
    
    do {
        // Menu Options
        cout << "\n1. Add Employee\n"
             << "2. Show Employee Report\n"
             << "3. Search Employee by Name\n"
             << "4. Show All Employee Data\n"
             << "5. Show Monthly Report\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            // Add Employee
            char type;
            cout << "Enter employee type (F for Full-time, P for Part-time): ";
            cin >> type;

            if (type == 'F' || type == 'f') {
                employees[employeeCount] = new FullTimeEmployee();
            } else {
                employees[employeeCount] = new PartTimeEmployee();
            }
            employees[employeeCount]->inputEmployeeInfo();
            employees[employeeCount]->calculateSalary();
            employeeCount++;
        } else if (choice == 2) {
            // Show Employee Report
            char type;
            cout << "Show report for (F for Full-time, P for Part-time): ";
            cin >> type;

            if (type == 'F' || type == 'f') {
                displayTableHeader("Full-Time Employee Report");
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i]->getEmployeeType() == "Full-Time") {
                        employees[i]->displayEmployeeInfoInTable();
                    }
                }
            } else {
                displayTableHeader("Part-Time Employee Report");
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i]->getEmployeeType() == "Part-Time") {
                        employees[i]->displayEmployeeInfoInTable();
                    }
                }
            }
        } else if (choice == 3) {
            // Search Employee by Name
            string name;
            cout << "Enter Employee Name to search: ";
            cin.ignore();
            getline(cin, name);

            // Sort employees by name before searching
            sort(employees, employees + employeeCount, compareByName);
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i]->getEmployeeName() == name) {
                    displayTableHeader("Employee Search Result");
                    employees[i]->displayEmployeeInfoInTable();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Employee not found!\n";
            }
        } else if (choice == 4) {
            // Show All Employee Data
            showAllEmployeeData(employees, employeeCount);
        } else if (choice == 5) {
            // Show Monthly Report
            showTotalMonthlyPayment(employees, employeeCount);
        } else if (choice == 6) {
            // Exit
            cout << "Exiting program...\n";
        } else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    // Clean up dynamic memory
    for (int i = 0; i < employeeCount; i++) {
        delete employees[i];
    }

    return 0;
}