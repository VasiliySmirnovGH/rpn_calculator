#ifndef RPN_H
#define RPN_H

#include <string>
#include <stdexcept>
#include <cmath>
#include <map>

double evaluate_rpn(const std::string& expression);
void set_variable(const std::string& name, double value);
double get_variable(const std::string& name);
void clear_variables();

// Новые функции
double factorial(double n);
double power(double base, double exponent);

#endif
/**
* @brief Evaluates a mathematical expression in Reverse Polish Notation (RPN).
*
* @param expression A string containing the RPN expression (e.g., "2 3 +").
* Tokens must be separated by spaces.
* @return double The result of the evaluated expression.
* @exception std::invalid_argument Thrown if the expression is invalid,
* contains an unknown operator, or attempts division by zero.
*/
