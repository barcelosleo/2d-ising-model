#ifndef MODELO_ISING_HPP_
#define MODELO_ISING_HPP_

#include <iostream>
#include <vector>

using namespace std;


namespace Unidimensional {
    typedef vector<int> RedeSpins;

};

namespace Bidimensional {
    typedef vector<vector<int>> RedeSpins;
    float energiaRede(RedeSpins rede, float J, float H, float beta);
    float magnetizacao(RedeSpins rede);
    RedeSpins passoMontecarlo(float *energia, RedeSpins rede, float J, float H, float beta);
};

#include "ModeloIsing.cpp"

#endif