
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// definindo quantidade máxima de de indústrias
#define T_MAX_INDUSTRIAS 15
// definindo quantidade máxima de sensores por setor
#define T_MAX_SENSORES 3
// definindo quantidade máxima de setores por indústria
#define T_MAX_SETORES 5
// definindo quantidade máxima de tipos de sensores
#define T_MAX_TIPOS_SENSORES 15
// definindo tamanho máximo para string
#define T_MAX_STR 500
// definindo string
typedef char string[T_MAX_STR];


// definindo um tipo para sensor
typedef struct tipo_sensores{
    int id_do_sensor;
    string tipo;
    float faixa_leitura[2];
    int numero_da_leitura;
    float primeira_leitura;
    string horario_1;
    float segunda_leitura;
    string horario_2;
    float variacao_leitura;
    float media;
    struct tipo_sensores *prox;
}sensores_t;




// definindo um tipo  setor
typedef struct setores{
    int id_do_setor;
    string descricao;
    sensores_t *sensores_do_setor;
    int qtd_sensores_no_setor;
    struct setores *prox;
}setores_t;

// definindo um tipo para uma planta de indústria
typedef struct planta_industria{
    int id_da_planta;
    setores_t *setores_da_planta;
    sensores_t *tipos_de_sensores;
    int qtd_setores_na_planta;
    int qtd_sensores_na_planta;
    struct planta_industria *prox;
}planta_industria_t;



// Industrias
int menu_industria(void);
planta_industria_t *cadastrar_industria(int qtd_industrias);
void listar_industrias(planta_industria_t *industria, int qtd_industrias);
int menu_setor_sensor(int industria);
// cria uma planta vazia
planta_industria_t *criar_planta_de_industria(void);

// setores
int menu_setor(int industria_selecionada);
int menu_opcao_setor_selecionado(int opcao_setor_selecionado);
setores_t cadastrar_setor(planta_industria_t *industria);
void cadastrar_sensor_no_setor(planta_industria_t *industria, int setor, int selecao);
void listar_setores_por_industria(planta_industria_t *industria);
int menu_escolha_setor(planta_industria_t *industria);
void listar_sensores_por_setor(planta_industria_t *industria, int setor);
void relatorio_de_leitura_por_setor(planta_industria_t *industria);
void relatorio_de_variacao_por_setor(planta_industria_t *industria, int setor);
void relatorio_de_leitura_pelo_setor(planta_industria_t *industria, int setor);
void pesquisar_setor_por_descricao(planta_industria_t *industria);
// cria um setor vazio
setores_t criar_setor_de_industria(void);


//sensores
int menu_sensores(int industria_slecionada);
int menu_sensor_selecionado(void);
void leitura_do_sensor(sensores_t *sensor);
void horario_da_leitura(sensores_t *sensor, int leitura);
void relatorio_de_variacao_por_sensor(planta_industria_t *industria, int setor, int sensor);
void relatorio_de_leitura_por_tipo(planta_industria_t *industria, int setor);
void relatorio_da_media_dos_setores(planta_industria_t *industria);
void relatorio_de_leitura_por_sensor(planta_industria_t *industria, int setor, int sensor);
void pesquisar_sensor_por_tipo(planta_industria_t *industria);
sensores_t cadastrar_sensor(planta_industria_t *industria);
void listar_sensores_por_industria(planta_industria_t *industria);

// funções auxiliares
void retirar_enter(string str);
void esperar_prosseguir(void);
void limpar_tela(void);



