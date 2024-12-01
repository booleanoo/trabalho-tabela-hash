#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Node {
    char name[50];
    char phone[20];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash += *name++;
    }
    return hash % TABLE_SIZE;
}

void adicionarContato() {
    char name[50];
    char phone[20];
    printf("Nome: ");
    scanf("%s", name);
    printf("Telefone: ");
    scanf("%s", phone);

    unsigned int index = hashFunction(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char name[50];
    printf("Nome: ");
    scanf("%s", name);

    unsigned int index = hashFunction(name);
    Node* current = hashTable[index];
    clock_t start = clock();

    while (current) {
        if (strcmp(current->name, name) == 0) {
            clock_t end = clock();
            double timeSpent = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", name, current->phone, timeSpent);
            return;
        }
        current = current->next;
    }
    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char name[50];
    printf("Nome: ");
    scanf("%s", name);

    unsigned int index = hashFunction(name);
    Node* current = hashTable[index];
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current);
            printf("Contato removido com sucesso.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            printf("Nome: %s, Telefone: %s\n", current->name, current->phone);
            current = current->next;
        }
    }
}

int main() {
    int opcao;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
