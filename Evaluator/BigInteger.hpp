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

    string BuildNumStr(ll &);

    inline BigInteger SubtractionHelper(const BigInteger &, const ui &, const ui &) const;

public:
    explicit BigInteger();

    explicit BigInteger(ll);

    explicit BigInteger(const char *);

    explicit BigInteger(const string &);

    explicit BigInteger(const uc, const string &);

    BigInteger(const BigInteger &);

    BigInteger(BigInteger &&) noexcept;

    bool IsNull() const;

    const ui Length() const;

    BigInteger Add(const BigInteger &) const;

    BigInteger Subtract(const BigInteger &) const;

    BigInteger Multiply(const BigInteger &) const;

    BigInteger Divide(const BigInteger &) const;

    BigInteger Pow(const BigInteger &) const;

    // Getters & Setters
    const uc GetSign() const;

    void SetSign(const uc);

    const string GetNum() const;

    void SetNum(const string &);

    inline const uc operator[](const ui &) const;

    friend BigInteger operator+(const BigInteger &, const BigInteger &);
    friend BigInteger operator+(const BigInteger &, const ll &);
    friend BigInteger operator-(const BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const ll &);
    friend BigInteger operator/(const BigInteger &, const BigInteger &);
    friend BigInteger operator^(const BigInteger &, const BigInteger &);

    BigInteger operator++(int temp); // postfix increment
    BigInteger &operator++();        // prefix increment
    BigInteger operator--(int temp); // postfix decrement
    BigInteger &operator--();        // prefix decrement

    friend bool operator==(const BigInteger &, const BigInteger &);
    friend bool operator==(const BigInteger &, const char *);
    friend bool operator!=(const BigInteger &, const BigInteger &);
    friend bool operator!=(const BigInteger &, const char *);
    friend bool operator<(const BigInteger &, const BigInteger &);
    friend bool operator<(const BigInteger &, const string &);
    friend bool operator>(const BigInteger &, const BigInteger &);
    friend bool operator>(const BigInteger &, const string &);
    friend bool operator<=(const BigInteger &, const BigInteger &);
    friend bool operator>=(const BigInteger &, const BigInteger &);

    BigInteger &operator=(const BigInteger &);
    BigInteger &operator=(BigInteger &&) noexcept;
    friend BigInteger &operator+=(BigInteger &, const BigInteger &);
    friend BigInteger &operator+=(BigInteger &, const ll &);
    friend BigInteger &operator-=(BigInteger &, const BigInteger &);
    friend BigInteger &operator-=(BigInteger &, const ll &);
    friend BigInteger &operator*=(BigInteger &, const BigInteger &);
    friend BigInteger &operator*=(BigInteger &, const ll &);
    friend BigInteger &operator/=(BigInteger &, const BigInteger &);
    friend BigInteger &operator/=(BigInteger &, const ll &);
    friend BigInteger &operator^=(BigInteger &, const BigInteger &);

    // OutStream & InStream
    friend ostream &operator<<(ostream &, const BigInteger &);
    friend istream &operator>>(istream &, BigInteger &);
};
