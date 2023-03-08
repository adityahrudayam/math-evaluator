#include <iostream>
#include <vector>
#include <algorithm>
#include "BigInteger.hpp"

using std::cout;
using std::endl;
using std::vector;

BigInteger::BigInteger() : Sign(0), Num("0") {}

BigInteger::BigInteger(ll num) : Sign(num < 0 ? 1 : 0), Num(BuildNumStr(num)) {}

BigInteger::BigInteger(const char *s)
{
    ui N = 0;
    while (s[N] != 0)
        N++;
    if (s[0] == '-')
    {
        Num.reserve(N - 1);
        Sign = 1;
        for (ui i = N - 1; i > 0; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                Num.clear();
                throw "bad input!";
            }
            Num.push_back(s[i]);
        }
    }
    else
    {
        Num.reserve(N);
        Sign = 0;
        for (ui i = N - 1; i > 0; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                Num.clear();
                throw "bad input!";
            }
            Num.push_back(s[i]);
        }
        if (s[0] != '+')
        {
            if (s[0] < '0' || s[0] > '9')
            {
                Num.clear();
                throw "bad input!";
            }
            Num.push_back(s[0]);
        }
    }
}

BigInteger::BigInteger(string &s)
{
    ui N = static_cast<ui>(s.length());
    if (s[0] == '-')
    {
        Sign = 1;
        Num.reserve(N - 1);
        for (ui i = N - 1; i > 0; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                Num.clear();
                throw "bad input!";
            }
            Num.push_back(s[i]);
        }
    }
    else
    {
        Sign = 0;
        Num.reserve(N);
        for (int i = N - 1; i > -1; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                Num.clear();
                throw "bad input!";
            }
            Num.push_back(s[i]);
        }
    }
}

BigInteger::BigInteger(uc sign, string s) : Sign(sign), Num(s) {}

BigInteger::BigInteger(const BigInteger &o) : Sign(o.Sign), Num(o.Num) {}

string BigInteger::BuildNumStr(ll &num)
{
    num = num < 0 ? -num : num;
    string res;
    do
    {
        res.push_back(num % 10 + '0');
        num /= 10;
    } while (num);
    return res;
}

