#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>

using namespace std;


const int indice_anterior(int i, int N) {
    return (((i - 1) % N) + N) % N;
}

vector<int> redeSpinsAleatorios(int L) {
    vector<int> rede;
    const int spins[2] = {-1, 1};

    for (int i = 0; i < L; i++) {
        rede.push_back(spins[rand() & 1]);
    }

    return rede;
}

float energiaRede(vector<int> rede, float J, float H, float beta) {
    float energia = 0;
    float vizinhos = 0;
    int L = rede.size();

    for (int i = 0; i < L; i++) {
        vizinhos = rede[indice_anterior(i, L)] + rede[(i + 1) % L];
        energia += J * vizinhos + H;
    }

    return -energia;
}

float magnetizacaoRede(vector<int> rede) {
    float M = 0;
    int L = rede.size();

    for (int i = 0; i < L; i++) {
        M += rede[i];
    }

    return M;
}

void __passoMonteCarlo(float *energia, vector<int> *rede, float J, float H, float beta) {
    float dE, E, E_k, nova_energia;
    int L = rede->size();
    vector<int> redeModificada;

    int i;

    for (int k = 0; k < L; k++) {
        i = rand() % L;

        (*rede)[i] *= -1;

        E_k = energiaRede(*rede, J, H, beta);

        dE = E_k - *energia;

        if (dE <= 0 || exp(-beta * dE) >= rand() / RAND_MAX) {
            nova_energia = E_k;
        } else {
            (*rede)[i] *= -1;
            nova_energia = E;
        }

        *energia = nova_energia;
    }
}

void passoMonteCarlo(float *energia, vector<int> *rede, float J, float H, float beta) {
    float dE, vizinhos;
    int L = rede->size();
    vector<int> redeModificada;

    int i;

    for (int k = 0; k < L; k++) {
        i = rand() % L;

        vizinhos = (*rede)[indice_anterior(i, L)] + (*rede)[(i + 1) % L];

        dE = 2 * J * (*rede)[i] * vizinhos;

        if (dE <= 0 || exp(-beta * dE) >= rand() / RAND_MAX) {
            (*energia) += dE;
            (*rede)[i] *= -1;
        }
    }
}

void graficosMCSteps() {
    float J = 1;
    float B_ext = 0;
    float K_B = 1;
    float T = 1;
    float beta = 1 / (K_B * T);
    int L = 500;
    float M = 0;
    float energia;
    int MCS = 1000;
    
    cout << "Iniciando processamento" << endl;

    vector<int> rede = redeSpinsAleatorios(L);

    FILE* arquivo_saida = fopen(".\\ising_1d_mc.csv", "w");

    energia = energiaRede(rede, J, B_ext, beta);
    M = magnetizacaoRede(rede);

    fprintf(arquivo_saida, "i,E,M\n");
    fprintf(arquivo_saida, "%d,%f,%f\n", 0, energia, M);


    for (int i = 1; i <= MCS; i++) {
        if (i % (MCS / 4) == 0) {
            cout << '.';
        }
        passoMonteCarlo(&energia, &rede, J, B_ext, beta);
        M = magnetizacaoRede(rede);
        fprintf(arquivo_saida, "%d,%f,%f\n", i, energia, M);
    }
    cout << endl;

    fclose(arquivo_saida);

    cout << "Fim processamento" << endl;
}

void graficosTemperatura() {
    float J = 1;
    float B_ext = 0;
    float K_B = 1;
    float T = 1;
    float beta;
    int L = 10;
    float M = 0;
    float E = 0;
    int MCS = 1000;
    float energia;
    vector<int> rede;

    FILE* arquivo_saida = fopen(".\\ising_1d_mc_temperatura.csv", "w");

    fprintf(arquivo_saida, "T,E,M\n");


    int pontosTemperatura = 1000;
    float T_min = 0.01, T_max = 100;
    float dT = (T_max - T_min) / pontosTemperatura;

    for (float T = T_min; T <= T_max; T += dT) {
        beta = 1 / (K_B * T);

        rede = redeSpinsAleatorios(L);
        energia = energiaRede(rede, J, B_ext, beta);
        M = 0;
        E = 0;

        for (int i = 0; i < MCS; i++) { // Para termalização
            passoMonteCarlo(&energia, &rede, J, B_ext, beta);
        }

        for (int i = 0; i < MCS; i++) { // Para termalização
            passoMonteCarlo(&energia, &rede, J, B_ext, beta);
            M += magnetizacaoRede(rede) / (L * MCS);
            E += energia / (L * MCS);
        }

        fprintf(arquivo_saida, "%f,%f,%f\n", T, E, M);
    }

    fclose(arquivo_saida);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    graficosTemperatura();

    return 0;
}