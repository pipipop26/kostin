#pragma once
#include "Employee.h"
#include "Interfaces.h"

class Personal : public Employee, public WorkBaseTime {
protected:
    double salary;
public:
    Personal(int id, const std::string& name, double salary);
    double calcBase(double salary, double hours) const override;
    double calcBonus() const override;
    void calc() override;
    std::string getPosition() const override;
};

class Cleaner : public Personal {
public:
    Cleaner(int id, const std::string& name, double rate);
    void calc() override;
    std::string getPosition() const override;
};

class Driver : public Personal {
    double nightHours;
public:
    Driver(int id, const std::string& name, double rate);
    void setNightHours(double hours);
    void calc() override;
    std::string getPosition() const override;
};