int main(){
    int qtd_industrias = 0;
    int opcao_main, setor_selecionado;
    string selecao_temp;
    planta_industria_t *industrias;
    do{
        limpar_tela();
        opcao_main = menu_industria();
        int selecao1, selecao2, selecao3, opcao_setor_selecionado, sensor_selecionado; 
        int opcao_setor, opcao_sensor;
        switch (opcao_main){
            case 1:
                limpar_tela();
                if(qtd_industrias < T_MAX_INDUSTRIAS){
                    cadastrar_industria(qtd_industrias);
                    qtd_industrias++;
                }
                else{
                    printf("\033[1;31mLimite maximo de industrias atingido!!!\033[0m\n");
                    esperar_prosseguir();
                }
                limpar_tela();
                break;
            case 2:
                limpar_tela();
                if(qtd_industrias > 0){
                    //listar_industrias(industrias); // Mudar pra alloc dinamic 
                }
                else{
                    printf("\033[31mAinda nao ha industrias cadastradas\n\033[0m");
                }
                esperar_prosseguir();
                break;
            case 3:
                limpar_tela();
                if(qtd_industrias > 0){
                    printf("Industrias disponiveis: \n");
                    listar_industrias(industrias, qtd_industrias); // Mudar pra alloc dinamic 
                    printf("Industria selecionada: ");
                    while(scanf("%i", &selecao1) != 1){
                        printf("Entrada invalida! Digite novamente: ");
                        while(getchar() != '\n'); // limpa
                    }
                    if(selecao1 < qtd_industrias){
                        do{
                            usleep(1000000);
                            limpar_tela();
                            //selecao2 = menu_setor_sensor(selecao1);
                            switch (selecao2){
                                case 1:
                                    do{
                                        limpar_tela();
                                        // opcao_setor = menu_setor(selecao1);
                                        
                                        switch (opcao_setor){
                                            case 1:
                                                getchar();
                                                // industrias[selecao1].setores_da_planta[industrias[selecao1].qtd_setores_na_planta] = cadastrar_setor(&industrias[selecao1]);
                                                break;
                                            case 2: 
                                                /*
                                                if(industrias[selecao1].qtd_setores_na_planta > 0){
                                                    listar_setores_por_industria(&industrias[selecao1]);
                                                    esperar_prosseguir();
                                                }
                                                else{
                                                    getchar();
                                                    printf("\033[1;31mAinda nao ha setores cadastrados!\033[0m\n");
                                                    printf("\033[1;34mDeseja cadastrar um novo setor? [S/N] \033[0m");
                                                    fgets(selecao_temp, T_MAX_STR, stdin);
                                                    retirar_enter(selecao_temp);
                                                    if(!strcmp(selecao_temp, "S")){
                                                        industrias[selecao1].setores_da_planta[industrias[selecao1].qtd_setores_na_planta] = cadastrar_setor(&industrias[selecao1]);
                                                    }
                                                }
                                                break;
                                                */
                                            case 3:
                                            /*
                                                if(industrias[selecao1].qtd_setores_na_planta > 0){
                                                        printf("Setores diposniveis:\n");
                                                        listar_setores_por_industria(&industrias[selecao1]);    
                                                        setor_selecionado = menu_escolha_setor(&industrias[selecao1]);
                                                        if(setor_selecionado < industrias[selecao1].qtd_setores_na_planta){
                                                            do{
                                                                limpar_tela();
                                                                opcao_setor_selecionado = menu_opcao_setor_selecionado(setor_selecionado);
                                                                switch (opcao_setor_selecionado)
                                                                {
                                                                case 1:
                                                                    if(industrias[selecao1].qtd_sensores_na_planta > 0){
                                                                            cadastrar_sensor_no_setor(&industrias[selecao1], setor_selecionado, selecao1);
                                                                            esperar_prosseguir();
                                                                        
                                                                        
                                                                    }
                                                                    else{
                                                                        getchar();
                                                                        printf("\033[1;31mAinda nao ha sensores cadastrados!\033[0m\n");
                                                                        do{    
                                                                            printf("\033[1;34mDeseja cadastrar um novo sensor? [S/N] \033[0m");
                                                                            fgets(selecao_temp, T_MAX_STR, stdin);
                                                                            retirar_enter(selecao_temp);
                                                                        }while(strcmp(selecao_temp, "S") && strcmp(selecao_temp, "N"));
                                                                        if(!strcmp(selecao_temp, "S")){
                                                                            industrias[selecao1].tipos_de_sensores[industrias[selecao1].qtd_sensores_na_planta] = cadastrar_sensor(&industrias[selecao1]);
                                                                        }
                                                                    }
                                                                    break;
                                                                case 2:
                                                                    if(industrias[selecao1].setores_da_planta[setor_selecionado].qtd_sensores_no_setor > 0){
                                                                        listar_sensores_por_setor(&industrias[selecao1], setor_selecionado);
                                                                        printf("\033[1;34mOpcao escolhida:\033[0m ");
                                                                        while(scanf("%i", &sensor_selecionado) != 1){
                                                                            printf("Entrada invalida! Digite novamente: ");
                                                                            while(getchar() != '\n'); // limpa
                                                                        }
                                                                        if(sensor_selecionado < industrias[selecao1].setores_da_planta[setor_selecionado].qtd_sensores_no_setor){
                                                                            do{
                                                                                limpar_tela();
                                                                                opcao_sensor = menu_sensor_selecionado();
                                                                                switch (opcao_sensor)
                                                                                {
                                                                                case 1:
                                                                                    if(industrias[selecao1].setores_da_planta[setor_selecionado].sensores_do_setor[sensor_selecionado].numero_da_leitura < 3){
                                                                                        leitura_do_sensor(&industrias[selecao1].setores_da_planta[setor_selecionado].sensores_do_setor[sensor_selecionado]);
                                                                                    }
                                                                                    else{
                                                                                        printf("Leituras ja efetuadas!");
                                                                                        esperar_prosseguir();
                                                                                    }
                                                                                    break;
                                                                                case 2:
                                                                                    relatorio_de_leitura_por_sensor(&industrias[selecao1], setor_selecionado, sensor_selecionado);
                                                                                    esperar_prosseguir();
                                                                                    break;
                                                                                case 3:
                                                                                    relatorio_de_variacao_por_sensor(&industrias[selecao1], setor_selecionado, sensor_selecionado);
                                                                                    esperar_prosseguir();
                                                                                    break;
                                                                                case 0: break;
                                                                                default:
                                                                                    break;
                                                                                }
                                                                            }while(opcao_sensor);
                                                                        }
                                                                        else{
                                                                            printf("\033[31mSensor %i nao encontrado!!\033[0m\n", sensor_selecionado);
                                                                            esperar_prosseguir();
                                                                        }
                                                                    }
                                                                    else{
                                                                        printf("\033[31mSem sensores cadastrados!!\033[0m\n");
                                                                        esperar_prosseguir();
                                                                    }
                                                                    break;
                                                                case 3:
                                                                    listar_sensores_por_setor(&industrias[selecao1], setor_selecionado);
                                                                    esperar_prosseguir();
                                                                    break;
                                                                case 4:
                                                                    relatorio_de_leitura_pelo_setor(&industrias[selecao1], setor_selecionado);
                                                                    esperar_prosseguir();
                                                                    break;
                                                                case 5:
                                                                    relatorio_de_leitura_por_tipo(&industrias[selecao1], setor_selecionado);
                                                                    esperar_prosseguir();
                                                                    break;
                                                                case 6:
                                                                    relatorio_de_variacao_por_setor(&industrias[selecao1], setor_selecionado);
                                                                    esperar_prosseguir();
                                                                    break;
                                                                case 0: break;
                                                                default:
                                                                    printf("\033[1;31mOpcao invalida!!!\033[0m\n");
                                                                    usleep(1000000);
                                                                    break;
                                                                }    
                                                            }while(opcao_setor_selecionado);
                                                        }
                                                        else{
                                                            printf("\033[1;31mNao ha setor %i no catalogo\n\033[0m", setor_selecionado);
                                                            esperar_prosseguir();
                                                        }
                                                    
                                                }
                                                else{
                                                    getchar();
                                                    printf("\033[1;31mAinda nao ha setores cadastrados!\033[0m\n");
                                                    printf("\033[1;34mDeseja cadastrar um novo setor? [S/N] \033[0m");
                                                    fgets(selecao_temp, T_MAX_STR, stdin);
                                                    retirar_enter(selecao_temp);
                                                    if(!strcmp(selecao_temp, "S")){
                                                        industrias[selecao1].setores_da_planta[industrias[selecao1].qtd_setores_na_planta] = cadastrar_setor(&industrias[selecao1]);
                                                    }
                                                }
                                                break;
                                                */
                                            case 4:
                                                //pesquisar_setor_por_descricao(&industrias[selecao1]);
                                                esperar_prosseguir();
                                                break;
                                            case 5:
                                                //relatorio_de_leitura_por_setor(&industrias[selecao1]);
                                                esperar_prosseguir();
                                                break;
                                            case 6:
                                                //relatorio_da_media_dos_setores(&industrias[selecao1]);
                                                esperar_prosseguir();
                                                break;
                                            case 0: break;
                                            default:
                                                printf("\033[1;31mOpcao invalida!!!\033[0m\n");
                                                usleep(1000000);
                                                break;
                                        }
                                    }while(opcao_setor);
                                    break;
                                case 2:
                                    do{
                                        limpar_tela();
                                        selecao3 = menu_sensores(selecao1);
                                        switch (selecao3)
                                        {
                                        case 1:
                                            getchar();
                                            //industrias[selecao1].tipos_de_sensores[industrias[selecao1].qtd_sensores_na_planta] = cadastrar_sensor(&industrias[selecao1]);
                                            break;
                                        case 2:
                                            /*
                                            if(industrias[selecao1].qtd_sensores_na_planta > 0){
                                                listar_sensores_por_industria(&industrias[selecao1]);
                                                esperar_prosseguir();}
                                            else{ 
                                                getchar();
                                                printf("\033[1;31mAinda nao ha sensores cadastrados!\033[0m\n");
                                                printf("\033[1;34mDeseja cadastrar um novo sensor? [S/N] \033[0m");
                                                fgets(selecao_temp, T_MAX_STR, stdin);
                                                retirar_enter(selecao_temp);
                                                if(!strcmp(selecao_temp, "S")){
                                                    industrias[selecao1].tipos_de_sensores[industrias[selecao1].qtd_sensores_na_planta] = cadastrar_sensor(&industrias[selecao1]);
                                                }
                                            }
                                            */
                                            break;
                                        case 3:
                                            // pesquisar_sensor_por_tipo(&industrias[selecao1]);
                                            esperar_prosseguir();
                                            break;
                                        case 0: 
                                            break;
                                        default:
                                            printf("\033[1;31mOpcao invalida!!!\033[0m");
                                            usleep(1000000);
                                            break;
                                        }
                                    
                                    }while(selecao3);
                                    break;
                                
                                case 0: break;
                                default:
                                    printf("\033[1;31mOpcao invalida!!!\033[0m");
                                    usleep(1000000);
                                    break;
                            }
                        } while(selecao2);
                    }
                    else{
                        printf("\033[1;31mNao ha industria %i no catalogo\n\033[0m", selecao1);
                        esperar_prosseguir();  
                    }
                }
                else{
                    printf("\033[31mAinda nao ha industrias cadastradas\n\033[0m");
                    esperar_prosseguir();    
                }
                break;
                        
            case 0: break;
            
            default:
                printf("\033[1;31mOpcao invalida!!!\033[0m");
                usleep(1000000);
                break;
        }

    }while(opcao_main);
}



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