inline BigInteger BigInteger::SubtractionHelper(BigInteger &o, const ui &M, const ui &N)
{
    if (*this < o)
    {
        string curr = o.Num;
        char carry = 0;
        for (int i = 0; i < N; i++)
        {
            char dig;
            if (i < M)
                dig = carry + curr[i] - Num[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(o.Sign, curr);
    }
    else
    {
        string curr = this->Num;
        char carry = 0;
        for (int i = 0; i < M; i++)
        {
            char dig;
            if (i < N)
                dig = carry + curr[i] - o[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(this->Sign, curr);
    }
}

inline BigInteger BigInteger::SubtractionHelper(const BigInteger &o, const ui &M, const ui &N)
{
    if (*this < o)
    {
        string curr = o.Num;
        char carry = 0;
        for (int i = 0; i < N; i++)
        {
            char dig;
            if (i < M)
                dig = carry + curr[i] - Num[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(o.Sign, curr);
    }
    else
    {
        string curr = this->Num;
        char carry = 0;
        for (int i = 0; i < M; i++)
        {
            char dig;
            if (i < N)
                dig = carry + curr[i] - o[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(this->Sign, curr);
    }
}

bool BigInteger::IsNull() const
{
    if (Num == "0" || Num.empty() || Num[0] == 0)
        return true;
    return false;
}

const ui BigInteger::Length() const
{
    return static_cast<ui>(Num.length());
}

BigInteger BigInteger::Add(const BigInteger &o)
{
    const ui M = Length(), N = o.Length();
    if (this->Sign != o.Sign)
        return SubtractionHelper(o, M, N);
    uc carry = 0;
    string res;
    const ui len = std::max(M, N);
    res.reserve(len + 1);
    for (ui i = 0; i < len; i++)
    {
        uc x1 = i < M ? Num[i] - '0' : 0, x2 = i < N ? o[i] - '0' : 0;
        uc sum = (x1 + x2 + carry) % 10;
        res.push_back(sum + '0');
        carry = (x1 + x2 + carry) / 10;
    }
    if (carry)
        res.push_back(carry + '0');
    return BigInteger(this->Sign, res);
}

BigInteger BigInteger::Add(BigInteger &o)
{
    const ui M = Length(), N = o.Length();
    if (this->Sign != o.Sign)
        return SubtractionHelper(o, M, N);
    uc carry = 0;
    string res;
    const ui len = std::max(M, N);
    res.reserve(len + 1);
    for (ui i = 0; i < len; i++)
    {
        uc x1 = i < M ? Num[i] - '0' : 0, x2 = i < N ? o[i] - '0' : 0;
        uc sum = (x1 + x2 + carry) % 10;
        res.push_back(sum + '0');
        carry = (x1 + x2 + carry) / 10;
    }
    if (carry)
        res.push_back(carry + '0');
    return BigInteger(this->Sign, res);
}

BigInteger BigInteger::Subtract(const BigInteger &o)
{
    const ui M = Length(), N = o.Length();
    if (this->Sign != o.Sign)
    {
        uc carry = 0;
        string res;
        const ui len = std::max(M, N);
        res.reserve(len + 1);
        for (ui i = 0; i < len; i++)
        {
            uc x1 = i < M ? Num[i] - '0' : 0, x2 = i < N ? o[i] - '0' : 0;
            uc sum = (x1 + x2 + carry) % 10;
            res.push_back(sum + '0');
            carry = (x1 + x2 + carry) / 10;
        }
        if (carry)
            res.push_back(carry + '0');
        return BigInteger(this->Sign, res);
    }
    if (*this < o)
    {
        string curr = o.Num;
        char carry = 0;
        for (int i = 0; i < N; i++)
        {
            char dig;
            if (i < M)
                dig = carry + curr[i] - Num[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(1 - o.Sign, curr);
    }
    else
    {
        string curr = this->Num;
        char carry = 0;
        for (int i = 0; i < M; i++)
        {
            char dig;
            if (i < N)
                dig = carry + curr[i] - o[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(this->Sign, curr);
    }
}

BigInteger BigInteger::Subtract(BigInteger &o)
{
    const ui M = Length(), N = o.Length();
    if (this->Sign != o.Sign)
    {
        uc carry = 0;
        string res;
        const ui len = std::max(M, N);
        res.reserve(len + 1);
        for (ui i = 0; i < len; i++)
        {
            uc x1 = i < M ? Num[i] - '0' : 0, x2 = i < N ? o[i] - '0' : 0;
            uc sum = (x1 + x2 + carry) % 10;
            res.push_back(sum + '0');
            carry = (x1 + x2 + carry) / 10;
        }
        if (carry)
            res.push_back(carry + '0');
        return BigInteger(this->Sign, res);
    }
    if (*this < o)
    {
        string curr = o.Num;
        char carry = 0;
        for (int i = 0; i < N; i++)
        {
            char dig;
            if (i < M)
                dig = carry + curr[i] - Num[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(1 - o.Sign, curr);
    }
    else
    {
        string curr = this->Num;
        char carry = 0;
        for (int i = 0; i < M; i++)
        {
            char dig;
            if (i < N)
                dig = carry + curr[i] - o[i];
            else
                dig = carry + curr[i] - '0';
            if (dig < 0)
            {
                carry = -1;
                dig += 10;
            }
            else
                carry = 0;
            curr[i] = dig + '0';
        }
        while (curr.back() == '0')
            curr.pop_back();
        return BigInteger(this->Sign, curr);
    }
}

BigInteger BigInteger::Multiply(const BigInteger &o)
{
    if (*this == "0" || o.GetNum() == "0")
        return BigInteger(Sign, "0");
    const ui M = Length(), N = o.Length();
    string res(M + N, '0');
    for (ui j = 0; j < N; j++)
    {
        for (ui i = 0; i < M; i++)
        {
            const ui pos = i + j;
            const uc mult = (Num[i] - '0') * (o[j] - '0') + res[pos] - '0';
            res[pos] = mult % 10 + '0';
            res[pos + 1] += mult / 10;
        }
    }
    if (res.back() == '0')
        res.pop_back();
    uc numSign = this->Sign != o.Sign ? 1 : 0;
    return BigInteger(numSign, res);
}

BigInteger BigInteger::Multiply(BigInteger &o)
{
    if (*this == "0" || o.GetNum() == "0")
        return BigInteger(Sign, "0");
    const ui M = Length(), N = o.Length();
    string res(M + N, '0');
    for (ui j = 0; j < N; j++)
    {
        for (ui i = 0; i < M; i++)
        {
            const ui pos = i + j;
            const uc mult = (Num[i] - '0') * (o[j] - '0') + res[pos] - '0';
            res[pos] = mult % 10 + '0';
            res[pos + 1] += mult / 10;
        }
    }
    if (res.back() == '0')
        res.pop_back();
    uc numSign = this->Sign != o.Sign ? 1 : 0;
    return BigInteger(numSign, res);
}

BigInteger BigInteger::Divide(BigInteger &o)
{
    if (o.IsNull())
        throw "bad input!";
    if (*this < o)
        return BigInteger(Sign, "0");
    const uc numSign = Sign != o.Sign ? 1 : 0;
    if (*this == o)
        return BigInteger(numSign, "1");
    const ui M = Length();
    BigInteger dd;
    string res(M, '0'); // upper limit for size
    int i;
    ui idx = 0;
    for (i = M - 1; dd * 10 + (Num[i] - '0') < o; i--)
        dd = dd * 10 + (Num[i] - '0');
    while (i > -1)
    {
        dd = dd * 10 + (Num[i] - '0');
        uc coeff = 9;
        while (o * coeff > dd)
            coeff--;
        res[idx++] = coeff + '0';
        BigInteger val = o * coeff;
        dd -= val;
        i--;
    }
    res.resize(idx);
    reverse(res.begin(), res.end());
    return BigInteger(numSign, res);
}

BigInteger BigInteger::Pow(BigInteger &o)
{
    if (o.Sign)
        throw "negative powers not allowed!";
    BigInteger res(1), base(*this), pow(o);
    while (!pow.IsNull())
    {
        if ((pow[0] - '0') & 1)
            res *= base;
        base *= base;
        pow /= 2;
    }
    return res;
}

const uc BigInteger::GetSign() const
{
    return Sign;
}

void BigInteger::SetSign(const uc &sign)
{
    this->Sign = sign;
}

const string BigInteger::GetNum() const
{
    return Num;
}

void BigInteger::SetNum(const string &num)
{
    this->Num = num;
}

inline const uc BigInteger::operator[](const ui &i) const
{
    if (Num.length() <= i || i < 0)
        throw "invalid access!";
    return Num[i];
}

BigInteger BigInteger::operator+(const BigInteger &o)
{
    return Add(o);
}

BigInteger BigInteger::operator+(BigInteger &o)
{
    return Add(o);
}

BigInteger BigInteger::operator+(const ll &o)
{
    BigInteger temp(o);
    return Add(temp);
}

BigInteger BigInteger::operator-(const BigInteger &o)
{
    return Subtract(o);
}

BigInteger BigInteger::operator-(BigInteger &o)
{
    return Subtract(o);
}

BigInteger BigInteger::operator*(const BigInteger &o)
{
    return Multiply(o);
}

BigInteger BigInteger::operator*(BigInteger &o)
{
    return Multiply(o);
}

BigInteger BigInteger::operator*(const ll &o)
{
    BigInteger temp(o);
    return Multiply(temp);
}

BigInteger BigInteger::operator/(BigInteger &o)
{
    return Divide(o);
}

BigInteger BigInteger::operator^(BigInteger &o)
{
    return Pow(o);
}

// postfix increment
BigInteger BigInteger::operator++(int temp)
{
    BigInteger res(*this);
    ++(*this);
    return res;
}

// prefix increment
BigInteger &BigInteger::operator++()
{
    if (Num == "1" && Sign == 1)
    {
        Sign = 0;
        Num = "0";
        return *this;
    }
    const ui M = static_cast<ui>(Num.length());
    ui i = 0;
    if (Sign)
    {
        while (i < M && Num[i] == '0')
            Num[i++] = '9';
        Num[i]--;
        if (M > 1 && Num[M - 1] == '0')
            Num.pop_back();
    }
    else
    {
        while (i < M && Num[i] == '9')
            Num[i++] = '0';
        if (i == M)
            Num.push_back('1');
        else
            Num[i]++;
    }
    return *this;
}

// postfix decrement
BigInteger BigInteger::operator--(int temp)
{
    BigInteger res(*this);
    --(*this);
    return res;
}

// prefix decrement
BigInteger &BigInteger::operator--()
{
    if (Num == "0")
    {
        Sign = 1;
        Num = "1";
        return *this;
    }
    const ui M = static_cast<ui>(Num.length());
    ui i = 0;
    if (Sign)
    {
        while (i < M && Num[i] == '9')
            Num[i++] = '0';
        if (i == M)
            Num.push_back('1');
        else
            Num[i]++;
    }
    else
    {
        while (i < M && Num[i] == '0')
            Num[i++] = '9';
        Num[i]--;
        if (M > 1 && Num[M - 1] == '0')
            Num.pop_back();
    }
    return *this;
}

bool BigInteger::operator==(BigInteger &o)
{
    return Num == o.Num && (Sign == o.Sign || Num == "0");
}

bool BigInteger::operator==(const char *num)
{
    return (Sign && this->Num != "0" ? "-" + this->Num : this->Num) == num;
}

bool BigInteger::operator!=(BigInteger &o)
{
    return !(*this == o);
}

bool BigInteger::operator<(const BigInteger &o)
{
    ui M = Length(), N = o.Length();
    if (M != N)
        return M < N;
    while (M--)
        if (Num[M] != o[M])
            return Num[M] < o[M];
    return false;
}

bool BigInteger::operator<(BigInteger &o)
{
    ui M = Length(), N = o.Length();
    if (M != N)
        return M < N;
    while (M--)
        if (Num[M] != o[M])
            return Num[M] < o[M];
    return false;
}

bool BigInteger::operator<(const string &o)
{
    ui M = Length(), N = static_cast<ui>(o.length());
    if (M != N)
        return M < N;
    while (M--)
        if (Num[M] != o[M])
            return Num[M] < o[M];
    return false;
}

bool BigInteger::operator>(BigInteger &o)
{
    ui M = Length(), N = o.Length();
    if (M != N)
        return M > N;
    while (M--)
        if (Num[M] != o[M])
            return Num[M] > o[M];
    return false;
}

bool BigInteger::operator>(const string &o)
{
    ui M = Length(), N = static_cast<ui>(o.length());
    if (M != N)
        return M > N;
    while (M--)
        if (Num[M] != o[M])
            return Num[M] > o[M];
    return false;
}

bool BigInteger::operator<=(BigInteger &o)
{
    return !(*this > o);
}

bool BigInteger::operator>=(BigInteger &o)
{
    return !(*this < o);
}

BigInteger &BigInteger::operator=(const BigInteger &o)
{
    Num = o.Num;
    Sign = o.Sign;
    return *this;
}

BigInteger &BigInteger::operator+=(const BigInteger &o)
{
    return *this = Add(o);
}

BigInteger &BigInteger::operator+=(BigInteger &o)
{
    return *this = Add(o);
}

BigInteger &BigInteger::operator+=(const ll &o)
{
    BigInteger temp(o);
    return *this = Add(temp);
}

BigInteger &BigInteger::operator-=(const BigInteger &o)
{
    return *this = Subtract(o);
}

BigInteger &BigInteger::operator-=(BigInteger &o)
{
    return *this = Subtract(o);
}

BigInteger &BigInteger::operator-=(const ll &o)
{
    BigInteger temp(o);
    return *this = Subtract(temp);
}

BigInteger &BigInteger::operator*=(const BigInteger &o)
{
    return *this = Multiply(o);
}

BigInteger &BigInteger::operator*=(BigInteger &o)
{
    return *this = Multiply(o);
}

BigInteger &BigInteger::operator*=(const ll &o)
{
    BigInteger temp(o);
    return *this = Multiply(temp);
}

BigInteger &BigInteger::operator/=(BigInteger &o)
{
    return *this = Divide(o);
}

BigInteger &BigInteger::operator/=(const ll &o)
{
    BigInteger temp(o);
    return *this = Divide(temp);
}

BigInteger &BigInteger::operator^=(BigInteger &o)
{
    return *this = Pow(o);
}

ostream &operator<<(ostream &out, const BigInteger &curr)
{
    const ui M = curr.Length();
    if (curr.Sign)
        out << '-';
    for (int i = M - 1; i > -1; i--)
        out << curr.Num[i] - '0';
    return out;
}

istream &operator>>(istream &in, BigInteger &curr)
{
    string s;
    in >> s;
    const ui N = static_cast<ui>(s.length());
    if (s[0] == '-')
    {
        curr.Sign = 1;
        curr.Num.reserve(N - 1);
        for (ui i = N - 1; i > 0; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                curr.Num.clear();
                throw "bad input!";
            }
            curr.Num.push_back(s[i]);
        }
    }
    else
    {
        curr.Sign = 0;
        curr.Num.reserve(N);
        for (int i = N - 1; i > -1; i--)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                curr.Num.clear();
                throw "bad input!";
            }
            curr.Num.push_back(s[i]);
        }
    }
    return in;
}
