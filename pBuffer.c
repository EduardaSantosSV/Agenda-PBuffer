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
#define MENU_OP (int *)(pBuffer + sizeof(int))
#define SIZE_LIST *(int *)pBuffer
#define TEMP_NAME (char *)(pBuffer + sizeof(int) + sizeof(int))
#define TEMP_OPTION (int *)(pBuffer + sizeof(int) + NAME)
#define TEMP_RESULT (void **)(pBuffer + sizeof(int) + NAME + sizeof(int))
#define TEMP_NODE (void **)(pBuffer + sizeof(int) + NAME + sizeof(int) + sizeof(void *))
#define TEMP_PREV (void **)(pBuffer + sizeof(int) + NAME + sizeof(int) + 2 * sizeof(void *))
#define TEMP_NEXT (void **)(pBuffer + sizeof(int) + NAME + sizeof(int) + 3 * sizeof(void *))
typedef void **Node;

void addPerson(void *pBuffer, void *mananger);
void removePerson(void *pBuffer, void *mananger);
void searchPerson(void *pBuffer, void *mananger);
void printList(void *mananger);
void freeMemory(void *pBuffer, void *mananger);

int main() {
    // Buffer principal
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + NAME + sizeof(int) + 4 * sizeof(void *));
    SIZE_LIST = 0;

    // Manager para controle da lista
    void *mananger = malloc(2 * sizeof(void *));
    START = NULL;
    FINAL = NULL;

    do {
        printf("Menu:\n1. Adicionar pessoa\n2. Remover pessoa\n3. Buscar pessoa\n4. Imprimir lista\n5. Sair\n");
        printf("Escolha uma opcao: ");
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
                printf("Opcao invalida!\n");
                break;
        }
    } while (*TEMP_OPTION != 5);

    freeMemory(pBuffer, mananger);
    return 0;
}

void addPerson(void *pBuffer, void *mananger) {
    void *newNode = malloc(PREVIOUS_LINK + sizeof(void *) * 2);

    printf("Digite o nome (ate 9 caracteres): ");
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
    printf("Digite o nome da pessoa a ser removida (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    // Search for the node to be removed
    void **prev = NULL;
    void **curr = &START;
    while (*curr != NULL && strcmp(TEMP_NAME, (char *)*curr) != 0) {
        prev = curr;
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    // Node not found
    if (*curr == NULL) {
        printf("Pessoa nao encontrada.\n");
        return;
    }

    // Update previous node's NEXT_LINK
    if (prev != NULL) {
        *(void **)((char *)*prev + NEXT_LINK) = *(void **)((char *)*curr + NEXT_LINK);
    } else {
        START = *(void **)((char *)*curr + NEXT_LINK);
    }

    // Update next node's PREVIOUS_LINK if it's not FINAL
    void **next = *(void **)((char *)*curr + NEXT_LINK);
    if (next != FINAL) {
        *(void **)((char *)next + PREVIOUS_LINK) = prev;
    } else {
        FINAL = prev;
    }

    // Free the memory of the removed node
    free(*curr);

    SIZE_LIST--;

    printf("Pessoa removida com sucesso.\n");
}


void searchPerson(void *pBuffer, void *mananger) {
    printf("Digite o nome da pessoa a ser buscada (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    *TEMP_RESULT = START;

    while (*TEMP_RESULT != NULL && strcmp(TEMP_NAME, (char *)*TEMP_RESULT) != 0) {
        *TEMP_RESULT = *(void **)((char *)(*TEMP_RESULT) + NEXT_LINK);
    }

    if (*TEMP_RESULT == NULL) {
        printf("Pessoa nao encontrada.\n");
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

