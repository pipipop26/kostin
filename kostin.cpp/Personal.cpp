#include "Personal.h"

Personal::Personal(int id, const std::string& name, double salary)
    : Employee(id, name), salary(salary) {}

double Personal::calcBase(double salary, double hours) const {
    return salary * hours;
}

double Personal::calcBonus() const {
    return 0.0;
}

void Personal::calc() {
    payment = calcBase(salary, worktime) + calcBonus();
}

std::string Personal::getPosition() const {
    return "Personal";
}

Cleaner::Cleaner(int id, const std::string& name, double salary)
    : Personal(id, name, salary) {}

void Cleaner::calc() {
    payment = calcBase(salary, worktime);
}

std::string Cleaner::getPosition() const {
    return "Cleaner";
}

Driver::Driver(int id, const std::string& name, double salary)
    : Personal(id, name, salary), nightHours(0) {}

void Driver::setNightHours(double hours) {
    nightHours = hours;
}

void Driver::calc() {
    payment = calcBase(salary, worktime) + nightHours * 50; // пример надбавки
}

std::string Driver::getPosition() const {
    return "Driver";
}