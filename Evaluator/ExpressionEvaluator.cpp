#include <iostream>
#include <math.h>
#include <stack>
#include "ExpressionEvaluator.hpp"

using std::cout;
using std::endl;
using std::stack;

// inline static void preprocessAndValidate(string &s)
// {
//     if (!s.empty() && (s[0] == '*' || s[0] == '/' || s[0] == '^'))
//         throw "bad input!";
//     string text;
//     int openingBrackets = 0;
//     ui idx = 0, N = static_cast<ui>(s.length());
//     for (ui i = 0; i < s.length(); i++)
//     {
//         while (i < N && s[i] == ' ')
//             i++;
//         while (i < N && s[i] != ' ')
//         {
//             if (s[i] == '(')
//                 openingBrackets++;
//             else if (s[i] == ')')
//                 openingBrackets--;
//             s[idx++] = s[i++];
//         }
//     }
//     if (openingBrackets != 0)
//         throw "bad input!";
//     s.resize(idx);
//     // cout << s << endl;
// }

inline static uc getFunction(const string &s)
{
    string f = s;
    for (char &c : f)
        tolower(c);
    if (f == "(")
        return 0;
    if (f == "+" || f == "-")
        return 1;
    if (f == "*" || f == "/")
        return 2;
    if (f == "^")
        return 3;
    // if (f == "sin")
    //     return 4;
    // if (f == "sinr")
    //     return 5;
    // if (f == "cos")
    //     return 6;
    // if (f == "cosr")
    //     return 7;
    // if (f == "tan")
    //     return 8;
    // if (f == "tanr")
    //     return 9;
    // if (f == "cot")
    //     return 10;
    // if (f == "cotr")
    //     return 11;
    // if (f == "cosec")
    //     return 12;
    // if (f == "cosecr")
    //     return 13;
    // if (f == "sec")
    //     return 14;
    // if (f == "secr")
    //     return 15;
    // if (f == "log2")
    //     return 16;
    // if (f == "loge")
    //     return 17;
    // if (f == "log")
    //     return 18;
    throw "bad input!";
}

inline static BigInteger performOperation(BigInteger &a, BigInteger &b, const string &op)
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
        // if (b.GetNum() == "0")
        //     throw "bad input!";
        return a / b;
    case '^':
        // if (a < "0" || a.GetSign() == 1)
        //     throw "bad input!";
        return a ^ b;
    default:
        throw "bad input!";
    };
}

// inline static ld performOperation(const ld &x, const uc &op, const ld &y = 10)
// {
//     ld deg = x * M_PI / 180;
//     switch (op)
//     {
//     case 4:
//         return sinl(deg);
//     case 5:
//         return sinl(x);
//     case 6:
//         return cosl(deg);
//     case 7:
//         return cosl(x);
//     case 8:
//         return tanl(deg);
//     case 9:
//         return tanl(x);
//     case 10:
//         return 1 / tanl(deg);
//     case 11:
//         return 1 / tanl(x);
//     case 12:
//         return 1 / sinl(deg);
//     case 13:
//         return 1 / sinl(x);
//     case 14:
//         return 1 / cosl(deg);
//     case 15:
//         return 1 / cosl(x);
//     case 16:
//         if (x <= 0)
//             throw "bad input!";
//         return log2l(x);
//     case 17:
//         if (x <= 0)
//             throw "bad input!";
//         return logl(x);
//     case 18:
//         if (x <= 0 || y <= 0)
//             throw "bad input!";
//         return log10l(x) / log10l(y);
//     default:
//         return 0;
//     };
// }

