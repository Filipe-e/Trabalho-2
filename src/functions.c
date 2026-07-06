#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../Includes/types.h"
#include "../Includes/functions.h"


    planta_industria_t *criar_planta_de_industria(){
        planta_industria_t *industria_zerada = malloc(sizeof(planta_industria_t));

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
        usleep(15000);
        return industria_auxiliar;
    }

    void inserir_sensor_no_setor(sensores_t **sensores_no_setor, sensores_t *tipo_de_sensor, setores_t *setor){
        tipo_de_sensor->id_do_setor_mae = setor->id_do_setor;
        tipo_de_sensor->prox = *sensores_no_setor;
        *sensores_no_setor = tipo_de_sensor;

    }

    void inserir_industria(planta_industria_t **industrias, planta_industria_t *nova_industria){
        nova_industria->prox = *industrias;
        *industrias = nova_industria;
    }

    void inserir_setor_na_industria(setores_t **setores_da_planta, setores_t *setor_novo){

        setor_novo->prox = *setores_da_planta;
        *setores_da_planta = setor_novo;
    }

    void inserir_sensor_na_industria(sensores_t **tipos_de_sensores, sensores_t *sensor_novo){

        sensor_novo->prox = *tipos_de_sensores;
        *tipos_de_sensores = sensor_novo;
    }

    void listar_industrias(planta_industria_t *industria, int qtd_industrias){
        printf("===================\n");
        printf("Lista de Industrias: \n");
        for(industria; industria != NULL; industria = industria->prox){
            printf("Industria \033[1;32m[%i]\033[0m\n", industria->id_da_planta);
            printf("Quantidade de setores cadastrados\t \033[1;32m%i\033[0m\n", industria->qtd_setores_na_planta);
            printf("Quantidade de sensores cadastrados\t \033[1;32m%i\033[0m\n", industria->qtd_sensores_na_planta);
        }
        printf("=====================\n\n");
    }

    planta_industria_t *pesquisar_industria_por_id(planta_industria_t *industrias, int id_industria){
        for(industrias; industrias != NULL; industrias = industrias->prox){
            if(industrias->id_da_planta == id_industria){
                return industrias;
            }
        }
        return NULL;
    }

    setores_t *criar_setor_de_industria(void){
        setores_t *setor_zerado = NULL;
        setor_zerado = malloc(sizeof(setores_t));


        setor_zerado->qtd_sensores_no_setor = 0;
        setor_zerado->descricao[0] = '\0';
        setor_zerado->sensores_do_setor = NULL;
        return setor_zerado;
    }

    setores_t *cadastrar_setor(planta_industria_t *industria){
        if(industria->qtd_setores_na_planta < 5){

            setores_t *setor_auxiliar = criar_setor_de_industria();
            setor_auxiliar->id_da_planta_mae = industria->id_da_planta;
            setor_auxiliar->id_do_setor = industria->qtd_setores_na_planta;
            industria->qtd_setores_na_planta = industria->qtd_setores_na_planta + 1; //atualizando a quantidade de setores na industria selecionada
            printf("| Cadastro do setor %i |\n", setor_auxiliar->id_do_setor);
            printf("Descricao do setor:\t\t ");
            fgets(setor_auxiliar->descricao, T_MAX_STR, stdin);
            retirar_enter(setor_auxiliar->descricao);
            return setor_auxiliar;
        }
        else{
            printf("\033[31mQuantidade maxima de setores atingida!!\033[0m");
            usleep(1000000);
            return NULL;
        }
    }

    void listar_setores_por_industria(setores_t *industria){
        printf("===================\n");
        printf("Lista de Setores: \n");
        for(industria; industria != NULL; industria = industria->prox){
            printf("Setor:\t \033[1;32m[%i]\033[0m\n", industria->id_do_setor);
            printf("Descricao:\t \033[1;32m%s\033[0m\n", industria->descricao);
            printf("Quantidade de sensores no setor: \033[1;32m%i\033[0m\n", industria->qtd_sensores_no_setor);
        }
        printf("===================\n\n");
    }

    sensores_t *criar_sensor_de_industria(void){
        sensores_t *sensor_zerado = NULL;
        sensor_zerado = malloc(sizeof(sensores_t));
        sensor_zerado->faixa_leitura_1 = 0;
        sensor_zerado->faixa_leitura_2 = 0;
        sensor_zerado->numero_da_leitura = 1;
        sensor_zerado->tipo[0] = '\0';
        sensor_zerado->variacao_leitura = 0;
        sensor_zerado->media = 0;
        sensor_zerado->id_da_planta_mae = 99;
        sensor_zerado->id_do_setor_mae = 99;
        return sensor_zerado;
    }

    sensores_t *cadastrar_sensor(planta_industria_t *industria){
        sensores_t *sensor_auxiliar = criar_sensor_de_industria();
        string escolha_temp;
        sensor_auxiliar->id_da_planta_mae = industria->id_da_planta;
        if(industria-> qtd_sensores_na_planta < 15){
            sensor_auxiliar->id_do_sensor = industria->qtd_sensores_na_planta;
            industria->qtd_sensores_na_planta = industria->qtd_sensores_na_planta + 1; //atualizando a quantidade de sensores na industria selecionada
            printf("| Cadastro do tipo de sensor %i |\n", sensor_auxiliar->id_do_sensor);
            printf("Tipo do sensor:\t\t ");
            fgets(sensor_auxiliar->tipo, T_MAX_STR, stdin);
            printf("Faixa de leitura minima do sensor:\t ");
            retirar_enter(sensor_auxiliar->tipo);
            while(scanf("%f", &sensor_auxiliar->faixa_leitura_1) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
            }
            printf("Faixa de leitura maxima do sensor:\t ");
            while(scanf("%f", &sensor_auxiliar->faixa_leitura_2) != 1){
                printf("Entrada invalida! Digite novamente: ");
                while(getchar() != '\n'); // limpa
            }
            getchar();
            while(sensor_auxiliar->faixa_leitura_1 == sensor_auxiliar->faixa_leitura_2){
                printf("\033[31mFaixas de leitura maxima e minima apresentam valores iguais, tem certeza que deseja cadastra-lo? [S/N]\033[0m ");
                fgets(escolha_temp, T_MAX_STR, stdin);
                retirar_enter(escolha_temp);
                if (!(strcmp(escolha_temp, "N"))){
                    printf("Faixa de leitura maxima do sensor:\t ");
                    while(scanf("%f", &sensor_auxiliar->faixa_leitura_2) != 1){
                    printf("Entrada invalida! Digite novamente: ");
                    while(getchar() != '\n'); // limpa
                    }
                }
                if (!(strcmp(escolha_temp, "S"))){
                    break;
                }
            }
            while(sensor_auxiliar->faixa_leitura_1 > sensor_auxiliar->faixa_leitura_2){
                printf("\033[31mFaixa de leitura minima apresentam valor maior que a maxima\033[0m\n");
                    printf("Faixa de leitura maxima do sensor:\t ");
                    while(scanf("%f", &sensor_auxiliar->faixa_leitura_2) != 1){
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


    void listar_sensores_por_industria(sensores_t *tipo_sensores){
        printf("===================\n");
        printf("Lista de Sensores: \n");
        for(tipo_sensores; tipo_sensores !=NULL ; tipo_sensores = tipo_sensores->prox){
            printf("Sensor\t \033[1;32m[%i]\033[0m\n", tipo_sensores->id_do_sensor);
            printf("Tipo:\t \033[1;32m%s\033[0m\n", tipo_sensores->tipo);
            printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", tipo_sensores->faixa_leitura_1,tipo_sensores->faixa_leitura_2);
        }
        printf("===================\n\n");
    }

    void listar_sensores_por_setor(sensores_t *sensores_no_setor){
        printf("===================\n");
        printf("Lista de Sensores: \n");
        for(sensores_no_setor; sensores_no_setor != NULL; sensores_no_setor = sensores_no_setor->prox){
            printf("Sensor numero \033[1;32m[%i]\033[0m\n", sensores_no_setor->id_do_sensor_no_setor);
            printf("Sensor\t \033[1;32m[%i]\033[0m\n", sensores_no_setor->id_do_sensor);
            printf("Tipo:\t \033[1;32m%s\033[0m\n", sensores_no_setor->tipo);
            printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", sensores_no_setor->faixa_leitura_1, sensores_no_setor->faixa_leitura_2);
        }
        printf("===================\n\n");
    }



    sensores_t *criar_uma_copia(sensores_t *tipo_de_sensor, int qtd_sensores_no_setor){
        sensores_t *sensor_copia = NULL;
        sensor_copia = malloc(sizeof(sensores_t));
        sensor_copia->id_da_planta_mae = tipo_de_sensor->id_da_planta_mae;
        sensor_copia->id_do_sensor_no_setor = qtd_sensores_no_setor;
        sensor_copia->id_do_sensor = tipo_de_sensor->id_do_sensor;
        strcpy((sensor_copia->tipo), (tipo_de_sensor->tipo));
        (sensor_copia->faixa_leitura_1) = (tipo_de_sensor->faixa_leitura_1);
        (sensor_copia->faixa_leitura_2) = (tipo_de_sensor->faixa_leitura_2);
        (sensor_copia->numero_da_leitura) = (tipo_de_sensor->numero_da_leitura);
        (sensor_copia->primeira_leitura) = (tipo_de_sensor->primeira_leitura);
        strcpy((sensor_copia->horario_1) , (tipo_de_sensor->horario_1));
        (sensor_copia->segunda_leitura) = (tipo_de_sensor->segunda_leitura);
        strcpy((sensor_copia->horario_2) , (tipo_de_sensor->horario_2));
        (sensor_copia->variacao_leitura) = (tipo_de_sensor->variacao_leitura);
        (sensor_copia->media) = (tipo_de_sensor->media);
        

        return sensor_copia;

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
                if(sensor->primeira_leitura <= sensor->faixa_leitura_2 && sensor->primeira_leitura >= sensor->faixa_leitura_1){
                    leitura = 0;
                }    
            }
            if(sensor->numero_da_leitura == 2){
                while(scanf("%f", &sensor->segunda_leitura) != 1){
                    printf("Entrada invalida! Digite novamente: ");
                    while(getchar() != '\n'); // limpa
                }
                if(sensor->segunda_leitura <= sensor->faixa_leitura_2 && sensor->segunda_leitura >= sensor->faixa_leitura_1){
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

    void relatorio_de_leitura_por_sensor(sensores_t *sensor_escolhido){
        if(sensor_escolhido->numero_da_leitura > 1){
                        printf("Primeira Leitura: \n");
                        printf("[%s]\n", sensor_escolhido->horario_1);
                        printf("-> %2.f\n", sensor_escolhido->primeira_leitura);
                        if(sensor_escolhido->numero_da_leitura > 2){
                            printf("Segunda Leitura: \n");
                            printf("[%s]\n", sensor_escolhido->horario_2);
                            printf("-> %2.f\n", sensor_escolhido->segunda_leitura);
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

    void relatorio_de_leitura_por_setor(setores_t *setor, int qtd_setores_na_planta){
        sensores_t *lista_de_sensores_aux = NULL;
        if(qtd_setores_na_planta > 0){
            for(setor; setor != NULL; setor = setor->prox){
                printf("=================================\n");
                printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        printf("Sensor numero \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        printf("Sensor\t \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor);
                        printf("Tipo:\t \033[1;32m%s\033[0m\n", lista_de_sensores_aux->tipo);
                        printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            printf("Primeira Leitura: \n");
                            printf("[%s]\n", lista_de_sensores_aux->horario_1);
                            printf("-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                printf("Segunda Leitura: \n");
                                printf("[%s]\n", lista_de_sensores_aux->horario_2);
                                printf("-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
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

    void relatorio_de_leitura_pelo_setor(setores_t *setor){
            sensores_t *lista_de_sensores_aux = NULL;
            printf("=================================\n");
            printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor->id_do_setor);
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                    printf("Sensor numero \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                    printf("Sensor\t \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor);
                    printf("Tipo:\t \033[1;32m%s\033[0m\n", lista_de_sensores_aux->tipo);
                    printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        printf("Primeira Leitura: \n");
                        printf("[%s]\n", lista_de_sensores_aux->horario_1);
                        printf("-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            printf("Segunda Leitura: \n");
                            printf("[%s]\n", lista_de_sensores_aux->horario_2);
                            printf("-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
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


    void relatorio_de_leitura_por_tipo(setores_t *setor){
        getchar();
        sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        int tipo_nao_econtrado = 1;
        string tipo;
        printf("Tipo: ");
        fgets(tipo, T_MAX_STR, stdin);
        retirar_enter(tipo);

        printf("=================================\n");
            for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                if(!(strcmp(tipo, lista_de_sensores_aux->tipo))){
                    printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor->id_do_setor);
                    tipo_nao_econtrado = 0;
                    printf("Sensor numero \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                    printf("Sensor\t \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor);
                    printf("Tipo:\t \033[1;32m%s\033[0m\n", lista_de_sensores_aux->tipo);
                    printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        printf("Primeira Leitura: \n");
                        printf("[%s]\n", lista_de_sensores_aux->horario_1);
                        printf("-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            printf("Segunda Leitura: \n");
                            printf("[%s]\n", lista_de_sensores_aux->horario_2);
                            printf("-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
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

    void relatorio_de_variacao_por_setor(setores_t *setor){
        sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        printf("=================================\n");
            printf("Relatorio de Variacao dos Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        printf("Sensor \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        printf("Sensor ID:\033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                printf("Variacao: %.2f\n", lista_de_sensores_aux->variacao_leitura);
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
        


    void relatorio_de_variacao_por_sensor(sensores_t *sensor){
        printf("=================================\n");
                    if(sensor->numero_da_leitura > 2){
                        printf("Sensor \033[1;32m[%i]\033[0m\n", sensor->id_do_sensor_no_setor);
                        printf("Variacao: %.2f\n", sensor->variacao_leitura);     
                    }
                    else{
                        printf("\033[1;31mSem leitura suficientes para o calculo da variacao\033[0m\n");
                    }
                printf("=================================\n\n"); 
    }

    void relatorio_da_media_dos_setores(setores_t *setor, int qtd_setores_na_planta){
        sensores_t *lista_de_sensores_aux = NULL;
        if(qtd_setores_na_planta > 0){
            for(setor; setor != NULL; setor = setor->prox){
                printf("=================================\n");
                printf("Relatorio de Sensores do Setor \033[1;32m[%i]\033[0m: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        printf("Sensor numero \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        printf("Sensor\t \033[1;32m[%i]\033[0m\n", lista_de_sensores_aux->id_do_sensor);
                        printf("Tipo:\t \033[1;32m%s\033[0m\n", lista_de_sensores_aux->tipo);
                        printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                printf("Media: %.2f\n", lista_de_sensores_aux->media);
                            }
                            else{
                                printf("\033[1;31mSem leituras suficentes para executar a media\033[0m \n");
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

    //Pesquisas

    void pesquisar_setor_por_descricao(setores_t *setores_da_planta, int qtd_setores_na_planta){
        getchar();
        int setor_nao_encontrado = 1;
        string descricao;
        if(qtd_setores_na_planta > 0){
            printf("Qual a descricao do setor que deseja procurar: ");
            fgets(descricao, T_MAX_STR, stdin);
            retirar_enter(descricao);
            for(setores_da_planta ; setores_da_planta !=NULL; setores_da_planta = setores_da_planta->prox){
                if(!(strcmp(descricao, setores_da_planta->descricao))){
                        printf("Setor\t \033[1;32m[%i]\033[0m\n", setores_da_planta->id_do_setor);
                        printf("Descricao:\t \033[1;32m%s\033[0m\n", setores_da_planta->descricao);
                        printf("Quantidade de sensores do setor: \033[1;32m[%i]\033[0m\n", setores_da_planta->qtd_sensores_no_setor);
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

    sensores_t *pesquisar_sensor_por_id_no_setor(sensores_t *sensor, int id_sensor_no_setor){
        for(sensor; sensor!=NULL; sensor = sensor->prox){
            if(id_sensor_no_setor == sensor->id_do_sensor_no_setor)
            return sensor;
        }    
        return NULL;
    }

    setores_t *pesquisar_setor_por_id(setores_t *setores_da_planta , int id_do_setor){
        for(setores_da_planta; setores_da_planta != NULL; setores_da_planta = setores_da_planta->prox){
            if(setores_da_planta->id_do_setor == id_do_setor){
                return setores_da_planta;
            }
        }
        return NULL;
    }

    setores_t *pesquisar_setor_por_id_recursiva(setores_t *setores_da_planta , int id_do_setor){
        if(setores_da_planta == NULL){
            return NULL;
        }
        if(setores_da_planta->id_do_setor == id_do_setor){
            return setores_da_planta;
        }
            return pesquisar_setor_por_id_recursiva(setores_da_planta->prox, id_do_setor);
    }

    void pesquisar_sensor_por_tipo(sensores_t *tipo_sensores, int qtd_sensores_na_planta){
        getchar();
        int sensor_nao_encontrado = 1;
        string tipo;
        if(qtd_sensores_na_planta > 0){
            printf("Qual o tipo que deseja procurar: ");
            fgets(tipo, T_MAX_STR, stdin);
            retirar_enter(tipo);
            for(tipo_sensores; tipo_sensores != NULL; tipo_sensores = tipo_sensores->prox){
                    if(!(strcmp(tipo, tipo_sensores->tipo))){
                        printf("Sensor\t \033[1;32m[%i]\033[0m\n", tipo_sensores->id_do_sensor);
                        printf("Tipo:\t \033[1;32m%s\033[0m\n", tipo_sensores->tipo);
                        printf("Faixa de leitura: \033[1;32m[%.2f - %.2f]\033[0m\n",tipo_sensores->faixa_leitura_1, tipo_sensores->faixa_leitura_2);
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

    sensores_t *pesquisar_sensor_por_id(sensores_t *tipo_sensores, int id_do_sensor){
        getchar();
            for(tipo_sensores; tipo_sensores != NULL; tipo_sensores = tipo_sensores->prox){
                    if(id_do_sensor == tipo_sensores->id_do_sensor){
                        return tipo_sensores;   
                    }
            
        }
    }

    void remover_sensor(sensores_t **sensor, setores_t *setor_atual){
        int i;
        sensores_t *lista_de_sensores_aux_2 = *sensor;
        sensores_t *lista_de_sensores_aux = *sensor;
        sensores_t *anterior = NULL;
        int id_do_sensor_no_setor;
        printf("\033[1;31mQUAL NUMERO DO SENSOR DENTRO DESSE SETOR?\033[0m\n");
        while(scanf("%i", &id_do_sensor_no_setor) != 1){
        printf("Entrada invalida! Digite novamente: ");
        while(getchar() != '\n'); // limpa
        }
        if(id_do_sensor_no_setor < setor_atual->qtd_sensores_no_setor){
            while(lista_de_sensores_aux->prox){
                if(lista_de_sensores_aux->id_do_sensor_no_setor == id_do_sensor_no_setor){
                    break;
                }
                anterior = lista_de_sensores_aux;
                lista_de_sensores_aux = lista_de_sensores_aux->prox;    
            }
            if(!anterior){
                *sensor = lista_de_sensores_aux->prox;        
                free(lista_de_sensores_aux);
            }
            else{
                if(!lista_de_sensores_aux){
                    anterior->prox == NULL;
                }
                anterior->prox = lista_de_sensores_aux->prox;
                free(lista_de_sensores_aux);
            }
            setor_atual->qtd_sensores_no_setor = setor_atual->qtd_sensores_no_setor - 1;
            for(i = setor_atual->qtd_sensores_no_setor-1,lista_de_sensores_aux_2;i != 0, lista_de_sensores_aux_2!=NULL;i--, lista_de_sensores_aux_2 = lista_de_sensores_aux_2->prox){
                lista_de_sensores_aux_2->id_do_sensor_no_setor = i;
            }
        }
        else(printf("\033[1;31m[sensor nn existe]\033[0m\n"));
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


    // exportacoes

    void exportar_industrias_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        fp = fopen(nome_arq, "wb");

        while (industrias)
        {
            fwrite(industrias, sizeof(planta_industria_t), 1, fp);
            industrias = industrias->prox;
        }
        fclose(fp);
        
    }
    void exportar_setores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        fp = fopen(nome_arq, "wb");
        for(industrias; industrias != NULL; industrias = industrias->prox){
            setores_t *setor_aux = industrias->setores_da_planta;
        while (setor_aux)
        {
            fwrite(setor_aux, sizeof(setores_t), 1, fp);
            setor_aux = setor_aux->prox;
        }
        }
        fclose(fp);
        
    }
    void exportar_tipos_sensores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        fp = fopen(nome_arq, "wb");
        for(industrias; industrias != NULL; industrias = industrias->prox){
            sensores_t *tipo_sensores_aux = industrias->tipos_de_sensores;
            while (tipo_sensores_aux)
            {
                fwrite(tipo_sensores_aux, sizeof(sensores_t), 1, fp);
                tipo_sensores_aux = tipo_sensores_aux->prox;
            } 
        } 
        fclose(fp);
        
    }
    void exportar_sensores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        fp = fopen(nome_arq, "wb");
        planta_industria_t *ind_aux = industrias;
        for(ind_aux; ind_aux != NULL; ind_aux = ind_aux->prox){
            setores_t *lista_setores_aux = ind_aux->setores_da_planta;
            for(lista_setores_aux; lista_setores_aux != NULL; lista_setores_aux = lista_setores_aux->prox){  
                sensores_t *lista_sensores_aux = lista_setores_aux->sensores_do_setor;
                for(lista_sensores_aux; lista_sensores_aux != NULL; lista_sensores_aux = lista_sensores_aux->prox){ 
                    fwrite(lista_sensores_aux, sizeof(sensores_t), 1, fp);}}}
        fclose(fp);
        
    }

    void ler_industrias_bin(planta_industria_t **industrias, char *nome_arq, int *qtd_industrias){
        FILE *fp= NULL;
        planta_industria_t *nova_industria =NULL;
        fp = fopen(nome_arq, "rb");
        if(fp == NULL) return;
        while (!feof(fp)) {
        nova_industria = malloc(sizeof(planta_industria_t));
        fread(nova_industria, sizeof(planta_industria_t), 1, fp);
        nova_industria->prox = NULL;
        nova_industria->setores_da_planta = NULL;
        nova_industria->tipos_de_sensores = NULL;
            if (!feof(fp)) {
                    inserir_industria(industrias, nova_industria);
                    *qtd_industrias = *qtd_industrias+1;
                }
                else {
                    free(nova_industria);
                }
        
        }
        fclose(fp);
    }

    void ler_setores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        setores_t *novo_setor = NULL;
        planta_industria_t *ind_aux = industrias;
        for(ind_aux; ind_aux != NULL; ind_aux = ind_aux->prox){  
        setores_t *nova_lista_de_setores = NULL;
            fp = fopen(nome_arq, "rb");
            if(fp == NULL) return;
            while (!feof(fp)) {
                novo_setor = malloc(sizeof(setores_t));
                fread(novo_setor, sizeof(setores_t), 1, fp);
                if(novo_setor->id_da_planta_mae == ind_aux->id_da_planta){
                    novo_setor->prox = NULL;
                    novo_setor->sensores_do_setor = NULL;
                        if (!feof(fp)) {
                                inserir_setor_na_industria(&nova_lista_de_setores, novo_setor);
                            }
                            else {
                                free(novo_setor);
                            }
            }
            ind_aux->setores_da_planta = nova_lista_de_setores;
            }fclose(fp);
        }
        
    }

    void ler_tipo_sensores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        sensores_t *novo_sensor = NULL;
        planta_industria_t *ind_aux = industrias;
        for(ind_aux; ind_aux != NULL; ind_aux = ind_aux->prox){  
        sensores_t *nova_lista_de_sensores = NULL;
            fp = fopen(nome_arq, "rb");
            if(fp == NULL) return;
            while (!feof(fp)) {
                novo_sensor = malloc(sizeof(sensores_t));
                fread(novo_sensor, sizeof(sensores_t), 1, fp);
                if(novo_sensor->id_da_planta_mae == ind_aux->id_da_planta){
                    novo_sensor->prox = NULL;
                        if (!feof(fp)) {
                                inserir_sensor_na_industria(&nova_lista_de_sensores, novo_sensor);
                            }
                            else {
                                free(novo_sensor);
                            }
            }
            else{
                    free(novo_sensor);
                }
            }fclose(fp);
            ind_aux->tipos_de_sensores = nova_lista_de_sensores;
        }
    }
    
    void ler_sensores_no_setores_bin(planta_industria_t *industrias, char *nome_arq){
        FILE *fp= NULL;
        sensores_t *novo_sensor = NULL;
        planta_industria_t *ind_aux = industrias;
        for(ind_aux; ind_aux != NULL; ind_aux = ind_aux->prox){
            setores_t *lista_setores_aux = ind_aux->setores_da_planta;
            for(lista_setores_aux; lista_setores_aux != NULL; lista_setores_aux = lista_setores_aux->prox){  
            sensores_t *nova_lista_de_sensores = NULL;
                fp = fopen(nome_arq, "rb");
                if(fp == NULL) return;
                while (!feof(fp)) {
                    novo_sensor = malloc(sizeof(sensores_t));
                    fread(novo_sensor, sizeof(sensores_t), 1, fp);
                    if(novo_sensor->id_da_planta_mae == ind_aux->id_da_planta){
                        if(novo_sensor->id_do_setor_mae == lista_setores_aux->id_do_setor){
                            novo_sensor->prox = NULL;
                            if (!feof(fp)) {
                                    inserir_sensor_na_industria(&nova_lista_de_sensores, novo_sensor);
                                }
                                else {
                                    free(novo_sensor);
                                }
                        }
                        else{
                            free(novo_sensor);
                        }
                    }
                    else{
                        free(novo_sensor);
                    }
                }fclose(fp);
                lista_setores_aux->sensores_do_setor = nova_lista_de_sensores;
            }
        }
    }

    void exportar_relatorio_de_leitura_por_setor(setores_t *setor,  int qtd_setores_na_planta){
        getchar();
        sensores_t *lista_de_sensores_aux = NULL;

        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");

        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        if(qtd_setores_na_planta > 0){
            for(setor; setor != NULL; setor = setor->prox){
                fprintf(fp, "=================================\n");
                fprintf(fp, "Relatorio de Sensores do Setor %i: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "Sensor numero :%i\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "Sensor\t :%i\n", lista_de_sensores_aux->id_do_sensor);
                        fprintf(fp, "Tipo:\t :%s\n", lista_de_sensores_aux->tipo);
                        fprintf(fp, "Faixa de leitura: %.2f\n", lista_de_sensores_aux->faixa_leitura_1);
                        fprintf(fp, "Faixa de leitura: %.2f\n", lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            fprintf(fp, "Primeira Leitura: \n");
                            fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_1);
                            fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "Segunda Leitura: \n");
                                fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_2);
                                fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
                            }
                            else{
                                fprintf(fp, "\033[31mAguardando segunda leitura.\033[0m\n");
                            }
                        }
                        else{
                            fprintf(fp, "\033[31mSem leituras.\033[0m\n");
                        }
                        fprintf(fp, "=================================\n\n"); 
                    }
                }
                else{
                    fprintf(fp, "\033[31mSem sensores cadastrados.\033[0m\n");
                }
            }
        }
        else{
                fprintf(fp, "\033[31mSem setores cadastrados.\033[0m\n");
            }
        fclose(fp);   
    }

    void exportar_relatorio_de_variacao_por_setor(setores_t *setor){
        getchar();
        sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");
        
        FILE *fp = fopen(nome_do_arquivo,"w");

        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        
        fprintf(fp, "=================================\n");
            fprintf(fp, "Relatorio de Variacao dos Sensores do Setor %i: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "Sensor %i\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "Sensor ID:%i\n", lista_de_sensores_aux->id_do_sensor);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "Variacao: %.2f\n", lista_de_sensores_aux->variacao_leitura);
                            }
                            else{
                                fprintf(fp, "Sem leitura suficientes para o calculo da variacao\n");
                            }
                        fprintf(fp, "=================================\n\n"); 
                        }
                    }
                    else{
                        fprintf(fp, "Sem sensores cadastrados.\n");
                    }
            fclose(fp);
        }
        
    void exportar_relatorio_de_leitura_pelo_setor(setores_t *setor){
        getchar();
            sensores_t *lista_de_sensores_aux = NULL;

            string nome_do_arquivo; 
            printf("Nome do arquivo: "); 
            fgets(nome_do_arquivo, T_MAX_STR, stdin); 
            retirar_enter(nome_do_arquivo);
            strcat(nome_do_arquivo, ".txt");
            FILE *fp = fopen(nome_do_arquivo,"w");
            if (fp == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
            }

            fprintf(fp, "=================================\n");
            fprintf(fp, "Relatorio de Sensores do Setor %i: \n", setor->id_do_setor);
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                    fprintf(fp, "Sensor numero %i\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                    fprintf(fp, "Sensor\t %i\n", lista_de_sensores_aux->id_do_sensor);
                    fprintf(fp, "Tipo:\t %s\n", lista_de_sensores_aux->tipo);
                    fprintf(fp, "Faixa de leitura: %.2f - %.2f\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        fprintf(fp, "Primeira Leitura: \n");
                        fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_1);
                        fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            fprintf(fp, "Segunda Leitura: \n");
                            fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_2);
                            fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
                        }
                        else{
                            fprintf(fp, "Aguardando segunda leitura.\n");
                        }
                    }
                    else{
                        fprintf(fp, "Sem leituras.\n");
                    }
                    fprintf(fp, "=================================\n\n"); 
                }
            }
            else{
                fprintf(fp, "Sem sensores cadastrados.\n");
            }
            fclose(fp);
    }

    void exportar_relatorio_de_variacao_por_sensor(sensores_t *sensor){
        getchar();
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "=================================\n");
                    if(sensor->numero_da_leitura > 2){
                        fprintf(fp, "Sensor no Setor %i\n", sensor->id_do_sensor_no_setor);
                        fprintf(fp, "Sensor %i\n", sensor->id_do_sensor);
                        fprintf(fp, "Tipo: %s\n", sensor->tipo);
                        fprintf(fp, "Variacao: %.2f\n", sensor->variacao_leitura);     
                    }
                    else{
                        fprintf(fp, "Sem leitura suficientes para o calculo da variacao\n");
                    }
                fprintf(fp, "=================================\n\n"); 
        fclose(fp);
    }

    void exportar_relatorio_de_leitura_por_tipo(setores_t *setor){
        getchar();
        sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        int tipo_nao_econtrado = 1;
        string tipo;
        printf("Tipo: ");
        fgets(tipo, T_MAX_STR, stdin);
        retirar_enter(tipo);
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        fprintf(fp, "=================================\n");
            for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                if(!(strcmp(tipo, lista_de_sensores_aux->tipo))){
                    fprintf(fp, "Relatorio de Sensores do Setor %i: \n", setor->id_do_setor);
                    tipo_nao_econtrado = 0;
                    fprintf(fp, "Sensor numero %i\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                    fprintf(fp, "Sensor\t %i\n", lista_de_sensores_aux->id_do_sensor);
                    fprintf(fp, "Tipo:\t %s\n", lista_de_sensores_aux->tipo);
                    fprintf(fp, "Faixa de leitura: %.2f - %.2f\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        fprintf(fp, "Primeira Leitura: \n");
                        fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_1);
                        fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            fprintf(fp, "Segunda Leitura: \n");
                            fprintf(fp, "[%s]\n", lista_de_sensores_aux->horario_2);
                            fprintf(fp, "-> %2.f\n", lista_de_sensores_aux->segunda_leitura);
                        }
                        else{
                            fprintf(fp, "Aguardando segunda leitura.\n");
                        }
                    }
                    else{
                        fprintf(fp, "Sem leituras.\n");
                    }
                    fprintf(fp, "=================================\n\n"); 
                }
            }
            if(tipo_nao_econtrado){
                fprintf(stdout, "Nao foi encontrado sensor com o tipo: %s", tipo);
            }       
        fclose(fp);
    }

    void exportar_relatorio_da_media_dos_setores(setores_t *setor, int qtd_setores_na_planta){
        getchar();
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        sensores_t *lista_de_sensores_aux = NULL;
        if(qtd_setores_na_planta > 0){
            for(setor; setor != NULL; setor = setor->prox){
                fprintf(fp, "=================================\n");
                fprintf(fp, "Relatorio de Sensores do Setor %i: \n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "Sensor numero %i\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "Sensor\t %i\n", lista_de_sensores_aux->id_do_sensor);
                        fprintf(fp, "Tipo:\t %s\n", lista_de_sensores_aux->tipo);
                        fprintf(fp, "Faixa de leitura: %.2f - %.2f\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "Media: %.2f\n", lista_de_sensores_aux->media);
                            }
                            else{
                                fprintf(fp, "\033[1;31mSem leituras suficentes para executar a media\033[0m \n");
                            }
                        }
                        else{
                            fprintf(fp, "\033[31mSem leituras.\033[0m\n");
                        }
                        fprintf(fp, "=================================\n\n"); 
                    }
                }
                else{
                    fprintf(fp, "\033[31mSem sensores cadastrados.\033[0m\n");
                }
            }
        }
        else{
                fprintf(fp, "\033[31mSem setores cadastrados.\033[0m\n");
            }
            fclose(fp);
    }

    void exportar_relatorio_de_leitura_por_sensor(sensores_t *sensor_escolhido){
        getchar();
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".txt");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        if(sensor_escolhido->numero_da_leitura > 1){
                        fprintf(fp, "Primeira Leitura: \n");
                        fprintf(fp, "[%s]\n", sensor_escolhido->horario_1);
                        fprintf(fp, "-> %2.f\n", sensor_escolhido->primeira_leitura);
                        if(sensor_escolhido->numero_da_leitura > 2){
                            fprintf(fp, "Segunda Leitura: \n");
                            fprintf(fp, "[%s]\n", sensor_escolhido->horario_2);
                            fprintf(fp, "-> %2.f\n", sensor_escolhido->segunda_leitura);
                        }
                        else{
                            fprintf(fp, "\033[31mAguardando segunda leitura.\033[0m\n");
                        }
                    }
                    else{
                        fprintf(fp, "\033[31mSem leituras.\033[0m\n");
                    }
                    fprintf(fp, "=================================\n\n"); 
        fclose(fp);
    }

void exportar_relatorio_de_leitura_por_setor_em_csv(setores_t *setor,  int qtd_setores_na_planta){
    getchar();
    FILE *fp = NULL;
    sensores_t *lista_de_sensores_aux = NULL;

    string nome_do_arquivo; 
    printf("Nome do arquivo: "); 
    fgets(nome_do_arquivo, T_MAX_STR, stdin); 
    retirar_enter(nome_do_arquivo);
    strcat(nome_do_arquivo, ".csv");
    fp = fopen(nome_do_arquivo, "w"); 
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
    fprintf(fp, "Setor;SensorSetor;SensorID;Tipo;FaixaMin;FaixaMax;Horario1;Leitura1;Horario2;Leitura2\n");
    if(qtd_setores_na_planta > 0){
        for(setor; setor != NULL; setor = setor->prox){
            fprintf(fp, "%i;", setor->id_do_setor);
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor);
                        fprintf(fp, "%s;", lista_de_sensores_aux->tipo);
                        fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_1);
                        fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_2); 
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            fprintf(fp, "%s;", lista_de_sensores_aux->horario_1);
                            fprintf(fp, "%.2f;", lista_de_sensores_aux->primeira_leitura);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "%s;", lista_de_sensores_aux->horario_2);
                                fprintf(fp, "%.2f;\n", lista_de_sensores_aux->segunda_leitura);  
                            }
                            else{
                                fprintf(fp,"aguardando segunda leitura\n");
                            }
                        }
                        else{
                            fprintf(fp,"Sem leitura\n");
                        }
                        fprintf(fp, "\n");
                        }
                
            }
            else{
                fprintf(fp,"sem sensores cadastrados\n");
            }
        }
        
    }
    else{
        fprintf(fp,"sem setores cadastrados\n");
    }
        fclose(fp);
}

