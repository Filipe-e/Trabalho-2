#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "./Includes/types.h"
#include "./Includes/menus.h"

int menu_industria(void){
    int opcao;

    printf("\t| Menu - Industria |\n");
    printf("\033[1;32m[ 1 ]\033[0m - Cadastrar\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar industria\n");
    printf("\033[1;32m[ 3 ]\033[0m - Selecionar industria\n");
    printf("\033[1;32m[ 0 ]\033[0m - Sair\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
} 

int menu_setor(int industria_selecionada){
    int opcao;

    printf("\t| Menu - Setor |\n");
    printf("Cadastro de setores da industria: %i\n", industria_selecionada);
    printf("\033[1;32m[ 1 ]\033[0m - Cadastrar\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar \n");
    printf("\033[1;32m[ 3 ]\033[0m - Selecionar setores\n");
    printf("\033[1;32m[ 4 ]\033[0m - Pesquisar um setor\n");
    printf("\033[1;32m[ 5 ]\033[0m - Relatorio dos setores\n");
    printf("\033[1;32m[ 6 ]\033[0m - Relatorio de media dos setores\n");
    printf("\033[1;32m[ 7 ]\033[0m - Exportar relatorio dos setores em txt\n");
    printf("\033[1;32m[ 8 ]\033[0m - Exportar elatorio de media dos setores em txt\n");
    printf("\033[1;32m[ 9 ]\033[0m - Exportar relatorio dos setores em csv\n");
    printf("\033[1;32m[ 10 ]\033[0m - Exportar relatorio de media dos setores em csv\n");
    printf("\033[1;32m[ 11 ]\033[0m - Exportar relatorio de leitura por setor em html\n");
    printf("\033[1;32m[ 12 ]\033[0m - Exportar relatorio da media dos setores em html\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}

int menu_setor_sensor(int industria){
    int opcao;

    printf("\t| Menu - Industria %i |\n", industria);
    printf("\033[1;32m[ 1 ]\033[0m - Menu de setores\n");
    printf("\033[1;32m[ 2 ]\033[0m - Menu de sensores\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}
int menu_opcao_setor_selecionado(int opcao_setor_selecionado){
    int opcao;

    printf("\t| Menu - Setor %i |\n", opcao_setor_selecionado);
    printf("\033[1;32m[ 1 ]\033[0m - Cadastrar um sensor\n");
    printf("\033[1;32m[ 2 ]\033[0m - Selecionar um sensor\n");
    printf("\033[1;32m[ 3 ]\033[0m - Mostrar sensores disponiveis\n");
    printf("\033[1;32m[ 4 ]\033[0m - [GERAL] Relatorio dos sensores cadastrados\n");
    printf("\033[1;32m[ 5 ]\033[0m - [POR TIPO] Relatorio dos sensores cadastrados\n");
    printf("\033[1;32m[ 6 ]\033[0m - [GERAL] Relatorio de variacao dos sensores cadastrados\n");
    printf("\033[1;32m[ 7 ]\033[0m - Exportar relatorio de variacao por setor\n");
    printf("\033[1;32m[ 8 ]\033[0m - Exportar relatorio de leitura pelo setor\n");
    printf("\033[1;32m[ 9 ]\033[0m - Exportar relatorio de leitura por tipo\n");
    printf("\033[1;32m[ 10 ]\033[0m - Exportar relatorio de variacao por setor em csv\n");
    printf("\033[1;32m[ 11 ]\033[0m - Exportar relatorio de leitura pelo setor em csv\n");
    printf("\033[1;32m[ 12 ]\033[0m - Exportar relatorio de leitura por tipo em csv\n");
    printf("\033[1;31m[ 13 ] - REMOVER UM SENSOR]\033[0m\n");
    printf("\033[1;32m[ 14 ]\033[0m - Exportar relatorio de leitura pelo setor em hmtl\n");
    printf("\033[1;32m[ 15 ]\033[0m - Exportar relatorio de leitura por tipo em hmtl\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}
int menu_escolha_setor(){
    int opcao;
    
    printf("\033[1;34mSetor escolhido:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}
int menu_sensores(int industria_selecionada){
    int opcao;

    printf("\t| Menu - Sensores |\n");
    printf("Cadastro de sensores da industria: %i\n", industria_selecionada);
    printf("\033[1;32m[ 1 ]\033[0m - Cadastrar\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar\n");
    printf("\033[1;32m[ 3 ]\033[0m - Pesquisar um sensor por tipo\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}
int menu_sensor_selecionado(void){
    int opcao;
    
    printf("\t| Menu - Monitoramento |\n");
    printf("\033[1;32m[ 1 ]\033[0m - Efetuar Leitura\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar Leituras\n");
    printf("\033[1;32m[ 3 ]\033[0m - Relatorio de variacao\n");
    printf("\033[1;32m[ 4 ]\033[0m - Exportar lista de Leituras\n");
    printf("\033[1;32m[ 5 ]\033[0m - Exportar relatorio de variacao\n");
    printf("\033[1;32m[ 6 ]\033[0m - Exportar lista de Leituras em csv\n");
    printf("\033[1;32m[ 7 ]\033[0m - Exportar relatorio de variacao em csv\n");
    printf("\033[1;32m[ 8 ]\033[0m - Exportar relatorio de variacao em html\n");
    printf("\033[1;32m[ 9 ]\033[0m - Exportar relatorio de Leituras em html\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}