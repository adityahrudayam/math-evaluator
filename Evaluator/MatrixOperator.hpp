#pragma once

#include <vector>
// #include <string>
#include "Matrix.hpp"

using std::vector;

template <class T>
concept Matrix = std::is_same<T, MatrixLD>::value || std::is_same<T, MatrixLL>::value || std::is_same<T, MatrixBigInteger>::value;

template <Matrix T>
T performOperation(T &, T &, char &);

template <Matrix T>
T matrixExpEval(string &, vector<T> &);

string findOrderOfMinOps(uc[], const ui &);

template <Matrix T>
T multiplyAndGetResult(vector<T> &);

void takeInputAndEvalLD();

void takeInputAndEvalLL();

void takeInputAndEvalBI();

bool saveLDMToFile(const char *, MatrixLD &);

// vector<MatrixLD> LoadLDMFromFile(const char *, ll);

void splitOnSymbol(string &, const char &);

void splitOnSymbols(string &, const char *);