planta_industria_t *criar_planta_de_industria(){
    planta_industria_t *industria_zerada;

    industria_zerada = malloc(sizeof(planta_industria_t));

    industria_zerada->qtd_sensores_na_planta = 0;
    industria_zerada->qtd_setores_na_planta = 0;
    industria_zerada->prox = NULL;
    industria_zerada->setores_da_planta = NULL;
    industria_zerada->tipos_de_sensores = NULL;
    return industria_zerada;
}

planta_industria_t *cadastrar_industria(int qtd_industrias){
    planta_industria_t *industria_auxiliar = criar_planta_de_industria();
    industria_auxiliar->id_da_planta = qtd_industrias;
    printf("Cadastrando a industria: %i\n", industria_auxiliar->id_da_planta);
    printf("\033[1;32mCadastro realizado com sucesso!!\033[0m\t\n");
    usleep(1500000);
    return industria_auxiliar;
}

void inserir_industria(planta_industria_t **industrias, planta_industria_t *nova_industria){
    
    nova_industria->prox = *industrias;
    *industrias = nova_industria;
}

void listar_industrias(planta_industria_t *industria, int qtd_industrias){
    printf("===================\n");
    printf("Lista de Industrias: \n");
    for(industria; industria != NULL; industria = industria->prox){
        printf("Industria \033[1;32m[%i]\033[0m\n", industria->id_da_planta);
        printf("Quantidade de setores cadastrados\t \033[1;32m%i\033[0m\n", industria->qtd_setores_na_planta);
        printf("Quantidade de sensores cadastrados\t \033[1;32m%i\033[0m\n", industria->qtd_sensores_na_planta);
    }
    printf("===================\n\n");
}

