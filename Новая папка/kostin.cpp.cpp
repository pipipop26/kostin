#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Employee.h"
#include "Factory.h"
#include "Personal.h"
#include "Engineer.h"
#include "Manager.h"

void printMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Показать всех сотрудников\n";
    std::cout << "2. Поиск по имени\n";
    std::cout << "3. Поиск по должности\n";
    std::cout << "4. Поиск по зарплате (больше/меньше)\n";
    std::cout << "5. Показать сотрудников проекта\n";
    std::cout << "6. Добавить сотрудника\n";
    std::cout << "7. Добавить проект\n";
    std::cout << "8. Сохранить данные\n";
    std::cout << "9. Загрузить данные\n";
    std::cout << "0. Выйти\n";
    std::cout << "Выберите действие: ";
}

void printTable(const std::vector<std::shared_ptr<Employee>>& staff) {
    std::cout << std::left
        << std::setw(6)  << "ID"
        << std::setw(25) << "ФИО"
        << std::setw(18) << "Должность"
        << std::setw(10) << "Время"
        << std::setw(10) << "Зарплата"
        << std::endl;
    for (const auto& emp : staff) {
        emp->printInfo();
    }
}

void searchByName(const std::vector<std::shared_ptr<Employee>>& staff) {
    std::string name;
    std::cout << "Введите имя или часть имени: ";
    std::cin >> name;
    std::cout << std::left
        << std::setw(6)  << "ID"
        << std::setw(25) << "ФИО"
        << std::setw(18) << "Должность"
        << std::setw(10) << "Время"
        << std::setw(10) << "Зарплата"
        << std::endl;
    for (const auto& emp : staff) {
        if (emp->getName().find(name) != std::string::npos) {
            emp->printInfo();
        }
    }
}

void searchByPosition(const std::vector<std::shared_ptr<Employee>>& staff) {
    std::string pos;
    std::cout << "Введите должность: ";
    std::cin >> pos;
    std::cout << std::left
        << std::setw(6)  << "ID"
        << std::setw(25) << "ФИО"
        << std::setw(18) << "Должность"
        << std::setw(10) << "Время"
        << std::setw(10) << "Зарплата"
        << std::endl;
    for (const auto& emp : staff) {
        if (emp->getPosition().find(pos) != std::string::npos) {
            emp->printInfo();
        }
    }
}

void searchBySalary(const std::vector<std::shared_ptr<Employee>>& staff) {
    double value;
    char sign;
    std::cout << "Введите знак (< или >): ";
    std::cin >> sign;
    std::cout << "Введите сумму: ";
    std::cin >> value;
    for (const auto& emp : staff) {
        if ((sign == '<' && emp->getPayment() < value) ||
            (sign == '>' && emp->getPayment() > value)) {
            emp->printInfo();
        }
    }
}

void showByProject(const std::vector<std::shared_ptr<Employee>>& staff) {
    std::string project;
    std::cout << "Введите название проекта: ";
    std::cin >> project;
    for (const auto& emp : staff) {
        auto eng = std::dynamic_pointer_cast<Engineer>(emp);
        if (eng && eng->getProjectName() == project) {
            emp->printInfo();
        }
    }
}

