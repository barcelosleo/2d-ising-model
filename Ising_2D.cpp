#include <iostream>
#include <vector>
#include <time.h>
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
    int MCS = parametros.MCS;

    string caminhoImagens = PASTA_EVOLUCAO_SISTEMA + "/imagens";
    string caminhoCsv = PASTA_EVOLUCAO_SISTEMA + "/csv";
    
    vector<float> E, E_quad, M, M_abs, M_quad, C, Chi;

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
        E_quad.push_back(energia * energia / (N * N));
        M.push_back(magnetizacao(rede) / N);
        M_abs.push_back(magnetizacao_absoluta(rede) / N);
        M_quad.push_back(magnetizacao_quadrado(rede) / (N * N));

        float ve_E_quad = 0, ve_E = 0;
        float ve_M_quad = 0, ve_M = 0;

        for (int i = 0; i < E.size(); i++) {
            ve_E_quad += E_quad[i];
            ve_E += E[i];
            ve_M_quad += M_quad[i];
            ve_M += M[i];
        }
        C.push_back((ve_E_quad - ve_E) / (K_B * T * T));
        Chi.push_back((ve_M_quad - ve_M) / (K_B * T * T));

        if (i % (MCS / parametros.numeroFramesGif) == 0) {
            salvaEstadoAtual(rede, to_string(n++), caminhoImagens, parametros.identificador);
        }
    }

    salvaEvolucaoSistema(T, E, M, C, Chi, caminhoCsv, parametros.identificador);
}

void variacaoTemperatura(ParametrosVariacaoTemperatura parametros) {
    float J = parametros.J;
    float H = parametros.H;
    float K_B = parametros.K_B;
    float beta;
    int largura = parametros.N;
    int altura = parametros.M;
    int N = altura * largura;
    int MCS = parametros.MCS;

    string caminhoImagens = PASTA_VARIACAO_TEMPERATURA + "/imagens";
    string caminhoCsv = PASTA_VARIACAO_TEMPERATURA + "/csv";

    float T_min = parametros.T_min;
    float T_max = parametros.T_max;
    float nTs = parametros.pontosTemperatura;
    float dT = (T_max - T_min) / nTs;
    
    vector<float> Ts, E, E_quad, M, M_abs, M_quad, C, Chi;

    int n = 0;

    beta = (1 / (K_B * T_min));

    RedeSpins rede = redeSpinsAleatorios(altura, largura);
    float energia = energiaRede(rede, J, H, beta);

    for (float T = T_min; T <= T_max; T += dT) {
        beta = (1 / (K_B * T));

        for (int i = 0; i < MCS; i++) { // Termalização
            rede = passoMontecarlo(&energia, rede, J, H, beta);
        }

        Ts.push_back(T);
        E.push_back(energia / N);
        E_quad.push_back(energia * energia / N);
        M.push_back(magnetizacao(rede) / N);
        M_abs.push_back(magnetizacao_absoluta(rede) / N);
        M_quad.push_back(magnetizacao_quadrado(rede) / N);

        float ve_E_quad = 0, ve_E = 0;
        float ve_M_quad = 0, ve_M = 0;

        for (int i = 0; i < E.size(); i++) {
            ve_E_quad += E_quad[i];
            ve_E += E[i];
            ve_M_quad += M_quad[i];
            ve_M += M[i];
        }
        C.push_back((ve_E_quad - ve_E) / (K_B * T * T));
        Chi.push_back((ve_M_quad - ve_M) / (K_B * T * T));

        salvaEstadoAtual(rede, to_string(n++), caminhoImagens, parametros.identificador);
    }

    salvaVariacaoTemperatura(Ts, E, M, C, Chi, caminhoCsv, parametros.identificador);
}

