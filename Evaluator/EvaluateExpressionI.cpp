#include <iostream>
#include <math.h>
#include <stack>
#include "EvaluateExpressionI.hpp"

using std::cout;
using std::endl;
using std::stack;

inline static void preprocessAndValidate(std::string &s)
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
            if (s[i] == '.')
                throw "bad input!";
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

inline static uc getFunction(const std::string &s)
{
    std::string f = s;
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

inline static ll powI(ll x, ll n)
{
    if (x == 0)
    {
        if (n == 0)
            throw "bad input!";
        return 0;
    }
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n & 1)
        return powI(x * x, n / 2) * x;
    else
        return powI(x * x, n / 2);
}

inline static ll performOperation(const ll &b, const ll &a, const std::string &op)
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
        if (b == 0)
            throw "bad input!";
        return a % b;
    case '^':
        return powI(a, b);
    default:
        throw "bad input!";
    };
}

inline static ll performOperation(const ll &x, const uc &op, const ll &y = 10)
{
    long double deg = x * M_PI / 180;
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

// Evaluating any given expression with logarithmic, trigonometric functions - returning an int
ll evaluateExpressionI(std::string s) noexcept
{
    try
    {
        preprocessAndValidate(s);
        const ui N = static_cast<ui>(s.length());
        if (N == 0)
            return 0;
        stack<std::string> operators;
        stack<ll> operands;
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
                    cout << e << endl;
                    throw e;
                }
                std::string op = s.substr(j, i - j);
                getFunction(op);
                operators.push(op);
                operators.push("(");
                i++;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                ui j = i;
                while (i < N && s[i] >= '0' && s[i] <= '9')
                    i++;
                ll num = stod(s.substr(j, i - j));
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
                    std::string op = operators.top();
                    operators.pop();
                    uc f = getFunction(op);
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ll num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ll n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ll n1 = operands.top();
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
                    while (i < N && (s[i] >= '0' && s[i] <= '9'))
                        i++;
                    ll num = stod(s.substr(j, i - j));
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
                const std::string currOp(1, s[i]);
                uc f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    std::string op = operators.top();
                    operators.pop();
                    if (f > 3 && f != 18)
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ll num = operands.top();
                        operands.pop();
                        operands.push(performOperation(num, f));
                    }
                    else
                    {
                        if (operands.empty())
                            throw "bad input!";
                        ll n2 = operands.top();
                        operands.pop();
                        if (operands.empty())
                            throw "bad input!";
                        ll n1 = operands.top();
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
            std::string op = operators.top();
            if (op == "(")
                throw "bad input!";
            operators.pop();
            uc f = getFunction(op);
            if (f > 3 && f != 18)
            {
                if (operands.empty())
                    throw "bad input!";
                ll num = operands.top();
                operands.pop();
                operands.push(performOperation(num, f));
            }
            else
            {
                if (operands.empty())
                    throw "bad input!";
                ll n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                ll n1 = operands.top();
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
    catch (std::string e)
    {
        cout << e << endl;
        return 0.0;
    }
    catch (...)
    {
        cout << "bad input!" << endl;
        return 0.0;
    }
}
