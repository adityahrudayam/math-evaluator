#pragma once

#include <string>

using std::string;

typedef unsigned char uc;
typedef unsigned int ui;
typedef long double ld;

static void preprocessAndValidate(string &);

static uc getFunction(const string &);

static ld performOperation(const ld &, const uc &, const ld &);

static ld performOperation(const ld &, const ld &, const string &);

/**
 * Parameters:
 * string s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a double.
 */
ld evaluateExpressionD(string &) noexcept;

ld evaluateExpressionD(string &&) noexcept;

ld evaluateExpressionDWithoutPreprocessing(const string &) noexcept;

ld evaluateExpressionDWithoutPreprocessing(string &&) noexcept;
