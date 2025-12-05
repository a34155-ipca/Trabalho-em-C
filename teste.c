///****************************************************************************************
 *  ESports Tournament Manager 2025 - Trabalho de AED
 *  Tudo num único ficheiro - Como os professores clássicos gostam
 *  Cumpre 100% dos conteúdos programáticos
 *  Divisão perfeita para dupla: um faz a parte de cima, outro a parte de baixo
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ================================== CONSTANTES E ESTRUTURAS ==================================
#define MAX_EQUIPAS     100
#define MAX_JOGADORES   500
#define MAX_JOGOS       200
#define MAX_NOME        50

typedef struct {
    int id;
    char nome[MAX_NOME];
    char tag[MAX_NOME];      // ex: "FURIA", "G2"
    int vitorias, derrotas;
    float winrate;
} Equipa;

typedef struct {
    int id;
    char nickname[30];
    char nome_real[50];
    int idade;
    char equipa_tag[MAX_NOME];
} Jogador;

typedef struct {
    int equipa1_id, equipa2_id;
    int golos1, golos2;
    int ronda;
} Jogo;

// ================================== VARIÁVEIS GLOBAIS ==================================
Equipa  equipas[MAX_EQUIPAS];
Jogador jogadores[MAX_JOGADORES];
Jogo    jogos[MAX_JOGOS];

int total_equipas = 0;
int total_jogadores = 0;
int total_jogos = 0;

// ================================== PROTÓTIPOS DAS FUNÇÕES ==================================
void limpar_ecra();
void pausa();
void menu_principal();
void menu_equipas();
void menu_jogadores();
void menu_jogos();
void menu_ordenacao();
void menu_procuras();
void menu_estatisticas();

// Funções de equipas
void adicionar_equipa();
void listar_equipas();
void remover_equipa();

// Funções de jogadores
void adicionar_jogador();
void listar_jogadores();

// Funções de jogos
void registar_jogo();
void listar_jogos();

// Algoritmos de ordenação (vão implementar vários)
void bubble_sort_equipas();
void selection_sort_equipas();
void quick_sort_equipas(int esq, int dir);
void merge_sort_equipas(int esq, int dir);

// Algoritmos de procura
int procura_linear_equipa(char *tag);
int procura_binaria_equipa(char *tag); // só funciona se estiver ordenado por tag

// Estatísticas
void mostrar_classificacao();
void estatisticas_torneio();

// Guardar/carregar
void guardar_dados();
void carregar_dados();

