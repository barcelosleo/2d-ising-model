import os

mkdir = lambda diretorio: os.makedirs(diretorio) if not os.path.exists(diretorio) else None

resultados = "./Resultados"

evolucaSistema = f"{resultados}/EvolucaoSistema"
variacaoCampo = f"{resultados}/VariacaoCampo"
variacaoTemperatura = f"{resultados}/VariacaoTemperatura"

modalidades = (evolucaSistema, variacaoCampo, variacaoTemperatura)

for mod in modalidades:
    mkdir(f"{mod}/imagens")
    mkdir(f"{mod}/csv")
    mkdir(f"{mod}/gifs")
    mkdir(f"{mod}/graficos")

