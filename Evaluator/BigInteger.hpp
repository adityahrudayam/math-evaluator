#pragma once

#include <string>

using std::istream;
using std::ostream;
using std::string;

typedef unsigned char uc;
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;

class BigInteger
{
private:
    uc Sign : 1;
    string Num;

    inline BigInteger SubtractionHelper(BigInteger &, const ui &, const ui &);

    string BuildNumStr(ll &);

public:
    BigInteger();

    explicit BigInteger(ll);

    explicit BigInteger(const char *);

    explicit BigInteger(string);

    explicit BigInteger(uc, string);

    BigInteger(const BigInteger &);

    bool IsNull() const;

    const ui Length() const;

    BigInteger Add(BigInteger &);

    BigInteger Subtract(BigInteger &);

    BigInteger Multiply(BigInteger &);

    BigInteger Divide(BigInteger &);

    BigInteger Pow(BigInteger &);

    // Getters & Setters
    const uc &GetSign() const;

    void SetSign(const uc &);

    const string &GetNum() const;

    void SetNum(const string &);

    inline const uc operator[](const ui &) const;

    BigInteger operator+(BigInteger &);
    BigInteger operator+(const ll &);
    BigInteger operator-(BigInteger &);
    BigInteger operator*(BigInteger &);
    BigInteger operator*(const ll &);
    BigInteger operator/(BigInteger &);
    BigInteger operator^(BigInteger &);

    BigInteger operator++(int temp); // postfix increment
    BigInteger &operator++();        // prefix increment
    BigInteger operator--(int temp); // postfix decrement
    BigInteger &operator--();        // prefix decrement

    bool operator==(BigInteger &);
    bool operator==(const char *);
    bool operator!=(BigInteger &);
    bool operator<(BigInteger &);
    bool operator<(const string &);
    bool operator>(BigInteger &);
    bool operator>(const string &);
    bool operator<=(BigInteger &);
    bool operator>=(BigInteger &);

    BigInteger &operator=(const BigInteger &);
    BigInteger &operator+=(BigInteger &);
    BigInteger &operator+=(const ll &);
    BigInteger &operator-=(BigInteger &);
    BigInteger &operator-=(const ll &);
    BigInteger &operator*=(BigInteger &);
    BigInteger &operator*=(const ll &);
    BigInteger &operator/=(BigInteger &);
    BigInteger &operator/=(const ll &);
    BigInteger &operator^=(BigInteger &);

    // OutStream & InStream
    friend ostream &operator<<(ostream &, const BigInteger &);
    friend istream &operator>>(istream &, BigInteger &);
};
