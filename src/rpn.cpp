#include "rpn.h"
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

double evaluate_rpn(const string& expression) {
    stack<double> stack;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        // Обработка чисел
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            stack.push(stod(token));
            continue;
        }

        // Проверка, что достаточно операндов
        if (stack.size() < 2) {
            throw invalid_argument("Недостаточно операндов для операции: " + token);
        }

        double b = stack.top(); stack.pop();
        double a = stack.top(); stack.pop();

        // Обработка операций (ВНУТРИ ФУНКЦИИ!)
        if (token == "+") stack.push(a + b);
        else if (token == "-") stack.push(a - b);
        else if (token == "*") stack.push(a * b);
        else if (token == "/") {
            if (b == 0) throw invalid_argument("Деление на ноль");
            stack.push(a / b);
        }
        else if (token == "^") stack.push(pow(a, b));
        else {
            throw invalid_argument("Неизвестная операция: " + token);
        }
    }

    if (stack.size() != 1) {
        throw invalid_argument("Некорректное выражение");
    }

    return stack.top();
}
