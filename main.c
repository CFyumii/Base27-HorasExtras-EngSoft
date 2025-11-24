#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FUNCIONARIOS 10
#define MAX_REGISTROS 50

// ============================================================
// ESTRUTURAS DE DADOS (Conforme RF01)
// ============================================================

typedef struct {
    int id;
    char nome[50];
    char login[20];
    char senha[20];
    float valorHoraBase;
    int ehGestor; // 1 = Gestor, 0 = Funcionário
} Funcionario;

typedef struct {
    int id;
    int idFuncionario;
    float horasTrabalhadas;
    int tipo; // 1 = 50% (Dia útil), 2 = 100% (Fim de semana/Feriado)
} HoraExtra;

// Variáveis Globais (Simulando Banco de Dados)
Funcionario funcionarios[MAX_FUNCIONARIOS];
HoraExtra horasExtras[MAX_REGISTROS];
int qtdFuncionarios = 0;
int qtdHorasExtras = 0;
Funcionario* usuarioLogado = NULL;

// ============================================================
// PROTÓTIPOS DAS FUNÇÕES (Mapeamento da Matriz)
// ============================================================
void inicializarDados();
bool login();
void verificarHorario(float horas); // RF03
float calcularValorExtra(float valorBase, float horas, int tipo); // RF04
void cadastrarHoraExtra(); // RF02
void mostrarResultados(); // RF05
void menuPrincipal();

// ============================================================
// FUNÇÃO MAIN
// ============================================================
int main() {
    inicializarDados(); // Cria dados fake para teste

    // Loop do Login
    while (true) {
        if (login()) {
            menuPrincipal();
            usuarioLogado = NULL; // Logout ao sair do menu
        } else {
            printf("\nEncerrando o sistema.\n");
            break;
        }
    }
    return 0;
}

// ============================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================

// Cria usuários iniciais para teste (Fake Login Setup)
void inicializarDados() {
    // Funcionario 1: Gestor
    funcionarios[0].id = 1;
    strcpy(funcionarios[0].nome, "Carlos Silva (Gestor)");
    strcpy(funcionarios[0].login, "admin");
    strcpy(funcionarios[0].senha, "123");
    funcionarios[0].valorHoraBase = 50.0;
    funcionarios[0].ehGestor = 1; // RF01: Campo ehGestor

    // Funcionario 2: Comum
    funcionarios[1].id = 2;
    strcpy(funcionarios[1].nome, "Joao Souza (Funcionario)");
    strcpy(funcionarios[1].login, "joao");
    strcpy(funcionarios[1].senha, "123");
    funcionarios[1].valorHoraBase = 30.0;
    funcionarios[1].ehGestor = 0; // RF01: Campo ehGestor

    qtdFuncionarios = 2;
}

// Função de Login "Fake"
bool login() {
    char loginInput[20];
    char senhaInput[20];

    printf("\n=== SISTEMA DE HORAS EXTRAS - LOGIN ===\n");
    printf("Usuarios teste: 'admin' ou 'joao' (senha: 123)\n");
    printf("Login: ");
    scanf("%s", loginInput);
    printf("Senha: ");
    scanf("%s", senhaInput);

    for (int i = 0; i < qtdFuncionarios; i++) {
        if (strcmp(funcionarios[i].login, loginInput) == 0 && 
            strcmp(funcionarios[i].senha, senhaInput) == 0) {
            usuarioLogado = &funcionarios[i];
            printf("\nBem-vindo, %s!\n", usuarioLogado->nome);
            
            // RF01: Diferenciação no Login
            if(usuarioLogado->ehGestor) {
                printf("Perfil: GESTOR (Acesso total)\n");
            } else {
                printf("Perfil: COLABORADOR (Acesso restrito)\n");
            }
            return true;
        }
    }

    printf("\nLogin ou senha invalidos!\n");
    return false; // Retornar false poderia perguntar se quer tentar de novo, aqui simplificado.
}

// RF03: Validar horário (Simulação da regra de corte ou validação lógica)
void verificarHorario(float horas) {
    // Na matriz original, isso valida horário de corte (13h/14h).
    // Aqui faremos uma validação lógica para garantir consistência.
    if (horas <= 0 || horas > 24) {
        printf("ERRO: Quantidade de horas invalida (RF03 Check).\n");
    } else {
        printf("Horario validado pelo sistema.\n");
    }
}

