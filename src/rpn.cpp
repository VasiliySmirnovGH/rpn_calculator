#include "rpn.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype>
#include <functional>
#include <unordered_map>
#include <random>

std::unordered_map<std::string, double> variables;
std::stack<double> history_stack;

double factorial(double n) {
    if (n < 0 || std::floor(n) != n) {
        throw std::invalid_argument("Factorial requires non-negative integer");
    }
    double result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double power(double base, double exponent) {
    return std::pow(base, exponent);
}

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (iss >> token) {
        // Проверка на число
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stack.push(std::stod(token));
            continue;
        }

        // Проверка на переменную
        if (variables.find(token) != variables.end()) {
            stack.push(variables[token]);
            continue;
        }

        // Операции
        if (token == "+") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for +");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        }
        else if (token == "-") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for -");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        }
        else if (token == "*") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for *");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a * b);
        }
        else if (token == "/") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for /");
            double b = stack.top(); stack.pop();
            if (b == 0) throw std::invalid_argument("Division by zero");
            double a = stack.top(); stack.pop();
            stack.push(a / b);
        }
        // НОВЫЕ ОПЕРАЦИИ
        else if (token == "^") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for ^");
            double exponent = stack.top(); stack.pop();
            double base = stack.top(); stack.pop();
            stack.push(power(base, exponent));
        }
        else if (token == "%") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for %");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(std::fmod(a, b));
        }
        else if (token == "!") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for !");
            double a = stack.top(); stack.pop();
            stack.push(factorial(a));
        }
        else if (token == "sqrt") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for sqrt");
            double a = stack.top(); stack.pop();
            if (a < 0) throw std::invalid_argument("Square root of negative number");
            stack.push(std::sqrt(a));
        }
        else if (token == "abs") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for abs");
            double a = stack.top(); stack.pop();
            stack.push(std::abs(a));
        }
        else if (token == "sin") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for sin");
            double a = stack.top(); stack.pop();
            stack.push(std::sin(a));
        }
        else if (token == "cos") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for cos");
            double a = stack.top(); stack.pop();
            stack.push(std::cos(a));
        }
        else if (token == "tan") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for tan");
            double a = stack.top(); stack.pop();
            stack.push(std::tan(a));
        }
        else if (token == "log") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for log");
            double a = stack.top(); stack.pop();
            if (a <= 0) throw std::invalid_argument("Logarithm of non-positive number");
            stack.push(std::log(a));
        }
        else if (token == "log10") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for log10");
            double a = stack.top(); stack.pop();
            if (a <= 0) throw std::invalid_argument("Logarithm of non-positive number");
            stack.push(std::log10(a));
        }
        else if (token == "pi") {
            stack.push(3.14159265358979323846);
        }
        else if (token == "e") {
            stack.push(2.71828182845904523536);
        }
        else if (token == "rand") {
            std::uniform_real_distribution<> dis(0.0, 1.0);
            stack.push(dis(gen));
        }
        else if (token == "round") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for round");
            double a = stack.top(); stack.pop();
            stack.push(std::round(a));
        }
        else if (token == "floor") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for floor");
            double a = stack.top(); stack.pop();
            stack.push(std::floor(a));
        }
        else if (token == "ceil") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for ceil");
            double a = stack.top(); stack.pop();
            stack.push(std::ceil(a));
        }
        else if (token == "min") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for min");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(std::min(a, b));
        }
        else if (token == "max") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for max");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(std::max(a, b));
        }
        else if (token == "dup") {
            if (stack.empty()) throw std::invalid_argument("Stack is empty for dup");
            stack.push(stack.top());
        }
        else if (token == "swap") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for swap");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(b);
            stack.push(a);
        }
        else if (token == "drop") {
            if (stack.empty()) throw std::invalid_argument("Stack is empty for drop");
            stack.pop();
        }
        else if (token == "clear") {
            while (!stack.empty()) stack.pop();
        }
        else if (token == "store") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for store");
            double value = stack.top(); stack.pop();
            std::string var_name = std::to_string(static_cast<int>(stack.top())); stack.pop();
            variables[var_name] = value;
        }
        else if (token == "recall") {
            if (stack.empty()) throw std::invalid_argument("Not enough operands for recall");
            std::string var_name = std::to_string(static_cast<int>(stack.top())); stack.pop();
            if (variables.find(var_name) == variables.end()) {
                throw std::invalid_argument("Variable not found: " + var_name);
            }
            stack.push(variables[var_name]);
        }
        else {
            throw std::invalid_argument("Unknown token: " + token);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return stack.top();
}

void set_variable(const std::string& name, double value) {
    variables[name] = value;
}

double get_variable(const std::string& name) {
    return variables[name];
}

void clear_variables() {
    variables.clear();
}
