#pragma once

#include <string>

typedef unsigned char uc;
typedef unsigned int ui;
typedef long long ll;

inline static ll powI(ll, ll);

inline static void preprocessAndValidate(std::string &);

inline static uc getFunction(const std::string &);

inline static ll performOperation(const ll &, const uc &, const ll &);

inline static ll performOperation(const ll &, const ll &, const std::string &);

/**
 * Parameters:
 * string s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a 64-bit integer.
 */
ll evaluateExpressionI(std::string &) noexcept;

ll evaluateExpressionI(std::string &&) noexcept;
