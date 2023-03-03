#pragma once

#include <string>

using std::string;

typedef unsigned char uc;
typedef unsigned int ui;
typedef long double ld;

inline static void preprocessAndValidate(string &);

inline static uc getFunction(const string &);

inline static ld performOperation(const ld &, const uc &, const ld &);

inline static ld performOperation(const ld &, const ld &, const string &);

/**
 * Parameters:
 * s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a double.
 */
ld evaluateExpressionD(string) noexcept;

ld evaluateExpressionDWithoutPreprocessing(string s) noexcept;
