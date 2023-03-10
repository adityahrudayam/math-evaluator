#pragma once

#include <string>
#include "BigInteger.hpp"

// inline static void preprocessAndValidate(string &);

inline static uc getFunction(const string &);

// inline static ld performOperation(const ld &, const uc &, const ld &);

inline static BigInteger performOperation(const BigInteger &, const BigInteger &, const string &);

/**
 * Parameters:
 * string s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a BigInteger.
 */
BigInteger evaluateExpression(const string &) noexcept;

BigInteger evaluateExpression(string &&) noexcept;
