import sys
import imageio

PASTA_EVOLUCAO_SISTEMA = "./Resultados/EvolucaoSistema"
PASTA_VARIACAO_CAMPO = "./Resultados/VariacaoCampo"
PASTA_VARIACAO_TEMPERATURA = "./Resultados/VariacaoTemperatura"

def salvaGif(imagens, pasta, identificador, resize = None, fps = 15):
    nome_arquivo = identificador + '.gif'
    caminho_arquivo = pasta + f"/gifs/{nome_arquivo}"

    imageio.mimsave(caminho_arquivo, imagens, fps=15)
    
def leImagens(pasta, identificador, frames):
    imagens = []
    caminho = f"{pasta}/imagens/estado_{identificador}"
    for i in range(frames + 1):
        im = imageio.imread(f"{caminho}{i}.bmp")
        imagens.append(im)
        
    return imagens

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Você deve informar um arquivo de configuração!")
        exit(-1)

    for i in range(1, len(sys.argv)):
        caminhoArquivo = sys.argv[i]
        print(f"Processando arquivo {caminhoArquivo}")

        caminhoArquivo = sys.argv[i]
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

                imagens = leImagens(PASTA_EVOLUCAO_SISTEMA, IDENTIFICADOR, int(NUMERO_FRAMES_GIF))
                salvaGif(imagens, PASTA_EVOLUCAO_SISTEMA, IDENTIFICADOR)

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

                imagens = leImagens(PASTA_VARIACAO_TEMPERATURA, IDENTIFICADOR, int(NUMERO_FRAMES_GIF))
                salvaGif(imagens, PASTA_VARIACAO_TEMPERATURA, IDENTIFICADOR)

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

                imagens = leImagens(PASTA_VARIACAO_CAMPO, IDENTIFICADOR, int(NUMERO_FRAMES_GIF))
                salvaGif(imagens, PASTA_VARIACAO_CAMPO, IDENTIFICADOR)

            else:
                print("Tipo de simulação desconhecido")
                exit(-1)