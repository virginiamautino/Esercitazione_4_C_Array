#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool ImportData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{
    ifstream file(inputFilePath);
    
    if (file.fail()) {
        return false;
    }
    
    std::string line;  // Dichiarazione di una stringa per memorizzare la riga letta dal file

    
    // Legge la prima riga del file
    if (getline(file, line)) {
        size_t pos = line.find(';');  // Trova la posizione del carattere ';' nella riga
        if (pos != string::npos) {  // Controlla se il carattere ';' è stato trovato
            S = stod(line.substr(pos + 1));
        }
    }
    
    if (getline(file, line)) {
        size_t pos = line.find(';');  // Trova la posizione del carattere ';' nella riga
        if (pos != string::npos) {  // Controlla se il carattere ';' è stato trovato
            n = stod(line.substr(pos + 1));
        }
    }
    
    getline(file, line);
    
    w = new double[n];
    r = new double[n];
    
    
    for (size_t i = 0; i < n; i++) {
        if (!getline(file, line)) {
            cerr << "Errore: il file ha meno righe del previsto!" << endl;
            delete[] w;
            delete[] r;
            return false;
        }
        
        // Trovare la posizione del separatore ';'
        size_t pos = line.find(';');
        if (pos == string::npos) {
            cerr << "Errore nel formato della riga: " << line << endl;
            delete[] w;
            delete[] r;
            return false;
        }
        
        // Estrarre i due valori come double
        w[i] = stod(line.substr(0, pos));      // Parte prima del ';'
        r[i] = stod(line.substr(pos + 1));    // Parte dopo il ';'
    }

    return true;
}

double CalculateRateOfReturn(const size_t& n,
                              const double* const& w,
                              const double* const& r) {
    double rateOfReturn = 0.0;

    for (size_t i = 0; i < n; i++) {
        rateOfReturn += w[i] * r[i];
    }

    return rateOfReturn;
}

double CalculateFinalValue(const double& S, const double& rateOfReturn) {
    return (1 + rateOfReturn) * S;
}

bool ExportResult(const string& outputFilePath,
                  const double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& rateOfReturn,
                  const double& finalValue) {
    ofstream file(outputFilePath);

    if (file.fail()) {
        cerr << "File open failed" << endl;
        return false;
    }

    file << "S = " << std::fixed << std::setprecision(2) << S << ", n = " << n << endl;
    file << "w = [ ";
    for (size_t i = 0; i < n; i++) {
        file << w[i] << " ";
    }
    file << "]" << endl;

    file << "r = [ ";
    for (size_t i = 0; i < n; i++) {
        file << r[i] << " ";
    }
    file << "]" << endl;

    file << "Rate of return of the portfolio: " << std::fixed << std::setprecision(4) << rateOfReturn << endl;
    file << "V: " << std::fixed << std::setprecision(2) << finalValue << endl;

    file.close();

    return true;
}

