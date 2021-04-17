#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>
#include "Source/ModeloIsing.hpp"
#include "Source/Utilitarios.hpp"

using namespace std;
using namespace Bidimensional;

void evolucaoSistema(ParametrosEvolucaoRede parametros) {
    float J = parametros.J;
    float H = parametros.H;
    float K_B = parametros.K_B;
    float T = parametros.T;
    float beta = (1 / (K_B * T));
    int largura = parametros.N;
    int altura = parametros.M;
    int N = altura * largura;
    int MCS = 5000;

    string caminhoImagens = PASTA_EVOLUCAO_SISTEMA + "/imagens";
    string caminhoCsv = PASTA_EVOLUCAO_SISTEMA + "/csv";
    
    vector<float> M, E;

    RedeSpins rede = redeSpinsAleatorios(largura, altura);
    float energia = energiaRede(rede, J, H, beta);
    M.push_back(magnetizacao(rede) / N);
    E.push_back(energia / N);

    int n = 1;
    salvaEstadoAtual(rede, "0", caminhoImagens, parametros.identificador);

    for (int i = 0; i < MCS; i++) {
        rede = passoMontecarlo(&energia, rede, J, H, beta);
        M.push_back(magnetizacao(rede) / N);
        E.push_back(energia / N);

        if (i % (MCS / 100) == 0) {
            salvaEstadoAtual(rede, to_string(n++), caminhoImagens, parametros.identificador);
        }
    }

    salvaEvolucaoSistema(T, E, M, caminhoCsv, parametros.identificador);
}

void variacaoTemperatura() {
    float J = 1;
    float H = 0;
    float K_B = 1;
    float beta;
    int L = 100;
    int N = L * L;
    int MCS = 5000;

    float T_min = 0.1, T_max = 5, nTs = 100, dT = (T_max - T_min) / nTs;
    
    vector<float> Ts, E, M;

    int n = 0;

    beta = (1 / (K_B * T_min));

    RedeSpins rede = redeSpinsAleatorios(L, L);
    float energia = energiaRede(rede, J, H, beta);

    for (float T = T_min; T <= T_max; T += dT) {
        beta = (1 / (K_B * T));

        for (int i = 0; i < MCS; i++) { // Termalização
            rede = passoMontecarlo(&energia, rede, J, H, beta);
        }

        Ts.push_back(T);
        E.push_back(energia / N);
        M.push_back(magnetizacao(rede) / N);

        salvaEstadoAtual(rede, to_string(n++), "estado_", "./temperaturas/");
    }

    salvaEvolucaoSistemaTemperatura(Ts, E, M);
}

int main(int argc, char const *argv[]) {    
    srand(time(NULL));

    // evolucaoSistema();
    // variacaoTemperatura();

    if (argc < 2) {
        cout << "Você deve informar um arquivo de configuração!" << endl;
        return -1;
    }

    string caminhoArquivo = argv[1];

    ifstream config(caminhoArquivo);

    if (config.fail()) {
        cout << "Não foi possível ler o arquivo!" << endl;
        return -1;
    }

    string tipo;

    config >> tipo;

    vector<string> parametroValor = explode(tipo, '=');

    if (parametroValor[0] != "TIPO") {
        cout << "Arquivo não segue os padrões. Consultar README." << endl;
        config.close();
        return -1;
    }

    if (parametroValor[1] == "EVOLUCAO_ATE_EQUILIBRIO") {
        cout << "Lendo parâmetros.." << endl;

        ParametrosEvolucaoRede parametros = leParametrosEvolucaoSistema(&config);

        cout << "Iniciando simulação.." << endl;

        evolucaoSistema(parametros);

        cout << "Simulação finalizada.." << endl;
    } else {
        cout << "Tipo de simulação desconhecido" << endl;
        config.close();
        return -1;
    }

    config.close();
    return 0;
}
