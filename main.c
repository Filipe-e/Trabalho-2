    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>
    #include <unistd.h>
    #include <time.h>
    #include <stdlib.h>
    #include "./Includes/types.h"
    #include "./Includes/menus.h"
    #include "./Includes/functions.h"


    int main(){
        sensores_t *sensor_atual = NULL;
        setores_t *setor_atual = NULL;
        planta_industria_t *industria_atual = NULL;
        int qtd_industrias = 0;
        int opcao_main, setor_selecionado, sensor_a_ser_copiado;
        string selecao_temp;
        planta_industria_t *industrias = NULL;
        planta_industria_t *industria_zerada = NULL;
        industria_zerada = malloc(sizeof(planta_industria_t));
        ler_industrias_bin(&industrias, "industrias.bin", &qtd_industrias);
        ler_setores_bin(industrias, "setores.bin");
        ler_tipo_sensores_bin(industrias, "tipos_sensores.bin");
        ler_sensores_no_setores_bin(industrias, "sensores_do_setor.bin");
        do{
            limpar_tela();
            opcao_main = menu_industria();
            int selecao1, selecao2, selecao3, opcao_setor_selecionado, sensor_selecionado; 
            int opcao_setor, opcao_sensor;
            switch (opcao_main){
                //case industria - cadastrar
                case 1:
                    
                    limpar_tela();
                    if(qtd_industrias < T_MAX_INDUSTRIAS){
                        planta_industria_t *nova = cadastrar_industria(qtd_industrias);
                        inserir_industria(&industrias, nova);
                        qtd_industrias++;
                    }
                    else{
                        printf("\033[1;31mLimite maximo de industrias atingido!!!\033[0m\n");
                        esperar_prosseguir();
                    }
                    limpar_tela();
                    break;
                    //case industria - listar 
                case 2:
                    limpar_tela();
                    if(qtd_industrias > 0){      
                    listar_industrias(industrias, qtd_industrias); 
                    }
                    else{
                        printf("\033[31mAinda nao ha industrias cadastradas\n\033[0m");
                    }
                    esperar_prosseguir();
                    break;
                //case industria selecionar    
                case 3:
                    printf("qtd: %i \n", qtd_industrias);
                    limpar_tela();
                    if(qtd_industrias > 0){
                        printf("Industrias disponiveis: \n");
                        listar_industrias(industrias, qtd_industrias);  
                        printf("Industria selecionada: ");
                        while(scanf("%i", &selecao1) != 1){
                            printf("Entrada invalida! Digite novamente: ");
                            while(getchar() != '\n'); // limpa
                        }
                        if(selecao1 < qtd_industrias){
                            do{
                                usleep(1000000);
                                limpar_tela();
                                selecao2 = menu_setor_sensor(selecao1); 
                                industria_atual = pesquisar_industria_por_id(industrias, selecao1);
                                switch (selecao2){
                                    //menu dentro industria escolhida - entra em setores
                                    case 1:
                                        do{
                                            limpar_tela();
                                            opcao_setor = menu_setor(selecao1);
                                            switch (opcao_setor){
                                                // Menu dentro de setor dentro da industria - cadastra um setor
                                                case 1:
                                                    getchar();
                                                    if(industria_atual->qtd_setores_na_planta < T_MAX_SETORES){
                                                        inserir_setor_na_industria(&(industria_atual->setores_da_planta), cadastrar_setor(industria_atual));
                                                    }else{
                                                        printf("\033[31mNumero de setores maximo atingido\033[0m");
                                                    }
                                                    break;
                                                // Menu dentro de setor dentro da industria - lista os setores
                                                case 2:   
                                                    if(industria_atual->qtd_setores_na_planta  > 0){
                                                        listar_setores_por_industria(industria_atual->setores_da_planta);
                                                        esperar_prosseguir();
                                                    }
                                                    else{
                                                        getchar();
                                                        printf("\033[1;31mAinda nao ha setores cadastrados!\033[0m\n");
                                                        printf("\033[1;34mDeseja cadastrar um novo setor? [S/N] \033[0m");
                                                        fgets(selecao_temp, T_MAX_STR, stdin);
                                                        retirar_enter(selecao_temp);
                                                        if(!strcmp(selecao_temp, "S")){
                                                            inserir_setor_na_industria(&(industria_atual->setores_da_planta), cadastrar_setor(industria_atual));
                                                        }
                                                    }
                                                    break;
                                                // Menu dentro de setor dentro da industria - seleciona um setor para atribuir um sensor 
                                                case 3:
                                                    if(industria_atual->qtd_setores_na_planta > 0){
                                                            printf("Setores diposniveis:\n");
                                                            listar_setores_por_industria(industria_atual->setores_da_planta);    
                                                            setor_selecionado = menu_escolha_setor();
                                                            setor_atual = pesquisar_setor_por_id_recursiva(industria_atual->setores_da_planta, setor_selecionado);
                                                            if(setor_selecionado < industria_atual->qtd_setores_na_planta){
                                                                do{
                                                                    limpar_tela();
                                                                    opcao_setor_selecionado = menu_opcao_setor_selecionado(setor_selecionado);
                                                                    switch (opcao_setor_selecionado)
                                                                    {
                                                                        // menu dentro de setor escolhido - cadastra um sensor 
                                                                    case 1:
                                                                        if(industria_atual->qtd_setores_na_planta > 0){
                                                                            listar_sensores_por_industria(industria_atual->tipos_de_sensores);
                                                                            printf("Sensor escolhido: ");
                                                                            scanf("%i", &sensor_a_ser_copiado);
                                                                            inserir_sensor_no_setor(&(setor_atual->sensores_do_setor), criar_uma_copia(pesquisar_sensor_por_id(industria_atual->tipos_de_sensores, sensor_a_ser_copiado), setor_atual->qtd_sensores_no_setor), setor_atual);
                                                                            setor_atual->qtd_sensores_no_setor = setor_atual->qtd_sensores_no_setor + 1;
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
                                                                                inserir_sensor_na_industria(&(industria_atual->tipos_de_sensores), cadastrar_sensor(industria_atual));
                                                                            }
                                                                        }
                                                                        break;
                                                                        // menu dentro de setor escolhido - seleciona um sensor para efetuar as leituras/entra no menu de monitoramento 
                                                                    case 2:
                                                                        if(setor_atual->qtd_sensores_no_setor > 0){
                                                                            //sensor_atual = pesquisar_sensor_por_id_no_setor(setor_atual->sensores_do_setor, sensor_selecionado);
                                                                            listar_sensores_por_setor(setor_atual->sensores_do_setor);
                                                                            printf("\033[1;34mOpcao escolhida:\033[0m ");
                                                                            while(scanf("%i", &sensor_selecionado) != 1){
                                                                                printf("Entrada invalida! Digite novamente: ");
                                                                                while(getchar() != '\n'); // limpa
                                                                            }
                                                                            sensor_atual = pesquisar_sensor_por_id_no_setor(setor_atual->sensores_do_setor, sensor_selecionado);
                                                                            if(sensor_selecionado < setor_atual->qtd_sensores_no_setor){
                                                                                do{
                                                                                    limpar_tela();
                                                                                    opcao_sensor = menu_sensor_selecionado();
                                                                                    switch (opcao_sensor)
                                                                                    {
                                                                                    case 1:
                                                                                        if(sensor_atual->numero_da_leitura < 3){
                                                                                            leitura_do_sensor(sensor_atual);
                                                                                        }
                                                                                        else{
                                                                                            printf("Leituras ja efetuadas!");
                                                                                            esperar_prosseguir();
                                                                                        }
                                                                                        break;
                                                                                    case 2:
                                                                                        relatorio_de_leitura_por_sensor(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 3:
                                                                                        relatorio_de_variacao_por_sensor(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 4:
                                                                                        exportar_relatorio_de_variacao_por_sensor(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 5: 
                                                                                        exportar_relatorio_de_leitura_por_sensor(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 6:
                                                                                        exportar_relatorio_de_variacao_por_sensor_em_csv(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 7: 
                                                                                        exportar_relatorio_de_leitura_por_sensor_em_csv(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 8:
                                                                                        exportar_relatorio_de_variacao_por_sensor_em_html(sensor_atual);
                                                                                        esperar_prosseguir();
                                                                                        break;
                                                                                    case 9:
                                                                                        exportar_relatorio_de_leitura_por_sensor_em_html(sensor_atual);
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
                                                                        listar_sensores_por_setor(setor_atual->sensores_do_setor);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 4:
                                                                        relatorio_de_leitura_pelo_setor(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 5:
                                                                        relatorio_de_leitura_por_tipo(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 6:
                                                                        relatorio_de_variacao_por_setor(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 7:
                                                                        exportar_relatorio_de_variacao_por_setor(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 8:
                                                                        exportar_relatorio_de_leitura_pelo_setor(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 9:
                                                                        exportar_relatorio_de_leitura_por_tipo(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 10:
                                                                        exportar_relatorio_de_variacao_por_setor_em_csv(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 11:
                                                                        exportar_relatorio_de_leitura_pelo_setor_em_csv(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 12:
                                                                        exportar_relatorio_de_leitura_por_tipo_em_csv(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 13:
                                                                        listar_sensores_por_setor(setor_atual->sensores_do_setor);
                                                                        remover_sensor(&(setor_atual->sensores_do_setor), setor_atual);
                                                                        printf("\033[1;32mLista atualizada com sucesso\033[0m\n");
                                                                        listar_sensores_por_setor(setor_atual->sensores_do_setor);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 14:
                                                                        exportar_relatorio_de_leitura_pelo_setor_em_html(setor_atual);
                                                                        esperar_prosseguir();
                                                                        break;
                                                                    case 15:
                                                                        exportar_relatorio_de_leitura_por_tipo_em_html(setor_atual);
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
                                                            inserir_setor_na_industria(&(industria_atual->setores_da_planta), cadastrar_setor(industria_atual));
                                                        }
                                                    }
                                                    break;
                                                    // Menu dentro de setor dentro da industria - pesquisa por setor 
                                                case 4:
                                                    pesquisar_setor_por_descricao(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                    // Menu dentro de setor dentro da industria - relatorio dos setores
                                                case 5:
                                                    relatorio_de_leitura_por_setor(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                    // Menu dentro de setor dentro da industria - relatorio das medias dos setores
                                                case 6:
                                                    relatorio_da_media_dos_setores(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 7:
                                                    exportar_relatorio_de_leitura_por_setor(industria_atual->setores_da_planta,   industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 8:
                                                    exportar_relatorio_da_media_dos_setores(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 9:
                                                    exportar_relatorio_de_leitura_por_setor_em_csv(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 10:
                                                    exportar_relatorio_da_media_dos_setores_em_csv(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 11:
                                                    exportar_relatorio_de_leitura_por_setor_em_html(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
                                                    esperar_prosseguir();
                                                    break;
                                                case 12:
                                                    exportar_relatorio_da_media_dos_setores_em_html(industria_atual->setores_da_planta, industria_atual->qtd_setores_na_planta);
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
                                        //menu dentro industria escolhida - entra em sensores
                                    case 2:
                                        do{
                                            limpar_tela();
                                            selecao3 = menu_sensores(selecao1);
                                            switch (selecao3)
                                            {
                                            case 1:
                                                getchar();
                                                inserir_sensor_na_industria(&(industria_atual->tipos_de_sensores), cadastrar_sensor(industria_atual));
                                                break;
                                            case 2:
                                                if(industria_atual->qtd_sensores_na_planta > 0){
                                                    listar_sensores_por_industria(industria_atual->tipos_de_sensores);
                                                    esperar_prosseguir();
                                                }
                                                else{ 
                                                    getchar();
                                                    printf("\033[1;31mAinda nao ha sensores cadastrados!\033[0m\n");
                                                    printf("\033[1;34mDeseja cadastrar um novo sensor? [S/N] \033[0m");
                                                    fgets(selecao_temp, T_MAX_STR, stdin);
                                                    retirar_enter(selecao_temp);
                                                    if(!strcmp(selecao_temp, "S")){
                                                        inserir_sensor_na_industria(&(industria_atual->tipos_de_sensores), cadastrar_sensor(industria_atual));
                                                    }
                                                }
                                                break;
                                            case 3:
                                                pesquisar_sensor_por_tipo(industria_atual->tipos_de_sensores, industria_atual->qtd_sensores_na_planta);
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

        }while(opcao_main != 0);
        exportar_industrias_bin(industrias, "industrias.bin");
        exportar_setores_bin(industrias, "setores.bin");
        exportar_tipos_sensores_bin(industrias, "tipos_sensores.bin");
        exportar_sensores_bin(industrias, "sensores_do_setor.bin");
    }
