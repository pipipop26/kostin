#include "Factory.h"
#include "Personal.h"
#include "Engineer.h"
#include "Manager.h"
#include <fstream>
#include <sstream>

std::vector<std::shared_ptr<Employee>> StaffFactory::makeStaff(const std::string& filename) {
    std::vector<std::shared_ptr<Employee>> staff;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string name, position, projectName;
        double rate = 0, budget = 0;
        iss >> id >> name >> position >> rate >> projectName >> budget;
        // Пример создания сотрудников, доработайте под свой формат файла
        if (position == "Cleaner") {
            staff.push_back(std::make_shared<Cleaner>(id, name, rate));
        }
        // Добавьте остальные должности аналогично
    }
    return staff;
}