int menu_setor(int industria_slecionada){
    int opcao;
    printf("\t| Menu - Setor |\n");

    printf("Cadastro de setores da industria: %i\n", industria_slecionada);

    printf("\033[1;32m[ 1 ]\033[0m - Cadastrar\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar \n");
    printf("\033[1;32m[ 3 ]\033[0m - Selecionar setores\n");
    printf("\033[1;32m[ 4 ]\033[0m - Pesquisar um setor\n");
    printf("\033[1;32m[ 5 ]\033[0m - Relatorio dos setores\n");
    printf("\033[1;32m[ 6 ]\033[0m - Relatorio de media dos setores\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }

    return opcao;
}

setores_t criar_setor_de_industria(void){
    setores_t setor_zerado;

    setor_zerado.qtd_sensores_no_setor = 0;
    setor_zerado.descricao[0] = '\0';
    return setor_zerado;
}

setores_t cadastrar_setor(planta_industria_t *industria){
    if(industria->qtd_setores_na_planta < 5){
        setores_t setor_auxiliar = criar_setor_de_industria();
        setor_auxiliar.id_do_setor = industria->qtd_setores_na_planta;
        industria->qtd_setores_na_planta = industria->qtd_setores_na_planta + 1; //atualizando a quantidade de setores na industria selecionada
        printf("| Cadastro do setor %i |\n", setor_auxiliar.id_do_setor);
        printf("Descricao do setor:\t\t ");
        fgets(setor_auxiliar.descricao, T_MAX_STR, stdin);
        retirar_enter(setor_auxiliar.descricao);
        return setor_auxiliar;
    }
    else{
        printf("\033[31mQuantidade maxima de setores atingida!!\033[0m");
        usleep(1000000);
    }
}



void listar_setores_por_industria(planta_industria_t *industria){
    printf("===================\n");
    printf("Lista de Setores: \n");
    for(int i = 0; i < industria->qtd_setores_na_planta; i++){
        printf("Setor:\t \033[1;32m[%i]\033[0m\n", i);
        printf("Descricao:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[i].descricao);
        printf("Quantidade de sensores no setor: \033[1;32m%i\033[0m\n", industria->setores_da_planta[i].qtd_sensores_no_setor);
    }
    printf("===================\n\n");
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


int menu_escolha_setor(planta_industria_t *industria){
    int opcao;
    
    
    printf("\033[1;34mSetor escolhido:\033[0m ");
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
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
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

sensores_t criar_sensor_de_industria(void){
    sensores_t sensor_zerado;

    sensor_zerado.faixa_leitura[0] = 0;
    sensor_zerado.faixa_leitura[1] = 0;
    sensor_zerado.numero_da_leitura = 1;
    sensor_zerado.tipo[0] = '\0';
    sensor_zerado.variacao_leitura = 0;
    sensor_zerado.media = 0;
    return sensor_zerado;
}


sensores_t cadastrar_sensor(planta_industria_t *industria){
    sensores_t sensor_auxiliar = criar_sensor_de_industria();
    string escolha_temp;
    if(industria->qtd_sensores_na_planta < 15){
        sensor_auxiliar.id_do_sensor = industria->qtd_sensores_na_planta;
        industria->qtd_sensores_na_planta = industria->qtd_sensores_na_planta + 1; //atualizando a quantidade de sensores na industria selecionada
        printf("| Cadastro do tipo de sensor %i |\n", sensor_auxiliar.id_do_sensor);
        printf("Tipo do sensor:\t\t ");
        fgets(sensor_auxiliar.tipo, T_MAX_STR, stdin);
        printf("Faixa de leitura minima do sensor:\t ");
        retirar_enter(sensor_auxiliar.tipo);
        while(scanf("%f", &sensor_auxiliar.faixa_leitura[0]) != 1){
            printf("Entrada invalida! Digite novamente: ");
            while(getchar() != '\n'); // limpa
        }
        printf("Faixa de leitura maxima do sensor:\t ");
        while(scanf("%f", &sensor_auxiliar.faixa_leitura[1]) != 1){
            printf("Entrada invalida! Digite novamente: ");
            while(getchar() != '\n'); // limpa
        }
        getchar();
        while(sensor_auxiliar.faixa_leitura[0] == sensor_auxiliar.faixa_leitura[1]){
            printf("\033[31mFaixas de leitura maxima e minima apresentam valores iguais, tem certeza que deseja cadastra-lo? [S/N]\033[0m ");
            fgets(escolha_temp, T_MAX_STR, stdin);
            retirar_enter(escolha_temp);
            if (!(strcmp(escolha_temp, "N"))){
                printf("Faixa de leitura maxima do sensor:\t ");
                while(scanf("%f", &sensor_auxiliar.faixa_leitura[1]) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
                }
            }
            if (!(strcmp(escolha_temp, "S"))){
                break;
            }
        }
        while(sensor_auxiliar.faixa_leitura[0] > sensor_auxiliar.faixa_leitura[1]){
            printf("\033[31mFaixa de leitura minima apresentam valor maior que a maxima\033[0m\n");
                printf("Faixa de leitura maxima do sensor:\t ");
                while(scanf("%f", &sensor_auxiliar.faixa_leitura[1]) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
                }
        }
        return sensor_auxiliar;
    }
    else{
        printf("\033[31mQuantidade maxima de sensores na planta atingida!!\033[0m");
        usleep(1000000);
    }
}


void listar_sensores_por_industria(planta_industria_t *industria){
    printf("===================\n");
    printf("Lista de Sensores: \n");
    for(int i = 0; i < industria->qtd_sensores_na_planta; i++){
        printf("Sensor\t \033[1;32m[%i]\033[0m\n", i);
        printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->tipos_de_sensores[i].tipo);
        printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->tipos_de_sensores[i].faixa_leitura[0], industria->tipos_de_sensores[i].faixa_leitura[1]);
    }
    printf("===================\n\n");
}

void listar_sensores_por_setor(planta_industria_t *industria, int setor){
    printf("===================\n");
    printf("Lista de Sensores: \n");
    for(int i = 0; i < industria->setores_da_planta[setor].qtd_sensores_no_setor; i++){
        printf("Sensor numero \033[1;32m[%i]\033[0m\n", i);
        printf("Sensor\t \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].id_do_sensor);
        printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].tipo);
        printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[0], industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[1]);
    }
    printf("===================\n\n");
}

