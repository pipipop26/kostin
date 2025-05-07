#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>

//---------------------------------------------------------------------------- Пример1
double divide_1(int a, int b) {
    return a / b;
}

void example_1() {
    int x{500};
    int y{0};
    assert(y != 0);
    double z = divide_1(x, y);
    std::cout << z << std::endl;
    std::cout << "The End..." << std::endl;
}

//---------------------------------------------------------------------------- Пример2
double divide_2(int a, int b) {
    if (b != 0)
        return a / b;
    throw "Division by zero!";
}

void example_2() {
    int x{500};
    int y{0};

    try {
        double z = divide_2(x, y);
        std::cout << z << std::endl;
    }
    catch (...) {
        std::cout << "Error!" << std::endl;
    }
    std::cout << "The End..." << std::endl;
}

//---------------------------------------------------------------------------- Пример3
double divide_3(int a, int b) {
    if (b != 0)
        return a / b;
    throw std::string{"Division by zero!"};
}

void example_3() {
    int x{500};
    int y{0};

    try {
        double z = divide_3(x, y);
        std::cout << z << std::endl;
    }
    catch (const std::string &error_message)    // строка передается по ссылке
    {
        std::cout << error_message << std::endl;
    }
    std::cout << "The End..." << std::endl;
}

//---------------------------------------------------------------------------- Пример4
double divide_4(int a, int b) {
    if (!b)  // если b == 0
    {
        throw 0;
    }
    if (b > a) {
        throw "The second number is greater than the first one";
    }
    return a / b;
}

void example_4(int a, int b) {
    try {
        double result = divide_4(a, b);
        std::cout << result << std::endl;
    }
    catch (int code) {
        std::cout << "Error code: " << code << std::endl;
    }
    catch (const char *error_message) {
        std::cout << error_message << std::endl;
    }
}

//---------------------------------------------------------------------------- Пример5
double divide_5(int a, int b) {
    if (b != 0)
        return a / b;
    throw std::invalid_argument("Введен 0 в качестве делимого");
}

void example_5() {
    int x{500};
    int y{0};

    try {
        double z = divide_5(x, y);
        std::cout << z << std::endl;
    }
    catch (const std::invalid_argument &error){
        std::cout<<error.what()<< std::endl;
    }
    std::cout << "The End..." << std::endl;
}

//---------------------------------------------------------------------------- Пример6
class Exception {
};

class VectorError : public Exception {
};

class Overflow : public VectorError {
};

class WrongSize : public VectorError {
};

class StackError : public Exception {
};

class Underflow : public StackError {
};


bool canHandleItCompletely(Exception &exception) {
    return false;
}

void doWhatYouCanDo(Exception &exception) {

}

void f() {
    try {
        // ...
        throw Underflow();
    }
    catch (Exception &re) {
        if (canHandleItCompletely(re)) {
            // обработка исключения в функции
            return;
        } else {
            doWhatYouCanDo(re);
            throw;
        }
    }
}

void g() {
    try {
        f();
    }
    catch (StackError &re) {
        // обработка stack error
    }
    catch (VectorError &re) {
        // обработка vector error
    }
}
//----------------------------------------------------------------------------

int main() {
//    example_1();
//    example_2();
//    example_3();
//    example_4(100, 20);      // 5
//    example_4(100, 0);       // Error code: 0
//    example_4(100, 1000);    // The second number is greater than the first one
    example_5();
}
