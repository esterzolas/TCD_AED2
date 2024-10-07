#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"
#include "tad_bsb_candidato.h"

// Declarações das funções de filtragem e busca

// Função auxiliar de comparação para filtrar por chave
int comparar_chave(Candidato candidato, char chave, char argumento[]);

// Árvore Binária de Busca
Arvore_abb *filtrar_por_estado_abb(Arvore_abb *arv, char estado[]);
void copiar_subarvore_abb(No_abb *no, Arvore_abb *sub_arv, char estado[]);
Arvore_abb *filtrar_por_cidade_abb(Arvore_abb *arv, char cidade[]);
void copiar_subarvore_cidade_abb(No_abb *no, Arvore_abb *sub_arv, char cidade[]);
Arvore_abb *filtrar_por_chave_abb(Arvore_abb *arv, char chave, char argumento[]);
void copiar_subarvore_chave_abb(No_abb *no, Arvore_abb *sub_arv, char chave, char argumento[]);

// Árvore AVL
Arvore_avl *filtrar_por_estado_avl(Arvore_avl *arv, char estado[]);
void copiar_subarvore_avl(No_avl *no, Arvore_avl *sub_arv, char estado[]);
Arvore_avl *filtrar_por_cidade_avl(Arvore_avl *arv, char cidade[]);
void copiar_subarvore_cidade_avl(No_avl *no, Arvore_avl *sub_arv, char cidade[]);
Arvore_avl *filtrar_por_chave_avl(Arvore_avl *arv, char chave, char argumento[]);
void copiar_subarvore_chave_avl(No_avl *no, Arvore_avl *sub_arv, char chave, char argumento[]);

// Busca Binária
Vetor_bsb *filtrar_por_estado_bsb(Vetor_bsb *vet, char estado[]);
Vetor_bsb *filtrar_por_cidade_bsb(Vetor_bsb *vet, char cidade[]);
Vetor_bsb *filtrar_por_chave_bsb(Vetor_bsb *vet, char chave, char argumento[]);

// Implementações
int main()
{
    // Criação das estruturas
    Arvore_abb *abb = abb_criar();
    Arvore_avl *avl = avl_criar();
    Vetor_bsb *vetor_bsb = bsb_criar();

    // Criação de candidatos
    Candidato c1 = {"SP", "Sao Paulo", "12", "prefeito", "Joao Silva", "Joao", "PSDB", "Masculino", "Superior", "Indigena"};
    Candidato c2 = {"SP", "Sao Paulo", "40", "prefeito", "Maria Souza", "Maria", "PSD", "Feminino", "Ensino Medio", "Pardo"};
    Candidato c3 = {"SP", "Sao Paulo", "70111", "vereador", "Pedro Santos", "Pedro", "PSD", "Masculino", "Fundamental", "Branco"};
    Candidato c4 = {"MG", "Belo Horizonte", "13", "prefeito", "Duda Salabert", "Duda", "PT", "Feminino", "Superior", "Branca"};

    // Inserção dos candidatos nas estruturas
    abb_inserir(abb, c1);
    abb_inserir(abb, c2);
    abb_inserir(abb, c3);
    abb_inserir(abb, c4);

    avl_inserir(avl, c1);
    avl_inserir(avl, c2);
    avl_inserir(avl, c3);
    avl_inserir(avl, c4);

    bsb_inserir(vetor_bsb, c1);
    bsb_inserir(vetor_bsb, c2);
    bsb_inserir(vetor_bsb, c3);
    bsb_inserir(vetor_bsb, c4);

    // Impressão das estruturas
    printf("ABB:\n");
    abb_imprimir_in_ordem(abb);
    printf("\n");

    printf("AVL:\n");
    avl_imprimir_in_ordem(avl);
    printf("\n");

    printf("Vetor com Busca Binaria:\n");
    bsb_imprimir(vetor_bsb);
    printf("\n");

    // Busca de um candidato
    No_abb *no_abb = abb_buscar(abb, c4);
    No_avl *no_avl = avl_buscar(avl, c4);
    int indice_bsb = bsb_buscar(vetor_bsb, c4);

    if (no_abb != NULL)
    {
        printf("Candidato encontrado na ABB!\n");
    }

    if (no_avl != NULL)
    {
        printf("Candidato encontrado na AVL!\n");
    }

    if (indice_bsb != -1)
    {
        printf("Candidato encontrado no Vetor com Busca Binaria!\n");
    }

    Arvore_abb *sub_abb = filtrar_por_estado_abb(abb, "SP");
    printf("\nCandidatos do estado %s (ABB):\n", "SP");
    abb_imprimir_in_ordem(sub_abb);

    sub_abb = filtrar_por_cidade_abb(sub_abb, "Sao Paulo");
    printf("\nCandidatos da cidade %s (ABB):\n", "Sao Paulo");
    abb_imprimir_in_ordem(sub_abb);

    sub_abb = filtrar_por_chave_abb(sub_abb, 'P', "PSD");
    printf("\nCandidatos do partido %s (ABB):\n", "PSD");
    abb_imprimir_in_ordem(sub_abb);

    sub_abb = filtrar_por_chave_abb(sub_abb, 'G', "Feminino");
    printf("\nCandidatos do genero %s (ABB):\n", "Feminino");
    abb_imprimir_in_ordem(sub_abb);

    Vetor_bsb *sub_bsb = filtrar_por_estado_bsb(vetor_bsb, "SP");
    printf("\nCandidatos do estado %s (Vetor com Busca Binaria):\n", "SP");
    bsb_imprimir(sub_bsb);
    bsb_liberar(sub_bsb);

    // Remoção de um candidato
    abb_remover(abb, c2);
    avl_remover(avl, c2);
    bsb_remover(vetor_bsb, c2);

    // Impressão das estruturas após a remoção
    printf("\nApos a remocao de Maria Souza:\n");
    printf("ABB:\n");
    abb_imprimir_in_ordem(abb);
    printf("\n");

    printf("AVL:\n");
    avl_imprimir_in_ordem(avl);
    printf("\n");

    printf("Vetor com Busca Binaria:\n");
    bsb_imprimir(vetor_bsb);
    printf("\n");

    // Liberação de memória
    abb_liberar(abb);
    avl_liberar(avl);
    bsb_liberar(vetor_bsb);

    return 0;
}

