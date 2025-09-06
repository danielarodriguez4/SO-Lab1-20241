#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar las líneas en una lista enlazada
typedef struct LineNode {
    char *line;
    struct LineNode *next;
} LineNode;

LineNode* createNode(char *line) {
    LineNode *newNode = malloc(sizeof(LineNode));
    if (newNode == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
        
    newNode->line = malloc(strlen(line) + 1);
    if (newNode->line == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    
    strcpy(newNode->line, line);
    newNode->next = NULL;
    return newNode;
}

// Función para agregar un nodo al inicio de la lista (para facilitar la inversión)
void addToFront(LineNode **head, char *line) {
    LineNode *newNode = createNode(line);
    newNode->next = *head;
    *head = newNode;
}

// Función para liberar memoria de la lista
void freeList(LineNode *head) {
    LineNode *current = head;
    while (current != NULL) {
        LineNode *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}

void printList(LineNode *head, FILE *output) {
    LineNode *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        current = current->next;
    }
}

int sameFile(char *file1, char *file2) {
    return strcmp(file1, file2) == 0;
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    LineNode *head = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Verificar número de argumentos
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Caso 1: ./reverse input.txt output.txt
    if (argc == 3) {
        // Verificar que los archivos de entrada y salida sean diferentes
        if (sameFile(argv[1], argv[2])) {
            fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
            exit(1);
        }

        // Abrir archivo de entrada
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        // Abrir archivo de salida
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(input);
            exit(1);
        }
    }
    // Caso 2: ./reverse input.txt
    else if (argc == 2) {
        // Abrir archivo de entrada
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    // Caso 3: ./reverse (sin argumentos)
    
    while ((read = getline(&line, &len, input)) != -1) {
        addToFront(&head, line);
    }
    free(line);

    printList(head, output);

    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }

    freeList(head);

    return 0;
}