void exportar_relatorio_de_variacao_por_setor_em_csv(setores_t *setor){
    getchar();
    sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".csv");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "Setor;IdSensorSetor;IdSetor;Variacao\n");
        fprintf(fp, "%i;", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "%.2f\n;", lista_de_sensores_aux->variacao_leitura);
                            }
                        }
                    }
                    else{
                        fprintf(fp, "Sem sensores cadastrados\n");
                    }
            fclose(fp);
}

void exportar_relatorio_de_leitura_pelo_setor_em_csv(setores_t *setor){
    getchar();
                sensores_t *lista_de_sensores_aux = NULL;

            string nome_do_arquivo; 
            printf("Nome do arquivo: "); 
            fgets(nome_do_arquivo, T_MAX_STR, stdin); 
            retirar_enter(nome_do_arquivo);
            strcat(nome_do_arquivo, ".csv");

            FILE *fp = fopen(nome_do_arquivo,"w");
            if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
            fprintf(fp, "IdSetor;IdSensorSetor;IdSensor;Tipo;FaixaLeitura1;FaixaLeitura2;Horario1;Leitura1;Horario2;Leitura2\n");
            fprintf(fp, "%i;", setor->id_do_setor);
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                    fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor_no_setor);
                    fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor);
                    fprintf(fp, "%s;", lista_de_sensores_aux->tipo);
                    fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_1);
                    fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        fprintf(fp, "%s;", lista_de_sensores_aux->horario_1);
                        fprintf(fp, "%2.f;", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            fprintf(fp, "%s;", lista_de_sensores_aux->horario_2);
                            fprintf(fp, "%2.f;\n", lista_de_sensores_aux->segunda_leitura);
                        }
                        else{
                            fprintf(fp,"Aguardando segunda leitura\n");
                        }
                    }
                    else{
                        fprintf(fp,"Sem leituras\n");
                    }
                }   
            }
            else{
                fprintf(fp,"Sem sensores cadastrados\n");
            }
            fclose(fp);
    }

