#ifndef MODELO_ISING_CPP_
#define MODELO_ISING_CPP_

#include "ModeloIsing.hpp"
#include "Utilitarios.hpp"

float Bidimensional::energiaRede(Bidimensional::RedeSpins rede, float J, float H, float beta) {
    float vizinhos, energia = 0;
    int N = rede.size(), M = rede[0].size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            vizinhos = rede[indice_anterior(i, N)][j] + rede[(i + 1) % N][j]; // Vizinhos a esquerda e adireita
            vizinhos += rede[i][indice_anterior(j, M)] + rede[i][(j + 1) % M]; // Vizinhos a abaixo e acima

            energia += rede[i][j] * (J * vizinhos + H);
        }
    }

    return -energia;
}

float Bidimensional::magnetizacao(Bidimensional::RedeSpins rede) {
    float mag = 0;
    int N = rede.size(), M = rede[0].size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            mag += rede[i][j];
        }
    }

    return mag;
}

RedeSpins Bidimensional::passoMontecarlo(float *energia, Bidimensional::RedeSpins rede, float J, float H, float beta) {
    float dE;
    int i, j, vizinhos, N = rede.size(), M = rede[0].size();

    for (int k = 0; k < N; k++) {
        for (int l = 0; l < M; l++) {
            i = rand() % N;
            j = rand() % M;

            vizinhos = rede[indice_anterior(i, N)][j] + rede[(i + 1) % N][j]; // Vizinhos a esquerda e adireita
            vizinhos += rede[i][indice_anterior(j, M)] + rede[i][(j + 1) % M]; // Vizinhos a abaixo e acima

            dE = 2 * rede[i][j] * (J * vizinhos + H);

            if (dE <= 0) {
                rede[i][j] *= -1;
                (*energia) += dE;
            } else if (exp(-beta * dE) >= (rand() / (RAND_MAX + 1.0))) {
                rede[i][j] *= -1;
                (*energia) += dE;
            }
        }
    }

    return rede;
}

#endif