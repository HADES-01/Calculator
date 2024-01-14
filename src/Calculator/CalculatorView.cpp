#include <string>
#include <iostream>
#include <math.h>

namespace Calculator
{
    class CalculatorData
    {
    private:
        std::string operand1;
        std::string operand2;
        std::string operation;
        std::string expression;

    public:
        CalculatorData()
        {
            reset();
        }

        std::string GetOperand2() { return operand2; }
        std::string GetExpression() { return expression; }

        void OnNumKeyPressed(std::string key)
        {
            updateOperands(key);
        }

        void OnSpecialKeyPressed(std::string key)
        {
            switch (key.back())
            {
            case '=':
                calculate();
                break;

            case '.':
                updateOperands(key);
                break;

            default:
                updateOperation(key);
            }
        }

        void OnBackspacePressed()
        {
            backspacePressed();
        }

        void Reset()
        {
            reset();
        }

    private:
        std::string sanitizeFloat(std::string &str)
        {
            size_t pos = str.find_first_of('.');
            if (pos != str.npos)
            {
                bool f = 0;
                int last_non_zero = 0;
                for (int i = pos + 1; i < str.size(); i++)
                {
                    if (str[i] != '0')
                    {
                        f = 1;
                        last_non_zero = i;
                    }
                }
                if (!f)
                    return str.substr(0, pos);
                else
                    return str.substr(0, last_non_zero + 1);
            }
            return str;
        }

        void updateOperands(std::string op)
        {
            if (expression.back() == '=')
            {
                reset();
            }
            if (op == "." && operand2.empty())
            {
                operand2 = "0";
            }
            operand2 += op;
        }

        void updateOperation(std::string op)
        {
            if (operand1.empty())
            {
                operand1 = operand2;
            }
            operand2 = "";
            operation = op;
            expression = operand1 + " " + operation;
        }

        void backspacePressed()
        {
            if (operand2.size() > 0)
                operand2.pop_back();
        }

        void reset()
        {
            operand1 = "";
            operand2 = "";
            operation = "";
            expression = "";
        }

        void calculate()
        {
            std::string ans;
            if (operand1.empty() || operand2.empty() || operation.empty())
                return;
            switch (operation.back())
            {
            case '+':
            {
                double temp = std::stod(operand1) + std::stod(operand2);
                ans = std::to_string(temp);
                break;
            }
            case '-':
            {
                double temp = std::stod(operand1) - std::stod(operand2);
                ans = std::to_string(temp);
                break;
            }
            case '*':
            {
                double temp = std::stod(operand1) * std::stod(operand2);
                ans = std::to_string(temp);
                break;
            }
            case '/':
            {
                double temp = std::stod(operand1) / std::stod(operand2);
                ans = std::to_string(temp);
                break;
            }
            case '^':
            {
                double temp = std::pow(std::stod(operand1), std::stod(operand2));
                ans = std::to_string(temp);
                break;
            }
            }
            expression = operand1 + " " + operation + " " + operand2 + " =";
            ans = sanitizeFloat(ans);
            operand1 = operand2 = ans;
            operation = "";
        }
    };
}