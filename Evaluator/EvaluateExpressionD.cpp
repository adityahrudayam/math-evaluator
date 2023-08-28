#include <iostream>
#include <math.h>
#include <stack>
#include "EvaluateExpressionD.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::stack;

static void preprocessAndValidate(string &s)
{
    if (!s.empty() && (s[0] == '*' || s[0] == '/' || s[0] == '^' || s[0] == '%'))
        throw "bad input!";
    int openingBrackets = 0;
    ui idx = 0, N = static_cast<ui>(s.length());
    for (ui i = 0; i < s.length(); i++)
    {
        while (i < N && s[i] == ' ')
            i++;
        while (i < N && s[i] != ' ')
        {
            if (s[i] == '(')
                openingBrackets++;
            else if (s[i] == ')')
                openingBrackets--;
            s[idx++] = s[i++];
        }
    }
    if (openingBrackets != 0)
        throw "bad input!";
    s.resize(idx);
    // cout << s << endl;
}

static uc getFunction(const string &s)
{
    string f = s;
    for (char &c : f)
        tolower(c);
    if (f == "(")
        return 0;
    if (f == "+" || f == "-")
        return 1;
    if (f == "*" || f == "/" || f == "%")
        return 2;
    if (f == "^")
        return 3;
    if (f == "sin")
        return 4;
    if (f == "sinr")
        return 5;
    if (f == "cos")
        return 6;
    if (f == "cosr")
        return 7;
    if (f == "tan")
        return 8;
    if (f == "tanr")
        return 9;
    if (f == "cot")
        return 10;
    if (f == "cotr")
        return 11;
    if (f == "cosec")
        return 12;
    if (f == "cosecr")
        return 13;
    if (f == "sec")
        return 14;
    if (f == "secr")
        return 15;
    if (f == "log2")
        return 16;
    if (f == "loge")
        return 17;
    if (f == "log")
        return 18;
    throw "bad input!";
}

static ld performOperation(const ld &b, const ld &a, const string &op)
{
    if (op.empty())
        throw "bad input!";
    switch (op[0])
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw "bad input!";
        return a / b;
    case '%':
        if (static_cast<long long>(b) == 0 || static_cast<long long>(a) != a || static_cast<long long>(b) != b)
            throw "bad input!";
        return static_cast<long long>(a) % static_cast<long long>(b);
    case '^':
        if (a < 0 && static_cast<long long>(b) != b)
            throw "bad input!";
        return pow(a, b);
    default:
        throw "bad input!";
    };
}

static ld performOperation(const ld &x, const uc &op, const ld &y = 10)
{
    ld deg = x * M_PI / 180;
    switch (op)
    {
    case 4:
        return sinl(deg);
    case 5:
        return sinl(x);
    case 6:
        return cosl(deg);
    case 7:
        return cosl(x);
    case 8:
        return tanl(deg);
    case 9:
        return tanl(x);
    case 10:
        return 1 / tanl(deg);
    case 11:
        return 1 / tanl(x);
    case 12:
        return 1 / sinl(deg);
    case 13:
        return 1 / sinl(x);
    case 14:
        return 1 / cosl(deg);
    case 15:
        return 1 / cosl(x);
    case 16:
        if (x <= 0)
            throw "bad input!";
        return log2l(x);
    case 17:
        if (x <= 0)
            throw "bad input!";
        return logl(x);
    case 18:
        if (x <= 0 || y <= 0)
            throw "bad input!";
        return log10l(x) / log10l(y);
    default:
        return 0;
    };
}