void addEmployee(std::vector<std::shared_ptr<Employee>>& staff, std::vector<std::shared_ptr<Project>>& projects) {
    std::cout << "Выберите тип сотрудника:\n";
    std::cout << "1. Cleaner\n";
    std::cout << "2. Driver\n";
    std::cout << "3. Engineer\n";
    std::cout << "4. Programmer\n";
    std::cout << "5. Tester\n";
    std::cout << "6. TeamLeader\n";
    std::cout << "7. ProjectManager\n";
    std::cout << "8. SeniorManager\n";
    int type;
    std::cin >> type;

    int id;
    std::string name;
    std::cout << "ID: ";
    std::cin >> id;
    std::cout << "ФИО: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (type == 1) { // Cleaner
        double rate;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        staff.push_back(std::make_shared<Cleaner>(id, name, rate));
    } else if (type == 2) { // Driver
        double rate;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        staff.push_back(std::make_shared<Driver>(id, name, rate));
    } else if (type == 3) { // Engineer
        double rate;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        std::cout << "ID проекта: ";
        int pid;
        std::cin >> pid;
        auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
        if (it != projects.end()) {
            staff.push_back(std::make_shared<Engineer>(id, name, rate, *it));
        } else {
            std::cout << "Проект не найден!\n";
        }
    } else if (type == 4) { // Programmer
        double rate, earlyBonus;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        std::cout << "Бонус за досрочно написанный код: ";
        std::cin >> earlyBonus;
        std::cout << "ID проекта: ";
        int pid;
        std::cin >> pid;
        auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
        if (it != projects.end()) {
            staff.push_back(std::make_shared<Programmer>(id, name, rate, *it, earlyBonus));
        } else {
            std::cout << "Проект не найден!\n";
        }
    } else if (type == 5) { // Tester
        double rate;
        int bugsFound;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        std::cout << "Количество найденных ошибок: ";
        std::cin >> bugsFound;
        std::cout << "ID проекта: ";
        int pid;
        std::cin >> pid;
        auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
        if (it != projects.end()) {
            staff.push_back(std::make_shared<Tester>(id, name, rate, *it, bugsFound));
        } else {
            std::cout << "Проект не найден!\n";
        }
    } else if (type == 6) { // TeamLeader
        double rate, earlyBonus;
        int programmersLed;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        std::cout << "Бонус за досрочно написанный код: ";
        std::cin >> earlyBonus;
        std::cout << "Количество программистов в подчинении: ";
        std::cin >> programmersLed;
        std::cout << "ID проекта: ";
        int pid;
        std::cin >> pid;
        auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
        if (it != projects.end()) {
            staff.push_back(std::make_shared<TeamLeader>(id, name, rate, *it, earlyBonus, programmersLed));
        } else {
            std::cout << "Проект не найден!\n";
        }
    } else if (type == 7) { // ProjectManager
        double rate;
        int teamSize, nproj;
        std::cout << "Ставка (руб/час): ";
        std::cin >> rate;
        std::cout << "Размер команды: ";
        std::cin >> teamSize;
        std::cout << "Сколько проектов курирует? ";
        std::cin >> nproj;
        std::vector<std::shared_ptr<Project>> mgrProjects;
        for (int i = 0; i < nproj; ++i) {
            std::cout << "ID проекта #" << (i+1) << ": ";
            int pid;
            std::cin >> pid;
            auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
            if (it != projects.end()) mgrProjects.push_back(*it);
            else std::cout << "Проект не найден!\n";
        }
        staff.push_back(std::make_shared<ProjectManager>(id, name, rate, mgrProjects, teamSize));
    } else if (type == 8) { // SeniorManager
        int totalStaff, nproj;
        std::cout << "Сколько сотрудников в подчинении? ";
        std::cin >> totalStaff;
        std::cout << "Сколько проектов курирует? ";
        std::cin >> nproj;
        std::vector<std::shared_ptr<Project>> mgrProjects;
        for (int i = 0; i < nproj; ++i) {
            std::cout << "ID проекта #" << (i+1) << ": ";
            int pid;
            std::cin >> pid;
            auto it = std::find_if(projects.begin(), projects.end(), [pid](const std::shared_ptr<Project>& p) { return p->id == pid; });
            if (it != projects.end()) mgrProjects.push_back(*it);
            else std::cout << "Проект не найден!\n";
        }
        staff.push_back(std::make_shared<SeniorManager>(id, name, mgrProjects, totalStaff));
    } else {
        std::cout << "Неизвестный тип сотрудника!\n";
    }

    if (!staff.empty()) {
        auto& emp = staff.back();
        double hours;
        std::cout << "Введите отработанное время для " << emp->getName() << ": ";
        std::cin >> hours;
        emp->setWorkTime(hours);
        emp->calc();
    }
    std::cout << "Сотрудник добавлен!\n";
}

void addProject(std::vector<std::shared_ptr<Project>>& projects) {
    int id;
    std::string name;
    double budget;
    std::cout << "ID проекта: ";
    std::cin >> id;
    std::cout << "Название проекта: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Бюджет проекта: ";
    std::cin >> budget;
    projects.push_back(std::make_shared<Project>(Project{id, name, budget}));
    std::cout << "Проект добавлен!\n";
}

void saveProjects(const std::vector<std::shared_ptr<Project>>& projects, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& prj : projects) {
        file << prj->id << "|" << prj->name << "|" << prj->budget << std::endl;
    }
}

void saveStaff(const std::vector<std::shared_ptr<Employee>>& staff, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& emp : staff) {
        // Пример: id|name|position|worktime|payment
        file << emp->getId() << "|"
             << emp->getName() << "|"
             << emp->getPosition() << "|"
             << emp->getWorkTime() << "|"
             << emp->getPayment() << std::endl;
        // Для расширения: добавьте нужные поля для каждого типа сотрудника
    }
    std::cout << "Данные сотрудников сохранены.\n";
}

void loadProjects(std::vector<std::shared_ptr<Project>>& projects, const std::string& filename) {
    projects.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string idStr, name, budgetStr;

        if (std::getline(iss, idStr, '|') &&
            std::getline(iss, name, '|') &&
            std::getline(iss, budgetStr)) {
            int id = std::stoi(idStr);
            double budget = std::stod(budgetStr);
            projects.push_back(std::make_shared<Project>(Project{id, name, budget}));
        } else {
            std::cerr << "Ошибка: некорректный формат строки: " << line << std::endl;
        }
    }
}

int main() {
    system("chcp 1251");
    std::vector<std::shared_ptr<Employee>> staff;
    std::vector<std::shared_ptr<Project>> projects;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            printTable(staff);
            break;
        case 2:
            searchByName(staff);
            break;
        case 3:
            searchByPosition(staff);
            break;
        case 4:
            searchBySalary(staff);
            break;
        case 5:
            showByProject(staff);
            break;
        case 6:
            addEmployee(staff, projects);
            break;
        case 7:
            addProject(projects);
            break;
        case 8:
            saveStaff(staff, "staff.txt");
            saveProjects(projects, "projects.txt");
            break;
        case 9:
            loadProjects(projects, "projects.txt");
            // Реализуйте loadStaff при необходимости
            break;
        case 0:
            std::cout << "Выход...\n";
            return 0;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}