void exportar_relatorio_de_variacao_por_sensor_em_csv(sensores_t *sensor){
    getchar();
        
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".csv");
        
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "IdSensorSetor;VariacaoLeitura\n");
        if(sensor->numero_da_leitura > 2){
            fprintf(fp, "%i;", sensor->id_do_sensor_no_setor);
            fprintf(fp, "%.2f;\n", sensor->variacao_leitura);     
        }
        else{
            fprintf(fp,"Sem leitura suficiente para o calculo de variacao\n");
        } 
        fclose(fp);
}
void exportar_relatorio_de_leitura_por_tipo_em_csv(setores_t *setor){
    getchar();
        sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
        int tipo_nao_econtrado = 1;
        string tipo;
        printf("Tipo: ");
        fgets(tipo, T_MAX_STR, stdin);
        retirar_enter(tipo);
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".csv");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "Setor;SensorSetor;SensorID;Tipo;FaixaMin;FaixaMax;Horario1;Leitura1;Horario2;Leitura2\n");
            for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                if(!(strcmp(tipo, lista_de_sensores_aux->tipo))){
                    fprintf(fp, "%i;", setor->id_do_setor);
                    tipo_nao_econtrado = 0;
                    fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor_no_setor);
                    fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor);
                    fprintf(fp, "%s;", lista_de_sensores_aux->tipo);
                    fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_1);
                    fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        fprintf(fp, "%s;", lista_de_sensores_aux->horario_1);
                        fprintf(fp, "%2.f;", lista_de_sensores_aux->primeira_leitura);
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            fprintf(fp, "%s;", lista_de_sensores_aux->horario_2);
                            fprintf(fp, "%2.f;\n", lista_de_sensores_aux->segunda_leitura);
                        }
                        else{
                            fprintf(fp,"Aguardando segunda leitura\n");
                        }
                    }
                    else{
                        fprintf(fp,"Sem leitura\n");
                    }
                }
            }
            if(tipo_nao_econtrado){
                fprintf(stdout, "Tipo: %s nao encontrado.\n", tipo);
            }       
        fclose(fp);
}
void exportar_relatorio_da_media_dos_setores_em_csv(setores_t *setor, int qtd_setores_na_planta){
    getchar();
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".csv");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        sensores_t *lista_de_sensores_aux = NULL;
        fprintf(fp, "Setor;IdSensorSetor;IdSensor;Tipo;Leitura1;Leitura2;Media\n");
        if(qtd_setores_na_planta > 0){
            for(setor; setor != NULL; setor = setor->prox){
                fprintf(fp, "%i", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "%i;", lista_de_sensores_aux->id_do_sensor);
                        fprintf(fp, "%s;", lista_de_sensores_aux->tipo);
                        fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_1);
                        fprintf(fp, "%.2f;", lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "%.2f;\n", lista_de_sensores_aux->media);
                            }
                            else{
                                fprintf(fp,"Sem leituras para executar a media\n");
                            }
                           
                        }
                        else{
                            fprintf(fp,"Sem leitura\n");
                        }
                        
                    }
                }
                else{
                    fprintf(fp,"Sem sensores cadastrados\n");
                }
                
            }
        }
        else{
            fprintf(fp,"Sem setores cadastrados\n");
        }
        
            fclose(fp);
}
void exportar_relatorio_de_leitura_por_sensor_em_csv(sensores_t *sensor_escolhido){
    getchar();
    string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".csv");
        
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "Horario1;Leitura1;Horario2;Leitura2\n");
        if(sensor_escolhido->numero_da_leitura > 1){
                        fprintf(fp, "%s;", sensor_escolhido->horario_1);
                        fprintf(fp, "%2.f;", sensor_escolhido->primeira_leitura);
                        if(sensor_escolhido->numero_da_leitura > 2){
                            fprintf(fp, "%s;", sensor_escolhido->horario_2);
                            fprintf(fp, " %2.f\n;", sensor_escolhido->segunda_leitura);
                        }
                        else{
                            fprintf(fp,"Aguardando segunda leitura");
                            return;
                        }
                    }
                    else{
                        fprintf(fp,"Sem leitura");
                        return;
                    }
        fclose(fp);

}

