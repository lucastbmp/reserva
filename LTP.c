#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_RESERVAS 100
#define ARQUIVO_RESERVAS "reservas.txt"

typedef struct {
    char nome[100];
    char cpf[15];
    int dia;
    int quantidade_pessoas;
} Reserva;

Reserva reservas[MAX_RESERVAS];
int total_reservas = 0;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void salvar_reservas() {
    FILE *arquivo = fopen(ARQUIVO_RESERVAS, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as reservas.\n");
        return;
    }

    for (int i = 0; i < total_reservas; i++) {
        fprintf(arquivo, "%s;%s;%d;%d\n",
                reservas[i].nome,
                reservas[i].cpf,
                reservas[i].dia,
                reservas[i].quantidade_pessoas);
    }

    fclose(arquivo);
}

void carregar_reservas() {
    FILE *arquivo = fopen(ARQUIVO_RESERVAS, "r");
    if (arquivo == NULL) {
        // O arquivo nÃ£o existe ainda, isso não é um erro.
        return;
    }

    while (fscanf(arquivo, "%99[^;];%14[^;];%d;%d\n",
                  reservas[total_reservas].nome,
                  reservas[total_reservas].cpf,
                  &reservas[total_reservas].dia,
                  &reservas[total_reservas].quantidade_pessoas) != EOF) {
        total_reservas++;
    }

    fclose(arquivo);
}


void fazer_reserva() {
    if (total_reservas >= MAX_RESERVAS) {
        printf("\nLimite de reservas atingido.\n");
        return;
    }

    printf("\n--- Fazer Reserva ---\n");
    printf("Digite o nome: ");
    limpar_buffer();
    fgets(reservas[total_reservas].nome, 100, stdin);
    reservas[total_reservas].nome[strcspn(reservas[total_reservas].nome, "\n")] = '\0';

    printf("Digite o CPF: ");
    fgets(reservas[total_reservas].cpf, 15, stdin);
    reservas[total_reservas].cpf[strcspn(reservas[total_reservas].cpf, "\n")] = '\0';

    do {
        printf("Digite o dia da reserva (1-Quinta, 2-Sexta, 3-Sábado, 4-Domingo): ");
        scanf("%d", &reservas[total_reservas].dia);
    } while (reservas[total_reservas].dia < 1 || reservas[total_reservas].dia > 4);

    printf("Digite a quantidade de pessoas: ");
    scanf("%d", &reservas[total_reservas].quantidade_pessoas);

    total_reservas++;
    salvar_reservas();
    printf("\nReserva feita com sucesso!\n");
}


void listar_reservas() {
    if (total_reservas == 0) {
        printf("\nNenhuma reserva cadastrada.\n");
        return;
    }

    printf("\n--- Listar Reservas ---\n");
    int i;
    for (i = 0; i < total_reservas; i++) {
        printf("Nome: %s\n", reservas[i].nome);
        printf("CPF: %s\n", reservas[i].cpf);
        printf("Dia: %d\n", reservas[i].dia);
        printf("Número de Pessoas: %d\n", reservas[i].quantidade_pessoas);
        printf("===============================\n");
    }
}

void total_pessoas_por_dia() {
    int dia, total_pessoas = 0;

    do {
        printf("\nDigite o dia da reserva para calcular (1-Quinta, 2-Sexta, 3-Sábado, 4-Domingo): ");
        scanf("%d", &dia);
    } while (dia < 1 || dia > 4);

    int i;
    for (i = 0; i < total_reservas; i++) {
        if (reservas[i].dia == dia) {
            total_pessoas += reservas[i].quantidade_pessoas;
        }
    }

    printf("\nTotal de pessoas reservadas para o dia %d: %d\n", dia, total_pessoas);
}


int main() {
    setlocale(LC_ALL, "");
    int opcao;
    carregar_reservas();

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Fazer Reserva\n");
        printf("2 - Listar Reservas\n");
        printf("3 - Total de Pessoas Por Dia\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        system("cls");

        switch (opcao) {
            case 1:
                fazer_reserva();
                break;
            case 2:
                listar_reservas();
                break;
            case 3:
                total_pessoas_por_dia();
                break;
            case 4:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção Inválida. Tente novamente.\n");
        }

        printf("\n");
        system("pause");
        system("cls");

    } while (opcao != 4);

    return 0;
}
