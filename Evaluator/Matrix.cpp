#include <iostream>
#include "Matrix.hpp"

using std::cout;
using std::endl;

ld evaluateExpressionDWithoutPreprocessing(const string &) noexcept;

ll evaluateExpressionI(string &) noexcept;

BigInteger evaluateExpression(const string &) noexcept;

#define EvaluateLD evaluateExpressionDWithoutPreprocessing

#define EvaluateLL evaluateExpressionI

#define EvaluateBI evaluateExpression

MatrixLD::MatrixLD() : M(0), N(0), Array(nullptr)
{
}

MatrixLD::MatrixLD(const uc M, const uc N, ld *Array) : M(M), N(N), Array(Array)
{
}

MatrixLD::MatrixLD(const uc M, const uc N, const string *s) : M(M), N(N)
{
    Array = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateLD(s[j + i * N]);
}

MatrixLD::MatrixLD(const MatrixLD &o) : M{o.M}, N{o.N}
{
    Array = new ld[M * N];
    const ld *copyArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
}

MatrixLD::MatrixLD(MatrixLD &&o) noexcept : M{o.M}, N{o.N}, Array{o.Array}
{
    o.M = o.N = 0;
    o.Array = nullptr;
}

MatrixLD::~MatrixLD()
{
    if (Array != nullptr)
    {
        delete[] Array;
        Array = nullptr;
    }
}

MatrixLD MatrixLD::Add(const MatrixLD &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot add matrices of given dimensions!";
    ld *otherArr = o.Array;
    ld *res = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + otherArr[j + i * N];
    return MatrixLD(M, N, res);
}

MatrixLD MatrixLD::Subtract(const MatrixLD &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot subtract matrices of given dimensions!";
    ld *otherArr = o.Array;
    ld *res = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - otherArr[j + i * N];
    return MatrixLD(M, N, res);
}

