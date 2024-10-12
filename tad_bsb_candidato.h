#ifndef _TAD_BSB_CANDIDATO_H_
#define _TAD_BSB_CANDIDATO_H_

#include "tad_abb_candidato.h" // Inclui a definição de Candidato

#define MAX_CANDIDATOS 100

// Estrutura da Busca Binária em Vetor
typedef struct
{
    Candidato *candidatos; // Ponteiro para o vetor dinâmico
    int tamanho;
    int capacidade; // Capacidade atual do vetor
} Vetor_bsb;

// Funções auxiliares
int comparar_candidatos_bsb(Candidato c1, Candidato c2);
void imprimir_candidato_completo_bsb(Candidato c);
void imprimir_candidato_simples_bsb(Candidato c);
int bsb_redimensionar(Vetor_bsb *vet, int nova_capacidade);

// Funções de manipulação da Busca Binária em Vetor
Vetor_bsb *bsb_criar();
void bsb_liberar(Vetor_bsb *vet);
int bsb_inserir(Vetor_bsb *vet, Candidato candidato);
int bsb_remover(Vetor_bsb *vet, Candidato candidato);
int bsb_buscar(Vetor_bsb *vet, Candidato candidato);
int bsb_tamanho(Vetor_bsb *vet);
int bsb_vazia(Vetor_bsb *vet);
void bsb_imprimir(Vetor_bsb *vet);

Vetor_bsb *filtrar_por_estado_bsb(Vetor_bsb *vet, char estado[]);
Vetor_bsb *filtrar_por_cidade_bsb(Vetor_bsb *vet, char cidade[]);
Vetor_bsb *filtrar_por_chave_bsb(Vetor_bsb *vet, char chave, char argumento[]);
int comparar_chave_bsb(Candidato candidato, char chave, char argumento[]);

#endif // _TAD_BSB_CANDIDATO_H_