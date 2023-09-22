/*
Общая постановка.
Даны два выражения Z1 и Z2. 
Написать функции для вычисления этих выражений с организацией обнаружения исключительной ситуации
(например, деление на ноль) и ее обработки.
Передача аргументов в функции - по ссылкам.

Для генерации исключения реализовать свой класс CustomException, который будет производным от Exception и будет содержать :
 
-строку с сообщением об ошибке;
-значение, которое привело к ошибке;
-код ошибки.

При обработке исключения показать использование класса CustomException.
В случае успеха значения z1 и z2 должны быть приблизительно одинаковыми.

N9. Z1 = (2 + (1 + x + x²) / (2x + x²) - (1 - x + x²) / (2x - x²) ² * (5 - 2x²), 
    Z2 = (4 - x²) / 2.
*/

#include <iostream>
#include <cmath>

class CustomException : public std::exception {
public:
    CustomException(const std::string& message, double errorValue, int errorCode)
        : errorMessage(message), errorValue(errorValue), errorCode(errorCode) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }

private:
    std::string errorMessage;
    double errorValue;
    int errorCode;
};

template <typename T>
bool throwException(T& x) {

    if (x == 0) {
        throw CustomException("Ошибка: деление на нуль", x, 1);
    }
}

double calculateZ1(double& x) {
    double numerator1 = (1 + x + x * x);
    double denominator1 = (2 * x + x * x);

    double numerator2 = (1 - x + x * x);
    double denominator2 = (2 * x - x * x);

    double innerResult = (2 + (numerator1 / denominator1) - (numerator2 / denominator2));
    double result = innerResult * innerResult * (5 - 2 * x * x);

    throwException(result);

    return result;
}

double calculateZ2(double& x) {
    double result = (4 - x * x) / 2;

    throwException(result);

    return result;
}

int main() {
    setlocale(0, "ru");
    double Z1, Z2, x;

    try {
        std::cout << "Введите значение x: ";
        std::cin >> x;

        Z1 = calculateZ1(x);
        Z2 = calculateZ2(x);

        std::cout << "Z1 = " << Z1 << std::endl;
        std::cout << "Z2 = " << Z2 << std::endl;
    }
    catch (const CustomException& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }
    
    system("pause");
    return 0;
}