void exportar_relatorio_de_leitura_por_setor_em_html(setores_t *setor,  int qtd_setores_na_planta){
    getchar();
    FILE *fp = NULL;
    sensores_t *lista_de_sensores_aux = NULL;

    string nome_arq; 
    printf("Nome do arquivo: "); 
    fgets(nome_arq, T_MAX_STR, stdin); 
    retirar_enter(nome_arq);
    strcat(nome_arq, ".html");
    fp = fopen(nome_arq, "w"); 
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "   <title> Relatorio de Variacao dos Sensores pelos Setor</title>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    if(qtd_setores_na_planta > 0){
        for(setor; setor != NULL; setor = setor->prox){
            fprintf(fp, "<h1>Relatorio de leitura dos Sensores do Setor [%i]\n</h1>\n", setor->id_do_setor);;
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "<p>Sensor n. [%i]\n</p>", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "<p>Sensor - ID [%i]\n</p>", lista_de_sensores_aux->id_do_sensor);
                        fprintf(fp, "<p>Tipo: %s\n</p>", lista_de_sensores_aux->tipo);
                        fprintf(fp, "<p>Faixa: [%.2f - %.2f]\n</p>", lista_de_sensores_aux->faixa_leitura_1 , lista_de_sensores_aux->faixa_leitura_2);
                        if(lista_de_sensores_aux->numero_da_leitura > 1){
                            fprintf(fp, "<p>Horario 1: %s\n</p>;", lista_de_sensores_aux->horario_1);
                            fprintf(fp, "<p>Leitura 1: %.2f\n</p>;", lista_de_sensores_aux->primeira_leitura);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "<p>Horario 2: %s\n</p>\n", lista_de_sensores_aux->horario_2);
                                fprintf(fp, "<p>Leitura 2: %.2f\n</p>\n", lista_de_sensores_aux->segunda_leitura);  
                            }
                            else{
                                fprintf(fp,"<p>aguardando segunda leitura</p>\n");
                            }
                        }
                        else{
                            fprintf(fp,"<p>Sem leituras</p>\n");
                        }
                        fprintf(fp, "\n");
                        }
                
            }
            else{
                fprintf(fp,"sem sensores cadastrados\n");
            }
        }
        
    }
    else{
        fprintf(fp,"sem setores cadastrados\n");
    }
    
        fprintf(fp, "</body></html>\n");
        fclose(fp);

}
    
