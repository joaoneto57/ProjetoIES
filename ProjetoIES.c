#include <stdio.h>
#include <time.h>

#define MAX_CHAMADOS 10

typedef struct {
    int guiche;
    int senha;
    char tipo;
    char hora[20];
} Chamado;

Chamado painelChamados[MAX_CHAMADOS];
int indicePainel = 0;

void gerarSenha(int *prioridade, int *normal) {
    int tipoSenha;
    time_t agora;
    struct tm *local;

    time(&agora);
    local = localtime(&agora);

    printf("Para gerar a senha digite:  1- Prioridade  2- Normal  0- Voltar\n");
    scanf("%d", &tipoSenha);

    if (tipoSenha == 1) {
        printf("Senha: P%d\n", *prioridade);
        printf("Data atual: %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        printf("Hora atual: %02d:%02d\n\n", local->tm_hour, local->tm_min);
        (*prioridade)++;
    } else if (tipoSenha == 2) {
        printf("Senha: N%d\n", *normal);
        printf("Data atual: %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        printf("Hora atual: %02d:%02d\n\n", local->tm_hour, local->tm_min);
        (*normal)++;
    }
}

void registrarChamado(int guiche, int senha, char tipo) {
    time_t agora;
    struct tm *local;
    
    time(&agora);
    local = localtime(&agora);


    painelChamados[indicePainel].guiche = guiche;
    painelChamados[indicePainel].senha = senha;
    painelChamados[indicePainel].tipo = tipo;
    strftime(painelChamados[indicePainel].hora, sizeof(painelChamados[indicePainel].hora), "%d/%m/%Y %H:%M:%S", local);


    indicePainel = (indicePainel + 1) % MAX_CHAMADOS;
}

void mostrarPainelChamados() {
    printf("\n--- Painel de Chamados ---\n");


    if (indicePainel > 0) {
        Chamado maisRecente = painelChamados[(indicePainel - 1 + MAX_CHAMADOS) % MAX_CHAMADOS];
        printf("Chamado mais recente: \n");
        printf("Senha: %c%d, Guichê: %d\n", maisRecente.tipo, maisRecente.senha, maisRecente.guiche);
        printf("Hora: %s\n", maisRecente.hora);
    } else {
        printf("Nenhum chamado registrado ainda.\n");
    }


    printf("\nÚltimos chamados:\n");
    for (int i = 0; i < MAX_CHAMADOS; i++) {
        int index = (indicePainel - 1 - i + MAX_CHAMADOS) % MAX_CHAMADOS;
        if (indicePainel > 0 && painelChamados[index].hora[0] != '\0') {
            Chamado chamado = painelChamados[index];
            printf("Senha: %c%d, Guichê: %d\n", chamado.tipo, chamado.senha, chamado.guiche);
            printf("Hora: %s\n", chamado.hora);
        }
    }
}

void chamarSenha(int chamadasPrioridade, int chamadasNormal, int totalPrioridade, int totalNormal) {
    int guiche;
    char tipo;
    int senha;

    if (chamadasPrioridade < totalPrioridade) {
        tipo = 'P';
        senha = chamadasPrioridade + 100;
        printf("Informe o guichê para a senha P%d: ", senha);
        scanf("%d", &guiche);
        printf("\nChamando P%d no guichê %d\n", senha, guiche);
        registrarChamado(guiche, senha, tipo);
    } else if (chamadasNormal < totalNormal) {
        tipo = 'N';
        senha = chamadasNormal + 100;
        printf("Informe o guichê para a senha N%d: ", senha);
        scanf("%d", &guiche);
        printf("\nChamando N%d no guichê %d\n", senha, guiche);
        registrarChamado(guiche, senha, tipo);
    } else {
        printf("Nenhuma senha para chamar no momento.\n");
    }
}

int main() {
    int prioridade = 100, normal = 100;
    int totalPrioridade = 0, totalNormal = 0;
    int chamadasPrioridade = 0, chamadasNormal = 0;
    int opcao;

    do {
        printf("Menu: 1- Gerar Senha  2- Chamar Senha  3- Mostrar Painel  0- Sair\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            gerarSenha(&prioridade, &normal);
            totalPrioridade++;
        } else if (opcao == 2) {
            chamarSenha(chamadasPrioridade, chamadasNormal, totalPrioridade, totalNormal);
            chamadasPrioridade += (opcao == 1 && chamadasPrioridade < totalPrioridade);
            chamadasNormal += (opcao == 2 && chamadasNormal < totalNormal);
        } else if (opcao == 3) {
            mostrarPainelChamados();
        }
    } while (opcao != 0);

    printf("Programa encerrado.\n");

    return 0;
}
