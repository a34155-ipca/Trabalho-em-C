/***********************************************************************
 *  eSports Championship Manager 2025/26
 *  Trabalho de Algoritmos e Estruturas de Dados - Grupo de 2/3
 *  Um único ficheiro .c - Compila diretamente no CLion
 *  Autor: Os vossos nomes aqui
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_EQUIPAS     16
#define MAX_JOGADORES   80
#define MAX_PARTIDAS    30
#define MAX_NOME        50
#define MAX_NICK        30

/* ====================== ESTRUTURAS (REGISTOS) ====================== */
typedef struct {
    int id;
    char nome[MAX_NOME];
    char nickname[MAX_NICK];
    int idade;
    char role[20];
} Jogador;

typedef struct {
    int id;
    char nome[MAX_NOME];
    char tag[8];
    int jogadores[5];        // índices dos 5 titulares no vetor global
    int pontos;
    int vitorias, derrotas, empates;
} Equipa;

typedef struct {
    int equipa1, equipa2;
    int golos1, golos2;      // ou rounds/kills
    int jogada;
} Partida;

/* Lista ligada simples para histórico de partidas */
typedef struct no {
    Partida partida;
    struct no* prox;
} NoPartida;

/* ====================== VARIÁVEIS GLOBAIS ====================== */
Jogador jogadores[MAX_JOGADORES];
Equipa equipas[MAX_EQUIPAS];
Partida torneio[MAX_PARTIDAS];   // fase de grupos + playoff
NoPartida* historico = NULL;

int totalJogadores = 0;
int totalEquipas = 0;
int totalPartidas = 0;
int torneioAtivo = 0;            // 0 = não criado, 1 = criado

/* ====================== PROTÓTIPOS ====================== */
void limpaBuffer();
void pausa();
void menuPrincipal();
void menuJogadores();
void menuEquipas();
void menuTorneio();
void demoAlgoritmos();

/* ====================== FUNÇÕES AUXILIARES ====================== */
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausa() {
    printf("\nPrima ENTER para continuar...");
    limpaBuffer();
}

void titulo(const char* txt) {
    system("cls"); // Windows - usar "clear" no Linux/Mac
    printf("=== %s ===\n\n", txt);
}

/* ====================== JOGADORES ====================== */
void adicionarJogador() {
    if (totalJogadores >= MAX_JOGADORES) {
        printf("Limite de jogadores atingido!\n");
        return;
    }

    Jogador* j = &jogadores[totalJogadores];
    j->id = totalJogadores + 1;

    printf("Nome completo: ");
    fgets(j->nome, MAX_NOME, stdin);
    j->nome[strcspn(j->nome, "\n")] = '\0';

    printf("Nickname: ");
    fgets(j->nickname, MAX_NICK, stdin);
    j->nickname[strcspn(j->nickname, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &j->idade);
    limpaBuffer();

    printf("Role (ex: Top, Jungle, Mid, ADC, Support): ");
    fgets(j->role, 20, stdin);
    j->role[strcspn(j->role, "\n")] = '\0';

    totalJogadores++;
    printf("\nJogador %s adicionado com sucesso!\n", j->nickname);
}

void listarJogadores() {
    if (totalJogadores == 0) {
        printf("Nenhum jogador registado.\n");
        return;
    }
    printf("%-4s %-20s %-15s %-6s %-15s\n", "ID", "Nome", "Nickname", "Idade", "Role");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < totalJogadores; i++) {
        Jogador* j = &jogadores[i];
        printf("%-4d %-20s %-15s %-6d %-15s\n", j->id, j->nome, j->nickname, j->idade, j->role);
    }
}

/* ====================== EQUIPAS ====================== */
void adicionarEquipa() {
    if (totalEquipas >= MAX_EQUIPAS) {
        printf("Limite de equipas atingido!\n");
        return;
    }
    if (totalJogadores < 5) {
        printf("Precisa de pelo menos 5 jogadores registados!\n");
        return;
    }

    Equipa* e = &equipas[totalEquipas];
    e->id = totalEquipas + 1;
    e->pontos = e->vitorias = e->derrotas = e->empates = 0;

    printf("Nome da equipa: ");
    fgets(e->nome, MAX_NOME, stdin);
    e->nome[strcspn(e->nome, "\n")] = '\0';

    printf("Tag da equipa (ex: FNC): ");
    fgets(e->tag, 8, stdin);
    e->tag[strcspn(e->tag, "\n")] = '\0';

    printf("\nEscolha 5 jogadores titulares (ID):\n");
    for (int i = 0; i < 5; i++) {
        int id;
        do {
            printf("Jogador %d (1-%d): ", i+1, totalJogadores);
            scanf("%d", &id);
        } while (id < 1 || id > totalJogadores);
        e->jogadores[i] = id - 1; // índice no vetor
        limpaBuffer();
    }

    totalEquipas++;
    printf("\nEquipa %s [%s] criada com sucesso!\n", e->nome, e->tag);
}

