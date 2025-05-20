#include "Engineer.h"

Engineer::Engineer(int id, const std::string& name, double rate, std::shared_ptr<Project> project)
    : Employee(id, name), rate(rate), project(project) {}

double Engineer::calcBase(double rate, double hours) const {
    return rate * hours;
}

double Engineer::calcBonus() const {
    return 0.0;
}

double Engineer::calcBudgetPart(double projectBudget, double part) const {
    return projectBudget * part;
}

double Engineer::calcProAdditions() const {
    return 0.0;
}

void Engineer::calc() {
    payment = calcBase(rate, worktime) + calcBonus();
}

std::string Engineer::getPosition() const {
    return "Engineer";
}

std::string Engineer::getProjectName() const {
    return project ? project->name : "";
}

Programmer::Programmer(int id, const std::string& name, double rate, std::shared_ptr<Project> project, double earlyBonus)
    : Engineer(id, name, rate, project), earlyBonus(earlyBonus) {}

void Programmer::calc() {
    payment = calcBase(rate, worktime) + calcBudgetPart(project->budget, 0.1) + earlyBonus;
}

std::string Programmer::getPosition() const {
    return "Programmer";
}

Tester::Tester(int id, const std::string& name, double rate, std::shared_ptr<Project> project, int bugsFound)
    : Engineer(id, name, rate, project), bugsFound(bugsFound) {}

void Tester::calc() {
    payment = calcBase(rate, worktime) + calcBudgetPart(project->budget, 0.05) + bugsFound * 10;
}

std::string Tester::getPosition() const {
    return "Tester";
}