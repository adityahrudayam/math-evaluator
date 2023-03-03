#include <iostream>
#include "Matrix.hpp"

using std::endl;

MatrixLD::MatrixLD() : M(0), N(0), Array(nullptr) {}

MatrixLD::MatrixLD(const uc M, const uc N, ld *Array) : M(M), N(N), Array(Array) {}

MatrixLD::MatrixLD(const uc M, const uc N, string *s) : M(M), N(N)
{
    Array = new ld[M * N];
    for (uc i = 0; i < M; i++)
        for (uc j = 0; j < N; j++)
            Array[j + i * N] = Evaluate(s[j + i * N]);
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
