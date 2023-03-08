#include <iostream>
#include <fstream>
#include <stack>
#include "MatrixOperator.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::stack;

string findOrderOfMinOps(uc dim[], ui N)
{
    string sdp[N * N];
    ll dp[N * N];
    memset(dp, 0, sizeof(dp));
    for (ui len = 2; len <= N; len++)
    {
        for (ui i = 0, j = len - 1; j < N; i++, j++)
        {
            if (len == 2)
            {
                sdp[j + i * N] = std::to_string(i);
                continue;
            }
            ll min_mult = 1e18;
            string min_str;
            for (ui k = i + 1; k < j; k++)
            {
                ll mult = dp[k + i * N] + dp[j + k * N] + dim[i] * dim[k] * dim[j];
                if (mult < min_mult)
                {
                    min_mult = mult;
                    min_str = "(";
                    min_str.append(sdp[k + i * N]);
                    min_str.append("*");
                    min_str.append(sdp[j + k * N]);
                    min_str.append(")");
                }
            }
            dp[j + i * N] = min_mult;
            sdp[j + i * N] = min_str;
        }
    }
    cout << "Multiplications: " << dp[N - 1] << ", in the order: " << sdp[N - 1] << endl;
    return sdp[N - 1];
}

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
                T n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                T n1 = operands.top();
                operands.pop();
                operands.push(performOperation(n1, n2, op));
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
                T n2 = operands.top();
                operands.pop();
                if (operands.empty())
                    throw "bad input!";
                T n1 = operands.top();
                operands.pop();
                operands.push(performOperation(n1, n2, op));
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

template <Matrix T>
T performOperation(const T &n1, const T &n2, char &op)
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

void takeInputAndEvalLD()
{
    try
    {
        int size;
        cin >> size;
        vector<MatrixLD> vec;
        vec.reserve(size);
        while (size-- > 0)
        {
            int M, N;
            cin >> M >> N;
            ld *s = new ld[M * N];
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    cin >> s[j + i * N];
            vec.emplace_back(M, N, s);
        }
        cout << multiplyAndGetResult(vec) << endl;
    }
    catch (string e)
    {
        cout << e << endl;
    }
    catch (...)
    {
        cout << "bad input!" << endl;
    }
}

void takeInputAndEvalLL()
{
    try
    {
        int size;
        cin >> size;
        vector<MatrixLL> vec;
        vec.reserve(size);
        while (size-- > 0)
        {
            int M, N;
            cin >> M >> N;
            ll *s = new ll[M * N];
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    cin >> s[j + i * N];
            vec.emplace_back(M, N, s);
        }
        cout << multiplyAndGetResult(vec) << endl;
    }
    catch (string e)
    {
        cout << e << endl;
    }
    catch (...)
    {
        cout << "bad input!" << endl;
    }
}

void takeInputAndEvalBI()
{
    try
    {
        int size;
        cin >> size;
        vector<MatrixBigInteger> vec;
        vec.reserve(size);
        while (size-- > 0)
        {
            int M, N;
            cin >> M >> N;
            BigInteger *s = new BigInteger[M * N];
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    string num;
                    cin >> num;
                    new (&(s[j + i * N])) BigInteger(num);
                }
            }
            vec.emplace_back(M, N, s);
        }
        cout << multiplyAndGetResult(vec) << endl;
    }
    catch (string e)
    {
        cout << e << endl;
    }
    catch (...)
    {
        cout << "bad input!" << endl;
    }
}

bool saveLDMToFile(const char *path, MatrixLD &obj)
{
    try
    {
        ofstream fs(path, std::ios::ate | std::ios::app);
        fs.write((char *)&obj, sizeof(obj));
        return true;
    }
    catch (string e)
    {
        cout << e << endl;
        return false;
    }
    catch (...)
    {
        cout << "bad input!" << endl;
        return false;
    }
}

void splitOnSymbol(string &s, const char &symbol)
{
    ui idx = 0, N = static_cast<ui>(s.length());
    for (ui i = 0; i < s.length(); i++)
    {
        while (i < N && s[i] == symbol)
            i++;
        while (i < N && s[i] != symbol)
            s[idx++] = s[i++];
    }
    s.resize(idx);
}

void splitOnSymbols(string &s, const char *symbols)
{
    ui idx = 0, N = static_cast<ui>(s.length());
    auto find = [&symbols](char &c)
    {
        char *ptr = (char *)symbols;
        while (ptr != nullptr)
        {
            if (*ptr == c)
                return true;
            ptr++;
        }
        return false;
    };
    for (ui i = 0; i < s.length(); i++)
    {
        while (i < N && find(s[i]))
            i++;
        while (i < N && !find(s[i]))
            s[idx++] = s[i++];
    }
    s.resize(idx);
}
