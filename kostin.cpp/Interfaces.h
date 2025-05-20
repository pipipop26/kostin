#pragma once
#include <string>

class WorkBaseTime {
public:
    virtual double calcBase(double rate, double hours) const = 0;
    virtual double calcBonus() const = 0;
    virtual ~WorkBaseTime() = default;
};

class ProjectBudget {
public:
    virtual double calcBudgetPart(double projectBudget, double part) const = 0;
    virtual double calcProAdditions() const = 0;
    virtual ~ProjectBudget() = default;
};

class Heading {
public:
    virtual double calcHeads(int subordinates) const = 0;
    virtual ~Heading() = default;
};