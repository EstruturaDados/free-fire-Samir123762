#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



// Estrutura que representa um item na mochila
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item
    int quantidade;    // Quantidade de item
} Item;

// Estrutura do nó para lista encadeada
typedef struct No {
    Item dados;             // Cada nó guarda uma estrutura Item
    struct No* proximo;     // Ponteiro para o próximo nó da lista
} No;


// Gerenciamento da Estrutura Vetor (Array)

#define MAX_ITENS 100   // Capacidade máxima do vetor

Item mochilaVetor[MAX_ITENS];   // Vetor global para armazenar os itens
int tamanhoVetor = 0;           // Variável que rastreia o número atual de itens

// Contadores para medir desempenho das buscas
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;


// Insere novo item no final do vetor
void inserirItemVetor(Item novo) {
    if (tamanhoVetor < MAX_ITENS) {
        mochilaVetor[tamanhoVetor++] = novo; // Adiciona o novo item e, em seguida, incrementa o tamanho
    } else {
        printf("Mochila cheia!\n");
    }
}

// Remove item por nome
void removerItemVetor(char nome[]) {
    for (int i = 0; i < tamanhoVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) { // Compara o nome do item atual com o nome a remover
            // Move todos os elementos à direita uma posição à esquerda para preencher o "buraco"
            for (int j = i; j < tamanhoVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            tamanhoVetor--; // Diminui o tamanho lógico do vetor
            printf("Item removido.\n");
            return; // Sai da função após a remoção
        }
    }
    printf("Item não encontrado.\n");
}

// Lista todos os itens armazenados no vetor
void listarItensVetor() {
    if (tamanhoVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\n=== Itens na mochila (vetor) ===\n");
    for (int i = 0; i < tamanhoVetor; i++) {
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Busca sequencial simples (linear) no vetor
int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0; // Zera o contador
    for (int i = 0; i < tamanhoVetor; i++) {
        comparacoesSequencial++; // Incrementa o contador a cada comparação
        if (strcmp(mochilaVetor[i].nome, nome) == 0) // Compara por nome
            return i; // Retorna o índice onde o item foi encontrado
    }
    return -1; // Retorna -1 se não encontrado
}

// Ordenação por nome usando Bubble Sort
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < tamanhoVetor - 1; i++) {
        for (int j = 0; j < tamanhoVetor - i - 1; j++) {
            // Se o item 'j' for alfabeticamente maior que 'j+1'
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Realiza a troca
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados alfabeticamente.\n");
}

// Busca binária (apenas após o vetor estar ordenado)
int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = tamanhoVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2; // Calcula o índice do meio
        comparacoesBinaria++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome); // Compara o item do meio
        if (cmp == 0) return meio;          // Achou o item
        else if (cmp < 0) inicio = meio + 1; // O item está na metade direita (meio é menor que o buscado)
        else fim = meio - 1;                // O item está na metade esquerda (meio é maior que o buscado)
    }
    return -1; // Não encontrado
}


// --- Gerenciamento da Estrutura Lista Encadeada Simples ---

No* inicio = NULL; // Ponteiro para o primeiro nó da lista

// Insere novo item no início da lista
void inserirItemLista(Item novo) {
    No* novoNo = (No*) malloc(sizeof(No)); // Aloca memória para o novo nó
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novoNo->dados = novo;      // Copia os dados do item para o nó
    novoNo->proximo = inicio;  // O novo nó aponta para o antigo início
    inicio = novoNo;           // Atualiza o início da lista para o novo nó
    printf("Item inserido na lista.\n");
}

// Remove item pelo nome na lista
void removerItemLista(char nome[]) {
    No* atual = inicio;     // Ponteiro para o nó atual
    No* anterior = NULL;    // Ponteiro para o nó anterior (necessário para "pular" o nó a ser removido)

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            // Ajusta os ponteiros para remover o nó
            if (anterior == NULL)
                inicio = atual->proximo; // O item a remover é o primeiro
            else
                anterior->proximo = atual->proximo; // O nó anterior aponta para o próximo do 'atual'

            free(atual); // Libera a memória do nó removido
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;       // Avança o ponteiro anterior
        atual = atual->proximo; // Avança o ponteiro atual
    }
    printf("Item não encontrado na lista.\n");
}

