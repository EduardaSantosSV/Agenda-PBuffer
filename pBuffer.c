#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 10
#define EMAIL_LENGTH 20

// Estrutura para representar cada nó da lista
typedef struct PersonNode {
    char name[NAME_LENGTH];
    int age;
    char email[EMAIL_LENGTH];
    struct PersonNode *prev;
    struct PersonNode *next;
} PersonNode;

// Variáveis globais para controle da lista
PersonNode *START = NULL;
PersonNode *FINAL = NULL;
int SIZE_LIST = 0;

// Protótipos das funções
void addPerson();
void removePerson();
void searchPerson();
void printList();
void freeMemory();

int main()
{
    int option;

    do {
        printf("\n\nMenu:\n1. Adicionar pessoa\n2. Remover pessoa\n3. Buscar pessoa\n4. Imprimir lista\n5. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addPerson();
                break;
            case 2:
                removePerson();
                break;
            case 3:
                searchPerson();
                break;
            case 4:
                printList();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (option != 5);

    freeMemory();
    return 0;
}

void addPerson()
{
    PersonNode *newNode = (PersonNode *)malloc(sizeof(PersonNode));

    if (newNode == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        return;
    }

    printf("Digite o nome (até %d caracteres): ", NAME_LENGTH - 1);
    scanf("%9s", newNode->name); // Limitando a entrada para o tamanho do campo name - 1
    printf("Digite a idade: ");
    scanf("%d", &newNode->age);
    printf("Digite o e-mail (até %d caracteres): ", EMAIL_LENGTH - 1);
    scanf("%19s", newNode->email); // Limitando a entrada para o tamanho do campo email - 1

    newNode->prev = NULL;
    newNode->next = NULL;

    if (START == NULL) {
        START = newNode;
        FINAL = newNode;
    } else {
        PersonNode *current = START;
        while (current != NULL && strcmp(newNode->name, current->name) > 0) {
            current = current->next;
        }

        if (current == NULL) {
            // Inserir no final da lista
            FINAL->next = newNode;
            newNode->prev = FINAL;
            FINAL = newNode;
        } else {
            // Inserir antes de current
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev == NULL) {
                START = newNode;
            } else {
                current->prev->next = newNode;
            }
            current->prev = newNode;
        }
    }

    SIZE_LIST++;
}

void removePerson()
{
    if (START == NULL) {
        printf("Lista vazia. Nada a remover.\n");
        return;
    }

    char TEMP_NAME[NAME_LENGTH];
    printf("Digite o nome da pessoa a ser removida (até %d caracteres): ", NAME_LENGTH - 1);
    scanf("%9s", TEMP_NAME);

    PersonNode *current = START;

    while (current != NULL && strcmp(TEMP_NAME, current->name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        START = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        FINAL = current->prev;
    }
    
    free(current);
    SIZE_LIST--;
}

void searchPerson()
{
    if (START == NULL) {
        printf("Lista vazia. Nada a buscar.\n");
        return;
    }

    char TEMP_NAME[NAME_LENGTH];
    printf("Digite o nome da pessoa a ser buscada (até %d caracteres): ", NAME_LENGTH - 1);
    scanf("%9s", TEMP_NAME);

    PersonNode *current = START;

    while (current != NULL && strcmp(TEMP_NAME, current->name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Pessoa não encontrada.\n");
    } else {
        printf("Pessoa encontrada: Nome: %s, Idade: %d, E-mail: %s\n",
               current->name, current->age, current->email);
    }
}

void printList()
{
    if (START == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    PersonNode *current = START;

    while (current != NULL) {
        printf("Nome: %s, Idade: %d, E-mail: %s\n",
               current->name, current->age, current->email);
        current = current->next;
    }
}

void freeMemory()
{
    PersonNode *current = START;
    PersonNode *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    START = NULL;
    FINAL = NULL;
    SIZE_LIST = 0;
}