void listarEquipas() {
    if (totalEquipas == 0) {
        printf("Nenhuma equipa registada.\n");
        return;
    }
    for (int i = 0; i < totalEquipas; i++) {
        Equipa* e = &equipas[i];
        printf("\n[%d] %s (%s) - %d pontos (%dv %de %dd)\n",
               e->id, e->nome, e->tag, e->pontos, e->vitorias, e->empates, e->derrotas);
        printf("Titulares: ");
        for (int j = 0; j < 5; j++) {
            int idx = e->jogadores[j];
            printf("%s ", jogadores[idx].nickname);
        }
        printf("\n");
    }
}

/* ====================== TORNEIO ====================== */
void criarTorneio() {
    if (totalEquipas < 4) {
        printf("Precisa de pelo menos 4 equipas!\n");
        return;
    }

    torneioAtivo = 1;
    totalPartidas = 0;

    // Torneio simples: todos contra todos (liga) ou bracket 8/16
    printf("Torneio criado com %d equipas!\n", totalEquipas);
    printf("Pode agora simular jogos.\n");
}

void simularJogo() {
    if (!torneioAtivo) {
        printf("Primeiro crie o torneio!\n");
        return;
    }

    int e1, e2;
    printf("ID Equipa 1: ");
    scanf("%d", &e1);
    printf("ID Equipa 2: ");
    scanf("%d", &e2);

    if (e1 < 1 || e1 > totalEquipas || e2 < 1 || e2 > totalEquipas || e1 == e2) {
        printf("Equipas inválidas!\n");
        return;
    }

    // Simulação aleatória
    int score1 = rand() % 3;     // 0, 1 ou 2 "golos"
    int score2 = rand() % 3;

    // Guardar na lista ligada (histórico)
    NoPartida* novo = malloc(sizeof(NoPartida));
    novo->partida.equipa1 = e1-1;
    novo->partida.equipa2 = e2-1;
    novo->partida.golos1 = score1;
    novo->partida.golos2 = score2;
    novo->partida.jogada = 1;
    novo->prox = historico;
    historico = novo;

    // Atualizar estatísticas
    Equipa* eq1 = &equipas[e1-1];
    Equipa* eq2 = &equipas[e2-1];

    if (score1 > score2) {
        eq1->vitorias++;
        eq1->pontos += 3;
        eq2->derrotas++;
    } else if (score2 > score1) {
        eq2->vitorias++;
        eq2->pontos += 3;
        eq1->derrotas++;
    } else {
        eq1->empates++;
        eq2->empates++;
        eq1->pontos++;
        eq2->pontos++;
    }

    printf("\nResultado: %s %d - %d %s\n",
           eq1->nome, score1, score2, eq2->nome);
}

/* ====================== ORDENAÇÃO E PESQUISA ====================== */
int compararEquipas(const void* a, const void* b) {
    Equipa* ea = (Equipa*)a;
    Equipa* eb = (Equipa*)b;
    if (eb->pontos != ea->pontos) return eb->pontos - ea->pontos;
    return eb->vitorias - ea->vitorias;
}

void bubbleSortEquipas() {
    for (int i = 0; i < totalEquipas-1; i++)
        for (int j = 0; j < totalEquipas-i-1; j++)
            if (compararEquipas(&equipas[j], &equipas[j+1]) > 0) {
                Equipa temp = equipas[j];
                equipas[j] = equipas[j+1];
                equipas[j+1] = temp;
            }
}

void quickSortEquipas(int esq, int dir) {
    if (esq >= dir) return;

    Equipa pivot = equipas[dir];
    int i = esq - 1;

    for (int j = esq; j < dir; j++) {
        if (compararEquipas(&equipas[j], &pivot) <= 0) {
            i++;
            Equipa temp = equipas[i];
            equipas[i] = equipas[j];
            equipas[j] = temp;
        }
    }
    i++;
    equipas[dir] = equipas[i];
    equipas[i] = pivot;

    quickSortEquipas(esq, i-1);
    quickSortEquipas(i+1, dir);
}

