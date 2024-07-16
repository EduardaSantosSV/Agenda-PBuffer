// Eduarda dos Santos da Silva

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME (sizeof(char) * 10)
#define AGE (sizeof(int))
#define EMAIL (sizeof(char) * 20)

// Definições para utilizar a dupla ligação
#define PREVIOUS_LINK (sizeof(char) * 10) + sizeof(int) + (sizeof(char) * 20)
#define NEXT_LINK (sizeof(char) * 10) + sizeof(int) + (sizeof(char) * 20) + sizeof(void **)
#define START *(void **)mananger
#define FINAL *(void **)(mananger + sizeof(void **))

// Definições para menu e lista
#define SIZE_LIST *(int *)pBuffer
#define TEMP_NAME (char *)(pBuffer + sizeof(int) + sizeof(int))
#define TEMP_OPTION (int *)(pBuffer + sizeof(int) + NAME)
#define TEMP_RESULT (void **)(pBuffer + sizeof(int) + NAME + sizeof(int))

void addPerson(void *pBuffer, void *mananger);
void removePerson(void *pBuffer, void *mananger);
void searchPerson(void *pBuffer, void *mananger);
void printList(void *mananger);
void freeMemory(void *pBuffer, void *mananger);

int main() {
    // Buffer principal
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + NAME + sizeof(int) + sizeof(void *));
    SIZE_LIST = 0;

    // Manager para controle da lista
    void *mananger = malloc(2 * sizeof(void *));
    START = NULL;
    FINAL = NULL;

    do {
        printf("Menu:\n1. Adicionar pessoa\n2. Remover pessoa\n3. Buscar pessoa\n4. Imprimir lista\n5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", TEMP_OPTION);

        switch (*TEMP_OPTION) {
            case 1:
                addPerson(pBuffer, mananger);
                break;
            case 2:
                removePerson(pBuffer, mananger);
                break;
            case 3:
                searchPerson(pBuffer, mananger);
                break;
            case 4:
                printList(mananger);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (*TEMP_OPTION != 5);

    freeMemory(pBuffer, mananger);
    return 0;
}

void addPerson(void *pBuffer, void *mananger) {
    void *newNode = malloc(PREVIOUS_LINK + sizeof(void *) * 2);

    printf("Digite o nome (até 9 caracteres): ");
    scanf("%9s", (char *)newNode);
    printf("Digite a idade: ");
    scanf("%d", (int *)(newNode + NAME));
    printf("Digite o e-mail: ");
    scanf("%19s", (char *)(newNode + NAME + AGE));

    void **prev = NULL;
    void **curr = &START;

    while (*curr != NULL && strcmp((char *)newNode, (char *)*curr) > 0) {
        prev = curr;
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    *(void **)((char *)newNode + PREVIOUS_LINK) = prev ? *prev : NULL;
    *(void **)((char *)newNode + NEXT_LINK) = *curr;

    if (prev) {
        *(void **)((char *)*prev + NEXT_LINK) = newNode;
    } else {
        START = newNode;
    }

    if (*curr) {
        *(void **)((char *)*curr + PREVIOUS_LINK) = newNode;
    } else {
        FINAL = newNode;
    }

    SIZE_LIST++;
}

void removePerson(void *pBuffer, void *mananger) {
    printf("Digite o nome da pessoa a ser removida (até 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    void **curr = &START;

    while (*curr != NULL && strcmp(TEMP_NAME, (char *)*curr) != 0) {
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    if (*curr == NULL) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    void *nodeToRemove = *curr;
    void **prev = (void **)((char *)nodeToRemove + PREVIOUS_LINK);
    void **next = (void **)((char *)nodeToRemove + NEXT_LINK);

    if (*prev) {
        *(void **)((char *)(*prev) + NEXT_LINK) = *next;
    } else {
        START = *next;
    }

    if (*next) {
        *(void **)((char *)(*next) + PREVIOUS_LINK) = *prev;
    } else {
        FINAL = *prev;
    }

    free(nodeToRemove);
    SIZE_LIST--;
}

void searchPerson(void *pBuffer, void *mananger) {
    printf("Digite o nome da pessoa a ser buscada (até 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    *TEMP_RESULT = START;

    while (*TEMP_RESULT != NULL && strcmp(TEMP_NAME, (char *)*TEMP_RESULT) != 0) {
        *TEMP_RESULT = *(void **)((char *)(*TEMP_RESULT) + NEXT_LINK);
    }

    if (*TEMP_RESULT == NULL) {
        printf("Pessoa não encontrada.\n");
    } else {
        printf("Pessoa encontrada: Nome: %s, Idade: %d, E-mail: %s\n",
               (char *)*TEMP_RESULT,
               *(int *)((char *)(*TEMP_RESULT) + NAME),
               (char *)((char *)(*TEMP_RESULT) + NAME + AGE));
    }
}

void printList(void *mananger) {
    void *current = START;
    while (current != NULL) {
        printf("Nome: %s, Idade: %d, E-mail: %s\n",
               (char *)current,
               *(int *)(current + NAME),
               (char *)(current + NAME + AGE));
        current = *(void **)((char *)current + NEXT_LINK);
    }
}

void freeMemory(void *pBuffer, void *mananger) {
    void *current = START;
    void *next = NULL;

    while (current != NULL) {
        next = *(void **)((char *)current + NEXT_LINK);
        free(current);
        current = next;
    }

    free(mananger);
    free(pBuffer);
}
