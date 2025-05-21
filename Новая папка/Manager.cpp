#include "Manager.h"

TeamLeader::TeamLeader(int id, const std::string& name, double rate, std::shared_ptr<Project> project, double earlyBonus, int programmersLed)
    : Programmer(id, name, rate, project, earlyBonus), programmersLed(programmersLed) {}

double TeamLeader::calcHeads(int subordinates) const {
    return subordinates * 100;
}

void TeamLeader::calc() {
    // Используем геттер для earlyBonus
    payment = calcBase(rate, worktime) + calcBudgetPart(project->budget, 0.15) + getEarlyBonus() + calcHeads(programmersLed);
}

std::string TeamLeader::getPosition() const {
    return "TeamLeader";
}

ProjectManager::ProjectManager(int id, const std::string& name, double rate, const std::vector<std::shared_ptr<Project>>& projects, int teamSize)
    : Engineer(id, name, rate, projects.empty() ? nullptr : projects[0]), projects(projects), teamSize(teamSize) {}

double ProjectManager::calcHeads(int subordinates) const {
    return subordinates * 150;
}

void ProjectManager::calc() {
    double totalBudget = 0;
    for (const auto& prj : projects) totalBudget += prj->budget;
    payment = totalBudget * 0.2 + calcHeads(teamSize);
}

std::string ProjectManager::getPosition() const {
    return "ProjectManager";
}

SeniorManager::SeniorManager(int id, const std::string& name, const std::vector<std::shared_ptr<Project>>& projects, int totalStaff)
    : Employee(id, name), projects(projects), totalStaff(totalStaff) {}

double SeniorManager::calcHeads(int subordinates) const {
    return subordinates * 200;
}

void SeniorManager::calc() {
    double totalBudget = 0;
    for (const auto& prj : projects) totalBudget += prj->budget;
    payment = totalBudget * 0.05 + calcHeads(totalStaff);
}

std::string SeniorManager::getPosition() const {
    return "SeniorManager";
}