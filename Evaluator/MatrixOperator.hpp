#pragma once

#include <vector>
#include <string>
#include "Matrix.hpp"

using std::vector;

string findOrderOfMinOps(uc[], ui);

MatrixLD multiplyAndGetResult(vector<MatrixLD> &);

MatrixLL multiplyAndGetResult(vector<MatrixLL> &);

MatrixBigInteger multiplyAndGetResult(vector<MatrixBigInteger> &);

MatrixLD matrixExpEval(string &, vector<MatrixLD> &);

MatrixLL matrixExpEval(string &, vector<MatrixLL> &);

MatrixBigInteger matrixExpEval(string &, vector<MatrixBigInteger> &);

MatrixLD performOperation(const MatrixLD &, const MatrixLD &, char &);

MatrixLL performOperation(const MatrixLL &, const MatrixLL &, char &);

MatrixBigInteger performOperation(const MatrixBigInteger &, const MatrixBigInteger &, char &);

void takeInputAndEvalLD();

void takeInputAndEvalLL();

void takeInputAndEvalBI();

bool saveLDMToFile(const char *, MatrixLD &);

// vector<MatrixLD> LoadLDMFromFile(const char *, ll);

void splitOnSymbol(string &, const char &);

void splitOnSymbols(string &, const char *);
