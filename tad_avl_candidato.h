#ifndef _TAD_AVL_CANDIDATO_H_
#define _TAD_AVL_CANDIDATO_H_

#include "tad_abb_candidato.h" // Inclui a definição de Candidato

// Estrutura do nó da AVL
typedef struct No_avl
{
    Candidato candidato;
    struct No_avl *esq;
    struct No_avl *dir;
    int altura;
} No_avl;

// Estrutura da AVL
typedef struct Arvore_avl
{
    No_avl *raiz;
} Arvore_avl;

// Funções de manipulação da AVL
Arvore_avl *avl_criar();
void avl_liberar(Arvore_avl *arv);
int avl_inserir(Arvore_avl *arv, Candidato candidato);
int avl_remover(Arvore_avl *arv, Candidato candidato);
No_avl *avl_buscar(Arvore_avl *arv, Candidato candidato);
int avl_tamanho(Arvore_avl *arv);
int avl_vazia(Arvore_avl *arv);
void avl_imprimir_in_ordem(Arvore_avl *arv);
void avl_imprimir_pre_ordem(Arvore_avl *arv);
void avl_imprimir_pos_ordem(Arvore_avl *arv);

Arvore_avl *filtrar_por_estado_avl(Arvore_avl *arv, char estado[]);
void copiar_subarvore_avl(No_avl *no, Arvore_avl *sub_arv, char estado[]);
Arvore_avl *filtrar_por_cidade_avl(Arvore_avl *arv, char cidade[]);
void copiar_subarvore_cidade_avl(No_avl *no, Arvore_avl *sub_arv, char cidade[]);
Arvore_avl *filtrar_por_chave_avl(Arvore_avl *arv, char chave, char argumento[]);
void copiar_subarvore_chave_avl(No_avl *no, Arvore_avl *sub_arv, char chave, char argumento[]);
int comparar_chave_avl(Candidato candidato, char chave, char argumento[]);

#endif // _TAD_AVL_CANDIDATO_H_