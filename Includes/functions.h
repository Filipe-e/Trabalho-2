#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <string.h>
#include <stdlib.h>
#include "types.h"

// Industrias
planta_industria_t *cadastrar_industria(int qtd_industrias);
void listar_industrias(planta_industria_t *industria, int qtd_industrias);
void inserir_industria(planta_industria_t **industrias, planta_industria_t *nova_industria);
void inserir_sensor_na_industria(sensores_t **tipos_de_sensores, sensores_t *sensor_novo);
void inserir_setor_na_industria(setores_t **setores_da_planta, setores_t *setor_novo);
// cria uma planta vazia
planta_industria_t *criar_planta_de_industria(void);
// pesquisa por id
planta_industria_t *pesquisar_industria_por_id(planta_industria_t *industrias, int id_industria);
// setores
setores_t *cadastrar_setor(planta_industria_t *industria);
sensores_t *criar_uma_copia(sensores_t *tipo_de_sensor, int qtd_sensores_no_setor);
void listar_setores_por_industria(setores_t *industria);
void listar_sensores_por_setor(sensores_t *sensores_no_setor);
void relatorio_de_leitura_por_setor(setores_t *setor, int qtd_setores_na_planta);
void relatorio_de_variacao_por_setor(setores_t *setor);
void relatorio_de_leitura_pelo_setor(setores_t *setor);
void pesquisar_setor_por_descricao(setores_t *setor, int qtd_setores_no_sensor);
setores_t *pesquisar_setor_por_id_recursiva(setores_t *setores_da_planta , int id_do_setor);
setores_t *pesquisar_setor_por_id(setores_t *setores_da_planta , int id_do_setor);
// cria um setor vazio
setores_t *criar_setor_de_industria(void);
//cria um sensor vazio
sensores_t *criar_sensor_de_industria(void);
//sensores
void leitura_do_sensor(sensores_t *sensor);
void horario_da_leitura(sensores_t *sensor, int leitura);
void relatorio_de_variacao_por_sensor(sensores_t *industria);
void relatorio_de_leitura_por_tipo(setores_t *setor);
void relatorio_da_media_dos_setores(setores_t *setor, int qtd_sensores_na_planta);
void relatorio_de_leitura_por_sensor(sensores_t *industria);
void pesquisar_sensor_por_tipo(sensores_t *tipo_sensores, int qtd_sensores_na_planta);
sensores_t *pesquisar_sensor_por_id(sensores_t *tipo_sensores, int id_do_sensor);
sensores_t *cadastrar_sensor(planta_industria_t *industria);
void listar_sensores_por_industria(sensores_t *industria);
sensores_t *pesquisar_sensor_por_id_no_setor(sensores_t *sensor, int id_sensor_no_setor);
//setores
void inserir_sensor_no_setor(sensores_t **sensores_no_setor, sensores_t *tipo_de_sensor, setores_t *setor);
void remover_sensor(sensores_t **sensor, setores_t *setor_atual);
// funções auxiliares
void retirar_enter(string str);
void esperar_prosseguir(void);
void limpar_tela(void);
// exportacoes e leituras
void exportar_industrias_bin(planta_industria_t *industrias, char *nome_arq);
void ler_industrias_bin(planta_industria_t **industrias, char *nome_arq, int *qtd_industrias);
void exportar_setores_bin(planta_industria_t *industrias, char *nome_arq);
void exportar_tipos_sensores_bin(planta_industria_t *industrias, char *nome_arq);
void exportar_sensores_bin(planta_industria_t *industrias, char *nome_arq);
//EXPORTANDO EM .TXT
void exportar_relatorio_de_leitura_por_setor(setores_t *setor,  int qtd_setores_na_planta);
void exportar_relatorio_de_variacao_por_setor(setores_t *setor);
void exportar_relatorio_de_leitura_pelo_setor(setores_t *setor);
void exportar_relatorio_de_variacao_por_sensor(sensores_t *sensor);
void exportar_relatorio_de_leitura_por_tipo(setores_t *setor);
void exportar_relatorio_da_media_dos_setores(setores_t *setor, int qtd_setores_na_planta);
void exportar_relatorio_de_leitura_por_sensor(sensores_t *sensor);

//EXPORTANDO EM CSV
void exportar_relatorio_de_leitura_por_setor_em_csv(setores_t *setor,  int qtd_setores_na_planta);
void exportar_relatorio_de_variacao_por_setor_em_csv(setores_t *setor);
void exportar_relatorio_de_leitura_pelo_setor_em_csv(setores_t *setor);
void exportar_relatorio_de_variacao_por_sensor_em_csv(sensores_t *sensor);
void exportar_relatorio_de_leitura_por_tipo_em_csv(setores_t *setor);
void exportar_relatorio_da_media_dos_setores_em_csv(setores_t *setor, int qtd_setores_na_planta);
void exportar_relatorio_de_leitura_por_sensor_em_csv(sensores_t *sensor);
//EXPORTANDO EM HTML
void exportar_relatorio_de_leitura_por_setor_em_html(setores_t *setor,  int qtd_setores_na_planta);
void exportar_relatorio_de_variacao_por_setor_em_html(setores_t *setor);
void exportar_relatorio_de_leitura_pelo_setor_em_html(setores_t *setor);
void exportar_relatorio_de_variacao_por_sensor_em_html(sensores_t *sensor);
void exportar_relatorio_de_leitura_por_tipo_em_html(setores_t *setor);
void exportar_relatorio_da_media_dos_setores_em_html(setores_t *setor, int qtd_setores_na_planta);
void exportar_relatorio_de_leitura_por_sensor_em_html(sensores_t *sensor);
//Leitura de dados
void ler_setores_bin(planta_industria_t *industrias, char *nome_arq);
void ler_tipo_sensores_bin(planta_industria_t *industrias, char *nome_arq);
void ler_sensores_no_setores_bin(planta_industria_t *industrias, char *nome_arq);

#endif