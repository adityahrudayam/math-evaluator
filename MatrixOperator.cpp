#include "MatrixOperator.hpp"
#include <fstream>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

string findOrderOfMinOps(uc dim[], const ui &N)
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
        cout << multiplyAndGetResult<MatrixLD>(vec) << endl;
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
        cout << multiplyAndGetResult<MatrixLL>(vec) << endl;
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
                    s[j + i * N] = BigInteger(num);
                }
            }
            vec.emplace_back(M, N, s);
        }
        cout << multiplyAndGetResult<MatrixBigInteger>(vec) << endl;
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

bool saveLDMToFile(const char *path, MatrixLD &obj) // incomplete
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
        const char *ptr = (const char *)symbols;
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
