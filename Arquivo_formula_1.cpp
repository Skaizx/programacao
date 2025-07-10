#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define ARQUIVO "corridas.dat"

typedef struct {
    char nomeCorrida[MAX];
    int ano;
    char vencedor[MAX];
    char equipe[MAX];
} Corrida;

void incluirCorrida() {
    FILE *f = fopen(ARQUIVO, "ab");
    Corrida c;

    printf("Nome da corrida: ");
    fgets(c.nomeCorrida, MAX, stdin);
    c.nomeCorrida[strcspn(c.nomeCorrida, "\n")] = 0;

    printf("Ano: ");
    scanf("%d", &c.ano);
    getchar();

    printf("Vencedor: ");
    fgets(c.vencedor, MAX, stdin);
    c.vencedor[strcspn(c.vencedor, "\n")] = 0;

    printf("Equipe: ");
    fgets(c.equipe, MAX, stdin);
    c.equipe[strcspn(c.equipe, "\n")] = 0;

    fwrite(&c, sizeof(Corrida), 1, f);
    fclose(f);
    printf("Corrida adicionada com sucesso!\n");
}

void listarCorridas() {
    FILE *f = fopen(ARQUIVO, "rb");
    Corrida c;
    int i = 1;

    while (fread(&c, sizeof(Corrida), 1, f)) {
        printf("\n[%d] %s (%d) - %s / %s\n", i++, c.nomeCorrida, c.ano, c.vencedor, c.equipe);
    }
    fclose(f);
}

void editarCorrida() {
    FILE *f = fopen(ARQUIVO, "rb+");
    Corrida c;
    int pos, i = 1;

    listarCorridas();
    printf("\nDigite o número da corrida que deseja editar: ");
    scanf("%d", &pos);
    getchar();

    fseek(f, (pos - 1) * sizeof(Corrida), SEEK_SET);
    fread(&c, sizeof(Corrida), 1, f);

    printf("Novo nome da corrida (%s): ", c.nomeCorrida);
    fgets(c.nomeCorrida, MAX, stdin);
    c.nomeCorrida[strcspn(c.nomeCorrida, "\n")] = 0;

    printf("Novo ano (%d): ", c.ano);
    scanf("%d", &c.ano);
    getchar();

    printf("Novo vencedor (%s): ", c.vencedor);
    fgets(c.vencedor, MAX, stdin);
    c.vencedor[strcspn(c.vencedor, "\n")] = 0;

    printf("Nova equipe (%s): ", c.equipe);
    fgets(c.equipe, MAX, stdin);
    c.equipe[strcspn(c.equipe, "\n")] = 0;

    fseek(f, (pos - 1) * sizeof(Corrida), SEEK_SET);
    fwrite(&c, sizeof(Corrida), 1, f);
    fclose(f);
    printf("Corrida editada com sucesso!\n");
}

void excluirCorrida() {
    FILE *f = fopen(ARQUIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Corrida c;
    int pos, i = 1, count = 0;

    listarCorridas();
    printf("\nDigite o número da corrida que deseja excluir: ");
    scanf("%d", &pos);
    getchar();

    while (fread(&c, sizeof(Corrida), 1, f)) {
        if (i != pos) {
            fwrite(&c, sizeof(Corrida), 1, temp);
        }
        i++;
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    printf("Corrida excluída com sucesso!\n");
}

int main() {
    int opcao;

    do {
        printf("\n==== CRUD FÓRMULA 1 ====\n");
        printf("1. Incluir corrida\n");
        printf("2. Listar corridas\n");
        printf("3. Editar corrida\n");
        printf("4. Excluir corrida\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: incluirCorrida(); break;
            case 2: listarCorridas(); break;
            case 3: editarCorrida(); break;
            case 4: excluirCorrida(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

