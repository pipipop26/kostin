#pragma once
#include <string>
#include <iostream>

class Employee {
protected:
    int id;
    std::string name;
    double worktime;
    double payment;
public:
    Employee(int id, const std::string& name);
    virtual ~Employee() = default;

    virtual void setWorkTime(double hours);
    virtual void calc() = 0;
    virtual void printInfo() const;
    int getId() const;
    std::string getName() const;
    double getPayment() const;
    double getWorkTime() const; // Добавляем метод
    virtual std::string getPosition() const = 0;
};