#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para os jogadores
typedef struct {
    char nome[50];
    char time[50];
    int fase; // 1: Quartas, 2: Semi, 3: Final, 4: Campeão
} Jogador;

// --- VARIÁVEIS GLOBAIS ---
Jogador jogadores[8];
int total = 0;
int idioma = 1; // 1: Português, 2: Inglês

// Função auxiliar para tradução simplificada
void texto(char *pt, char *en) {
    if (idioma == 1) printf("%s", pt);
    else printf("%s", en);
}

// Salva os dados em arquivo binário
void salvarDados() {
    FILE *f = fopen("torneio_fifa.dat", "wb");
    if (f) {
        fwrite(&total, sizeof(int), 1, f);
        fwrite(&idioma, sizeof(int), 1, f); // Salva a preferência de idioma
        fwrite(jogadores, sizeof(Jogador), total, f);
        fclose(f);
    }
}

// Carrega os dados ao iniciar
void carregarDados() {
    FILE *f = fopen("torneio_fifa.dat", "rb");
    if (f) {
        fread(&total, sizeof(int), 1, f);
        fread(&idioma, sizeof(int), 1, f);
        fread(jogadores, sizeof(Jogador), total, f);
        fclose(f);
    }
}

// 1. Adicionar jogador
void adicionarJogador() {
    if (total < 8) {
        printf("\n--- "); texto("Cadastro", "Registration"); printf(" (%d/8) ---\n", total + 1);
        texto("Nome do Jogador: ", "Player Name: ");
        scanf(" %[^\n]s", jogadores[total].nome);
        texto("Time: ", "Team: ");
        scanf(" %[^\n]s", jogadores[total].time);

        jogadores[total].fase = 1;
        total++;
        salvarDados();
        texto(">> Sucesso!\n", ">> Success!\n");
    } else {
        texto("\n>> Erro: Limite de 8 atingido.\n", "\n>> Error: 8 players limit reached.\n");
    }
}

// 2. Listar jogadores
void listarJogadores() {
    if (total == 0) {
        texto("\n>> Nenhum jogador cadastrado.\n", "\n>> No players registered.\n");
        return;
    }
    printf("\n--- "); texto("Lista de Participantes", "Participants List"); printf(" ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s [%s]\n", i + 1, jogadores[i].nome, jogadores[i].time);
    }
}

// Função auxiliar para simular uma partida
int realizarPartida(int id1, int id2) {
    int g1 = rand() % 6;
    int g2 = rand() % 6;
    if (g1 == g2) g1++;

    printf("   %s %d x %d %s -> ", jogadores[id1].nome, g1, g2, jogadores[id2].nome);
    texto("Venceu: ", "Winner: ");

    if (g1 > g2) {
        printf("%s\n", jogadores[id1].nome);
        return id1;
    } else {
        printf("%s\n", jogadores[id2].nome);
        return id2;
    }
}

// 3. Simular Torneio
void simularTorneio() {
    if (total < 8) {
        texto("\n>> Erro: Sao necessarios 8 jogadores.\n", "\n>> Error: 8 players required.\n");
        return;
    }
    srand(time(NULL));
    int s[4], f[2], campeao;

    texto("\n--- QUARTAS DE FINAL ---\n", "\n--- QUARTER-FINALS ---\n");
    s[0] = realizarPartida(0, 1); jogadores[s[0]].fase = 2;
    s[1] = realizarPartida(2, 3); jogadores[s[1]].fase = 2;
    s[2] = realizarPartida(4, 5); jogadores[s[2]].fase = 2;
    s[3] = realizarPartida(6, 7); jogadores[s[3]].fase = 2;

    texto("\n--- SEMIFINAIS ---\n", "\n--- SEMI-FINALS ---\n");
    f[0] = realizarPartida(s[0], s[1]); jogadores[f[0]].fase = 3;
    f[1] = realizarPartida(s[2], s[3]); jogadores[f[1]].fase = 3;

    texto("\n--- FINAL ---\n", "\n--- FINAL ---\n");
    campeao = realizarPartida(f[0], f[1]); jogadores[campeao].fase = 4;

    salvarDados();
    texto("\n>> Simulacao concluida!\n", "\n>> Simulation finished!\n");
}

// 4. Resultado
void mostrarResultado() {
    if (total == 0) {
        texto("\n>> Sem dados.\n", "\n>> No data.\n");
        return;
    }
    printf("\n--- "); texto("RESULTADOS FINAIS", "FINAL RESULTS"); printf(" ---\n");
    for (int nivel = 4; nivel >= 1; nivel--) {
        for (int i = 0; i < total; i++) {
            if (jogadores[i].fase == nivel) {
                if (nivel == 4) texto("[CAMPEAO] ", "[CHAMPION] ");
                else if (nivel == 3) texto("[VICE]    ", "[RUNNER-UP] ");
                else if (nivel == 2) texto("[SEMI]    ", "[SEMI]      ");
                else texto("[QUARTAS] ", "[QUARTERS]  ");
                printf("%s (%s)\n", jogadores[i].nome, jogadores[i].time);
            }
        }
    }
}

// 5. Limpar Torneio
void limparTorneio() {
    total = 0;
    remove("torneio_fifa.dat");
    texto("\n>> Torneio resetado.\n", "\n>> Tournament reset.\n");
}

// 6. Alterar Idioma
void alterarIdioma() {
    printf("\nSelect / Selecione:\n1. Portugues\n2. English\n>> ");
    scanf("%d", &idioma);
    if (idioma != 1 && idioma != 2) idioma = 1;
    salvarDados();
}

int main() {
    carregarDados();
    int opcao;

    do {
        printf("\n========= FIFA 26 =========");
        texto("\n1. Adicionar jogador", "\n1. Add player");
        texto("\n2. Listar jogadores",  "\n2. List players");
        texto("\n3. Simular Torneio",  "\n3. Simulate Tournament");
        texto("\n4. Resultado",         "\n4. Results");
        texto("\n5. Limpar Torneio",    "\n5. Clear Tournament");
        texto("\n6. Alterar Idioma",    "\n6. Change Language");
        texto("\n0. Sair",              "\n0. Exit");
        texto("\nEscolha: ",            "\nChoice: ");

        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1: adicionarJogador(); break;
            case 2: listarJogadores(); break;
            case 3: simularTorneio(); break;
            case 4: mostrarResultado(); break;
            case 5: limparTorneio(); break;
            case 6: alterarIdioma(); break;
            case 0: texto("Encerrando...\n", "Exiting...\n"); break;
            default: texto("Opcao invalida!\n", "Invalid option!\n");
        }
    } while (opcao != 0);

    return 0;
}