void variacaoCampoExterno(ParametrosVariacaoCampoExterno parametros) {
    float J = parametros.J;
    float T = parametros.T;
    float K_B = parametros.K_B;
    float beta = (1 / (K_B * T));
    int largura = parametros.N;
    int altura = parametros.M;
    int N = altura * largura;
    int MCS = parametros.MCS;

    string caminhoImagens = PASTA_VARIACAO_CAMPO + "/imagens";
    string caminhoCsv = PASTA_VARIACAO_CAMPO + "/csv";

    float H_min = parametros.H_min;
    float H_max = parametros.H_max;
    float nHs = parametros.pontosCampoExterno;
    float dH = (H_max - H_min) / nHs;
    
    vector<float> Hs, E, E_quad, M, M_abs, M_quad, C, Chi;

    int n = 0;

    RedeSpins rede = redeSpinsAleatorios(altura, largura);
    float energia = energiaRede(rede, J, H_min, beta);

    for (float H = H_min; H <= H_max; H += dH) {
        for (int i = 0; i < MCS; i++) { // Termalização
            rede = passoMontecarlo(&energia, rede, J, H, beta);
        }

        Hs.push_back(H);
        E.push_back(energia / N);
        E_quad.push_back(energia * energia / N);
        M.push_back(magnetizacao(rede) / N);
        M_abs.push_back(magnetizacao_absoluta(rede) / N);
        M_quad.push_back(magnetizacao_quadrado(rede) / N);

        float ve_E_quad = 0, ve_E = 0;
        float ve_M_quad = 0, ve_M = 0;

        for (int i = 0; i < E.size(); i++) {
            ve_E_quad += E_quad[i];
            ve_E += E[i];
            ve_M_quad += M_quad[i];
            ve_M += M[i];
        }
        C.push_back((ve_E_quad - ve_E) / (K_B * T * T));
        Chi.push_back((ve_M_quad - ve_M) / (K_B * T * T));

        salvaEstadoAtual(rede, to_string(n++), caminhoImagens, parametros.identificador);
    }

    salvaVariacaoCampoExterno(T, Hs, E, M, C, Chi, caminhoCsv, parametros.identificador);
}

int main(int argc, char const *argv[]) {    
    srand(time(NULL));
    if (argc < 2) {
        cout << "Você deve informar um arquivo de configuração!" << endl;
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        string caminhoArquivo = argv[i];
        ifstream config(caminhoArquivo);
        if (config.fail()) {
            cout << "Não foi possível ler o arquivo!" << endl;
            return -1;
        }

        cout << "Processando arquivo \"" << caminhoArquivo << "\"" << endl;

        string tipo;
        config >> tipo;
        vector<string> parametroValor = explode(tipo, '=');

        if (parametroValor[0] != "TIPO") {
            cout << "Arquivo não segue os padrões. Consultar README." << endl;
            config.close();
            return -1;
        }

        if (parametroValor[1] == "EVOLUCAO_ATE_EQUILIBRIO") {
            ParametrosEvolucaoRede parametros = leParametrosEvolucaoSistema(&config);
            cout << "Iniciando simulacao.." << endl;
            evolucaoSistema(parametros);
            cout << "Simulacao finalizada.." << endl;
        } else if (parametroValor[1] == "VARIACAO_TEMPERATURA") {
            ParametrosVariacaoTemperatura parametros = leParametrosVariacaoTemperatura(&config);
            cout << "Iniciando simulacao.." << endl;
            variacaoTemperatura(parametros);
            cout << "Simulacao finalizada.." << endl;
        } else if (parametroValor[1] == "VARIACAO_CAMPO_EXTERNO") {
            ParametrosVariacaoCampoExterno parametros = leParametrosVariacaoCampoExterno(&config);
            cout << "Iniciando simulacao.." << endl;
            variacaoCampoExterno(parametros);
            cout << "Simulacao finalizada.." << endl;
        } else {
            cout << "Tipo de simulacao desconhecido" << endl;
            config.close();
            return -1;
        }

        config.close();

        cout << "\n\n";
    }
    return 0;
}
