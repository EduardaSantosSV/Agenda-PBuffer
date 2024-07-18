// Eduarda dos Santos da Silva
// Matricula: 22201985
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições básicas
#define NAME (sizeof(char) * 10)
#define AGE (sizeof(int))

// Definições para estruturas de dados
#define PREVIOUS_LINK (sizeof(char) * 10 + sizeof(int) + sizeof(char) * 20)
#define NEXT_LINK (sizeof(char) * 10 + sizeof(int) + sizeof(char) * 20 + sizeof(void *))

// Definições para acesso a dados em memória
#define START *(void **)manager
#define FINAL *(void **)(manager + sizeof(void **))

// Definições para menu e lista
#define SIZE_LIST (*(int *)pBuffer)
#define TEMP_NAME (char *)(pBuffer + sizeof(int) + sizeof(int))
#define TEMP_OPTION (int *)(pBuffer + sizeof(int) + NAME)
#define TEMP_RESULT (void **)(pBuffer + sizeof(int) + NAME + sizeof(int))

// Declara as funções usadas
void addPerson(void *pBuffer, void *manager);
void removePerson(void *pBuffer, void *manager);
void searchPerson(void *pBuffer, void *manager);
void printList(void *manager);
void freeMemory(void *pBuffer, void *manager);

int main () {
    // Aloca memória para o Buffer
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + NAME + sizeof(int) + 4 * sizeof(void *));

    // Inicializa o tamanho da lista
    SIZE_LIST = 0;

    // Aloca memória pro gerenciador de lista
    void *manager = malloc(2 * sizeof(void *));

    // Inicializa o inicio e o final da lista
    START = NULL;
    FINAL = NULL;
    
    // Loop para o menu
        do {
            printf("\nTamanho da lista: %d\n", SIZE_LIST);
            printf("\n---- Menu: ----\n1. Adicionar pessoa\n2. Remover pessoa\n3. Buscar pessoa\n4. Imprimir lista\n5. Sair\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", TEMP_OPTION);

    // Executa a ação baseada na opção escolhida
            switch (*TEMP_OPTION)
            {
            case 1:
                addPerson(pBuffer, manager);
                break;
            case 2:
                removePerson(pBuffer, manager);
                break;
            case 3:
                searchPerson(pBuffer, manager);
                break;
            case 4:
                printList(manager);
                break;
            case 5:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
            }
        } while (*TEMP_OPTION != 5);

    freeMemory(pBuffer, manager);
    return 0;
}

void addPerson (void *pBuffer, void *manager) {
    // Aloca memória para o novo nó
    void *newNode = malloc(PREVIOUS_LINK + sizeof(void *) * 2);

    // Solicita os dados da pessoa
    printf("\nDigite o nome (ate 9 caracteres): ");
    scanf("%9s", (char *)newNode);
    printf("Digite a idade: ");
    scanf("%d", (int *)(newNode + NAME));
    printf("Digite o e-mail: ");
    scanf("%19s", (char *)(newNode + NAME + AGE));

    // Inicializa ponteiros para percorrer a lista
    void **prev = NULL;
    void **curr = &START;

    // Encontra a posição correta para o novo nó
    while (*curr != NULL && strcmp((char *)newNode, (char *)*curr) > 0) {
        prev = curr;
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    // Ajusta os ponteiros de ligação
    *(void **)((char *)newNode + PREVIOUS_LINK) = prev ? *prev : NULL;
    *(void **)((char *)newNode + NEXT_LINK) = *curr;

    // Atualiza o nó anterior para apontar para o novo nó
        if (prev) {
            *(void **)((char *)*prev + NEXT_LINK) = newNode;
        } else {
            START = newNode;
        }

    // Atualiza o nó seguinte para apontar para o novo nó
        if (*curr) {
            *(void **)((char *)*curr + PREVIOUS_LINK) = newNode;
        } else {
            FINAL = newNode;
        }

    SIZE_LIST++;
}

void removePerson (void *pBuffer, void *manager) {
    printf("\nDigite o nome da pessoa a ser removida (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    // Inicilizar ponteiros
    void **prev = NULL;
    void **curr = &START;

    // Encontrar o nó a ser removido
    while (*curr != NULL && strcmp(TEMP_NAME, (char *)*curr) != 0) {
        prev = curr;
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    // Verificar se o nó foi encontrado
        if (*curr == NULL) {
            printf("\nPessoa nao encontrada.\n");
            return;
        } 
    
    // Atualizar ponteiros para remover o nó
        if (prev != NULL) {
            *(void **)((char *)*prev + NEXT_LINK) = *(void **)((char *)*curr + NEXT_LINK);
        } else {
            START = *(void **)((char *)*curr + NEXT_LINK);
        }

    // Atualizar ponteiro do próximo nó
    void **next = *(void **)((char *)*curr + NEXT_LINK);
        if (next != NULL) {
            *(void **)((char *)next + PREVIOUS_LINK) = prev;
        } else {
            FINAL = prev;
        }

    // Liberar a memória e atualizar o contador
    free(*curr);
    SIZE_LIST--;

    printf("\nPessoa removida com sucesso.\n");
}

void searchPerson (void *pBuffer, void *manager) {
    printf("\nDigite o nome da pessoa a ser buscada (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    // Iniciliza o resultado da busca
    *TEMP_RESULT = START;

    // Recorre a lista pra encontrar a pessoa
    while (*TEMP_RESULT != NULL && strcmp(TEMP_NAME, (char *)*TEMP_RESULT) != 0) {
        *TEMP_RESULT = *(void **)((char *)(*TEMP_RESULT) + NEXT_LINK);
    }

    // Verifica se a pessoa foi encontrada
        if (*TEMP_RESULT == NULL) {
            printf("\nPessoa nao encontrada.\n");
        } else {
            printf("\nPessoa encontrada: \nNome: %s, Idade: %d, E-mail: %s\n",
                (char *)*TEMP_RESULT,
                *(int *)((char *)(*TEMP_RESULT) + NAME),
                (char *)((char *)(*TEMP_RESULT) + NAME + AGE));
        }
}

void printList (void *manager) {
    // Iniciliza o ponteiro atual
    void *current = START;

    // Percorre a lista e imprime as informações do nó atual
    while (current != NULL) {
        printf("\nNome: %s, Idade: %d, E-mail: %s\n",
               (char *)current,
               *(int *)(current + NAME),
               (char *)(current + NAME + AGE));
        current = *(void **)((char *)current + NEXT_LINK);
    }
}

void freeMemory (void *pBuffer, void *manager) {
    // Iniciliza os ponteiros
    void *current = START;
    void *next = NULL;

    // Percorre a lista e libera memória dos nós
    while (current != NULL) {
        next = *(void **)((char *)current + NEXT_LINK);
        free(current);
        current = next;
    }

    // Libera memória das estruturas auxiliares
    free(manager);
    free(pBuffer);
}