// ================================== MAIN ==================================
int main() {
    carregar_dados(); // tenta carregar torneio anterior
    limpar_ecra();
    printf("\n   ███████ ███████ ██████  ██████  ██████  ████████ ███████ \n");
    printf("   ██      ██      ██   ██ ██   ██ ██   ██    ██    ██      \n");
    printf("   ███████ ███████ ██████  ██████  ██████     ██    ███████ \n");
    printf("        ██      ██ ██      ██   ██ ██         ██         ██ \n");
    printf("   ███████ ███████ ██      ██   ██ ██         ██    ███████ \n\n");
    printf("         Bem-vindo ao Esports Tournament Manager 2025\n\n");

    int op;
    do {
        printf("╔══════════════════════════════════════╗\n");
        printf("║           MENU PRINCIPAL             ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("  1. Gerir Equipas\n");
        printf("  2. Gerir Jogadores\n");
        printf("  3. Gerir Jogos\n");
        printf("  4. Classificação e Ordenação\n");
        printf("  5. Procuras Rápidas\n");
        printf("  6. Estatísticas\n");
        printf("  7. Guardar Torneio\n");
        printf("  8. Sair\n");
        printf("╚══════════════════════════════════════╝\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch(op) {
            case 1: menu_equipas(); break;
            case 2: menu_jogadores(); break;
            case 3: menu_jogos(); break;
            case 4: menu_ordenacao(); break;
            case 5: menu_procuras(); break;
            case 6: menu_estatisticas(); break;
            case 7: guardar_dados(); printf("\nTorneio guardado com sucesso!\n"); pausa(); break;
            case 8: printf("\nAté à próxima, glória eterna aos campeões!\n"); break;
            default: printf("Opção inválida!\n"); pausa();
        }
        limpar_ecra();
    } while(op != 8);

    return 0;
}

// ================================== FUNÇÕES AUXILIARES ==================================
void limpar_ecra() {
    system("clear||cls");
}

void pausa() {
    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

// ================================== MENUS ==================================
void menu_equipas() {
    int op;
    do {
        limpar_ecra();
        printf("=== GESTÃO DE EQUIPAS ===\n");
        printf("1. Adicionar Equipa\n");
        printf("2. Listar Equipas\n");
        printf("3. Remover Equipa\n");
        printf("4. Voltar\n");
        printf("Opção: "); scanf("%d",&op);
        switch(op) {
            case 1: adicionar_equipa(); break;
            case 2: listar_equipas(); pausa(); break;
            case 3: remover_equipa(); break;
        }
    } while(op != 4);
}

void menu_jogadores() {
    int op;
    do {
        limpar_ecra();
        printf("=== GESTÃO DE JOGADORES ===\n");
        printf("1. Adicionar Jogador\n");
        printf("2. Listar Jogadores\n");
        printf("3. Voltar\n");
        printf("Opção: "); scanf("%d",&op);
        switch(op) {
            case 1: adicionar_jogador(); break;
            case 2: listar_jogadores(); pausa(); break;
        }
    } while(op != 3);
}

void menu_jogos() {
    int op;
    do {
        limpar_ecra();
        printf("=== GESTÃO DE JOGOS ===\n");
        printf("1. Registar Jogo\n");
        printf("2. Listar Jogos\n");
        printf("3. Voltar\n");
        printf("Opção: "); scanf("%d",&op);
        switch(op) {
            case 1: registar_jogo(); break;
            case 2: listar_jogos(); pausa(); break;
        }
    } while(op != 3);
}

void menu_ordenacao() {
    limpar_ecra();
    printf("=== ALGORITMOS DE ORDENAÇÃO ===\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Quick Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Voltar\n");
    int op; scanf("%d",&op);
    clock_t inicio = clock();
    switch(op) {
        case 1: bubble_sort_equipas(); break;
        case 2: selection_sort_equipas(); break;
        case 3: quick_sort_equipas(0, total_equipas-1); break;
        case 4: merge_sort_equipas(0, total_equipas-1); break;
    }
    if(op >=1 && op <=4) {
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Ordenação concluída em %.4f segundos!\n", tempo);
        pausa();
    }
}

void menu_procuras() {
    limpar_ecra();
    char tag[MAX_NOME];
    printf("Tag da equipa a procurar: ");
    scanf(" %49[^\n]", tag);
    int pos = procura_linear_equipa(tag);
    if(pos != -1) printf("Procura linear: encontrada na posição %d\n", pos);
    else printf("Procura linear: não encontrada\n");

    pos = procura_binaria_equipa(tag);
    if(pos != -1) printf("Procura binária: encontrada na posição %d\n", pos);
    else printf("Procura binária: não encontrada (lista precisa estar ordenada)\n");
    pausa();
}

void menu_estatisticas() {
    limpar_ecra();
    mostrar_classificacao();
    estatisticas_torneio();
    pausa();
}

// ================================== IMPLEMENTAÇÃO DAS FUNÇÕES (a partir daqui vocês completam) ==================================

void adicionar_equipa() {
    if(total_equipas >= MAX_EQUIPAS) { printf("Limite de equipas atingido!\n"); pausa(); return; }
    Equipa e;
    e.id = total_equipas + 1;
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", e.nome);
    printf("Tag (ex: FURIA): ");
    scanf(" %49[^\n]", e.tag);
    e.vitorias = e.derrotas = 0;
    e.winrate = 0.0;
    equipas[total_equipas++] = e;
    printf("Equipa adicionada com sucesso!\n");
    pausa();
}

void listar_equipas() {
    printf("\n%-3s %-20s %-10s %-4s %-4s %-8s\n", "ID", "Nome", "Tag", "V", "D", "WinRate");
    printf("----------------------------------------------------------------\n");
    for(int i=0; i<total_equipas; i++) {
        printf("%-3d %-20s %-10s %-4d %-4d %.2f%%\n",
               equipas[i].id, equipas[i].nome, equipas[i].tag,
               equipas[i].vitorias, equipas[i].derrotas, equipas[i].winrate);
    }
}

// (as outras funções seguem o mesmo padrão – posso mandar completas se quiserem)

void registar_jogo() {
    // código completo se precisarem
}

// ================================== ALGORITMOS DE ORDENAÇÃO (implementem aqui vários) ==================================
void bubble_sort_equipas() {
    // implementar ordenação por winrate descendente
    // ...
}

void quick_sort_equipas(int esq, int dir) {
    // implementar
}

// ================================== GUARDAR E CARREGAR ==================================
void guardar_dados() {
    FILE *f = fopen("torneio.dat", "wb");
    if(!f) { printf("Erro ao guardar!\n"); return; }
    fwrite(&total_equipas, sizeof(int), 1, f);
    fwrite(equipas, sizeof(Equipa), total_equipas, f);
    fwrite(&total_jogadores, sizeof(int), 1, f);
    fwrite(jogadores, sizeof(Jogador), total_jogadores, f);
    fwrite(&total_jogos, sizeof(int), 1, f);
    fwrite(jogos, sizeof(Jogo), total_jogos, f);
    fclose(f);
}

void carregar_dados() {
    FILE *f = fopen("torneio.dat", "rb");
    if(!f) return; // primeiro uso
    fread(&total_equipas, sizeof(int), 1, f);
    fread(equipas, sizeof(Equipa), total_equipas, f);
    fread(&total_jogadores, sizeof(int), 1, f);
    fread(jogadores, sizeof(Jogador), total_jogadores, f);
    fread(&total_jogos, sizeof(int), 1, f);
    fread(jogos, sizeof(Jogo), total_jogos, f);
    fclose(f);
}
// Created by kauan on 04/12/2025.
//