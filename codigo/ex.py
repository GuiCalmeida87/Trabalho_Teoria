import time
import random
import statistics
from typing import List

# ----------------------------------------------------
# 1. FUNÇÃO is_subset_sum (Sem comentários, conforme solicitado)
# ----------------------------------------------------
def is_subset_sum(conjunto: List[int], soma_alvo: int) -> bool:
    n = len(conjunto)
    dp = [[False] * (soma_alvo + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        dp[i][0] = True

    for i in range(1, n + 1):
        for j in range(1, soma_alvo + 1):
            dp[i][j] = dp[i-1][j]
            
            elemento_atual = conjunto[i-1]
            if elemento_atual <= j:
                dp[i][j] = dp[i][j] or dp[i-1][j - elemento_atual]

    return dp[n][soma_alvo]

# ----------------------------------------------------
# 2. FUNÇÕES DE GERAÇÃO DE DADOS
# ----------------------------------------------------

def gerar_conjunto(tamanho: int, max_valor: int) -> List[int]:

    return [random.randint(1, max_valor) for _ in range(tamanho)]

# ----------------------------------------------------
# 3. CONFIGURAÇÃO DOS TESTES E SIMULAÇÃO
# ----------------------------------------------------

# Definindo as configurações dos testes
NUM_REPETICOES = 20  # Número de vezes que cada teste será executado
CONFIGURACOES = [
    {"nome": "Pequeno", "tamanho_conjunto": 5, "max_valor": 10, "soma_alvo": 15},
    {"nome": "Médio", "tamanho_conjunto": 50, "max_valor": 50, "soma_alvo": 1250},
    {"nome": "Grande", "tamanho_conjunto": 100, "max_valor": 100, "soma_alvo": 3000},
]

print(" Iniciando Simulação de Desempenho do Subconjunto Soma (DP)")
print(f"Número de Repetições por Teste: {NUM_REPETICOES}\n")

resultados_simulacao = []

for config in CONFIGURACOES:
    tempos = []
    
    # Geração dos dados para o teste
    conjunto = gerar_conjunto(config["tamanho_conjunto"], config["max_valor"])
    soma_alvo = config["soma_alvo"]
    
    # Execução das repetições
    for _ in range(NUM_REPETICOES):
        inicio = time.perf_counter()
        
        # Chamada do algoritmo Subconjunto Soma
        is_subset_sum(conjunto, soma_alvo)
        
        fim = time.perf_counter()
        tempos.append(fim - inicio)
        
    # Cálculo das estatísticas
    media_tempo = statistics.mean(tempos)
    desvio_padrao = statistics.stdev(tempos) if len(tempos) > 1 else 0

    resultados_simulacao.append({
        "Configuração": config["nome"],
        "Tamanho (N)": config["tamanho_conjunto"],
        "Soma Alvo (W)": config["soma_alvo"],
        "Tempo Médio (s)": f"{media_tempo:.6f}",
        "Desvio Padrão (s)": f"{desvio_padrao:.6f}",
    })

# ----------------------------------------------------
 # EXIBIÇÃO DOS RESULTADOS
# ----------------------------------------------------

print("Resultados da Simulação:")
print("-" * 75)
print(f"| {'Configuração':<15} | {'Tamanho (N)':<11} | {'Soma Alvo (W)':<13} | {'Tempo Médio (s)':<16} | {'Desvio Padrão (s)':<17} |")
print("-" * 75)

for res in resultados_simulacao:
    print(f"| {res['Configuração']:<15} | {res['Tamanho (N)']:<11} | {res['Soma Alvo (W)']:<13} | {res['Tempo Médio (s)']:<16} | {res['Desvio Padrão (s)']:<17} |")
    
print("-" * 75)