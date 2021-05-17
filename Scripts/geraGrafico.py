import sys
import pandas as pd
import matplotlib.pyplot as plt

PASTA_EVOLUCAO_SISTEMA = "./Resultados/EvolucaoSistema"
PASTA_VARIACAO_CAMPO = "./Resultados/VariacaoCampo"
PASTA_VARIACAO_TEMPERATURA = "./Resultados/VariacaoTemperatura"

def leDados(pasta, identificador):
    nome_arquivo = identificador + '.csv'
    caminho_arquivo = pasta + f"/csv/{nome_arquivo}"
    return pd.read_csv(caminho_arquivo)

def graficoEvolucaoSistema(pasta, identificador, dados, H, W):
    nome_arquivo = identificador + '.png'
    caminho_arquivo = pasta + f"/graficos/{nome_arquivo}"

    plt.subplot(2, 1, 1)
    plt.title(f"Rede {H} x {W}")
    plt.grid(True)
    plt.scatter(dados['i'], dados['E'], marker='.', color='red')
    plt.ylabel("E/N")
    # plt.xlabel("PMC (Passos de Montecarlo)")
    
    plt.subplot(2, 1, 2)
    plt.grid(True)
    plt.scatter(dados['i'], dados['M'], marker='.', color='blue')
    plt.ylabel("M/N")
    plt.xlabel("PMC (Passos de Monte Carlo)")

    plt.savefig(caminho_arquivo)
    # plt.show()

def graficoVariacaoTemperatura(pasta, identificador, dados, J):
    nome_arquivo = identificador + '.png'
    caminho_arquivo = pasta + f"/graficos/{nome_arquivo}"

    # plt.figure(figsize=(6, 7))

    # plt.subplot(4, 1, 1)
    # # plt.title(f"$J = {J}$")
    # plt.grid(True)
    # plt.scatter(dados['T'], dados['E'], marker='.', color='red')
    # plt.ylabel("E/JN")
    # plt.xlabel("PMC (Passos de Montecarlo)")
    
    # plt.subplot(4, 1, 2)

    TC = 2.25
    plt.grid(True)
    plt.scatter(dados['T'], dados['M'], marker='.', color='blue')
    plt.ylabel("M/N")
    plt.vlines(TC, min(dados['M']), max(dados['M']), label='$T_C$', colors=('red', ))
    plt.text(TC - 1, 0.5, '$T_C \\approx ' + str(TC) + '$', color='red')
    # plt.xlabel("T")
    
    # plt.subplot(4, 1, 3)
    # plt.grid(True)
    # plt.scatter(dados['T'], dados['C'], marker='.', color='blue')
    # plt.ylabel("C/N")
    # # plt.xlabel("T")
    
    # plt.subplot(4, 1, 4)
    # plt.grid(True)
    # plt.scatter(dados['T'], dados['Chi'], marker='.', color='blue')
    # plt.ylabel("$\chi /N$")
    # plt.xlabel("T")

    plt.savefig(caminho_arquivo)
    # plt.show()

