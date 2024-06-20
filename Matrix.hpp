#pragma once

// #include <string>
#include "BigInteger.hpp"

// using std::istream;
// using std::ostream;
// using std::string;

// typedef unsigned char uc;
// typedef unsigned int ui;
// typedef long long ll;
// typedef long double ld;

class MatrixLD
{
private:
    uc M;
    uc N;
    ld *Array;

public:
    MatrixLD();

    MatrixLD(const uc, const uc, ld *);

    MatrixLD(const uc, const uc, const string *);

    MatrixLD(const MatrixLD &);

    MatrixLD(MatrixLD &&) noexcept;

    ~MatrixLD();

    MatrixLD Add(const MatrixLD &) const;

    MatrixLD Subtract(const MatrixLD &) const;

    MatrixLD Multiply(const MatrixLD &) const;

    // Getters & Setters
    const uc GetM() const;

    const uc GetN() const;

    const ld *GetArray() const;

    const ld operator[](const unsigned short &) const;

    friend MatrixLD operator+(const MatrixLD &, const MatrixLD &);
    friend MatrixLD operator+(const MatrixLD &, const ld &);
    friend MatrixLD operator-(const MatrixLD &, const MatrixLD &);
    friend MatrixLD operator-(const MatrixLD &, const ld &);
    friend MatrixLD operator*(const MatrixLD &, const MatrixLD &);
    friend MatrixLD operator*(const MatrixLD &, const ld &);
    // MatrixLD operator^(MatrixLD &);

    friend bool operator==(const MatrixLD &, const MatrixLD &);
    friend bool operator!=(const MatrixLD &, const MatrixLD &);

    MatrixLD &operator=(const MatrixLD &);
    MatrixLD &operator=(MatrixLD &&) noexcept;
    friend MatrixLD &operator+=(MatrixLD &, const MatrixLD &);
    friend MatrixLD &operator+=(MatrixLD &, const ld &);
    friend MatrixLD &operator-=(MatrixLD &, const MatrixLD &);
    friend MatrixLD &operator-=(MatrixLD &, const ld &);
    friend MatrixLD &operator*=(MatrixLD &, const MatrixLD &);
    friend MatrixLD &operator*=(MatrixLD &, const ld &);
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
    MatrixLL();

    MatrixLL(const uc, const uc, ll *);

    MatrixLL(const uc, const uc, string *);

    MatrixLL(const MatrixLL &);

    MatrixLL(MatrixLL &&) noexcept;

    ~MatrixLL();

    MatrixLL Add(const MatrixLL &) const;

    MatrixLL Subtract(const MatrixLL &) const;

    MatrixLL Multiply(const MatrixLL &) const;

    // Getters & Setters
    const uc GetM() const;

    const uc GetN() const;

    const ll *GetArray() const;

    const ll operator[](const unsigned short &) const;

    friend MatrixLL operator+(const MatrixLL &, const MatrixLL &);
    friend MatrixLL operator+(const MatrixLL &, const ll &);
    friend MatrixLL operator-(const MatrixLL &, const MatrixLL &);
    friend MatrixLL operator-(const MatrixLL &, const ll &);
    friend MatrixLL operator*(const MatrixLL &, const MatrixLL &);
    friend MatrixLL operator*(const MatrixLL &, const ll &);
    // MatrixLL operator^(MatrixLL &);

    friend bool operator==(const MatrixLL &, const MatrixLL &);
    friend bool operator!=(const MatrixLL &, const MatrixLL &);

    MatrixLL &operator=(const MatrixLL &);
    MatrixLL &operator=(MatrixLL &&) noexcept;
    friend MatrixLL &operator+=(MatrixLL &, const MatrixLL &);
    friend MatrixLL &operator+=(MatrixLL &, const ll &);
    friend MatrixLL &operator-=(MatrixLL &, const MatrixLL &);
    friend MatrixLL &operator-=(MatrixLL &, const ll &);
    friend MatrixLL &operator*=(MatrixLL &, const MatrixLL &);
    friend MatrixLL &operator*=(MatrixLL &, const ll &);
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
    MatrixBigInteger();

    MatrixBigInteger(const uc, const uc, BigInteger *);

    MatrixBigInteger(const uc, const uc, const string *);

    MatrixBigInteger(const MatrixBigInteger &);

    MatrixBigInteger(MatrixBigInteger &&) noexcept;

    ~MatrixBigInteger();

    MatrixBigInteger Add(const MatrixBigInteger &) const;

    MatrixBigInteger Subtract(const MatrixBigInteger &) const;

    MatrixBigInteger Multiply(const MatrixBigInteger &) const;

    // Getters & Setters
    const uc GetM() const;

    const uc GetN() const;

    const BigInteger *GetArray() const;

    const BigInteger operator[](const unsigned short &) const;

    friend MatrixBigInteger operator+(const MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger operator+(const MatrixBigInteger &, const BigInteger &);
    friend MatrixBigInteger operator-(const MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger operator-(const MatrixBigInteger &, const BigInteger &);
    friend MatrixBigInteger operator*(const MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger operator*(const MatrixBigInteger &, const BigInteger &);
    // MatrixBigInteger operator^(MatrixBigInteger &);

    friend bool operator==(const MatrixBigInteger &, const MatrixBigInteger &);
    friend bool operator!=(const MatrixBigInteger &, const MatrixBigInteger &);

    MatrixBigInteger &operator=(const MatrixBigInteger &);
    MatrixBigInteger &operator=(MatrixBigInteger &&) noexcept;
    friend MatrixBigInteger &operator+=(MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger &operator+=(MatrixBigInteger &, const BigInteger &);
    friend MatrixBigInteger &operator-=(MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger &operator-=(MatrixBigInteger &, const BigInteger &);
    friend MatrixBigInteger &operator*=(MatrixBigInteger &, const MatrixBigInteger &);
    friend MatrixBigInteger &operator*=(MatrixBigInteger &, const BigInteger &);
    // MatrixBigInteger &operator^=(MatrixBigInteger &);

    // OutStream
    friend ostream &operator<<(ostream &, const MatrixBigInteger &);
};