// Evaluating any given expression with logarithmic, trigonometric functions - returning a double.
ld evaluateExpressionD(string &s) noexcept
{
    try
    {
        preprocessAndValidate(s);
        const ui N = static_cast<ui>(s.length());
        if (N == 0)
            return 0;
        stack<string> operators;
        stack<ld> operands;
        ui i = 0;
        while (i < N)
        {
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                ui j = i;
                while (i < N && s[i] != '(')
                    i++;
                if (i == N)
                {
                    const char *e = "Wrong syntax or unknown symbols in the input!";
                    cerr << e << endl;
                    throw e;
                }
                string op = s.substr(j, i - j);
                getFunction(op);
                operators.push(op);
                operators.push("(");
                i++;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                ui j = i;
                while (i < N && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                    i++;
                ld num = stod(s.substr(j, i - j));
                operands.push(num);
            }
            else if (s[i] == '(')
            {
                operators.push("(");
                i++;
            }
            else if (s[i] == ')' || s[i] == ',')
            {
                while (!operators.empty() && operators.top() != "(")
                {
                    string op = operators.top();
                    operators.pop();
                    uc f = getFunction(op);
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                if (s[i] == ')')
                    operators.pop();
                i++;
            }
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == '^' || ((s[i - 1] < '0' || s[i - 1] > '9') && s[i - 1] != ')')))
            {
                if (i + 1 == N || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '%' || s[i + 1] == '^')
                    throw "bad input!";
                if (s[i + 1] >= '0' && s[i + 1] <= '9')
                {
                    ui j = ++i;
                    while (i < N && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                        i++;
                    ld num = stod(s.substr(j, i - j));
                    operands.push(s[j - 1] == '-' ? -num : num);
                }
                else
                {
                    operators.push(s[i] == '-' ? "-" : "+");
                    operands.push(0);
                    i++;
                }
            }
            else if (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^') && ((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == ')'))
            {
                const string currOp(1, s[i]);
                uc f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    string op = operators.top();
                    operators.pop();
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                operators.push(currOp);
                i++;
            }
            else
                throw "bad input!";
        }
        while (!operators.empty())
        {
            string op = operators.top();
            if (op == "(")
                throw "bad input!";
            operators.pop();
            uc f = getFunction(op);
            if (f > 3 && f != 18)
            {
                if (operands.empty())
                    throw "bad input!";
                ld num = operands.top();
                operands.pop();
                operands.push(performOperation(num, f));
            }
            else
            {
                if (operands.empty())
                    throw "bad input!";
                ld n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                ld n1 = operands.top();
                operands.pop();
                if (f != 18)
                    operands.push(performOperation(n2, n1, op));
                else
                    operands.push(performOperation(n1, f, n2));
            }
        }
        if (operands.empty() || !operators.empty() || operands.size() > 1)
            throw "bad input!";
        return operands.top();
    }
    catch (string e)
    {
        cerr << e << endl;
        return 0.0;
    }
    catch (...)
    {
        cerr << "bad input!" << endl;
        return 0.0;
    }
}

ld evaluateExpressionD(string &&s) noexcept
{
    try
    {
        preprocessAndValidate(s);
        const ui N = static_cast<ui>(s.length());
        if (N == 0)
            return 0;
        stack<string> operators;
        stack<ld> operands;
        ui i = 0;
        while (i < N)
        {
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                ui j = i;
                while (i < N && s[i] != '(')
                    i++;
                if (i == N)
                {
                    const char *e = "Wrong syntax or unknown symbols in the input!";
                    cerr << e << endl;
                    throw e;
                }
                string op = s.substr(j, i - j);
                getFunction(op);
                operators.push(op);
                operators.push("(");
                i++;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                ui j = i;
                while (i < N && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                    i++;
                ld num = stod(s.substr(j, i - j));
                operands.push(num);
            }
            else if (s[i] == '(')
            {
                operators.push("(");
                i++;
            }
            else if (s[i] == ')' || s[i] == ',')
            {
                while (!operators.empty() && operators.top() != "(")
                {
                    string op = operators.top();
                    operators.pop();
                    uc f = getFunction(op);
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                if (s[i] == ')')
                    operators.pop();
                i++;
            }
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == '^' || ((s[i - 1] < '0' || s[i - 1] > '9') && s[i - 1] != ')')))
            {
                if (i + 1 == N || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '%' || s[i + 1] == '^')
                    throw "bad input!";
                if (s[i + 1] >= '0' && s[i + 1] <= '9')
                {
                    ui j = ++i;
                    while (i < N && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                        i++;
                    ld num = stod(s.substr(j, i - j));
                    operands.push(s[j - 1] == '-' ? -num : num);
                }
                else
                {
                    operators.push(s[i] == '-' ? "-" : "+");
                    operands.push(0);
                    i++;
                }
            }
            else if (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^') && ((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == ')'))
            {
                const string currOp(1, s[i]);
                uc f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    string op = operators.top();
                    operators.pop();
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                operators.push(currOp);
                i++;
            }
            else
                throw "bad input!";
        }
        while (!operators.empty())
        {
            string op = operators.top();
            if (op == "(")
                throw "bad input!";
            operators.pop();
            uc f = getFunction(op);
            if (f > 3 && f != 18)
            {
                if (operands.empty())
                    throw "bad input!";
                ld num = operands.top();
                operands.pop();
                operands.push(performOperation(num, f));
            }
            else
            {
                if (operands.empty())
                    throw "bad input!";
                ld n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                ld n1 = operands.top();
                operands.pop();
                if (f != 18)
                    operands.push(performOperation(n2, n1, op));
                else
                    operands.push(performOperation(n1, f, n2));
            }
        }
        if (operands.empty() || !operators.empty() || operands.size() > 1)
            throw "bad input!";
        return operands.top();
    }
    catch (string e)
    {
        cerr << e << endl;
        return 0.0;
    }
    catch (...)
    {
        cerr << "bad input!" << endl;
        return 0.0;
    }
}