// Lista todos os itens da lista encadeada
void listarItensLista() {
    if (inicio == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    No* atual = inicio;
    printf("\n=== Itens na mochila (lista encadeada) ===\n");
    while (atual != NULL) {
        printf("%s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo; // Move para o próximo nó
    }
}

// Busca sequencial na lista (linear)
int buscarSequencialLista(char nome[]) {
    int comparacoes = 0;
    No* atual = inicio;

    while (atual != NULL) {
        comparacoes++; // Conta a comparação
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado após %d comparações.\n", comparacoes);
            return 1; // Encontrado
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado após %d comparações.\n", comparacoes);
    return 0; // Não encontrado
}


// --- Função Principal

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao, estrutura;
    Item novo;
    char nomeBusca[30];

    printf("=== SISTEMA DE MOCHILA ===\n");
    while(1){
    printf("Escolha a estrutura de dados:\n");
        printf("1 - Vetor\n");
        printf("2 - Lista Encadeada\n> ");
        scanf("%d", &estrutura); // Escolhe qual estrutura será usada
        if(estrutura==1||estrutura==2)
            break;
        else
            printf("\nValor incorreto!\n");
}
    do {
        // Exibição do menu de opções
        printf("\n=== MENU ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        printf("5 - Ordenar vetor\n");         // Apenas para vetor
        printf("6 - Busca binária (vetor)\n"); // Apenas para vetor
        printf("0 - Sair\n> ");
        scanf("%d", &opcao); // Lê a opção do usuário

        switch (opcao) {
            case 1: // Inserir
                // Coleta os dados do novo item
                printf("Nome: "); scanf("%s", novo.nome);
                printf("Tipo: "); scanf("%s", novo.tipo);
                printf("Quantidade: "); scanf("%d", &novo.quantidade);

                if (estrutura == 1)
                    inserirItemVetor(novo); // Insere no vetor
                else
                    inserirItemLista(novo); // Insere na lista
                break;

            case 2: // Remover
                printf("Nome do item a remover: ");
                scanf("%s", nomeBusca);
                if (estrutura == 1)
                    removerItemVetor(nomeBusca); // Remove do vetor
                else
                    removerItemLista(nomeBusca); // Remove da lista
                break;

            case 3: // Listar
                if (estrutura == 1)
                    listarItensVetor(); // Lista o vetor
                else
                    listarItensLista(); // Lista a lista encadeada
                break;

            case 4: // Buscar Sequencial
                printf("Nome do item a buscar: ");
                scanf("%s", nomeBusca);
                if (estrutura == 1) {
                    int pos = buscarSequencialVetor(nomeBusca);
                    // Exibe o resultado e o número de comparações
                    if (pos != -1)
                        printf("Item encontrado após %d comparações.\n", comparacoesSequencial);
                    else
                        printf("Item não encontrado (%d comparações).\n", comparacoesSequencial);
                } else {
                    buscarSequencialLista(nomeBusca); // Busca na lista encadeada (já exibe o resultado)
                }
                break;

            case 5: // Ordenar
                if (estrutura == 1)
                    ordenarVetor(); // Ordena o vetor (Bubble Sort)
                else
                    printf("Ordenação indisponível para lista encadeada.\n");
                break;

            case 6: // Busca Binária
                if (estrutura == 1) {
                    printf("Nome do item a buscar (binária): ");
                    scanf("%s", nomeBusca);
                    int pos = buscarBinariaVetor(nomeBusca); // Busca no vetor (requer ordenado)
                    // Exibe o resultado e o número de comparações
                    if (pos != -1)
                        printf("Item encontrado após %d comparações.\n", comparacoesBinaria);
                    else
                        printf("Item não encontrado (%d comparações).\n", comparacoesBinaria);
                } else {
                    printf("Busca binária não disponível para listas encadeadas.\n");
                }
                break;

            case 0: // Sair
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0); // Continua o loop até que a opção seja 0

    return 0;
}