void exportar_relatorio_de_variacao_por_setor_em_html(setores_t *setor){
    sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
    FILE *fp = NULL;
     getchar();
    string nome_arq; 
        printf("Nome do arquivo: "); 
        fgets(nome_arq, T_MAX_STR, stdin); 
        retirar_enter(nome_arq);
        strcat(nome_arq, ".html");

    fp = fopen(nome_arq, "w");
        fprintf(fp, "<html>\n");
        fprintf(fp, "<head>\n");
        fprintf(fp, "   <title> Relatorio de Variacao dos Sensores por Setor</title>\n");
        fprintf(fp, "</head>\n");
        fprintf(fp, "<body>\n");
        fprintf(fp, "<h1>Relatorio de Variacao dos Sensores do Setor [%i]\n", setor->id_do_setor);
                if(setor->qtd_sensores_no_setor > 0){
                    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                        fprintf(fp, "<p>=================================\n</p>\n"); 
                        fprintf(fp, "<p>Sensor [%i]</p>\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                        fprintf(fp, "<p>Sensor ID:[%i]</p>\n", lista_de_sensores_aux->id_do_sensor);
                            if(lista_de_sensores_aux->numero_da_leitura > 2){
                                fprintf(fp, "<p>Variacao: %.2f</p>\n", lista_de_sensores_aux->variacao_leitura);
                            }
                            else{
                                fprintf(fp, "<p>Sem leitura suficientes para o calculo da variacao</p>\n");
                            }
                        fprintf(fp, "<p>=================================\n\n</p>\n"); 
                        }
                    }
                    else{
                        fprintf(fp, "<p>Sem sensores cadastrados.</p>\n");
                    }
        fprintf(fp, "</body>\n");
        fprintf(fp, "</body></html>\n");
        fclose(fp);
}