ld evaluateExpressionDWithoutPreprocessing(const string &s) noexcept
{
    try
    {
        char prev = '\0';
        const unsigned int N = static_cast<unsigned int>(s.length());
        if (N == 0)
            return 0;
        stack<string> operators;
        stack<ld> operands;
        unsigned int i = 0;
        while (i < N)
        {
            if (s[i] == ' ')
                i++;
            else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                string substr;
                while (i < N && (s[i] != '(' || s[i] == ' '))
                {
                    if (s[i] != ' ')
                        substr += s[i];
                    i++;
                }
                if (i == N)
                {
                    const char *e = "Wrong syntax or unknown symbols in the input!";
                    cerr << e << endl;
                    throw e;
                }
                getFunction(substr);
                operators.push(substr);
                operators.push("(");
                prev = substr[0];
                i++;
            }
            else if (isdigit(s[i]))
            {
                string substr;
                while (i < N && (isdigit(s[i]) || s[i] == '.' || s[i] == ' '))
                {
                    if (s[i] != ' ')
                        substr += s[i];
                    i++;
                }
                ld num = stod(substr);
                operands.push(num);
                prev = substr[substr.length() - 1];
            }
            else if (s[i] == '(')
            {
                operators.push("(");
                prev = '(';
                i++;
            }
            else if (s[i] == ')' || s[i] == ',')
            {
                while (!operators.empty() && operators.top() != "(")
                {
                    string op = operators.top();
                    operators.pop();
                    unsigned char f = getFunction(op);
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                if (s[i] == ')')
                    operators.pop();
                prev = s[i];
                i++;
            }
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || prev == '^' || (!isdigit(prev) && prev != ')')))
            {
                unsigned int j = i + 1;
                while (j < N && s[j] == ' ')
                    j++;
                if (j == N || s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/' || s[j] == '%' || s[j] == '^')
                    throw "bad input!";
                if (isdigit(s[j]))
                {
                    string substr;
                    while (j < N && (isdigit(s[j]) || s[j] == '.' || s[j] == ' '))
                    {
                        if (s[j] != ' ')
                            substr += s[j];
                        j++;
                    }
                    ld num = stod(substr);
                    operands.push(s[i] == '-' ? -num : num);
                    prev = substr[substr.length() - 1];
                    i = j;
                }
                else
                {
                    operators.push(s[i] == '-' ? "-" : "+");
                    operands.push(0);
                    prev = s[i];
                    i++;
                }
            }
            else if (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^') && (isdigit(prev) || prev == ')'))
            {
                const string currOp(1, s[i]);
                unsigned char f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    string op = operators.top();
                    operators.pop();
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                operators.push(currOp);
                prev = s[i];
                i++;
            }
            else
                throw "bad input!";
        }
        while (!operators.empty())
        {
            string op = operators.top();
            if (op == "(")
                throw "bad input!";
            operators.pop();
            unsigned char f = getFunction(op);
            if (f > 3 && f != 18)
            {
                if (operands.empty())
                    throw "bad input!";
                ld num = operands.top();
                operands.pop();
                operands.push(performOperation(num, f));
            }
            else
            {
                if (operands.empty())
                    throw "bad input!";
                ld n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                ld n1 = operands.top();
                operands.pop();
                if (f != 18)
                    operands.push(performOperation(n2, n1, op));
                else
                    operands.push(performOperation(n1, f, n2));
            }
        }
        if (operands.empty() || !operators.empty() || operands.size() > 1)
            throw "bad input!";
        return operands.top();
    }
    catch (string e)
    {
        cerr << e << endl;
        return 0.0;
    }
    catch (...)
    {
        cerr << "bad input!" << endl;
        return 0.0;
    }
}

