#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <ctime>
#include <chrono>

double calculate(double a, char operation, double b) {
    switch (operation) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;  // Make sure to handle division by zero in your actual code
        default:
            return 0.0;
    }
}

double evaluate_expression(std::string expression) {
    std::stack<double> values;
    std::stack<char> ops;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;
        else if (isdigit(expression[i])) {
            double val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val*10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }
        else {
            while (!ops.empty() && ops.top() != '(' &&
                   ((ops.top() == '*' || ops.top() == '/') ||
                    ((ops.top() == '+' || ops.top() == '-') && (expression[i] == '+' || expression[i] == '-')))) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(calculate(val1, op, val2));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(calculate(val1, op, val2));
    }

    return values.top();
}

double calculate_expression(int n, int num_samples) {
    std::vector<char> operations = {'+', '-', '*', '/'};

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, operations.size() - 1);

    double total = 0.0;

    for (int i = 0; i < num_samples; ++i) {
        std::string expression = "3";
        for (int j = 1; j < n; ++j) {
            expression += ' ';
            expression += operations[distribution(generator)];
            expression += ' ';
            expression += "3";
        }
        //   std::cout << expression << "\n";
        total += evaluate_expression(expression);
    }

    return total / num_samples;
}

int main() {
    int n = 100;
    int num_samples = 1000000;
    double expected_value = calculate_expression(n, num_samples);
    std::cout << "The expected value for " << n << " 3's is: " << expected_value << std::endl;
    return 0;
}