void exportar_relatorio_de_leitura_pelo_setor_em_html(setores_t *setor){
    getchar();
    FILE *fp = NULL;
    sensores_t *lista_de_sensores_aux = NULL;

    string nome_arq; 
    printf("Nome do arquivo: "); 
    fgets(nome_arq, T_MAX_STR, stdin); 
    retirar_enter(nome_arq);
    strcat(nome_arq, ".html");
    fp = fopen(nome_arq, "w"); 
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "   <title> Relatorio de leitura dos Sensor pelo Setor</title>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    fprintf(fp, "<h1>Relatorio de leitura dos Sensores do Setor [%i]\n</h1>\n", setor->id_do_setor);;
    if(setor->qtd_sensores_no_setor > 0){
        lista_de_sensores_aux = setor->sensores_do_setor;
        fprintf(fp, "<p>Sensor n. [%i]\n</p>", lista_de_sensores_aux->id_do_sensor_no_setor);
        fprintf(fp, "<p>Sensor - ID [%i]\n</p>", lista_de_sensores_aux->id_do_sensor);
        fprintf(fp, "<p>Tipo: %s\n</p>", lista_de_sensores_aux->tipo);
        fprintf(fp, "<p>Faixa: [%.2f - %.2f]\n</p>", lista_de_sensores_aux->faixa_leitura_1 , lista_de_sensores_aux->faixa_leitura_2);
        if(lista_de_sensores_aux->numero_da_leitura > 1){
            fprintf(fp, "<p>Horario 1: %s\n</p>;", lista_de_sensores_aux->horario_1);
            fprintf(fp, "<p>Leitura 1: %.2f\n</p>;", lista_de_sensores_aux->primeira_leitura);
            if(lista_de_sensores_aux->numero_da_leitura > 2){
                fprintf(fp, "<p>Horario 2: %s\n</p>\n", lista_de_sensores_aux->horario_2);
                fprintf(fp, "<p>Leitura 2: %.2f\n</p>\n", lista_de_sensores_aux->segunda_leitura);  
            }
            else{
                fprintf(fp,"<p>aguardando segunda leitura</p>\n");
            }
        }
        else{
            fprintf(fp,"<p>Sem leituras</p>\n");
        }
        fprintf(fp, "\n");
    }
    else{
        fprintf(fp,"sem sensores cadastrados\n");
    }
        
    
        fprintf(fp, "</body></html>\n");
        fclose(fp);

}

