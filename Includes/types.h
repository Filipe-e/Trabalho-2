#ifndef _TYPES_H
#define _TYPES_H
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
        int id_da_planta_mae;
        int id_do_setor_mae;
        int id_do_sensor_no_setor;
        int id_do_sensor;
        string tipo;
        float faixa_leitura_1;
        float faixa_leitura_2;
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
        int id_da_planta_mae;
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

#endif