void cadastrar_sensor_no_setor(planta_industria_t *industria, int setor, int selecao){
    int sensor_escolhido;
        if(industria->setores_da_planta[setor].qtd_sensores_no_setor < 3){
            printf("Sensores diposniveis:\n");
            listar_sensores_por_industria(industria);
            printf("\033[1;34mOpcao escolhida:\033[0m ");
            while(scanf("%i", &sensor_escolhido) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
            }
            if(sensor_escolhido < industria->qtd_sensores_na_planta){
                industria->setores_da_planta[setor].sensores_do_setor[industria->setores_da_planta[setor].qtd_sensores_no_setor] = industria->tipos_de_sensores[sensor_escolhido];
                industria->setores_da_planta[setor].qtd_sensores_no_setor = (industria->setores_da_planta[setor].qtd_sensores_no_setor + 1);
            }
            else{
                printf("\033[31mSensor %i nao encontrado!!\033[0m\n", sensor_escolhido);
            }
        }
    else{
        printf("\033[31mVoce atingiu o numero maximo de sensores cadastrados!!!\033[0m\n");
    }

}


int menu_sensor_selecionado(void){
    int opcao;
    printf("\t| Menu - Monitoramento |\n");
    printf("\033[1;32m[ 1 ]\033[0m - Efetuar Leitura\n");
    printf("\033[1;32m[ 2 ]\033[0m - Listar Leituras\n");
    printf("\033[1;32m[ 3 ]\033[0m - Relatorio de variacao\n");
    printf("\033[1;32m[ 0 ]\033[0m - Voltar\n");
    printf("\033[1;34mOpcao escolhida:\033[0m ");
    while(scanf("%i", &opcao) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
    }
    return opcao;
}

