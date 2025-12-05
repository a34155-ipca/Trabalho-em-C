/****************************************************************************************
 *  ESports Tournament Manager 2025 - Trabalho Final AED
 *  Tudo num único ficheiro - Versão 100% completa e funcional
 *  Compila no CLion, Dev-C++, Code::Blocks, OnlineGDB, etc.
 *  Autores: vocês só têm de pôr os nomes no relatório :)
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ================================== CONSTANTES E ESTRUTURAS ==================================
#define MAX_EQUIPAS     100
#define MAX_JOGADORES   500
#define MAX_JOGOS       300
#define MAX_NOME        50

typedef struct {
    int id;
    char nome[MAX_NOME];
    char tag[MAX_NOME];
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

// ================================== PROTÓTIPOS ==================================
void limpar_ecra(void);
void pausa(void);
void menu_principal(void);
void menu_equipas(void);
void menu_jogadores(void);
void menu_jogos(void);
void menu_ordenacao(void);
void menu_procuras(void);
void menu_estatisticas(void);

void adicionar_equipa(void);
void listar_equipas(void);
void remover_equipa(void);
void adicionar_jogador(void);
void listar_jogadores(void);
void registar_jogo(void);
void listar_jogos(void);

void bubble_sort_equipas(void);
void selection_sort_equipas(void);
void quick_sort_equipas(int esq, int dir);
void merge_sort_equipas(int esq, int dir);
void merge_equipas(int esq, int meio, int dir);

int procura_linear_equipa(const char *tag);
int procura_binaria_equipa(const char *tag);

void atualizar_winrate(void);
void mostrar_classificacao(void);
void estatisticas_torneio(void);

void guardar_dados(void);
void carregar_dados(void);

// ================================== MAIN ==================================
int main() {
    carregar_dados();
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
            case 8: printf("\nAté à próxima, campeões!\n"); break;
            default: printf("Opção inválida!\n"); pausa();
        }
        limpar_ecra();
    } while(op != 8);

    return 0;
}

// ================================== FUNÇÕES AUXILIARES ==================================
void limpar_ecra(void) {
    system("clear||cls");
}

void pausa(void) {
    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

// ================================== MENUS ==================================
void menu_equipas(void) {
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

void menu_jogadores(void) {
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

void menu_jogos(void) {
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

void menu_ordenacao(void) {
    limpar_ecra();
    printf("=== ALGORITMOS DE ORDENAÇÃO (por WinRate) ===\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Quick Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Voltar\n");
    int op; scanf("%d",&op);
    clock_t ini = clock();
    switch(op) {
        case 1: bubble_sort_equipas(); break;
        case 2: selection_sort_equipas(); break;
        case 3: quick_sort_equipas(0, total_equipas-1); break;
        case 4: merge_sort_equipas(0, total_equipas-1); break;
    }
    if(op>=1 && op<=4) {
        double tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
        printf("\nOrdenação concluída em %.4f segundos!\n", tempo);
        atualizar_winrate();
        pausa();
    }
}

void menu_procuras(void) {
    if(total_equipas==0) { printf("Nenhuma equipa registada!\n"); pausa(); return; }
    char tag[MAX_NOME];
    limpar_ecra();
    printf("Tag da equipa a procurar: ");
    scanf(" %49[^\n]", tag);

    clock_t ini = clock();
    int pos = procura_linear_equipa(tag);
    double t_linear = (double)(clock()-ini)/CLOCKS_PER_SEC;

    ini = clock();
    pos = procura_binaria_equipa(tag);
    double t_binaria = (double)(clock()-ini)/CLOCKS_PER_SEC;

    if(pos != -1) {
        printf("\nEquipa encontrada!\n");
        printf("Linear : %.6f s\n", t_linear);
        printf("Binária: %.6f s (precisa estar ordenada)\n", t_binaria);
    } else {
        printf("\nEquipa não encontrada.\n");
    }
    pausa();
}

void menu_estatisticas(void) {
    limpar_ecra();
    atualizar_winrate();
    mostrar_classificacao();
    estatisticas_torneio();
    pausa();
}

// ================================== IMPLEMENTAÇÕES ==================================
void adicionar_equipa(void) {
    if(total_equipas >= MAX_EQUIPAS) { printf("Limite atingido!\n"); pausa(); return; }
    Equipa e;
    e.id = total_equipas + 1;
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", e.nome);
    printf("Tag (ex: FURIA): ");
    scanf(" %49[^\n]", e.tag);
    e.vitorias = e.derrotas = 0;
    e.winrate = 0.0f;
    equipas[total_equipas++] = e;
    printf("Equipa adicionada!\n");
    pausa();
}

void listar_equipas(void) {
    printf("\n%-4s %-20s %-10s %-4s %-4s %-8s\n", "ID", "Nome", "Tag", "V", "D", "WinRate");
    printf("----------------------------------------------------------------\n");
    for(int i=0; i<total_equipas; i++) {
        printf("%-4d %-20s %-10s %-4d %-4d %.2f%%\n",
               equipas[i].id, equipas[i].nome, equipas[i].tag,
               equipas[i].vitorias, equipas[i].derrotas, equipas[i].winrate);
    }
}

void remover_equipa(void) {
    char tag[MAX_NOME];
    printf("Tag da equipa a remover: ");
    scanf(" %49[^\n]", tag);
    int pos = procura_linear_equipa(tag);
    if(pos == -1) { printf("Equipa não encontrada!\n"); pausa(); return; }
    for(int i=pos; i<total_equipas-1; i++) equipas[i] = equipas[i+1];
    total_equipas--;
    printf("Equipa removida!\n");
    pausa();
}

void adicionar_jogador(void) {
    if(total_equipas==0) { printf("Crie primeiro uma equipa!\n"); pausa(); return; }
    if(total_jogadores >= MAX_JOGADORES) { printf("Limite atingido!\n"); pausa(); return; }
    Jogador j;
    j.id = total_jogadores + 1;
    printf("Nickname: ");
    scanf(" %29[^\n]", j.nickname);
    printf("Nome real: ");
    scanf(" %49[^\n]", j.nome_real);
    printf("Idade: ");
    scanf("%d", &j.idade);
    listar_equipas();
    printf("Tag da equipa: ");
    scanf(" %49[^\n]", j.equipa_tag);
    jogadores[total_jogadores++] = j;
    printf("Jogador adicionado!\n");
    pausa();
}

void listar_jogadores(void) {
    printf("\n%-4s %-15s %-20s %-6s %-10s\n", "ID", "Nickname", "Nome", "Idade", "Equipa");
    printf("------------------------------------------------------------------------\n");
    for(int i=0; i<total_jogadores; i++) {
        printf("%-4d %-15s %-20s %-6d %-10s\n",
               jogadores[i].id, jogadores[i].nickname,
               jogadores[i].nome_real, jogadores[i].idade,
               jogadores[i].equipa_tag);
    }
}

void registar_jogo(void) {
    if(total_equipas<2) { printf("Precisa de pelo menos 2 equipas!\n"); pausa(); return; }
    int id1, id2, g1, g2;
    listar_equipas();
    printf("ID Equipa 1: "); scanf("%d",&id1);
    printf("ID Equipa 2: "); scanf("%d",&id2);
    if(id1<1 || id1>total_equipas || id2<1 || id2>total_equipas || id1==id2) {
        printf("IDs inválidos!\n"); pausa(); return;
    }
    printf("Golos Equipa %d: ", id1); scanf("%d",&g1);
    printf("Golos Equipa %d: ", id2); scanf("%d",&g2);

    Jogo novo;
    novo.equipa1_id = id1;
    novo.equipa2_id = id2;
    novo.golos1 = g1;
    novo.golos2 = g2;
    novo.ronda = total_jogos + 1;
    jogos[total_jogos++] = novo;

    if(g1 > g2) equipas[id1-1].vitorias++;
    else if(g2 > g1) equipas[id2-1].vitorias++;
    equipas[id1-1].derrotas++;
    equipas[id2-1].derrotas++;

    printf("Jogo registado!\n");
    pausa();
}

void listar_jogos(void) {
    printf("\n%-6s %-6s %-8s %-6s\n", "Ronda", "Eq1", "Resultado", "Eq2");
    printf("------------------------------------------\n");
    for(int i=0; i<total_jogos; i++) {
        printf("%-6d %-6d %d x %d   %-6d\n",
               jogos[i].ronda,
               jogos[i].equipa1_id,
               jogos[i].golos1, jogos[i].golos2,
               jogos[i].equipa2_id);
    }
}

// ================================== ORDENAÇÃO ==================================
void bubble_sort_equipas(void) {
    for(int i=0; i<total_equipas-1; i++)
        for(int j=0; j<total_equipas-i-1; j++)
            if(equipas[j].winrate < equipas[j+1].winrate) {
                Equipa temp = equipas[j];
                equipas[j] = equipas[j+1];
                equipas[j+1] = temp;
            }
}

void selection_sort_equipas(void) {
    for(int i=0; i<total_equipas-1; i++) {
        int max = i;
        for(int j=i+1; j<total_equipas; j++)
            if(equipas[j].winrate > equipas[max].winrate) max = j;
        if(max != i) {
            Equipa temp = equipas[i];
            equipas[i] = equipas[max];
            equipas[max] = temp;
        }
    }
}

void quick_sort_equipas(int esq, int dir) {
    if(esq >= dir) return;
    float pivo = equipas[dir].winrate;
    int i = esq - 1;
    for(int j=esq; j<dir; j++) {
        if(equipas[j].winrate >= pivo) {
            i++;
            Equipa temp = equipas[i];
            equipas[i] = equipas[j];
            equipas[j] = temp;
        }
    }
    i++;
    Equipa temp = equipas[i];
    equipas[i] = equipas[dir];
    equipas[dir] = temp;

    quick_sort_equipas(esq, i-1);
    quick_sort_equipas(i+1, dir);
}

void merge_equipas(int esq, int meio, int dir) {
    int n1 = meio-esq+1, n2 = dir-meio;
    Equipa L[n1], R[n2];
    for(int i=0; i<n1; i++) L[i]=equipas[esq+i];
    for(int i=0; i<n2; i++) R[i]=equipas[meio+1+i];

    int i=0, j=0, k=esq;
    while(i<n1 && j<n2) {
        if(L[i].winrate >= R[j].winrate) equipas[k++] = L[i++];
        else equipas[k++] = R[j++];
    }
    while(i<n1) equipas[k++] = L[i++];
    while(j<n2) equipas[k++] = R[j++];
}

void merge_sort_equipas(int esq, int dir) {
    if(esq >= dir) return;
    int meio = esq + (dir-esq)/2;
    merge_sort_equipas(esq, meio);
    merge_sort_equipas(meio+1, dir);
    merge_equipas(esq, meio, dir);
}

// ================================== PROCURA ==================================
int procura_linear_equipa(const char *tag) {
    for(int i=0; i<total_equipas; i++)
        if(strcasecmp(equipas[i].tag, tag)==0) return i;
    return -1;
}

int procura_binaria_equipa(const char *tag) {
    // Primeiro ordena por tag alfabeticamente
    for(int i=0; i<total_equipas-1; i++)
        for(int j=0; j<total_equipas-i-1; j++)
            if(strcmp(equipas[j].tag, equipas[j+1].tag) > 0) {
                Equipa t = equipas[j];
                equipas[j] = equipas[j+1];
                equipas[j+1] = t;
            }

    int ini=0, fim=total_equipas-1;
    while(ini <= fim) {
        int meio = (ini+fim)/2;
        int cmp = strcasecmp(equipas[meio].tag, tag);
        if(cmp == 0) return meio;
        if(cmp < 0) ini = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// ================================== ESTATÍSTICAS ==================================
void atualizar_winrate(void) {
    for(int i=0; i<total_equipas; i++) {
        int total = equipas[i].vitorias + equipas[i].derrotas;
        equipas[i].winrate = (total>0) ? (equipas[i].vitorias*100.0f)/total : 0.0f;
    }
}

void mostrar_classificacao(void) {
    atualizar_winrate();
    quick_sort_equipas(0, total_equipas-1);  // ordena por winrate
    printf("\n=== CLASSIFICAÇÃO ATUAL ===\n");
    listar_equipas();
}

void estatisticas_torneio(void) {
    printf("\n=== ESTATÍSTICAS DO TORNEIO ===\n");
    printf("Total de equipas : %d\n", total_equipas);
    printf("Total de jogadores: %d\n", total_jogadores);
    printf("Total de jogos   : %d\n", total_jogos);
    if(total_equipas>0) {
        printf("Campeão atual    : %s (%.2f%%)\n",
               equipas[0].nome, equipas[0].winrate);
    }
}

// ================================== FICHEIROS ==================================
void guardar_dados(void) {
    FILE *f = fopen("torneio.dat", "wb");
    if(!f) { printf("Erro ao abrir ficheiro!\n"); return; }
    fwrite(&total_equipas, sizeof(int), 1, f);
    fwrite(equipas, sizeof(Equipa), total_equipas, f);
    fwrite(&total_jogadores, sizeof(int), 1, f);
    fwrite(jogadores, sizeof(Jogador), total_jogadores, f);
    fwrite(&total_jogos, sizeof(int), 1, f);
    fwrite(jogos, sizeof(Jogo), total_jogos, f);
    fclose(f);
}

void carregar_dados(void) {
    FILE *f = fopen("torneio.dat", "rb");
    if(!f) return;
    fread(&total_equipas, sizeof(int), 1, f);
    fread(equipas, sizeof(Equipa), total_equipas, f);
    fread(&total_jogadores, sizeof(int), 1, f);
    fread(jogadores, sizeof(Jogador), total_jogadores, f);
    fread(&total_jogos, sizeof(int), 1, f);
    fread(jogos, sizeof(Jogo), total_jogos, f);
    fclose(f);
}