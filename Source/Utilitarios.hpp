#ifndef UTILITARIOS_HPP_
#define UTILITARIOS_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "Bitmap/bitmap.hpp" // https://github.com/pertbanking/bitmap-monochrome

using namespace std;

typedef vector<vector<int>> RedeSpins;

typedef struct ParametrosEvolucaoRede_ {
    int N;
    int M;
    int J;
    float H;
    float K_B;
    float T;
    float MCS;
    string identificador;
    bool gerarGif;
    bool gerarGraficos;
    int numeroFramesGif;
} ParametrosEvolucaoRede;

typedef struct ParametrosVariacaoTemperatura_ {
    int N;
    int M;
    int J;
    float H;
    float K_B;
    float T_min;
    float T_max;
    float pontosTemperatura;
    float MCS;
    string identificador;
    bool gerarGif;
    bool gerarGraficos;
    int numeroFramesGif;
} ParametrosVariacaoTemperatura;

typedef struct ParametrosVariacaoCampoExterno_ {
    int N;
    int M;
    int J;
    float H_min;
    float H_max;
    float pontosCampoExterno;
    float K_B;
    float T;
    float MCS;
    string identificador;
    bool gerarGif;
    bool gerarGraficos;
    int numeroFramesGif;
} ParametrosVariacaoCampoExterno;

string PASTA_EVOLUCAO_SISTEMA = "./Resultados/EvolucaoSistema";
string PASTA_VARIACAO_CAMPO = "./Resultados/VariacaoCampo";
string PASTA_VARIACAO_TEMPERATURA = "./Resultados/VariacaoTemperatura";

ParametrosEvolucaoRede leParametrosEvolucaoSistema(ifstream *config);
ParametrosVariacaoTemperatura leParametrosVariacaoTemperatura(ifstream *config);
ParametrosVariacaoCampoExterno leParametrosVariacaoCampoExterno(ifstream *config);
vector<string> explode(string const & s, char delim); // https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
const int indice_anterior(int i, int N);
PixelMatrix redeParaPixels(RedeSpins rede);
void salvaEstadoAtual(RedeSpins rede, string sequencial, string pasta, string afixo, string prefixo = "estado_");
void salvaEvolucaoSistema(float T, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo = "evolucao", string prefixo = "", string sufixo = "", string extensao = ".csv");
void salvaVariacaoTemperatura(vector<float> T, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo = "evolucao", string prefixo = "", string sufixo = "", string extensao = ".csv");
void salvaVariacaoCampoExterno(float T, vector<float> H, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo = "evolucao", string prefixo = "", string sufixo = "", string extensao = ".csv");
RedeSpins redeSpinsAleatorios(int N, int M);
float funcaoParticao(vector<float> E, float beta);

#include "Utilitarios.cpp"

#endif