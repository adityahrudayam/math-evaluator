#include <iostream>
#include "Matrix.hpp"

using std::endl;

#define EvaluateLD evaluateExpressionDWithoutPreprocessing

#define EvaluateLL evaluateExpressionI

#define EvaluateBI evaluateExpression

ld evaluateExpressionDWithoutPreprocessing(string) noexcept;

ll evaluateExpressionI(string) noexcept;

BigInteger evaluateExpression(string) noexcept;

MatrixLD::MatrixLD() : M(0), N(0), Array(nullptr)
{
}

MatrixLD::MatrixLD(const uc M, const uc N, ld *Array) : M(M), N(N), Array(Array) {}

MatrixLD::MatrixLD(const uc M, const uc N, string *s) : M(M), N(N)
{
    Array = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateLD(s[j + i * N]);
}

MatrixLD::MatrixLD(const MatrixLD &o) : M(o.M), N(o.N)
{
    const ld *copyArr = o.Array;
    Array = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
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
    const ld *otherArr = o.Array;
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
    const ld *otherArr = o.Array;
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
    const ld *otherArr = o.Array;
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

uc MatrixLD::GetM() const
{
    return M;
}

uc MatrixLD::GetN() const
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

MatrixLD MatrixLD::operator+(MatrixLD &o)
{
    return Add(o);
}

MatrixLD MatrixLD::operator+(const ld &o)
{
    ld *res = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + o;
    return MatrixLD(M, N, res);
}

MatrixLD MatrixLD::operator-(MatrixLD &o)
{
    return Subtract(o);
}

MatrixLD MatrixLD::operator-(const ld &o)
{
    ld *res = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - o;
    return MatrixLD(M, N, res);
}

MatrixLD MatrixLD::operator*(MatrixLD &o)
{
    return Multiply(o);
}

MatrixLD MatrixLD::operator*(const ld &o)
{
    ld *res = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] * o;
    return MatrixLD(M, N, res);
}

bool MatrixLD::operator==(MatrixLD &o)
{
    if (M != o.M || N != o.N)
        return false;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return false;
    return true;
}

bool MatrixLD::operator!=(MatrixLD &o)
{
    if (M != o.M || N != o.N)
        return true;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return true;
    return false;
}

MatrixLD &MatrixLD::operator=(const MatrixLD &o)
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
    return *this;
}

MatrixLD &MatrixLD::operator+=(MatrixLD &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const ld *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += otherArr[j + i * N];
    return *this;
}

MatrixLD &MatrixLD::operator+=(const ld &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += o;
    return *this;
}

MatrixLD &MatrixLD::operator-=(MatrixLD &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const ld *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= otherArr[j + i * N];
    return *this;
}

MatrixLD &MatrixLD::operator-=(const ld &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= o;
    return *this;
}

MatrixLD &MatrixLD::operator*=(MatrixLD &o)
{
    if (N != o.M)
        return *this;
    return *this = Multiply(o);
}

MatrixLD &MatrixLD::operator*=(const ld &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] *= o;
    return *this;
}

ostream &operator<<(ostream &out, const MatrixLD &curr)
{
    const uc M = curr.M, N = curr.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << curr[j + i * N] << " ";
        out << endl;
    }
    return out;
}

MatrixLL::MatrixLL() : M(0), N(0), Array(nullptr)
{
}

MatrixLL::MatrixLL(const uc M, const uc N, ll *Array) : M(M), N(N), Array(Array) {}

MatrixLL::MatrixLL(const uc M, const uc N, string *s) : M(M), N(N)
{
    Array = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateLL(s[j + i * N]);
}

MatrixLL::MatrixLL(const MatrixLL &o) : M(o.M), N(o.N)
{
    const ll *copyArr = o.Array;
    Array = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
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
    const ll *otherArr = o.Array;
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
    const ll *otherArr = o.Array;
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
    const ll *otherArr = o.Array;
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

uc MatrixLL::GetM() const
{
    return M;
}

uc MatrixLL::GetN() const
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

MatrixLL MatrixLL::operator+(MatrixLL &o)
{
    return Add(o);
}

MatrixLL MatrixLL::operator+(const ll &o)
{
    ll *res = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + o;
    return MatrixLL(M, N, res);
}

MatrixLL MatrixLL::operator-(MatrixLL &o)
{
    return Subtract(o);
}

MatrixLL MatrixLL::operator-(const ll &o)
{
    ll *res = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - o;
    return MatrixLL(M, N, res);
}

MatrixLL MatrixLL::operator*(MatrixLL &o)
{
    return Multiply(o);
}

MatrixLL MatrixLL::operator*(const ll &o)
{
    ll *res = new ll[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] * o;
    return MatrixLL(M, N, res);
}

bool MatrixLL::operator==(MatrixLL &o)
{
    if (M != o.M || N != o.N)
        return false;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return false;
    return true;
}

bool MatrixLL::operator!=(MatrixLL &o)
{
    if (M != o.M || N != o.N)
        return true;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return true;
    return false;
}

MatrixLL &MatrixLL::operator=(const MatrixLL &o)
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
    return *this;
}