//leitura

void horario_da_leitura(sensores_t *sensor, int leitura){
    time_t momento = time(NULL);
    struct tm *t = localtime(&momento);
    if(leitura == 1){
        strftime(sensor->horario_1, T_MAX_STR, "%d/%m/%Y %H:%M:%S", t);
    }
    else{
        strftime(sensor->horario_2, T_MAX_STR, "%d/%m/%Y %H:%M:%S", t);
    }
}

void leitura_do_sensor(sensores_t *sensor){
    getchar();
    int leitura = 1;
    while(leitura){
        printf("Leitura \033[34m[%i]\033[0m: ", sensor->numero_da_leitura);
        if(sensor->numero_da_leitura == 1){
            while(scanf("%f", &sensor->primeira_leitura) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
            }
            if(sensor->primeira_leitura <= sensor->faixa_leitura[1] && sensor->primeira_leitura >= sensor->faixa_leitura[0]){
                leitura = 0;
            }    
        }
        if(sensor->numero_da_leitura == 2){
            while(scanf("%f", &sensor->segunda_leitura) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
            }
            if(sensor->segunda_leitura <= sensor->faixa_leitura[1] && sensor->segunda_leitura >= sensor->faixa_leitura[0]){
                    leitura = 0;
                    sensor->variacao_leitura = sensor->segunda_leitura - sensor->primeira_leitura;
                    sensor->media = (sensor->primeira_leitura + sensor->segunda_leitura) / 2;
            } 
        }
        if(leitura){
            printf("\033[1;31mLeitura invalida!!!\033[0m\n");
        }
    }
    horario_da_leitura(sensor, sensor->numero_da_leitura);
    sensor->numero_da_leitura = sensor->numero_da_leitura+1;
}



// relatorios

void relatorio_de_leitura_por_sensor(planta_industria_t *industria, int setor, int sensor){
    if(industria->setores_da_planta[setor].sensores_do_setor[sensor].numero_da_leitura > 1){
                    printf("Primeira Leitura: \n");
                    printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[sensor].horario_1);
                    printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[sensor].primeira_leitura);
                    if(industria->setores_da_planta[setor].sensores_do_setor[sensor].numero_da_leitura > 2){
                        printf("Segunda Leitura: \n");
                        printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[sensor].horario_2);
                        printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[sensor].segunda_leitura);
                    }
                    else{
                        printf("\033[31mAguardando segunda leitura.\033[0m\n");
                    }
                }
                else{
                    printf("\033[31mSem leituras.\033[0m\n");
                }
                printf("=================================\n\n"); 
}

void relatorio_de_leitura_por_setor(planta_industria_t *industria){
    if(industria->qtd_setores_na_planta > 0){
        for(int j = 0; j < industria->qtd_setores_na_planta; j++){
            printf("=================================\n");
            printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", j);
            if(industria->setores_da_planta[j].qtd_sensores_no_setor > 0){
                for(int i = 0; i < industria->setores_da_planta[j].qtd_sensores_no_setor; i++){
                    printf("Sensor numero \033[1;32m[%i]\033[0m\n", i);
                    printf("Sensor\t \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[j].sensores_do_setor[i].id_do_sensor);
                    printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[j].sensores_do_setor[i].tipo);
                    printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->setores_da_planta[j].sensores_do_setor[i].faixa_leitura[0], industria->setores_da_planta[j].sensores_do_setor[i].faixa_leitura[1]);
                    if(industria->setores_da_planta[j].sensores_do_setor[i].numero_da_leitura > 1){
                        printf("Primeira Leitura: \n");
                        printf("[%s]\n", industria->setores_da_planta[j].sensores_do_setor[i].horario_1);
                        printf("-> %2.f\n", industria->setores_da_planta[j].sensores_do_setor[i].primeira_leitura);
                        if(industria->setores_da_planta[j].sensores_do_setor[i].numero_da_leitura > 2){
                            printf("Segunda Leitura: \n");
                            printf("[%s]\n", industria->setores_da_planta[j].sensores_do_setor[i].horario_2);
                            printf("-> %2.f\n", industria->setores_da_planta[j].sensores_do_setor[i].segunda_leitura);
                        }
                        else{
                            printf("\033[31mAguardando segunda leitura.\033[0m\n");
                        }
                    }
                    else{
                        printf("\033[31mSem leituras.\033[0m\n");
                    }
                    printf("=================================\n\n"); 
                }
            }
            else{
                printf("\033[31mSem sensores cadastrados.\033[0m\n");
            }
        }
    }
    else{
            printf("\033[31mSem setores cadastrados.\033[0m\n");
        }
}

