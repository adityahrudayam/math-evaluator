#pragma once

#include <string>
#include "BigInteger.hpp"

// inline static void preprocessAndValidate(string &s);

inline static uc getFunction(const string &s);

// inline static ld performOperation(const ld &x, const uc &op, const ld &y);

inline static BigInteger performOperation(BigInteger &b, BigInteger &a, const string &op);

/**
 * Parameters:
 * s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a BigInteger.
 */
BigInteger evaluateExpression(string s) noexcept;