MatrixLL &MatrixLL::operator+=(MatrixLL &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const ll *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += otherArr[j + i * N];
    return *this;
}

MatrixLL &MatrixLL::operator+=(const ll &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += o;
    return *this;
}

MatrixLL &MatrixLL::operator-=(MatrixLL &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const ll *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= otherArr[j + i * N];
    return *this;
}

MatrixLL &MatrixLL::operator-=(const ll &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= o;
    return *this;
}

MatrixLL &MatrixLL::operator*=(MatrixLL &o)
{
    if (N != o.M)
        return *this;
    return *this = Multiply(o);
}

MatrixLL &MatrixLL::operator*=(const ll &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] *= o;
    return *this;
}

ostream &operator<<(ostream &out, const MatrixLL &curr)
{
    const uc M = curr.M, N = curr.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << curr[j + i * N] << " ";
        out << endl;
    }
    return out;
}

MatrixBigInteger::MatrixBigInteger() : M(0), N(0), Array(nullptr)
{
}

MatrixBigInteger::MatrixBigInteger(const uc M, const uc N, BigInteger *Array) : M(M), N(N), Array(Array) {}

MatrixBigInteger::MatrixBigInteger(const uc M, const uc N, string *s) : M(M), N(N)
{
    Array = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = EvaluateBI(s[j + i * N]);
}

MatrixBigInteger::MatrixBigInteger(const MatrixBigInteger &o) : M(o.M), N(o.N)
{
    const BigInteger *copyArr = o.Array;
    Array = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = copyArr[j + i * N];
}

MatrixBigInteger::~MatrixBigInteger()
{
    if (Array != nullptr)
    {
        // for (int i = 0; i < M; i++)
        //     for (int j = 0; j < N; j++)
        //         delete (Array + i * N + j);
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

uc MatrixBigInteger::GetM() const
{
    return M;
}

uc MatrixBigInteger::GetN() const
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

MatrixBigInteger MatrixBigInteger::operator+(MatrixBigInteger &o)
{
    return Add(o);
}

MatrixBigInteger MatrixBigInteger::operator+(const BigInteger &o)
{
    BigInteger *res = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] + o;
    return MatrixBigInteger(M, N, res);
}

MatrixBigInteger MatrixBigInteger::operator-(MatrixBigInteger &o)
{
    return Subtract(o);
}

MatrixBigInteger MatrixBigInteger::operator-(const BigInteger &o)
{
    BigInteger *res = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] - o;
    return MatrixBigInteger(M, N, res);
}

MatrixBigInteger MatrixBigInteger::operator*(MatrixBigInteger &o)
{
    return Multiply(o);
}

MatrixBigInteger MatrixBigInteger::operator*(const BigInteger &o)
{
    BigInteger *res = new BigInteger[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            res[j + i * N] = Array[j + i * N] * o;
    return MatrixBigInteger(M, N, res);
}

bool MatrixBigInteger::operator==(MatrixBigInteger &o)
{
    if (M != o.M || N != o.N)
        return false;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return false;
    return true;
}

bool MatrixBigInteger::operator!=(MatrixBigInteger &o)
{
    if (M != o.M || N != o.N)
        return true;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            if (Array[j + i * N] != o.Array[j + i * N])
                return true;
    return false;
}

MatrixBigInteger &MatrixBigInteger::operator=(const MatrixBigInteger &o)
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
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator+=(MatrixBigInteger &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const BigInteger *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += otherArr[j + i * N];
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator+=(const BigInteger &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] += o;
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator-=(MatrixBigInteger &o)
{
    if (o.M != M || o.N != N)
        return *this;
    const BigInteger *otherArr = o.Array;
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= otherArr[j + i * N];
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator-=(const BigInteger &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] -= o;
    return *this;
}

MatrixBigInteger &MatrixBigInteger::operator*=(MatrixBigInteger &o)
{
    if (N != o.M)
        return *this;
    return *this = Multiply(o);
}

MatrixBigInteger &MatrixBigInteger::operator*=(const BigInteger &o)
{
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] *= o;
    return *this;
}

ostream &operator<<(ostream &out, const MatrixBigInteger &curr)
{
    const uc M = curr.M, N = curr.N;
    for (uc i = 0; i < M; i++)
    {
        for (uc j = 0; j < N; j++)
            out << curr[j + i * N] << " ";
        out << endl;
    }
    return out;
}