ld evaluateExpressionDWithoutPreprocessing(string &&s) noexcept
{
    try
    {
        char prev = '\0';
        const unsigned int N = static_cast<unsigned int>(s.length());
        if (N == 0)
            return 0;
        stack<string> operators;
        stack<ld> operands;
        unsigned int i = 0;
        while (i < N)
        {
            if (s[i] == ' ')
                i++;
            else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                string substr;
                while (i < N && (s[i] != '(' || s[i] == ' '))
                {
                    if (s[i] != ' ')
                        substr += s[i];
                    i++;
                }
                if (i == N)
                {
                    const char *e = "Wrong syntax or unknown symbols in the input!";
                    cerr << e << endl;
                    throw e;
                }
                getFunction(substr);
                operators.push(substr);
                operators.push("(");
                prev = substr[0];
                i++;
            }
            else if (isdigit(s[i]))
            {
                string substr;
                while (i < N && (isdigit(s[i]) || s[i] == '.' || s[i] == ' '))
                {
                    if (s[i] != ' ')
                        substr += s[i];
                    i++;
                }
                ld num = stod(substr);
                operands.push(num);
                prev = substr[substr.length() - 1];
            }
            else if (s[i] == '(')
            {
                operators.push("(");
                prev = '(';
                i++;
            }
            else if (s[i] == ')' || s[i] == ',')
            {
                while (!operators.empty() && operators.top() != "(")
                {
                    string op = operators.top();
                    operators.pop();
                    unsigned char f = getFunction(op);
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                if (s[i] == ')')
                    operators.pop();
                prev = s[i];
                i++;
            }
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || prev == '^' || (!isdigit(prev) && prev != ')')))
            {
                unsigned int j = i + 1;
                while (j < N && s[j] == ' ')
                    j++;
                if (j == N || s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/' || s[j] == '%' || s[j] == '^')
                    throw "bad input!";
                if (isdigit(s[j]))
                {
                    string substr;
                    while (j < N && (isdigit(s[j]) || s[j] == '.' || s[j] == ' '))
                    {
                        if (s[j] != ' ')
                            substr += s[j];
                        j++;
                    }
                    ld num = stod(substr);
                    operands.push(s[i] == '-' ? -num : num);
                    prev = substr[substr.length() - 1];
                    i = j;
                }
                else
                {
                    operators.push(s[i] == '-' ? "-" : "+");
                    operands.push(0);
                    prev = s[i];
                    i++;
                }
            }
            else if (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^') && (isdigit(prev) || prev == ')'))
            {
                const string currOp(1, s[i]);
                unsigned char f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    string op = operators.top();
                    operators.pop();
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ld n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ld n1 = operands.top();
                        operands.pop();
                        if (f != 18)
                            operands.push(performOperation(n2, n1, op));
                        else
                            operands.push(performOperation(n1, f, n2));
                    }
                }
                operators.push(currOp);
                prev = s[i];
                i++;
            }
            else
                throw "bad input!";
        }
        while (!operators.empty())
        {
            string op = operators.top();
            if (op == "(")
                throw "bad input!";
            operators.pop();
            unsigned char f = getFunction(op);
            if (f > 3 && f != 18)
            {
                if (operands.empty())
                    throw "bad input!";
                ld num = operands.top();
                operands.pop();
                operands.push(performOperation(num, f));
            }
            else
            {
                if (operands.empty())
                    throw "bad input!";
                ld n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                ld n1 = operands.top();
                operands.pop();
                if (f != 18)
                    operands.push(performOperation(n2, n1, op));
                else
                    operands.push(performOperation(n1, f, n2));
            }
        }
        if (operands.empty() || !operators.empty() || operands.size() > 1)
            throw "bad input!";
        return operands.top();
    }
    catch (string e)
    {
        cerr << e << endl;
        return 0.0;
    }
    catch (...)
    {
        cerr << "bad input!" << endl;
        return 0.0;
    }
}
