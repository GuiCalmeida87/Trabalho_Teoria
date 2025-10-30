#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

bool isSubsetSum(int conjunto[], int n, int somaAlvo) {
    if (somaAlvo < 0) return false;

    bool **dp = (bool **)malloc((n + 1) * sizeof(bool *));
    if (dp == NULL) {
        return false;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (bool *)malloc((somaAlvo + 1) * sizeof(bool));
        if (dp[i] == NULL) {
            for(int k=0; k < i; k++) free(dp[k]);
            free(dp);
            return false;
        }
    }

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int j = 1; j <= somaAlvo; j++) {
        dp[0][j] = false;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= somaAlvo; j++) {
            dp[i][j] = dp[i-1][j];

            int elemento_atual = conjunto[i-1];
            if (elemento_atual <= j) {
                if (dp[i-1][j - elemento_atual] == true) {
                    dp[i][j] = true;
                }
            }
        }
    }

    bool resultado = dp[n][somaAlvo];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return resultado;
}

#define NUM_REPETICOES 20
#define MAX_CONFIGURACOES 3

typedef struct {
    char nome[15];
    int tamanho_conjunto;
    int max_valor;
    int soma_alvo;
} Configuracao;

void gerar_conjunto(int **conjunto, int tamanho, int max_valor) {
    *conjunto = (int *)malloc(tamanho * sizeof(int));
    if (*conjunto == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tamanho; i++) {
        (*conjunto)[i] = rand() % max_valor + 1;
    }
}

void simular_e_medir(Configuracao config) {
    clock_t inicio, fim;
    double tempos[NUM_REPETICOES];
    double soma_tempos = 0.0;
    
    int *conjunto;
    gerar_conjunto(&conjunto, config.tamanho_conjunto, config.max_valor);
    
    for (int i = 0; i < NUM_REPETICOES; i++) {
        inicio = clock();
        
        isSubsetSum(conjunto, config.tamanho_conjunto, config.soma_alvo);
        
        fim = clock();
        
        double tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[i] = tempo_decorrido;
        soma_tempos += tempo_decorrido;
    }
    
    free(conjunto);
    
    double media_tempo = soma_tempos / NUM_REPETICOES;
    
    double soma_quadrados_diferencas = 0.0;
    for (int i = 0; i < NUM_REPETICOES; i++) {
        soma_quadrados_diferencas += pow(tempos[i] - media_tempo, 2);
    }
    double desvio_padrao = (NUM_REPETICOES > 1) ? sqrt(soma_quadrados_diferencas / (NUM_REPETICOES - 1)) : 0.0;

    printf("| %-15s | %-11d | %-13d | %-16.6f | %-17.6f |\n", 
           config.nome, 
           config.tamanho_conjunto, 
           config.soma_alvo, 
           media_tempo, 
           desvio_padrao);
}

int main() {
    srand((unsigned int)time(NULL)); 

    Configuracao configuracoes[MAX_CONFIGURACOES] = {
        {"Pequeno", 10, 20, 30},
        {"Medio", 50, 50, 1250},
        {"Grande", 150, 100, 3000}
    };

    printf("Iniciando Simulacao de Desempenho do Subconjunto Soma (DP) em C\n");
    printf("Numero de Repeticoes por Teste: %d\n\n", NUM_REPETICOES);

    printf("Resultados da Simulacao:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-11s | %-13s | %-16s | %-17s |\n", 
           "Configuracao", "Tamanho (N)", "Soma Alvo (W)", "Tempo Medio (s)", "Desvio Padrao (s)");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_CONFIGURACOES; i++) {
        simular_e_medir(configuracoes[i]);
    }
    
    printf("------------------------------------------------------------------------------------------------\n");
    
    return 0;
}