// Funções auxiliares de comparação para filtrar por chave
int comparar_chave(Candidato candidato, char chave, char argumento[])
{
    switch (chave)
    {
    case 'G':
        return (strcmp(candidato.genero, argumento) == 0);
    case 'P':
        return (strcmp(candidato.sigla_partido, argumento) == 0);
    case 'R':
        return (strcmp(candidato.cor_raca, argumento) == 0);
    case 'N':
        return (strcmp(candidato.numero_urna, argumento) == 0);
    default:
        return 0;
    }
}

// Funções ABB
Arvore_abb *filtrar_por_estado_abb(Arvore_abb *arv, char estado[])
{
    Arvore_abb *sub_arv = abb_criar();
    if (arv == NULL || abb_vazia(arv))
    {
        return sub_arv;
    }

    No_abb *atual = arv->raiz;
    if (strcmp(atual->candidato.estado, estado) == 0)
    {
        abb_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_abb(atual->esq, sub_arv, estado);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_abb(atual->dir, sub_arv, estado);
    }

    if (abb_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }

    return sub_arv;
}

void copiar_subarvore_abb(No_abb *no, Arvore_abb *sub_arv, char estado[])
{
    if (no == NULL)
    {
        return;
    }
    if (strcmp(no->candidato.estado, estado) == 0)
    {
        abb_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_abb(no->esq, sub_arv, estado);
    copiar_subarvore_abb(no->dir, sub_arv, estado);
}

Arvore_abb *filtrar_por_cidade_abb(Arvore_abb *arv, char cidade[])
{
    Arvore_abb *sub_arv = abb_criar();

    if (arv == NULL || abb_vazia(arv))
    {
        return sub_arv;
    }

    No_abb *atual = arv->raiz;
    if (strcmp(atual->candidato.cidade, cidade) == 0)
    {
        abb_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_cidade_abb(atual->esq, sub_arv, cidade);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_cidade_abb(atual->dir, sub_arv, cidade);
    }

    if (abb_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado na cidade.\n");
    }

    return sub_arv;
}

void copiar_subarvore_cidade_abb(No_abb *no, Arvore_abb *sub_arv, char cidade[])
{
    if (no == NULL)
    {
        return;
    }
    if (strcmp(no->candidato.cidade, cidade) == 0)
    {
        abb_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_cidade_abb(no->esq, sub_arv, cidade);
    copiar_subarvore_cidade_abb(no->dir, sub_arv, cidade);
}

Arvore_abb *filtrar_por_chave_abb(Arvore_abb *arv, char chave, char argumento[])
{
    Arvore_abb *sub_arv = abb_criar();

    if (arv == NULL || abb_vazia(arv))
    {
        return sub_arv;
    }

    No_abb *atual = arv->raiz;
    if (comparar_chave(atual->candidato, chave, argumento))
    {
        abb_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_chave_abb(atual->esq, sub_arv, chave, argumento);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_chave_abb(atual->dir, sub_arv, chave, argumento);
    }

    if (abb_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }

    return sub_arv;
}

void copiar_subarvore_chave_abb(No_abb *no, Arvore_abb *sub_arv, char chave, char argumento[])
{
    if (no == NULL)
    {
        return;
    }
    if (comparar_chave(no->candidato, chave, argumento))
    {
        abb_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_chave_abb(no->esq, sub_arv, chave, argumento);
    copiar_subarvore_chave_abb(no->dir, sub_arv, chave, argumento);
}

// Funções AVL
Arvore_avl *filtrar_por_estado_avl(Arvore_avl *arv, char estado[])
{
    Arvore_avl *sub_arv = avl_criar();
    if (arv == NULL || avl_vazia(arv))
    {
        return sub_arv;
    }
    No_avl *atual = arv->raiz;
    if (strcmp(atual->candidato.estado, estado) == 0)
    {
        avl_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_avl(atual->esq, sub_arv, estado);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_avl(atual->dir, sub_arv, estado);
    }

    if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }

    return sub_arv;
}

void copiar_subarvore_avl(No_avl *no, Arvore_avl *sub_arv, char estado[])
{
    if (no == NULL)
    {
        return;
    }
    if (strcmp(no->candidato.estado, estado) == 0)
    {
        avl_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_avl(no->esq, sub_arv, estado);
    copiar_subarvore_avl(no->dir, sub_arv, estado);
}

Arvore_avl *filtrar_por_cidade_avl(Arvore_avl *arv, char cidade[])
{
    Arvore_avl *sub_arv = avl_criar();

    if (arv == NULL || avl_vazia(arv))
    {
        return sub_arv;
    }

    No_avl *atual = arv->raiz;
    if (strcmp(atual->candidato.cidade, cidade) == 0)
    {
        avl_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_cidade_avl(atual->esq, sub_arv, cidade);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_cidade_avl(atual->dir, sub_arv, cidade);
    }

    if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }

    return sub_arv;
}

void copiar_subarvore_cidade_avl(No_avl *no, Arvore_avl *sub_arv, char cidade[])
{
    if (no == NULL)
    {
        return;
    }
    if (strcmp(no->candidato.cidade, cidade) == 0)
    {
        avl_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_cidade_avl(no->esq, sub_arv, cidade);
    copiar_subarvore_cidade_avl(no->dir, sub_arv, cidade);
}

Arvore_avl *filtrar_por_chave_avl(Arvore_avl *arv, char chave, char argumento[])
{
    Arvore_avl *sub_arv = avl_criar();

    if (arv == NULL || avl_vazia(arv))
    {
        return sub_arv;
    }

    No_avl *atual = arv->raiz;
    if (comparar_chave(atual->candidato, chave, argumento))
    {
        avl_inserir(sub_arv, atual->candidato);
    }
    if (atual->esq != NULL)
    {
        copiar_subarvore_chave_avl(atual->esq, sub_arv, chave, argumento);
    }
    if (atual->dir != NULL)
    {
        copiar_subarvore_chave_avl(atual->dir, sub_arv, chave, argumento);
    }

    if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }

    return sub_arv;
}

void copiar_subarvore_chave_avl(No_avl *no, Arvore_avl *sub_arv, char chave, char argumento[])
{
    if (no == NULL)
    {
        return;
    }
    if (comparar_chave(no->candidato, chave, argumento))
    {
        avl_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_chave_avl(no->esq, sub_arv, chave, argumento);
    copiar_subarvore_chave_avl(no->dir, sub_arv, chave, argumento);
}

// Funções Busca Binária
Vetor_bsb *filtrar_por_estado_bsb(Vetor_bsb *vet, char estado[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet; // Retorna um vetor vazio se o original for nulo ou vazio
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (strcmp(vet->candidatos[i].estado, estado) == 0)
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}

Vetor_bsb *filtrar_por_cidade_bsb(Vetor_bsb *vet, char cidade[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet;
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (strcmp(vet->candidatos[i].cidade, cidade) == 0)
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}

Vetor_bsb *filtrar_por_chave_bsb(Vetor_bsb *vet, char chave, char argumento[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet;
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (comparar_chave(vet->candidatos[i], chave, argumento))
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}