def graficoVariacaoCampo(pasta, identificador, dados, J):
    nome_arquivo = identificador + '.png'
    caminho_arquivo = pasta + f"/graficos/{nome_arquivo}"

    plt.subplot(2, 1, 1)
    plt.title(f"$J = {J}$")
    plt.grid(True)
    plt.scatter(dados['H'], dados['E'], marker='.', color='red')
    plt.ylabel("E/JN")
    # plt.xlabel("PMC (Passos de Montecarlo)")
    
    plt.subplot(2, 1, 2)
    plt.grid(True)
    plt.scatter(dados['H'], dados['M'], marker='.', color='blue')
    plt.ylabel("M/N")
    plt.xlabel("H")

    plt.savefig(caminho_arquivo)
    # plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Você deve informar um arquivo de configuração!")
        exit(-1)

    for i in range(1, len(sys.argv)):
        caminhoArquivo = sys.argv[i]
        print(f"Processando arquivo {caminhoArquivo}")
        with open(caminhoArquivo, "r") as config:
            linhas = config.read().splitlines()
            _, TIPO = linhas[0].split('=')

            if TIPO == "EVOLUCAO_ATE_EQUILIBRIO":
                _, LARGURA_REDE = linhas[1].split('=')
                _, ALTURA_REDE = linhas[2].split('=')
                _, INTERACAO_VIZINHOS = linhas[3].split('=')
                _, CAMPO_EXTERNO = linhas[4].split('=')
                _, CONSTANTE_BOLTZMAN = linhas[5].split('=')
                _, TEMPERATURA = linhas[6].split('=')
                _, PASSOS_MONTECARLO = linhas[7].split('=')
                _, IDENTIFICADOR = linhas[8].split('=')
                _, GERAR_GIF = linhas[9].split('=')
                _, GERAR_GRAFICOS = linhas[10].split('=')
                _, NUMERO_FRAMES_GIF = linhas[11].split('=')

                dados = leDados(PASTA_EVOLUCAO_SISTEMA, IDENTIFICADOR)
                graficoEvolucaoSistema(PASTA_EVOLUCAO_SISTEMA, IDENTIFICADOR, dados, ALTURA_REDE, LARGURA_REDE)

            elif TIPO == "VARIACAO_TEMPERATURA":
                _, LARGURA_REDE = linhas[1].split('=')
                _, ALTURA_REDE = linhas[2].split('=')
                _, INTERACAO_VIZINHOS = linhas[3].split('=')
                _, CAMPO_EXTERNO = linhas[4].split('=')
                _, CONSTANTE_BOLTZMAN = linhas[5].split('=')
                _, TEMPERATURA_INICIAL = linhas[6].split('=')
                _, TEMPERATURA_FINAL = linhas[7].split('=')
                _, PONTOS_DE_TEMPERATURA = linhas[8].split('=')
                _, PASSOS_MONTECARLO = linhas[9].split('=')
                _, IDENTIFICADOR = linhas[10].split('=')
                _, GERAR_GIF = linhas[11].split('=')
                _, GERAR_GRAFICOS = linhas[12].split('=')
                _, NUMERO_FRAMES_GIF = linhas[13].split('=')

                dados = leDados(PASTA_VARIACAO_TEMPERATURA, IDENTIFICADOR)
                graficoVariacaoTemperatura(PASTA_VARIACAO_TEMPERATURA, IDENTIFICADOR, dados, INTERACAO_VIZINHOS)

            elif TIPO == "VARIACAO_CAMPO_EXTERNO":
                _, LARGURA_REDE = linhas[1].split('=')
                _, ALTURA_REDE = linhas[2].split('=')
                _, INTERACAO_VIZINHOS = linhas[3].split('=')
                _, CAMPO_EXTERNO_INICIAL = linhas[4].split('=')
                _, CAMPO_EXTERNO_FINAL = linhas[5].split('=')
                _, PONTOS_DE_CAMPO_EXTERNO = linhas[6].split('=')
                _, CONSTANTE_BOLTZMAN = linhas[7].split('=')
                _, TEMPERATURA = linhas[8].split('=')
                _, PASSOS_MONTECARLO = linhas[9].split('=')
                _, IDENTIFICADOR = linhas[10].split('=')
                _, GERAR_GIF = linhas[11].split('=')
                _, GERAR_GRAFICOS = linhas[12].split('=')
                _, NUMERO_FRAMES_GIF = linhas[13].split('=')

                dados = leDados(PASTA_VARIACAO_CAMPO, IDENTIFICADOR)
                graficoVariacaoCampo(PASTA_VARIACAO_CAMPO, IDENTIFICADOR, dados, INTERACAO_VIZINHOS)

            else:
                print("Tipo de simulação desconhecido")
                exit(-1)