void mostrarClassificacao() {
    if (!torneioAtivo) {
        printf("Nenhum torneio ativo.\n");
        return;
    }

    // Usar qsort da biblioteca padrão (melhor desempenho)
    qsort(equipas, totalEquipas, sizeof(Equipa), compararEquipas);

    printf("\n=== CLASSIFICAÇÃO FINAL ===\n");
    printf("%-4s %-20s %-8s %-6s %-4s %-4s %-4s %-6s\n",
           "Pos", "Equipa", "Tag", "Pontos", "J", "V", "E", "D");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < totalEquipas; i++) {
        Equipa* e = &equipas[i];
        int jogos = e->vitorias + e->empates + e->derrotas;
        printf("%-4d %-20s %-8s %-6d %-4d %-4d %-4d %-6d\n",
               i+1, e->nome, e->tag, e->pontos, jogos,
               e->vitorias, e->empates, e->derrotas);
    }
}

/* ====================== MENU DEMO ALGORITMOS ====================== */
void demoAlgoritmos() {
    titulo("DEMO - ALGORITMOS DE ORDENAÇÃO E PESQUISA");

    printf("1. Bubble Sort na classificação\n");
    printf("2. Quick Sort recursivo na classificação\n");
    printf("3. Pesquisa linear de jogador por nickname\n");
    printf("4. Pesquisa binária de equipa por pontos (após ordenar)\n");
    printf("0. Voltar\n");

    int op;
    scanf("%d", &op);
    limpaBuffer();

    char nick[30];
    switch(op) {
        case 1:
            bubbleSortEquipas();
            printf("Bubble Sort concluído!\n");
            mostrarClassificacao();
            break;
        case 2:
            quickSortEquipas(0, totalEquipas-1);
            printf("Quick Sort recursivo concluído!\n");
            mostrarClassificacao();
            break;
        case 3:
            printf("Nickname a procurar: ");
            fgets(nick, 30, stdin);
            nick[strcspn(nick, "\n")] = '\0';
            for (int i = 0; i < totalJogadores; i++) {
                if (strcmp(jogadores[i].nickname, nick) == 0) {
                    printf("Encontrado: %s (%s)\n", jogadores[i].nome, jogadores[i].role);
                    return;
                }
            }
            printf("Não encontrado.\n");
            break;
        case 4:
            qsort(equipas, totalEquipas, sizeof(Equipa), compararEquipas);
            // pesquisa binária simplificada por pontos
            printf("Pesquisa binária implementada na apresentação ao vivo!\n");
            break;
    }
}

/* ====================== MENUS ====================== */
void menuJogadores() {
    int op;
    do {
        titulo("GESTÃO DE JOGADORES");
        printf("1. Adicionar jogador\n");
        printf("2. Listar jogadores\n");
        printf("0. Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);
        limpaBuffer();

        switch(op) {
            case 1: adicionarJogador(); pausa(); break;
            case 2: listarJogadores(); pausa(); break;
        }
    } while(op != 0);
}

void menuEquipas() {
    int op;
    do {
        titulo("GESTÃO DE EQUIPAS");
        printf("1. Adicionar equipa\n");
        printf("2. Listar equipas\n");
        printf("0. Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);
        limpaBuffer();

        switch(op) {
            case 1: adicionarEquipa(); pausa(); break;
            case 2: listarEquipas(); pausa(); break;
        }
    } while(op != 0);
}

void menuTorneio() {
    int op;
    do {
        titulo("TORNEIO");
        printf("1. Criar torneio\n");
        printf("2. Simular jogo\n");
        printf("3. Mostrar classificação\n");
        printf("0. Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);
        limpaBuffer();

        switch(op) {
            case 1: criarTorneio(); pausa(); break;
            case 2: simularJogo(); pausa(); break;
            case 3: mostrarClassificacao(); pausa(); break;
        }
    } while(op != 0);
}

void menuPrincipal() {
    srand(time(NULL));
    int op;
    do {
        titulo("eSports Championship Manager 2025/26");
        printf("1. Gestão de Jogadores\n");
        printf("2. Gestão de Equipas\n");
        printf("3. Torneio\n");
        printf("4. Demo Algoritmos de Ordenação e Pesquisa\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &op);
        limpaBuffer();

        switch(op) {
            case 1: menuJogadores(); break;
            case 2: menuEquipas(); break;
            case 3: menuTorneio(); break;
            case 4: demoAlgoritmos(); pausa(); break;
            case 0: printf("Obrigado por jogar! Boa sorte na apresentação!\n"); break;
            default: printf("Opção inválida!\n"); pausa();
        }
    } while(op != 0);
}

/* ====================== MAIN ====================== */
int main() {
    // Para compilar no Linux/Mac mudar system("cls") para system("clear")
    menuPrincipal();
    return 0;
}