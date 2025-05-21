#pragma once
#include "Employee.h"
#include "Interfaces.h"
#include <memory>

struct Project {
    int id;
    std::string name;
    double budget;
};

class Engineer : public Employee, public WorkBaseTime, public ProjectBudget {
protected:
    double rate;
    std::shared_ptr<Project> project;
public:
    Engineer(int id, const std::string& name, double rate, std::shared_ptr<Project> project);
    double calcBase(double rate, double hours) const override;
    double calcBonus() const override; // Не использует earlyBonus!
    double calcBudgetPart(double projectBudget, double part) const override;
    double calcProAdditions() const override;
    void calc() override;
    std::string getPosition() const override;
    std::string getProjectName() const;
};

class Programmer : public Engineer {
protected:
    double earlyBonus;
public:
    Programmer(int id, const std::string& name, double rate, std::shared_ptr<Project> project, double earlyBonus);
    double getEarlyBonus() const { return earlyBonus; }
    void calc() override;
    std::string getPosition() const override;
    // Если нужен особый бонус, можно переопределить calcBonus() здесь
};

class Tester : public Engineer {
    int bugsFound;
public:
    Tester(int id, const std::string& name, double rate, std::shared_ptr<Project> project, int bugsFound);
    void calc() override;
    std::string getPosition() const override;
};