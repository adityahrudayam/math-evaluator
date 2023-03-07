#pragma once

#include <string>
#include "BigInteger.hpp"

using std::istream;
using std::ostream;
using std::string;

typedef unsigned char uc;
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;

class MatrixLD
{
private:
    uc M;
    uc N;
    ld *Array;

public:
    explicit MatrixLD();

    explicit MatrixLD(const uc, const uc, ld *);

    explicit MatrixLD(const uc, const uc, string *);

    MatrixLD(const MatrixLD &);

    ~MatrixLD();

    MatrixLD Add(const MatrixLD &) const;

    MatrixLD Subtract(const MatrixLD &) const;

    MatrixLD Multiply(const MatrixLD &) const;

    // Getters & Setters
    uc GetM() const;

    uc GetN() const;

    const ld *GetArray() const;

    const ld operator[](const unsigned short &) const;

    MatrixLD operator+(MatrixLD &);
    MatrixLD operator+(const ld &);
    MatrixLD operator-(MatrixLD &);
    MatrixLD operator-(const ld &);
    MatrixLD operator*(MatrixLD &);
    MatrixLD operator*(const ld &);
    // MatrixLD operator^(MatrixLD &);

    bool operator==(MatrixLD &);
    bool operator!=(MatrixLD &);

    MatrixLD &operator=(const MatrixLD &);
    MatrixLD &operator+=(MatrixLD &);
    MatrixLD &operator+=(const ld &);
    MatrixLD &operator-=(MatrixLD &);
    MatrixLD &operator-=(const ld &);
    MatrixLD &operator*=(MatrixLD &);
    MatrixLD &operator*=(const ld &);
    // MatrixLD &operator^=(MatrixLD &);

    // OutStream
    friend ostream &operator<<(ostream &, const MatrixLD &);
};

class MatrixLL
{
private:
    uc M;
    uc N;
    ll *Array;

public:
    explicit MatrixLL();

    explicit MatrixLL(const uc, const uc, ll *);

    explicit MatrixLL(const uc, const uc, string *);

    MatrixLL(const MatrixLL &);

    ~MatrixLL();

    MatrixLL Add(const MatrixLL &) const;

    MatrixLL Subtract(const MatrixLL &) const;

    MatrixLL Multiply(const MatrixLL &) const;

    // Getters & Setters
    uc GetM() const;

    uc GetN() const;

    const ll *GetArray() const;

    const ll operator[](const unsigned short &) const;

    MatrixLL operator+(MatrixLL &);
    MatrixLL operator+(const ll &);
    MatrixLL operator-(MatrixLL &);
    MatrixLL operator-(const ll &);
    MatrixLL operator*(MatrixLL &);
    MatrixLL operator*(const ll &);
    // MatrixLL operator^(MatrixLL &);

    bool operator==(MatrixLL &);
    bool operator!=(MatrixLL &);

    MatrixLL &operator=(const MatrixLL &);
    MatrixLL &operator+=(MatrixLL &);
    MatrixLL &operator+=(const ll &);
    MatrixLL &operator-=(MatrixLL &);
    MatrixLL &operator-=(const ll &);
    MatrixLL &operator*=(MatrixLL &);
    MatrixLL &operator*=(const ll &);
    // MatrixLL &operator^=(MatrixLL &);

    // OutStream
    friend ostream &operator<<(ostream &, const MatrixLL &);
};

class MatrixBigInteger
{
private:
    uc M;
    uc N;
    BigInteger *Array;

public:
    explicit MatrixBigInteger();

    explicit MatrixBigInteger(const uc, const uc, BigInteger *);

    explicit MatrixBigInteger(const uc, const uc, string *);

    MatrixBigInteger(const MatrixBigInteger &);

    ~MatrixBigInteger();

    MatrixBigInteger Add(const MatrixBigInteger &) const;

    MatrixBigInteger Subtract(const MatrixBigInteger &) const;

    MatrixBigInteger Multiply(const MatrixBigInteger &) const;

    // Getters & Setters
    uc GetM() const;

    uc GetN() const;

    const BigInteger *GetArray() const;

    const BigInteger operator[](const unsigned short &) const;

    MatrixBigInteger operator+(MatrixBigInteger &);
    MatrixBigInteger operator+(const BigInteger &);
    MatrixBigInteger operator-(MatrixBigInteger &);
    MatrixBigInteger operator-(const BigInteger &);
    MatrixBigInteger operator*(MatrixBigInteger &);
    MatrixBigInteger operator*(const BigInteger &);
    // MatrixBigInteger operator^(MatrixBigInteger &);

    bool operator==(MatrixBigInteger &);
    bool operator!=(MatrixBigInteger &);

    MatrixBigInteger &operator=(const MatrixBigInteger &);
    MatrixBigInteger &operator+=(MatrixBigInteger &);
    MatrixBigInteger &operator+=(const BigInteger &);
    MatrixBigInteger &operator-=(MatrixBigInteger &);
    MatrixBigInteger &operator-=(const BigInteger &);
    MatrixBigInteger &operator*=(MatrixBigInteger &);
    MatrixBigInteger &operator*=(const BigInteger &);
    // MatrixBigInteger &operator^=(MatrixBigInteger &);

    // OutStream
    friend ostream &operator<<(ostream &, const MatrixBigInteger &);
};
