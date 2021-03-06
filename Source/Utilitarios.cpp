#ifndef UTILITARIOS_CPP_
#define UTILITARIOS_CPP_

#include "Utilitarios.hpp"

vector<string> explode(string const & s, char delim) {
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

ParametrosEvolucaoRede leParametrosEvolucaoSistema(ifstream *config) {
    string LARGURA_REDE, ALTURA_REDE, INTERACAO_VIZINHOS, CAMPO_EXTERNO, CONSTANTE_BOLTZMAN, TEMPERATURA, PASSOS_MONTECARLO, IDENTIFICADOR, GERAR_GIF, GERAR_GRAFICOS, NUMERO_FRAMES_GIF;
    ParametrosEvolucaoRede parametros;
    vector<string> parametroValor;

    (*config) >> LARGURA_REDE;
    (*config) >> ALTURA_REDE;
    (*config) >> INTERACAO_VIZINHOS;
    (*config) >> CAMPO_EXTERNO;
    (*config) >> CONSTANTE_BOLTZMAN;
    (*config) >> TEMPERATURA;
    (*config) >> PASSOS_MONTECARLO;
    (*config) >> IDENTIFICADOR;
    (*config) >> GERAR_GIF;
    (*config) >> GERAR_GRAFICOS;
    (*config) >> NUMERO_FRAMES_GIF;
    
    parametroValor = explode(LARGURA_REDE, '=');
    if (parametroValor[0] != "LARGURA_REDE") {
        cout << "LARGURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.N = stod(parametroValor[1]);
    
    parametroValor = explode(ALTURA_REDE, '=');
    if (parametroValor[0] != "ALTURA_REDE") {
        cout << "ALTURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.M = stod(parametroValor[1]);
    
    parametroValor = explode(INTERACAO_VIZINHOS, '=');
    if (parametroValor[0] != "INTERACAO_VIZINHOS") {
        cout << "INTERACAO_VIZINHOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.J = stof(parametroValor[1]);
    
    parametroValor = explode(CAMPO_EXTERNO, '=');
    if (parametroValor[0] != "CAMPO_EXTERNO") {
        cout << "CAMPO_EXTERNO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.H = stof(parametroValor[1]);
    
    parametroValor = explode(CONSTANTE_BOLTZMAN, '=');
    if (parametroValor[0] != "CONSTANTE_BOLTZMAN") {
        cout << "CONSTANTE_BOLTZMAN inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.K_B = stof(parametroValor[1]);
    
    parametroValor = explode(TEMPERATURA, '=');
    if (parametroValor[0] != "TEMPERATURA") {
        cout << "TEMPERATURA inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.T = stof(parametroValor[1]);
    
    parametroValor = explode(PASSOS_MONTECARLO, '=');
    if (parametroValor[0] != "PASSOS_MONTECARLO") {
        cout << "PASSOS_MONTECARLO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.MCS = stof(parametroValor[1]);
    
    parametroValor = explode(IDENTIFICADOR, '=');
    if (parametroValor[0] != "IDENTIFICADOR") {
        cout << "IDENTIFICADOR inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.identificador = parametroValor[1];
    
    parametroValor = explode(GERAR_GIF, '=');
    if (parametroValor[0] != "GERAR_GIF") {
        cout << "GERAR_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGif = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(GERAR_GRAFICOS, '=');
    if (parametroValor[0] != "GERAR_GRAFICOS") {
        cout << "GERAR_GRAFICOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGraficos = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(NUMERO_FRAMES_GIF, '=');
    if (parametroValor[0] != "NUMERO_FRAMES_GIF") {
        cout << "NUMERO_FRAMES_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.numeroFramesGif = stod(parametroValor[1]);

    return parametros;
}

ParametrosVariacaoTemperatura leParametrosVariacaoTemperatura(ifstream *config) {
    string LARGURA_REDE, ALTURA_REDE, INTERACAO_VIZINHOS, CAMPO_EXTERNO, CONSTANTE_BOLTZMAN, TEMPERATURA_INICIAL, TEMPERATURA_FINAL, PONTOS_DE_TEMPERATURA, PASSOS_MONTECARLO, IDENTIFICADOR, GERAR_GIF, GERAR_GRAFICOS, NUMERO_FRAMES_GIF;
    ParametrosVariacaoTemperatura parametros;
    vector<string> parametroValor;

    (*config) >> LARGURA_REDE;
    (*config) >> ALTURA_REDE;
    (*config) >> INTERACAO_VIZINHOS;
    (*config) >> CAMPO_EXTERNO;
    (*config) >> CONSTANTE_BOLTZMAN;
    (*config) >> TEMPERATURA_INICIAL;
    (*config) >> TEMPERATURA_FINAL;
    (*config) >> PONTOS_DE_TEMPERATURA;
    (*config) >> PASSOS_MONTECARLO;
    (*config) >> IDENTIFICADOR;
    (*config) >> GERAR_GIF;
    (*config) >> GERAR_GRAFICOS;
    (*config) >> NUMERO_FRAMES_GIF;
    
    parametroValor = explode(LARGURA_REDE, '=');
    if (parametroValor[0] != "LARGURA_REDE") {
        cout << "LARGURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.N = stod(parametroValor[1]);
    
    parametroValor = explode(ALTURA_REDE, '=');
    if (parametroValor[0] != "ALTURA_REDE") {
        cout << "ALTURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.M = stod(parametroValor[1]);
    
    parametroValor = explode(INTERACAO_VIZINHOS, '=');
    if (parametroValor[0] != "INTERACAO_VIZINHOS") {
        cout << "INTERACAO_VIZINHOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.J = stof(parametroValor[1]);
    
    parametroValor = explode(CAMPO_EXTERNO, '=');
    if (parametroValor[0] != "CAMPO_EXTERNO") {
        cout << "CAMPO_EXTERNO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.H = stof(parametroValor[1]);
    
    parametroValor = explode(CONSTANTE_BOLTZMAN, '=');
    if (parametroValor[0] != "CONSTANTE_BOLTZMAN") {
        cout << "CONSTANTE_BOLTZMAN inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.K_B = stof(parametroValor[1]);
    
    parametroValor = explode(TEMPERATURA_INICIAL, '=');
    if (parametroValor[0] != "TEMPERATURA_INICIAL") {
        cout << "TEMPERATURA_INICIAL inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.T_min = stof(parametroValor[1]);
    
    parametroValor = explode(TEMPERATURA_FINAL, '=');
    if (parametroValor[0] != "TEMPERATURA_FINAL") {
        cout << "TEMPERATURA_FINAL inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.T_max = stof(parametroValor[1]);
    
    parametroValor = explode(PONTOS_DE_TEMPERATURA, '=');
    if (parametroValor[0] != "PONTOS_DE_TEMPERATURA") {
        cout << "PONTOS_DE_TEMPERATURA inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.pontosTemperatura = stod(parametroValor[1]);
    
    parametroValor = explode(PASSOS_MONTECARLO, '=');
    if (parametroValor[0] != "PASSOS_MONTECARLO") {
        cout << "PASSOS_MONTECARLO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.MCS = stof(parametroValor[1]);
    
    parametroValor = explode(IDENTIFICADOR, '=');
    if (parametroValor[0] != "IDENTIFICADOR") {
        cout << "IDENTIFICADOR inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.identificador = parametroValor[1];
    
    parametroValor = explode(GERAR_GIF, '=');
    if (parametroValor[0] != "GERAR_GIF") {
        cout << "GERAR_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGif = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(GERAR_GRAFICOS, '=');
    if (parametroValor[0] != "GERAR_GRAFICOS") {
        cout << "GERAR_GRAFICOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGraficos = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(NUMERO_FRAMES_GIF, '=');
    if (parametroValor[0] != "NUMERO_FRAMES_GIF") {
        cout << "NUMERO_FRAMES_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.numeroFramesGif = stod(parametroValor[1]);

    return parametros;
}

ParametrosVariacaoCampoExterno leParametrosVariacaoCampoExterno(ifstream *config) {
    string LARGURA_REDE, ALTURA_REDE, INTERACAO_VIZINHOS, CAMPO_EXTERNO_INICIAL, CAMPO_EXTERNO_FINAL, PONTOS_DE_CAMPO_EXTERNO, CONSTANTE_BOLTZMAN, TEMPERATURA, PASSOS_MONTECARLO, IDENTIFICADOR, GERAR_GIF, GERAR_GRAFICOS, NUMERO_FRAMES_GIF;
    ParametrosVariacaoCampoExterno parametros;
    vector<string> parametroValor;

    (*config) >> LARGURA_REDE;
    (*config) >> ALTURA_REDE;
    (*config) >> INTERACAO_VIZINHOS;
    (*config) >> CAMPO_EXTERNO_INICIAL;
    (*config) >> CAMPO_EXTERNO_FINAL;
    (*config) >> PONTOS_DE_CAMPO_EXTERNO;
    (*config) >> CONSTANTE_BOLTZMAN;
    (*config) >> TEMPERATURA;
    (*config) >> PASSOS_MONTECARLO;
    (*config) >> IDENTIFICADOR;
    (*config) >> GERAR_GIF;
    (*config) >> GERAR_GRAFICOS;
    (*config) >> NUMERO_FRAMES_GIF;
    
    parametroValor = explode(LARGURA_REDE, '=');
    if (parametroValor[0] != "LARGURA_REDE") {
        cout << "LARGURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.N = stod(parametroValor[1]);
    
    parametroValor = explode(ALTURA_REDE, '=');
    if (parametroValor[0] != "ALTURA_REDE") {
        cout << "ALTURA_REDE inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.M = stod(parametroValor[1]);
    
    parametroValor = explode(INTERACAO_VIZINHOS, '=');
    if (parametroValor[0] != "INTERACAO_VIZINHOS") {
        cout << "INTERACAO_VIZINHOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.J = stof(parametroValor[1]);
    
    parametroValor = explode(CAMPO_EXTERNO_INICIAL, '=');
    if (parametroValor[0] != "CAMPO_EXTERNO_INICIAL") {
        cout << "CAMPO_EXTERNO_INICIAL inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.H_min = stof(parametroValor[1]);
    
    parametroValor = explode(CAMPO_EXTERNO_FINAL, '=');
    if (parametroValor[0] != "CAMPO_EXTERNO_FINAL") {
        cout << "CAMPO_EXTERNO_FINAL inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.H_max = stof(parametroValor[1]);
    
    parametroValor = explode(PONTOS_DE_CAMPO_EXTERNO, '=');
    if (parametroValor[0] != "PONTOS_DE_CAMPO_EXTERNO") {
        cout << "PONTOS_DE_CAMPO_EXTERNO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.pontosCampoExterno = stod(parametroValor[1]);
    
    parametroValor = explode(CONSTANTE_BOLTZMAN, '=');
    if (parametroValor[0] != "CONSTANTE_BOLTZMAN") {
        cout << "CONSTANTE_BOLTZMAN inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.K_B = stof(parametroValor[1]);
    
    parametroValor = explode(TEMPERATURA, '=');
    if (parametroValor[0] != "TEMPERATURA") {
        cout << "TEMPERATURA inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.T = stof(parametroValor[1]);
    
    parametroValor = explode(PASSOS_MONTECARLO, '=');
    if (parametroValor[0] != "PASSOS_MONTECARLO") {
        cout << "PASSOS_MONTECARLO inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.MCS = stof(parametroValor[1]);
    
    parametroValor = explode(IDENTIFICADOR, '=');
    if (parametroValor[0] != "IDENTIFICADOR") {
        cout << "IDENTIFICADOR inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.identificador = parametroValor[1];
    
    parametroValor = explode(GERAR_GIF, '=');
    if (parametroValor[0] != "GERAR_GIF") {
        cout << "GERAR_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGif = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(GERAR_GRAFICOS, '=');
    if (parametroValor[0] != "GERAR_GRAFICOS") {
        cout << "GERAR_GRAFICOS inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.gerarGraficos = (bool) stod(parametroValor[1]);
    
    parametroValor = explode(NUMERO_FRAMES_GIF, '=');
    if (parametroValor[0] != "NUMERO_FRAMES_GIF") {
        cout << "NUMERO_FRAMES_GIF inválida. Arquivo não segue os padrões. Consultar README." << endl;
        exit(-1);
    }
    parametros.numeroFramesGif = stod(parametroValor[1]);

    return parametros;
}

const int indice_anterior(int i, int N) {
    return (((i - 1) % N) + N) % N;
}

PixelMatrix redeParaPixels(RedeSpins rede) {
    int N = rede.size(), M = rede[0].size();
    PixelMatrix pMatrix;

    for (int i = 0; i < N; i++) {
        vector<Pixel> linha;
        for (int j = 0; j < M; j++) {
            Pixel p;
            p.on = (bool) (0.5) * (rede[i][j] + 1);
            linha.push_back(p);
        }
        pMatrix.push_back(linha);
    }

    return pMatrix;
}

void salvaEstadoAtual(RedeSpins rede, string sequencial, string pasta, string afixo, string prefixo) {
    PixelMatrix bpm = redeParaPixels(rede);
    Bitmap imagem(bpm);

    string extensao = ".bmp";

    string caminho = pasta + "/" + prefixo + afixo + sequencial + extensao;

    imagem.save(caminho);

}

void salvaEvolucaoSistema(float T, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo, string prefixo, string sufixo, string extensao) {
    string caminho = pasta + "/" + prefixo + afixo + sufixo + extensao;
    FILE *arquivo = fopen(caminho.c_str(), "w");

    fprintf(arquivo, "i,T,E,M,C,Chi\n");

    for (int i = 0; i < E.size(); i++) {
        fprintf(arquivo, "%d,%f,%f,%f,%f,%f\n", i, T, E[i], M[i], C[i], Chi[i]);
    }

    fclose(arquivo);
}

void salvaVariacaoTemperatura(vector<float> T, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo, string prefixo, string sufixo, string extensao) {
    string caminho = pasta + "/" + prefixo + afixo + sufixo + extensao;
    FILE *arquivo = fopen(caminho.c_str(), "w");

    fprintf(arquivo, "T,E,M,C,Chi\n");

    for (int i = 0; i < E.size(); i++) {
        fprintf(arquivo, "%d,%f,%f,%f,%f,%f\n", i, T[i], E[i], M[i], C[i], Chi[i]);
    }

    fclose(arquivo);
}

void salvaVariacaoCampoExterno(float T, vector<float> H, vector<float> E, vector<float> M, vector<float> C, vector<float> Chi, string pasta, string afixo, string prefixo, string sufixo, string extensao) {
    string caminho = pasta + "/" + prefixo + afixo + sufixo + extensao;
    FILE *arquivo = fopen(caminho.c_str(), "w");

    fprintf(arquivo, "T,H,E,M,C,Chi\n");

    for (int i = 0; i < E.size(); i++) {
        fprintf(arquivo, "%d, %f,%f,%f,%f,%f,%f\n", i, T, H[i], E[i], M[i], C[i], Chi[i]);
    }

    fclose(arquivo);
}

RedeSpins redeSpinsAleatorios(int N, int M) {
    RedeSpins rede;
    const int spins[2] = {-1, 1};

    for (int i = 0; i < N; i++) {
        vector<int> linha;
        for (int j = 0; j < M; j++) {
            linha.push_back(spins[rand() & 1]);
        }
        rede.push_back(linha);
    }

    return rede;
}

float funcaoParticao(vector<float> E, float beta) {
    float Z = 0;

    for (int i = 0; i < E.size(); i++) {
        Z += exp(-beta * E[i]);
    }

    return Z;
}

#endif