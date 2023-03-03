#pragma once

#include <vector>
#include <string>
#include "Matrix.hpp"

using std::vector;

string findOrderOfMinOps(uc dim[], ui N);

MatrixLD multiplyAndGetResult(vector<MatrixLD> &);

MatrixLD matrixExpEval(string &, vector<MatrixLD> &);

MatrixLD performOperation(const MatrixLD &, const MatrixLD &, char &);

void takeInputAndEval();

bool saveLDMToFile(const char *, MatrixLD &);

// vector<MatrixLD> LoadLDMFromFile(const char *, ll);

void splitOnSymbol(string &, const char &);

void splitOnSymbols(string &, const char *);