// IN NEXT VERSION, THERE'LL BE AN ADDITION OF MATH FUNCTIONS & MORE
BigInteger evaluateExpression(string s) noexcept
{
    try
    {
        uc prev = '\0';
        const ui N = static_cast<ui>(s.length());
        if (N == 0)
            return BigInteger();
        stack<string> operators;
        stack<BigInteger> operands;
        ui i = 0;
        while (i < N)
        {
            if (s[i] == ' ')
                i++;
            // -------------IN NEXT VERSION------------
            // else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            // {
            //     string substr;
            //     while (i < N && (s[i] != '(' || s[i] == ' '))
            //     {
            //         if (s[i] != ' ')
            //             substr += s[i];
            //         i++;
            //     }
            //     if (i == N)
            //     {
            //         const char *e = "Wrong syntax or unknown symbols in the input!";
            //         cout << e << endl;
            //         throw e;
            //     }
            //     getFunction(substr);
            //     operators.push(substr);
            //     operators.push("(");
            //     prev = substr[0];
            //     i++;
            // }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                string substr;
                while (i < N && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.' || s[i] == ' '))
                {
                    if (s[i] == '.')
                        throw "bad input! fractional numbers not allowed.";
                    if (s[i] != ' ')
                        substr += s[i];
                    i++;
                }
                operands.push(BigInteger(substr));
                prev = substr[substr.length() - 1];
            }
            else if (s[i] == '(')
            {
                operators.push("(");
                prev = '(';
                i++;
            }
            else if (s[i] == ')')
            {
                while (!operators.empty() && operators.top() != "(")
                {
                    string op = operators.top();
                    operators.pop();
                    // uc f = getFunction(op);
                    // --------------IN NEXT VERSION--------------
                    // if (f > 3 && f != 18)
                    // {
                    //     if (operands.empty())
                    //         throw "bad input!";
                    //     ld num = operands.top();
                    //     operands.pop();
                    //     operands.push(performOperation(num, f));
                    // }
                    // else
                    // {
                    if (operands.empty())
                        throw "bad input!";
                    BigInteger n2 = operands.top();
                    operands.pop();
                    if (operands.empty())
                        throw "bad input!";
                    BigInteger n1 = operands.top();
                    operands.pop();
                    // if (f != 18)
                    operands.push(performOperation(n1, n2, op));
                    // else
                    //     operands.push(performOperation(n1, f, n2));
                    // }
                }
                operators.pop();
                prev = s[i];
                i++;
            }
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || prev == '^' || ((prev < '0' || prev > '9') && prev != ')')))
            {
                string substr;
                if (s[i] == '-')
                    substr.push_back('-');
                ui j = i + 1;
                while (j < N && s[j] == ' ')
                    j++;
                if (j == N || s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/' || s[j] == '^')
                    throw "bad input!";
                if (s[j] >= '0' && s[j] <= '9')
                {
                    while (j < N && ((s[j] >= '0' && s[j] <= '9') || s[j] == '.' || s[j] == ' '))
                    {
                        if (s[j] == '.')
                            throw "bad input! fractional numbers not allowed.";
                        if (s[j] != ' ')
                            substr += s[j];
                        j++;
                    }
                    operands.push(BigInteger(substr));
                    prev = substr[substr.length() - 1];
                    i = j;
                }
                else
                {
                    operators.push(s[i] == '-' ? "-" : "+");
                    operands.push(BigInteger());
                    prev = s[i];
                    i++;
                }
            }
            else if (i > 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') && ((prev >= '0' && prev <= '9') || prev == ')'))
            {
                const string currOp(1, s[i]);
                uc f, curr = getFunction(currOp);
                while (!operators.empty() && ((f = getFunction(operators.top())) > curr || (f == curr && curr < 3)))
                {
                    string op = operators.top();
                    operators.pop();
                    // --------------IN NEXT VERSION--------------
                    // if (f > 3 && f != 18)
                    // {
                    //     if (operands.empty())
                    //         throw "bad input!";
                    //     ld num = operands.top();
                    //     operands.pop();
                    //     operands.push(performOperation(num, f));
                    // }
                    // else
                    // {
                    if (operands.empty())
                        throw "bad input!";
                    BigInteger n2 = operands.top();
                    operands.pop();
                    if (operands.empty())
                        throw "bad input!";
                    BigInteger n1 = operands.top();
                    operands.pop();
                    // if (f != 18)
                    operands.push(performOperation(n1, n2, op));
                    // else
                    //     operands.push(performOperation(n1, f, n2));
                    // }
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
            // uc f = getFunction(op);
            // --------------IN NEXT VERSION-------------
            // if (f > 3 && f != 18)
            // {
            //     if (operands.empty())
            //         throw "bad input!";
            //     ld num = operands.top();
            //     operands.pop();
            //     operands.push(performOperation(num, f));
            // }
            // else
            // {
            if (operands.empty())
                throw "bad input!";
            BigInteger n2 = operands.top();
            operands.pop();
            if (operands.empty())
                throw "bad input!";
            BigInteger n1 = operands.top();
            operands.pop();
            // if (f != 18)
            operands.push(performOperation(n1, n2, op));
            // else
            //     operands.push(performOperation(n1, f, n2));
            // }
        }
        if (operands.empty() || !operators.empty() || operands.size() > 1)
            throw "bad input!";
        return operands.top();
    }
    catch (string e)
    {
        cout << e << endl;
        return BigInteger();
    }
    catch (...)
    {
        cout << "bad input!" << endl;
        return BigInteger();
    }
}
