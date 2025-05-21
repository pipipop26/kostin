#pragma once
#include <vector>
#include <memory>
#include "Employee.h"

class StaffFactory {
public:
    static std::vector<std::shared_ptr<Employee>> makeStaff(const std::string& filename);
};