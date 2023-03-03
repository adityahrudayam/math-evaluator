#pragma once

#include <string>

using std::istream;
using std::ostream;
using std::string;

typedef unsigned char uc;
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;

#define Evaluate evaluateExpressionDWithoutPreprocessing

ld evaluateExpressionDWithoutPreprocessing(string) noexcept;

class MatrixLD
{
private:
    uc M;
    uc N;
    ld *Array;

public:
    MatrixLD();

    MatrixLD(const uc, const uc, ld *);

    MatrixLD(const uc, const uc, string *);

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
