#pragma once

#include "Matrix.hpp"
#include <stack>
#include <type_traits>
#include <vector>

using std::stack;
using std::vector;

template <class T>
concept Matrix = std::is_same<T, MatrixLD>::value || std::is_same<T, MatrixLL>::value || std::is_same<T, MatrixBigInteger>::value;

template <Matrix T>
T performOperation(T &n1, T &n2, char &op)
{
    switch (op)
    {
    case '+':
        return n1.Add(n2);
    case '-':
        return n1.Subtract(n2);
    case '*':
        return n1.Multiply(n2);
    default:
        throw "bad input!";
    }
}

template <Matrix T>
T matrixExpEval(string &s, vector<T> &vec)
{
    const ui N = static_cast<ui>(s.length());
    stack<char> operators;
    stack<T> operands;
    int i = 0;
    while (i < N)
    {
        if (s[i] == '(')
        {
            operators.push('(');
            i++;
        }
        else if (s[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                if (operands.empty())
                    throw "bad input!";
                T n2{std::move(operands.top())};
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                T n1{std::move(operands.top())};
                operands.pop();
                operands.push(std::move(performOperation(n1, n2, op)));
            }
            operators.pop();
            i++;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            string substr;
            while (i < N && s[i] >= '0' && s[i] <= '9')
                substr.push_back(s[i++]);
            operands.push(vec[stoi(substr)]);
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*')
        {
            while (!operators.empty() && (operators.top() == '*' || s[i] != '*'))
            {
                char op = operators.top();
                operators.pop();
                if (operands.empty())
                    throw "bad input!";
                T n2{std::move(operands.top())};
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                T n1{std::move(operands.top())};
                operands.pop();
                operands.push(std::move(performOperation(n1, n2, op)));
            }
            operators.push(s[i++]);
        }
        else
            throw "bad input!";
    }
    if (!operators.empty() || operands.empty() || operands.size() > 1)
        throw "bad input!";
    return operands.top();
}

string findOrderOfMinOps(uc[], const ui &);

template <Matrix T>
T multiplyAndGetResult(vector<T> &vec)
{
    if (vec.empty())
        return T{};
    if (vec.size() == 1)
        return vec[0];
    const ui N = static_cast<ui>(vec.size());
    uc dim[N + 1];
    dim[0] = vec[0].GetM();
    for (int i = 1; i < N; i++)
    {
        if (vec[i].GetM() != vec[i - 1].GetN())
            throw "bad input! cannot multiply the matrices.";
        dim[i] = vec[i].GetM();
    }
    dim[N] = vec[N - 1].GetN();
    string order = findOrderOfMinOps(dim, N + 1);
    return matrixExpEval(order, vec);
}

void takeInputAndEvalLD();

void takeInputAndEvalLL();

void takeInputAndEvalBI();

bool saveLDMToFile(const char *, MatrixLD &);

// vector<MatrixLD> LoadLDMFromFile(const char *, ll);

void splitOnSymbol(string &, const char &);

void splitOnSymbols(string &, const char *);