// RF04: Calcular valor financeiro (50% / 100%)
float calcularValorExtra(float valorBase, float horas, int tipo) {
    float multiplicador = 1.0;
    
    if (tipo == 1) {
        multiplicador = 1.5; // 50% extra
    } else if (tipo == 2) {
        multiplicador = 2.0; // 100% extra
    }

    return valorBase * horas * multiplicador;
}

// RF02: Registrar entrada de horas extras
void cadastrarHoraExtra() {
    if (qtdHorasExtras >= MAX_REGISTROS) {
        printf("Memoria cheia!\n");
        return;
    }

    int idFuncionarioAlvo;
    
    // Se for gestor, pode lançar para qualquer um. Se for funcionário, só pra ele mesmo.
    if (usuarioLogado->ehGestor) {
        printf("ID do Funcionario (1 ou 2): ");
        scanf("%d", &idFuncionarioAlvo);
    } else {
        idFuncionarioAlvo = usuarioLogado->id;
    }

    float horas;
    int tipo;

    printf("Quantidade de horas extras: ");
    scanf("%f", &horas);
    verificarHorario(horas); // Aplica RF03

    if (horas > 0 && horas <= 24) {
        printf("Tipo de Hora Extra:\n1 - Dia util (50%%)\n2 - Domingo/Feriado (100%%)\nOpcao: ");
        scanf("%d", &tipo);

        if (tipo == 1 || tipo == 2) {
            horasExtras[qtdHorasExtras].id = qtdHorasExtras + 1;
            horasExtras[qtdHorasExtras].idFuncionario = idFuncionarioAlvo;
            horasExtras[qtdHorasExtras].horasTrabalhadas = horas;
            horasExtras[qtdHorasExtras].tipo = tipo;
            
            qtdHorasExtras++;
            printf("Hora extra cadastrada com sucesso!\n");
        } else {
            printf("Tipo invalido.\n");
        }
    }
}

// RF05: Gerar relatório final consolidado
void mostrarResultados() {
    // Apenas Gestor pode ver relatório de todos (Regra de negócio comum baseada no RF01)
    if (!usuarioLogado->ehGestor) {
        printf("\n[ACESSO NEGADO] Apenas Gestores podem ver o relatorio consolidado.\n");
        return;
    }

    printf("\n=== RELATORIO CONSOLIDADO (RF05) ===\n");
    printf("%-20s | %-10s | %-10s | %-10s\n", "Funcionario", "Horas", "Tipo", "Valor Total");
    printf("---------------------------------------------------------------\n");

    float totalGeral = 0;

    for (int i = 0; i < qtdHorasExtras; i++) {
        // Buscar nome e valor hora do funcionário
        char nomeFunc[50];
        float valorHora = 0;
        
        for(int j=0; j<qtdFuncionarios; j++) {
            if(funcionarios[j].id == horasExtras[i].idFuncionario) {
                strcpy(nomeFunc, funcionarios[j].nome);
                valorHora = funcionarios[j].valorHoraBase;
                break;
            }
        }

        float valorFinal = calcularValorExtra(valorHora, horasExtras[i].horasTrabalhadas, horasExtras[i].tipo);
        totalGeral += valorFinal;

        char descTipo[10];
        sprintf(descTipo, "%s", (horasExtras[i].tipo == 1 ? "50%" : "100%"));

        printf("%-20s | %-10.2f | %-10s | R$ %-10.2f\n", 
            nomeFunc, 
            horasExtras[i].horasTrabalhadas, 
            descTipo, 
            valorFinal);
    }
    printf("---------------------------------------------------------------\n");
    printf("CUSTO TOTAL DE HORAS EXTRAS: R$ %.2f\n", totalGeral);
}

void menuPrincipal() {
    int opcao = 0;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar Hora Extra (RF02)\n");
        printf("2. Gerar Relatorio Financeiro (RF05 - Gestor)\n");
        printf("0. Sair / Logout\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarHoraExtra();
                break;
            case 2:
                mostrarResultados();
                break;
            case 0:
                printf("Fazendo logout...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}