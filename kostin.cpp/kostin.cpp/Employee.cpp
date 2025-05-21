#include "Employee.h"
#include <iomanip> // добавить в начало файла
Employee::Employee(int id, const std::string& name)
    : id      (id)
    , name    (name)
    , worktime(0)
    , payment (0)
{}

void Employee::setWorkTime(double hours) {
    worktime = hours;
}

void Employee::printInfo() const {
    std::cout << std::left
        << std::setw(6)  << id
        << std::setw(25) << name.substr(0, 24)
        << std::setw(18) << getPosition()
        << std::setw(10) << worktime
        << std::setw(10) << payment
        << std::endl;
}

int Employee::getId() const { return id; }
std::string Employee::getName() const { return name; }
double Employee::getPayment() const { return payment; }
double Employee::getWorkTime() const {
    return worktime;
}