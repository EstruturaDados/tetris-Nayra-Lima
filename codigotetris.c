#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Programa: Simulação da fila de peças do Tetris Stack
    Descrição:
        Este programa simula a fila de peças futuras de um jogo tipo Tetris.
        Ele usa uma estrutura de dados do tipo FILA CIRCULAR para armazenar as peças.
        O jogador pode:
            1 - Jogar uma peça (remoção da frente da fila)
            2 - Inserir nova peça (adição ao final da fila)
            0 - Sair do programa
*/

// =============================
// Definições e estruturas
// =============================

#define MAX 5  // Tamanho máximo da fila de peças

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[MAX];
    int frente; // Índice da primeira peça
    int tras;   // Índice do último elemento
    int tamanho; // Quantidade atual de peças na fila
} Fila;

// =============================
// Funções da fila
// =============================

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma nova peça automaticamente com tipo aleatório
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça ao final da fila (enqueue)
void inserirPeca(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("\n  A fila está cheia! Não é possível inserir uma nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % MAX;
    f->elementos[f->tras] = nova;
    f->tamanho++;

    printf("\n Peça [%c %d] adicionada ao final da fila.\n", nova.nome, nova.id);
}

// Remove a peça da frente da fila (dequeue)
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("\n  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->elementos[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;

    printf("\n Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\n=== ESTADO ATUAL DA FILA DE PEÇAS ===\n");

    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    int i, index;
    for (i = 0; i < f->tamanho; i++) {
        index = (f->frente + i) % MAX;
        printf("[%c %d] ", f->elementos[index].nome, f->elementos[index].id);
    }
    printf("\n-------------------------------------\n");
}

// =============================
// Função principal do jogo
// =============================
int main() {
    Fila fila;
    int opcao;
    int contadorID = 0; // Controla o ID único das peças

    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserirPeca(&fila, gerarPeca(contadorID++));
    }

    printf("=== TETRIS STACK - FILA DE PEÇAS FUTURAS ===\n");

    // Loop principal do jogo
    do {
        exibirFila(&fila);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, gerarPeca(contadorID++));
                break;
            case 0:
                printf("\nSaindo do jogo... \n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
