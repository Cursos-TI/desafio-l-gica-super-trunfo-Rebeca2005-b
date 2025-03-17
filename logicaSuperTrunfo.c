#include <stdio.h>
#include <string.h>

#define MAX_CIDADES 32

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char codigo[4];  // Ex: "A01"
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} Cidade;

// Função para cadastrar uma cidade
void cadastrarCidade(Cidade *cidade) {
    printf("\nDigite o código da cidade (Ex: A01): ");
    scanf("%s", cidade->codigo);
    
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", cidade->nome);
    
    printf("Digite a população: ");
    scanf("%d", &cidade->populacao);
    
    printf("Digite a área (em km²): ");
    scanf("%f", &cidade->area);
    
    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &cidade->pib);
    
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);
}

// Função para exibir os dados de uma cidade
void exibirCidade(Cidade cidade) {
    printf("\nCódigo: %s\n", cidade.codigo);
    printf("Nome: %s\n", cidade.nome);
    printf("População: %d\n", cidade.populacao);
    printf("Área: %.2f km²\n", cidade.area);
    printf("PIB: %.2f bilhões\n", cidade.pib);
    printf("Pontos Turísticos: %d\n", cidade.pontos_turisticos);
}

// Função para buscar uma cidade pelo código
int buscarCidade(Cidade cidades[], int total, char codigo[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(cidades[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1; // Cidade não encontrada
}

// Função para comparar duas cidades com base em um atributo
void compararCartas(Cidade c1, Cidade c2, int atributo) {
    float valor1, valor2;
    int menorGanha = 0; // Se 1, o menor valor vence

    switch (atributo) {
        case 1: valor1 = c1.populacao; valor2 = c2.populacao; break;
        case 2: valor1 = c1.area; valor2 = c2.area; break;
        case 3: valor1 = c1.pib; valor2 = c2.pib; break;
        case 4: valor1 = c1.pontos_turisticos; valor2 = c2.pontos_turisticos; break;
        case 5: // Densidade populacional (população / área)
            valor1 = c1.populacao / c1.area;
            valor2 = c2.populacao / c2.area;
            menorGanha = 1;
            break;
        default:
            printf("\nAtributo inválido!\n");
            return;
    }

    printf("\nComparando %s (%s) vs %s (%s):\n", c1.nome, c1.codigo, c2.nome, c2.codigo);
    printf("Valores: %.2f vs %.2f\n", valor1, valor2);

    if ((menorGanha && valor1 < valor2) || (!menorGanha && valor1 > valor2)) {
        printf("Vencedora: %s (%s)!\n", c1.nome, c1.codigo);
    } else if ((menorGanha && valor2 < valor1) || (!menorGanha && valor2 > valor1)) {
        printf("Vencedora: %s (%s)!\n", c2.nome, c2.codigo);
    } else {
        printf("Empate!\n");
    }
}

int main() {
    Cidade cidades[MAX_CIDADES];
    int totalCidades = 0;
    int opcao;

    do {
        printf("\n--- Super Trunfo - Países ---\n");
        printf("1. Cadastrar cidade\n");
        printf("2. Comparar cartas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (totalCidades < MAX_CIDADES) {
                cadastrarCidade(&cidades[totalCidades]);
                totalCidades++;
            } else {
                printf("Limite de cidades atingido!\n");
            }
        } else if (opcao == 2) {
            if (totalCidades < 2) {
                printf("É necessário cadastrar pelo menos 2 cidades para comparar!\n");
                continue;
            }

            char codigo1[4], codigo2[4];
            printf("\nDigite o código da primeira cidade: ");
            scanf("%s", codigo1);
            printf("Digite o código da segunda cidade: ");
            scanf("%s", codigo2);

            int idx1 = buscarCidade(cidades, totalCidades, codigo1);
            int idx2 = buscarCidade(cidades, totalCidades, codigo2);

            if (idx1 == -1 || idx2 == -1) {
                printf("Uma ou ambas as cidades não foram encontradas!\n");
                continue;
            }

            printf("\nEscolha o atributo para comparação:\n");
            printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional\n");
            printf("Digite o número do atributo: ");
            int atributo;
            scanf("%d", &atributo);

            compararCartas(cidades[idx1], cidades[idx2], atributo);
        }
    } while (opcao != 3);

    printf("Obrigado por jogar Super Trunfo - Países!\n");
    return 0;
}
