#pragma once

#include <iostream>
#include <string>

using namespace std;

// ImportData legge i dati dal file
// inputFilePath: nome del path del file di input
// S: investimento inizialw
// n: numero di asset
// w: array di weights per ogni asset
// r: array di rates of return per ogni asset

bool ImportData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r);

// CalculateRateOfReturn calcola il rate of return
double CalculateRateOfReturn(const size_t& n,
                              const double* const& w,
                              const double* const& r);

// CalculateFinalValue calcola il valore finale

double CalculateFinalValue(const double& S, const double& rateOfReturn);

// ExportResult scrive i risultati su un file
bool ExportResult(const string& outputFilePath,
                  const double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& rateOfReturn,
                  const double& finalValue);

