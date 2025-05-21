#pragma once
#include <vector>
#include <memory>
#include "Engineer.h"
#include "Interfaces.h"

class SeniorManager : public Employee, public Heading {
    std::vector<std::shared_ptr<Project>> projects;
    int totalStaff;
public:
    SeniorManager(int id, const std::string& name, const std::vector<std::shared_ptr<Project>>& projects, int totalStaff);
    double calcHeads(int subordinates) const override;
    void calc() override;
    std::string getPosition() const override;
};

class TeamLeader : public Programmer, public Heading {
    int programmersLed;
public:
    TeamLeader(int id, const std::string& name, double rate, std::shared_ptr<Project> project, double earlyBonus, int programmersLed);
    double calcHeads(int subordinates) const override;
    void calc() override;
    std::string getPosition() const override;
};

class ProjectManager : public Engineer, public Heading {
    std::vector<std::shared_ptr<Project>> projects;
    int teamSize;
public:
    ProjectManager(int id, const std::string& name, double rate, const std::vector<std::shared_ptr<Project>>& projects, int teamSize);
    double calcHeads(int subordinates) const override;
    void calc() override;
    std::string getPosition() const override;
};