void relatorio_de_leitura_pelo_setor(planta_industria_t *industria, int setor){
        printf("=================================\n");
        printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor);
        if(industria->setores_da_planta[setor].qtd_sensores_no_setor > 0){
            for(int i = 0; i < industria->setores_da_planta[setor].qtd_sensores_no_setor; i++){
                printf("Sensor numero \033[1;32m[%i]\033[0m\n", i);
                printf("Sensor\t \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].id_do_sensor);
                printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].tipo);
                printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[0], industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[1]);
                if(industria->setores_da_planta[setor].sensores_do_setor[i].numero_da_leitura > 1){
                    printf("Primeira Leitura: \n");
                    printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[i].horario_1);
                    printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[i].primeira_leitura);
                    if(industria->setores_da_planta[setor].sensores_do_setor[i].numero_da_leitura > 2){
                        printf("Segunda Leitura: \n");
                        printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[i].horario_2);
                        printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[i].segunda_leitura);
                    }
                    else{
                        printf("\033[31mAguardando segunda leitura.\033[0m\n");
                    }
                }
                else{
                    printf("\033[31mSem leituras.\033[0m\n");
                }
                printf("=================================\n\n"); 
            }
        }
        else{
            printf("\033[31mSem sensores cadastrados.\033[0m\n");
        }
}


void relatorio_de_leitura_por_tipo(planta_industria_t *industria, int setor){
    getchar();
    int tipo_nao_econtrado = 1;
    string tipo;
    printf("Tipo: ");
    fgets(tipo, T_MAX_STR, stdin);
    retirar_enter(tipo);

    printf("=================================\n");
        for(int i = 0; i < industria->setores_da_planta[setor].qtd_sensores_no_setor; i++){
            if(!(strcmp(tipo, industria->setores_da_planta[setor].sensores_do_setor[i].tipo))){
                printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor);
                tipo_nao_econtrado = 0;
                printf("Sensor numero \033[1;32m[%i]\033[0m\n", i);
                printf("Sensor\t \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].id_do_sensor);
                printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].tipo);
                printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[0], industria->setores_da_planta[setor].sensores_do_setor[i].faixa_leitura[1]);
                if(industria->setores_da_planta[setor].sensores_do_setor[i].numero_da_leitura > 1){
                    printf("Primeira Leitura: \n");
                    printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[i].horario_1);
                    printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[i].primeira_leitura);
                    if(industria->setores_da_planta[setor].sensores_do_setor[i].numero_da_leitura > 2){
                        printf("Segunda Leitura: \n");
                        printf("[%s]\n", industria->setores_da_planta[setor].sensores_do_setor[i].horario_2);
                        printf("-> %2.f\n", industria->setores_da_planta[setor].sensores_do_setor[i].segunda_leitura);
                    }
                    else{
                        printf("\033[31mAguardando segunda leitura.\033[0m\n");
                    }
                }
                else{
                    printf("\033[31mSem leituras.\033[0m\n");
                }
                printf("=================================\n\n"); 
            }
        }
        if(tipo_nao_econtrado){
            printf("Nao foi encontrado sensor com o tipo: %s", tipo);
        }       
}