void exportar_relatorio_de_variacao_por_sensor_em_html(sensores_t *sensor){
    getchar();
    string nome_arq; 
    printf("Nome do arquivo: "); 
    fgets(nome_arq, T_MAX_STR, stdin); 
    retirar_enter(nome_arq);
    strcat(nome_arq, ".html");
    FILE *fp = fopen(nome_arq,"w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "   <title> Relatorio de variacao do Sensor [%i]</title>\n", sensor->id_do_sensor_no_setor);
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    if(sensor->numero_da_leitura > 2){
        fprintf(fp, "<h1>Sensor %i\n</h1>\n", sensor->id_do_sensor_no_setor);
        fprintf(fp, "<p>Variacao: %.2f\n</p>\n", sensor->variacao_leitura);     
    }
    else{
        fprintf(fp, "<p>Sem leitura suficientes para o calculo da variacao</p>\n");
    }
    fprintf(fp, "<p>\n\n</p>\n");
    fprintf(fp, "</body></html>\n"); 
    fclose(fp);
}

void exportar_relatorio_de_leitura_por_tipo_em_html(setores_t *setor){
    getchar();
    sensores_t *lista_de_sensores_aux = setor->sensores_do_setor;
    int tipo_nao_econtrado = 1;
    string tipo, nome_arq;
    printf("Tipo: ");
    fgets(tipo, T_MAX_STR, stdin);
    retirar_enter(tipo);
    printf("Nome do arquivo: "); 
    fgets(nome_arq, T_MAX_STR, stdin); 
    retirar_enter(nome_arq);
    strcat(nome_arq, ".html");
    FILE *fp = fopen(nome_arq,"w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "   <title> Relatorio de variacao do Setor [%i]</title>\n", setor->id_do_setor);
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
        if(!(strcmp(tipo, lista_de_sensores_aux->tipo))){
            tipo_nao_econtrado = 0;
            fprintf(fp, "<h1>Sensor numero %i\n</h1>\n", lista_de_sensores_aux->id_do_sensor_no_setor);
            fprintf(fp, "<h2>Sensor\t %i\n</h2>\n", lista_de_sensores_aux->id_do_sensor);
            fprintf(fp, "<p>Tipo:  \t %s\n</p>\n", lista_de_sensores_aux->tipo);
            fprintf(fp, "<p>Faixa de leitura: %.2f - %.2f\n</p>\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
            if(lista_de_sensores_aux->numero_da_leitura > 1){
                fprintf(fp, "<p>Primeira Leitura: \n</p>\n");
                fprintf(fp, "<p>[%s]\n</p>\n", lista_de_sensores_aux->horario_1);
                fprintf(fp, "<p>-> %2.f\n</p>\n", lista_de_sensores_aux->primeira_leitura);
                if(lista_de_sensores_aux->numero_da_leitura > 2){
                    fprintf(fp, "<p>Segunda Leitura: \n</p>\n");
                    fprintf(fp, "<p>[%s]\n</p>\n", lista_de_sensores_aux->horario_2);
                    fprintf(fp, "<p>-> %2.f\n</p>\n", lista_de_sensores_aux->segunda_leitura);
                }
                else{
                    fprintf(fp, "<p>Aguardando segunda leitura.\n</p>\n");
                }
            }
            else{
                fprintf(fp, "<p>Sem leituras.\n</p>\n");
            }
            fprintf(fp, "<p>\n\n</p>\n"); 
        }
    }
        if(tipo_nao_econtrado){
        fprintf(stdout, "Nao foi encontrado sensor com o tipo: %s", tipo);
        return;
        }    
    
    fprintf(fp, "<p>\n\n</p>\n");
    fprintf(fp, "</body></html>\n");    
    fclose(fp);
    
}
    
void exportar_relatorio_da_media_dos_setores_em_html(setores_t *setor,  int qtd_setores_na_planta){
    sensores_t *lista_de_sensores_aux = NULL;
    getchar();
    string nome_arq; 
    printf("Nome do arquivo: "); 
    fgets(nome_arq, T_MAX_STR, stdin); 
    retirar_enter(nome_arq);
    strcat(nome_arq, ".html");
    FILE *fp = fopen(nome_arq,"w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if(qtd_setores_na_planta > 0){
        fprintf(fp, "<html>\n");
        fprintf(fp, "<head>\n");
        fprintf(fp, "   <title> Relatorio de media dos Setores </title>\n");
        fprintf(fp, "</head>\n");
        fprintf(fp, "<body>\n");
        for(setor; setor != NULL; setor = setor->prox){
            fprintf(fp, "<h1>Relatorio de Sensores do Setor [%i]\n</h1>\n", setor->id_do_setor);
            if(setor->qtd_sensores_no_setor > 0){
                lista_de_sensores_aux = setor->sensores_do_setor;
                for(lista_de_sensores_aux; lista_de_sensores_aux != NULL; lista_de_sensores_aux = lista_de_sensores_aux->prox){
                    fprintf(fp, "<h2>Sensor numero [%i]\n</h2>\n", lista_de_sensores_aux->id_do_sensor_no_setor);
                    fprintf(fp, "<p>Sensor\t [%i]\n</p>\n", lista_de_sensores_aux->id_do_sensor);
                    fprintf(fp, "<p>Tipo: \t %s\n</p>\n", lista_de_sensores_aux->tipo);
                    fprintf(fp, "<p>Faixa de leitura: [%.2f - %.2f]</p>\n\n", lista_de_sensores_aux->faixa_leitura_1, lista_de_sensores_aux->faixa_leitura_2);
                    if(lista_de_sensores_aux->numero_da_leitura > 1){
                        if(lista_de_sensores_aux->numero_da_leitura > 2){
                            fprintf(fp, "Media: %.2f\n", lista_de_sensores_aux->media);
                        }
                        else{
                            fprintf(fp, "<p>Sem leituras suficentes para executar a media\n</p>\n");
                        }
                    }
                    else{
                        fprintf(fp, "<p>Sem leituras.\n</p>\n");
                    }
                    fprintf(fp, "=================================\n\n"); 
                }
            }
            else{
                fprintf(fp, "<p>Sem sensores cadastrados.\n</p>\n");
            }
        }
    }
    else{
            printf("Sem setores cadastrados.\n");
            fclose(fp);
            return;
        }
    
    fprintf(fp, "<p>\n\n</p>\n");
    fprintf(fp, "</body></html>\n"); 
    fclose(fp);
    }

    
void exportar_relatorio_de_leitura_por_sensor_em_html(sensores_t *sensor){
    getchar();
        string nome_do_arquivo; 
        printf("Nome do arquivo: "); 
        fgets(nome_do_arquivo, T_MAX_STR, stdin); 
        retirar_enter(nome_do_arquivo);
        strcat(nome_do_arquivo, ".html");
        FILE *fp = fopen(nome_do_arquivo,"w");
        if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        fprintf(fp, "<html>\n");
        fprintf(fp, "<head>\n");
        fprintf(fp, "   <title> Relatorio de media dos Setores </title>\n");
        fprintf(fp, "</head>\n");
        fprintf(fp, "<body>\n");
        fprintf(fp, "<h1>Sensor [%i]\n</h1>\n", sensor->id_do_sensor);
        if(sensor->numero_da_leitura > 1){
                        fprintf(fp, "<h2>Primeira Leitura: \n</h2>\n");
                        fprintf(fp, "<p>[%s]\n</p>\n", sensor->horario_1);
                        fprintf(fp, "<p>-> %2.f\n</p>\n", sensor->primeira_leitura);
                        if(sensor->numero_da_leitura > 2){
                            fprintf(fp, "<h2>Segunda Leitura:\n</h2>\n");
                            fprintf(fp, "<p>[%s]\n</p>\n", sensor->horario_2);
                            fprintf(fp, "<p>-> %2.f</p>\n\n", sensor->segunda_leitura);
                        }
                        else{
                            fprintf(fp, "<p>Aguardando segunda leitura.\n</p>\n\n");
                        }
                    }
                    else{
                        fprintf(fp, "<p>Sem leituras.\n</p>\n");
                    }
        
    fprintf(fp, "<p>\n\n</p>\n");
    fprintf(fp, "</body></html>\n"); 
    fclose(fp);
}