MatrixLD MatrixLD::Multiply(const MatrixLD &o) const
{
    if (o.M != N)
        throw "Cannot multiply matrices of given dimensions!";
    const uc resM = M, resN = o.N;
    ld *otherArr = o.Array;
    ld *res = new ld[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            ld sum = 0;
            for (uc k = 0; k < N; k++)
                sum += Array[k + i * N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    return MatrixLD(resM, resN, res);
}

const uc MatrixLD::GetM() const
{
    return M;
}

const uc MatrixLD::GetN() const
{
    return N;
}

const ld *MatrixLD::GetArray() const
{
    return Array;
}

const ld MatrixLD::operator[](const unsigned short &idx) const
{
    if (Array == nullptr || idx < 0 || idx >= M * N)
        throw "Invalid access!";
    return Array[idx];
}

MatrixLD operator+(const MatrixLD &c, const MatrixLD &o)
{
    return c.Add(o);
}

MatrixLD operator+(const MatrixLD &c, const ld &o)
{
    ld *res = new ld[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] + o;
    return MatrixLD(c.M, c.N, res);
}

MatrixLD operator-(const MatrixLD &c, const MatrixLD &o)
{
    return c.Subtract(o);
}

MatrixLD operator-(const MatrixLD &c, const ld &o)
{
    ld *res = new ld[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] - o;
    return MatrixLD(c.M, c.N, res);
}

MatrixLD operator*(const MatrixLD &c, const MatrixLD &o)
{
    return c.Multiply(o);
}

MatrixLD operator*(const MatrixLD &c, const ld &o)
{
    ld *res = new ld[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] * o;
    return MatrixLD(c.M, c.N, res);
}

bool operator==(const MatrixLD &c, const MatrixLD &o)
{
    if (c.M != o.M || c.N != o.N)
        return false;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return false;
    return true;
}

bool operator!=(const MatrixLD &c, const MatrixLD &o)
{
    if (c.M != o.M || c.N != o.N)
        return true;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return true;
    return false;
}

MatrixLD &MatrixLD::operator=(const MatrixLD &o)
{
    if (this != &o)
    {
        M = o.M;
        N = o.N;
        if (Array != nullptr)
            delete[] Array;
        const ld *copyArr = o.Array;
        Array = new ld[M * N];
        for (uc i = 0; i < M; i++)
            for (uc j = 0; j < N; j++)
                Array[j + i * N] = copyArr[j + i * N];
    }
    return *this;
}

MatrixLD &MatrixLD::operator=(MatrixLD &&o) noexcept
{
    if (this != &o)
    {
        delete[] Array;
        M = o.M;
        N = o.N;
        Array = o.Array;
        o.M = o.N = 0;
        o.Array = nullptr;
    }
    return *this;
}

MatrixLD &operator+=(MatrixLD &c, const MatrixLD &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const ld *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += otherArr[j + i * c.N];
    return c;
}

MatrixLD &operator+=(MatrixLD &c, const ld &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += o;
    return c;
}

MatrixLD &operator-=(MatrixLD &c, const MatrixLD &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const ld *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= otherArr[j + i * c.N];
    return c;
}

MatrixLD &operator-=(MatrixLD &c, const ld &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= o;
    return c;
}

MatrixLD &operator*=(MatrixLD &c, const MatrixLD &o)
{
    if (c.N != o.M)
        return c;
    const uc resM = c.M, resN = o.N;
    ld *otherArr = o.Array;
    ld *res = new ld[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            ld sum = 0;
            for (uc k = 0; k < c.N; k++)
                sum += c.Array[k + i * c.N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    c.M = resM;
    c.N = resN;
    delete[] c.Array;
    c.Array = res;
    return c;
}

MatrixLD &operator*=(MatrixLD &c, const ld &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] *= o;
    return c;
}

ostream &operator<<(ostream &out, const MatrixLD &c)
{
    const uc M = c.M, N = c.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << c[j + i * N] << " ";
        out << endl;
    }
    return out;
}

MatrixLL::MatrixLL() : M(0), N(0), Array(nullptr)
{
}

MatrixLL::MatrixLL(const uc M, const uc N, ll *Array) : M(M), N(N), Array(Array)
{
}

MatrixLL::MatrixLL(const uc M, const uc N, string *s) : M(M), N(N)
{
    Array = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateLL(s[j + i * N]);
}

MatrixLL::MatrixLL(const MatrixLL &o) : M{o.M}, N{o.N}
{
    Array = new ll[M * N];
    const ll *copyArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
}

MatrixLL::MatrixLL(MatrixLL &&o) noexcept : M{o.M}, N{o.N}, Array{o.Array}
{
    o.M = o.N = 0;
    o.Array = nullptr;
}

MatrixLL::~MatrixLL()
{
    if (Array != nullptr)
    {
        delete[] Array;
        Array = nullptr;
    }
}

MatrixLL MatrixLL::Add(const MatrixLL &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot add matrices of given dimensions!";
    ll *otherArr = o.Array;
    ll *res = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + otherArr[j + i * N];
    return MatrixLL(M, N, res);
}

MatrixLL MatrixLL::Subtract(const MatrixLL &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot subtract matrices of given dimensions!";
    ll *otherArr = o.Array;
    ll *res = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - otherArr[j + i * N];
    return MatrixLL(M, N, res);
}

MatrixLL MatrixLL::Multiply(const MatrixLL &o) const
{
    if (o.M != N)
        throw "Cannot multiply matrices of given dimensions!";
    const uc resM = M, resN = o.N;
    ll *otherArr = o.Array;
    ll *res = new ll[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            ll sum = 0;
            for (uc k = 0; k < N; k++)
                sum += Array[k + i * N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    return MatrixLL(resM, resN, res);
}

const uc MatrixLL::GetM() const
{
    return M;
}

const uc MatrixLL::GetN() const
{
    return N;
}

const ll *MatrixLL::GetArray() const
{
    return Array;
}

const ll MatrixLL::operator[](const unsigned short &idx) const
{
    if (Array == nullptr || idx < 0 || idx >= M * N)
        throw "Invalid access!";
    return Array[idx];
}

MatrixLL operator+(const MatrixLL &c, const MatrixLL &o)
{
    return c.Add(o);
}

MatrixLL operator+(const MatrixLL &c, const ll &o)
{
    ll *res = new ll[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] + o;
    return MatrixLL(c.M, c.N, res);
}

MatrixLL operator-(const MatrixLL &c, const MatrixLL &o)
{
    return c.Subtract(o);
}

MatrixLL operator-(const MatrixLL &c, const ll &o)
{
    ll *res = new ll[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] - o;
    return MatrixLL(c.M, c.N, res);
}

MatrixLL operator*(const MatrixLL &c, const MatrixLL &o)
{
    return c.Multiply(o);
}

MatrixLL operator*(const MatrixLL &c, const ll &o)
{
    ll *res = new ll[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] * o;
    return MatrixLL(c.M, c.N, res);
}

bool operator==(const MatrixLL &c, const MatrixLL &o)
{
    if (c.M != o.M || c.N != o.N)
        return false;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return false;
    return true;
}

bool operator!=(const MatrixLL &c, const MatrixLL &o)
{
    if (c.M != o.M || c.N != o.N)
        return true;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return true;
    return false;
}

MatrixLL &MatrixLL::operator=(const MatrixLL &o)
{
    if (this != &o)
    {
        M = o.M;
        N = o.N;
        if (Array != nullptr)
            delete[] Array;
        const ll *copyArr = o.Array;
        Array = new ll[M * N];
        for (uc i = 0; i < M; i++)
            for (uc j = 0; j < N; j++)
                Array[j + i * N] = copyArr[j + i * N];
    }
    return *this;
}

MatrixLL &MatrixLL::operator=(MatrixLL &&o) noexcept
{
    if (this != &o)
    {
        delete[] Array;
        M = o.M;
        N = o.N;
        Array = o.Array;
        o.M = o.N = 0;
        o.Array = nullptr;
    }
    return *this;
}

MatrixLL &operator+=(MatrixLL &c, const MatrixLL &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const ll *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += otherArr[j + i * c.N];
    return c;
}

MatrixLL &operator+=(MatrixLL &c, const ll &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += o;
    return c;
}

MatrixLL &operator-=(MatrixLL &c, const MatrixLL &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const ll *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= otherArr[j + i * c.N];
    return c;
}

MatrixLL &operator-=(MatrixLL &c, const ll &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= o;
    return c;
}

MatrixLL &operator*=(MatrixLL &c, const MatrixLL &o)
{
    if (c.N != o.M)
        return c;
    const uc resM = c.M, resN = o.N;
    ll *otherArr = o.Array;
    ll *res = new ll[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            ll sum = 0;
            for (uc k = 0; k < c.N; k++)
                sum += c.Array[k + i * c.N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    c.M = resM;
    c.N = resN;
    delete[] c.Array;
    c.Array = res;
    return c;
}

MatrixLL &operator*=(MatrixLL &c, const ll &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] *= o;
    return c;
}

ostream &operator<<(ostream &out, const MatrixLL &c)
{
    const uc M = c.M, N = c.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << c[j + i * N] << " ";
        out << endl;
    }
    return out;
}

MatrixBigInteger::MatrixBigInteger() : M(0), N(0), Array(nullptr)
{
}

MatrixBigInteger::MatrixBigInteger(const uc M, const uc N, BigInteger *Array) : M(M), N(N), Array(Array)
{
}

MatrixBigInteger::MatrixBigInteger(const uc M, const uc N, const string *s) : M(M), N(N)
{
    Array = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateBI(s[j + i * N]);
}

MatrixBigInteger::MatrixBigInteger(const MatrixBigInteger &o) : M{o.M}, N{o.N}
{
    Array = new BigInteger[M * N];
    const BigInteger *copyArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
}

MatrixBigInteger::MatrixBigInteger(MatrixBigInteger &&o) noexcept : M{o.M}, N{o.N}, Array{o.Array}
{
    o.M = o.N = 0;
    o.Array = nullptr;
}

MatrixBigInteger::~MatrixBigInteger()
{
    if (Array != nullptr)
    {
        delete[] Array;
        Array = nullptr;
    }
}

MatrixBigInteger MatrixBigInteger::Add(const MatrixBigInteger &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot add matrices of given dimensions!";
    BigInteger *otherArr = o.Array;
    BigInteger *res = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + otherArr[j + i * N];
    return MatrixBigInteger(M, N, res);
}

MatrixBigInteger MatrixBigInteger::Subtract(const MatrixBigInteger &o) const
{
    if (o.M != M || o.N != N)
        throw "Cannot subtract matrices of given dimensions!";
    BigInteger *otherArr = o.Array;
    BigInteger *res = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - otherArr[j + i * N];
    return MatrixBigInteger(M, N, res);
}

MatrixBigInteger MatrixBigInteger::Multiply(const MatrixBigInteger &o) const
{
    if (o.M != N)
        throw "Cannot multiply matrices of given dimensions!";
    const uc resM = M, resN = o.N;
    BigInteger *otherArr = o.Array;
    BigInteger *res = new BigInteger[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            BigInteger sum;
            for (uc k = 0; k < N; k++)
                sum += Array[k + i * N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    return MatrixBigInteger(resM, resN, res);
}

const uc MatrixBigInteger::GetM() const
{
    return M;
}

const uc MatrixBigInteger::GetN() const
{
    return N;
}

const BigInteger *MatrixBigInteger::GetArray() const
{
    return Array;
}

const BigInteger MatrixBigInteger::operator[](const unsigned short &idx) const
{
    if (Array == nullptr || idx < 0 || idx >= M * N)
        throw "Invalid access!";
    return Array[idx];
}

MatrixBigInteger operator+(const MatrixBigInteger &c, const MatrixBigInteger &o)
{
    return c.Add(o);
}

MatrixBigInteger operator+(const MatrixBigInteger &c, const BigInteger &o)
{
    BigInteger *res = new BigInteger[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] + o;
    return MatrixBigInteger(c.M, c.N, res);
}

MatrixBigInteger operator-(const MatrixBigInteger &c, const MatrixBigInteger &o)
{
    return c.Subtract(o);
}

MatrixBigInteger operator-(const MatrixBigInteger &c, const BigInteger &o)
{
    BigInteger *res = new BigInteger[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] - o;
    return MatrixBigInteger(c.M, c.N, res);
}

MatrixBigInteger operator*(const MatrixBigInteger &c, const MatrixBigInteger &o)
{
    return c.Multiply(o);
}

MatrixBigInteger operator*(const MatrixBigInteger &c, const BigInteger &o)
{
    BigInteger *res = new BigInteger[c.M * c.N];
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            res[j + i * c.N] = c.Array[j + i * c.N] * o;
    return MatrixBigInteger(c.M, c.N, res);
}

bool operator==(const MatrixBigInteger &c, const MatrixBigInteger &o)
{
    if (c.M != o.M || c.N != o.N)
        return false;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return false;
    return true;
}

bool operator!=(const MatrixBigInteger &c, const MatrixBigInteger &o)
{
    if (c.M != o.M || c.N != o.N)
        return true;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            if (c.Array[j + i * c.N] != o.Array[j + i * c.N])
                return true;
    return false;
}

MatrixBigInteger &MatrixBigInteger::operator=(const MatrixBigInteger &o)
{
    if (this != &o)
    {
        M = o.M;
        N = o.N;
        if (Array != nullptr)
            delete[] Array;
        const BigInteger *copyArr = o.Array;
        Array = new BigInteger[M * N];
        for (uc i = 0; i < M; i++)
            for (uc j = 0; j < N; j++)
                Array[j + i * N] = copyArr[j + i * N];
    }
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator=(MatrixBigInteger &&o) noexcept
{
    if (this != &o)
    {
        delete[] Array;
        M = o.M;
        N = o.N;
        Array = o.Array;
        o.M = o.N = 0;
        o.Array = nullptr;
    }
    return *this;
}

MatrixBigInteger &operator+=(MatrixBigInteger &c, const MatrixBigInteger &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const BigInteger *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += otherArr[j + i * c.N];
    return c;
}

MatrixBigInteger &operator+=(MatrixBigInteger &c, const BigInteger &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] += o;
    return c;
}

MatrixBigInteger &operator-=(MatrixBigInteger &c, const MatrixBigInteger &o)
{
    if (o.M != c.M || o.N != c.N)
        return c;
    const BigInteger *otherArr = o.Array;
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= otherArr[j + i * c.N];
    return c;
}

MatrixBigInteger &operator-=(MatrixBigInteger &c, const BigInteger &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] -= o;
    return c;
}

MatrixBigInteger &operator*=(MatrixBigInteger &c, const MatrixBigInteger &o)
{
    if (c.N != o.M)
        return c;
    const uc resM = c.M, resN = o.N;
    BigInteger *otherArr = o.Array;
    BigInteger *res = new BigInteger[resM * resN];
    for (uc i = 0; i < resM; i++)
    {
        for (uc j = 0; j < resN; j++)
        {
            BigInteger sum;
            for (uc k = 0; k < c.N; k++)
                sum += c.Array[k + i * c.N] * otherArr[j + k * resN];
            res[j + i * resN] = sum;
        }
    }
    c.M = resM;
    c.N = resN;
    delete[] c.Array;
    c.Array = res;
    return c;
}

MatrixBigInteger &operator*=(MatrixBigInteger &c, const BigInteger &o)
{
    for (uc i = 0; i < c.M; i++)
        for (uc j = 0; j < c.N; j++)
            c.Array[j + i * c.N] *= o;
    return c;
}

ostream &operator<<(ostream &out, const MatrixBigInteger &c)
{
    const uc M = c.M, N = c.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << c[j + i * N] << " ";
        out << endl;
    }
    return out;
}
