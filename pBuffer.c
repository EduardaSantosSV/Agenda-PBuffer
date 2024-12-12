// Eduarda dos Santos da Silva
// Matricula: 22201985

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME (sizeof(char) * 10)
#define AGE (sizeof(int))

#define PREVIOUS_LINK (sizeof(char) * 10 + sizeof(int) + sizeof(char) * 20)
#define NEXT_LINK (sizeof(char) * 10 + sizeof(int) + sizeof(char) * 20 + sizeof(void *))

#define START *(void **)manager
#define FINAL *(void **)(manager + sizeof(void **))

#define SIZE_LIST (*(int *)pBuffer)
#define TEMP_NAME (char *)(pBuffer + sizeof(int) + sizeof(int))
#define TEMP_OPTION (int *)(pBuffer + sizeof(int) + NAME)
#define TEMP_RESULT (void **)(pBuffer + sizeof(int) + NAME + sizeof(int))

void addPerson(void *pBuffer, void *manager);
void removePerson(void *pBuffer, void *manager);
void searchPerson(void *pBuffer, void *manager);
void printList(void *manager);
void freeMemory(void *pBuffer, void *manager);

int main () {
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + NAME + sizeof(int) + 4 * sizeof(void *));

    SIZE_LIST = 0;

    void *manager = malloc(2 * sizeof(void *));

    START = NULL;
    FINAL = NULL;
    
        do {
            printf("\nTamanho da lista: %d\n", SIZE_LIST);
            printf("\n---- Menu: ----\n1. Adicionar pessoa\n2. Remover pessoa\n3. Buscar pessoa\n4. Imprimir lista\n5. Sair\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", TEMP_OPTION);

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
    void *newNode = malloc(PREVIOUS_LINK + sizeof(void *) * 2);

    printf("\nDigite o nome (ate 9 caracteres): ");
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

void removePerson(void *pBuffer, void *manager) {
    printf("\nDigite o nome da pessoa a ser removida (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    void **prev = NULL;
    void **curr = &START;
    void *nodeToRemove = NULL;

    while (*curr != NULL && strcmp(TEMP_NAME, (char *)*curr) != 0) {
        prev = curr;
        curr = (void **)((char *)(*curr) + NEXT_LINK);
    }

    if (*curr == NULL) {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    void *next = *(void **)((char *)*curr + NEXT_LINK);
    nodeToRemove = *curr;

    if (prev != NULL) {
        *(void **)((char *)*prev + NEXT_LINK) = next;
    } else {
        START = next;
    }

    if (next != NULL) {
        *(void **)((char *)next + PREVIOUS_LINK) = prev;
    } else {
        FINAL = prev;
    }

    printf("\nRemovendo: %s\n", (char *)nodeToRemove);

    if (next != NULL) {
        printf("Proxima pessoa: %s\n", (char *)next);
    } else {
        printf("Nao ha proxima pessoa.\n");
    }

    if (prev != NULL) {
        printf("Pessoa anterior: %s\n", (char *)*prev);
    } else {
        printf("Nao ha pessoa anterior.\n");
    }

    free(nodeToRemove);

    SIZE_LIST--;

    printf("\nPessoa removida com sucesso.\n");
}



void searchPerson (void *pBuffer, void *manager) {
    printf("\nDigite o nome da pessoa a ser buscada (ate 9 caracteres): ");
    scanf("%9s", TEMP_NAME);

    *TEMP_RESULT = START;

    while (*TEMP_RESULT != NULL && strcmp(TEMP_NAME, (char *)*TEMP_RESULT) != 0) {
        *TEMP_RESULT = *(void **)((char *)(*TEMP_RESULT) + NEXT_LINK);
    }

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
    void *current = START;

    while (current != NULL) {
        printf("\nNome: %s, Idade: %d, E-mail: %s\n",
               (char *)current,
               *(int *)(current + NAME),
               (char *)(current + NAME + AGE));
        current = *(void **)((char *)current + NEXT_LINK);
    }
}

void freeMemory (void *pBuffer, void *manager) {
    void *current = START;
    void *next = NULL;

    while (current != NULL) {
        next = *(void **)((char *)current + NEXT_LINK);
        free(current);
        current = next;
    }

    free(manager);
    free(pBuffer);
}