void relatorio_de_variacao_por_setor(planta_industria_t *industria, int setor){
    if(industria->qtd_setores_na_planta > 0){
        printf("=================================\n");
            printf("Relatorio de Variacao dos Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor);
                if(industria->setores_da_planta[setor].qtd_sensores_no_setor > 0){
                    for(int i = 0; i < industria->setores_da_planta[setor].qtd_sensores_no_setor; i++){
                        printf("Sensor \033[1;32m[%i]\033[0m\n", i);
                            if(industria->setores_da_planta[setor].sensores_do_setor[i].numero_da_leitura > 2){
                                printf("Variacao: %.2f\n", industria->setores_da_planta[setor].sensores_do_setor[i].variacao_leitura);
                            }
                            else{
                                printf("\033[1;31mSem leitura suficientes para o calculo da variacao\033[0m\n");
                            }
                        printf("=================================\n\n"); 
                    }
                }
                else{
                    printf("\033[31mSem sensores cadastrados.\033[0m\n");
                }
            
    }
    else{
            printf("\033[31mSem setores cadastrados.\033[0m\n");
        }   
}

void relatorio_de_variacao_por_sensor(planta_industria_t *industria, int setor, int sensor){
    printf("=================================\n");
                if(industria->setores_da_planta[setor].sensores_do_setor[sensor].numero_da_leitura > 2){
                    printf("Sensor \033[1;32m[%i]\033[0m\n", sensor);
                    printf("Variacao: %.2f\n", industria->setores_da_planta[setor].sensores_do_setor[sensor].variacao_leitura);     
                }
                else{
                    printf("\033[1;31mSem leitura suficientes para o calculo da variacao\033[0m\n");
                }
            printf("=================================\n\n"); 
}

void relatorio_da_media_dos_setores(planta_industria_t *industria){
    if(industria->qtd_setores_na_planta > 0){
        printf("=================================\n");
        for(int i = 0; i < industria->qtd_setores_na_planta; i++ ){
            printf("Relatorio de media dos Sensores do Setor \033[1;32m[%i]\033[0m: \n", i);
            if(industria->setores_da_planta[i].qtd_sensores_no_setor > 0){
                for(int j = 0; j < industria->setores_da_planta[i].qtd_sensores_no_setor; j++){
                        printf("Sensor \033[1;32m[%i]\033[0m\n", j);
                        if(industria->setores_da_planta[i].sensores_do_setor[j].numero_da_leitura > 2){
                            printf("Media: %.2f\n", industria->setores_da_planta[i].sensores_do_setor[j].media);
                        }
                        else{
                            printf("\033[1;31mSem leituras suficentes para executar a media\033[0m \n");
                        }
                    }
            }
            else{
                printf("\033[31mSem sensores cadastrados.\033[0m\n");
                }
            printf("=================================\n\n"); 
        }
    }
    else{
            printf("\033[31mSem setores cadastrados.\033[0m\n");
        }
}

//Pesquisas

void pesquisar_setor_por_descricao(planta_industria_t *industria){
    getchar();
    int setor_nao_encontrado = 1;
    string descricao;
    if(industria->qtd_setores_na_planta > 0){
        printf("Qual a descricao do setor que deseja procurar: ");
        fgets(descricao, T_MAX_STR, stdin);
        retirar_enter(descricao);
        for(int i = 0; i < industria->qtd_setores_na_planta; i++){
            if(!(strcmp(descricao, industria->setores_da_planta[i].descricao))){
                    printf("Setor\t \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[i].id_do_setor);
                    printf("Descricao:\t \033[1;32m%s\033[0m\n", industria->setores_da_planta[i].descricao);
                    printf("Quantidade de sensores do setor: \033[1;32m[%i]\033[0m\n", industria->setores_da_planta[i].qtd_sensores_no_setor);
                    printf("=================================\n\n"); 
                    setor_nao_encontrado = 0; // nega a expressao se ele for encontrado
            }
        }
        if(setor_nao_encontrado){
        printf("Nao foi encontrado setor com a descriacao: \033[1;31m%s\033[0m\n", descricao);
    }
    }
    else{
        printf("\033[1;31mAinda nao ha setores.\n\033[0m");
    }
    
}


void pesquisar_sensor_por_tipo(planta_industria_t *industria){
    getchar();
    int sensor_nao_encontrado = 1;
    string tipo;
    if(industria->qtd_sensores_na_planta > 0){
        printf("Qual o tipo que deseja procurar: ");
        fgets(tipo, T_MAX_STR, stdin);
        retirar_enter(tipo);
        for(int i = 0; i < industria->qtd_sensores_na_planta; i++){
                if(!(strcmp(tipo, industria->tipos_de_sensores[i].tipo))){
                    printf("Sensor\t \033[1;32m[%i]\033[0m\n", industria->tipos_de_sensores[i].id_do_sensor);
                    printf("Tipo:\t \033[1;32m%s\033[0m\n", industria->tipos_de_sensores[i].tipo);
                    printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", industria->tipos_de_sensores[i].faixa_leitura[0], industria->tipos_de_sensores[i].faixa_leitura[1]);
                    printf("=================================\n\n"); 
                    sensor_nao_encontrado = 0; // nega a expressao se ele for encontrado
                }
        }
        if(sensor_nao_encontrado){
            printf("Nao foi encontrado sensor com o tipo: \033[1;31m%s\033[0m\n", tipo);
        }
    }
    else{
        printf("\033[1;32mAinda nao ha sensores cadastrados.\033[0m\n");
    }

}



//funções auxíliares

void retirar_enter(string str){
    str[strlen(str) - 1] = '\0';
}


void esperar_prosseguir(void){
    while((getchar()) != '\n');
    printf("\033[1;32mPressione ENTER para prosseguir: \033[0m");
    getchar();
}

void limpar_tela(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");   
    #else
        system("clear");
    #endif
}