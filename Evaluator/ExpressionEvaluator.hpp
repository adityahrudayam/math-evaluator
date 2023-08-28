#pragma once

#include <string>
#include "BigInteger.hpp"

//  static void preprocessAndValidate(string &);

static uc getFunction(const string &);

//  static ld performOperation(const ld &, const uc &, const ld &);

static BigInteger performOperation(const BigInteger &, const BigInteger &, const string &);

/**
 * Parameters:
 * string s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a BigInteger.
 */
BigInteger evaluateExpression(const string &) noexcept;

BigInteger evaluateExpression(string &&) noexcept;
