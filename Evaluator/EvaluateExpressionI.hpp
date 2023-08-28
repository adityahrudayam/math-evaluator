#pragma once

#include <string>

typedef unsigned char uc;
typedef unsigned int ui;
typedef long long ll;

static ll powI(ll, ll);

static void preprocessAndValidate(std::string &);

static uc getFunction(const std::string &);

static ll performOperation(const ll &, const uc &, const ll &);

static ll performOperation(const ll &, const ll &, const std::string &);

/**
 * Parameters:
 * string s – The string expression to evaluate.
 * Returns:
 * The function evaluates an expression & returns a 64-bit integer.
 */
ll evaluateExpressionI(std::string &) noexcept;

ll evaluateExpressionI(std::string &&) noexcept;
