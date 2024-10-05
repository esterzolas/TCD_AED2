#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_abb_candidato.h"

// Funções auxiliares

int comparar_candidatos_abb(Candidato c1, Candidato c2)
{
    int cmp = strcmp(c1.estado, c2.estado);
    if (cmp == 0)
    {
        cmp = strcmp(c1.cidade, c2.cidade);
        if (cmp == 0)
        {
            cmp = strcmp(c1.numero_urna, c2.numero_urna);
        }
    }
    return cmp;
}

void imprimir_candidato_abb(Candidato c)
{
    printf("Nome: %s\n", c.nome);
    printf("Nome na urna: %s\n", c.nome_urna);
    printf("Numero: %s\n", c.numero_urna);
    printf("Estado: %s\n", c.estado);
    printf("Cidade: %s\n", c.cidade);
    printf("Cargo: %s\n", c.cargo);
    printf("Partido: %s\n", c.sigla_partido);
    printf("Genero: %c\n", c.genero);
    printf("Grau de instrucao: %s\n", c.grau_instrucao);
    printf("Cor/Raca: %s\n", c.cor_raca);
    printf("--------------------\n");
}

// Funções da ABB

Arvore_abb *abb_criar()
{
    Arvore_abb *arv = (Arvore_abb *)malloc(sizeof(Arvore_abb));
    if (arv != NULL)
    {
        arv->raiz = NULL;
    }
    return arv;
}

void abb_liberar_no(No_abb *no)
{
    if (no != NULL)
    {
        abb_liberar_no(no->esq);
        abb_liberar_no(no->dir);
        free(no);
    }
}

void abb_liberar(Arvore_abb *arv)
{
    if (arv != NULL)
    {
        abb_liberar_no(arv->raiz);
        free(arv);
    }
}

int abb_inserir(Arvore_abb *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return 0;
    }

    No_abb *novo = (No_abb *)malloc(sizeof(No_abb));
    if (novo == NULL)
    {
        return 0;
    }

    novo->candidato = candidato;
    novo->esq = NULL;
    novo->dir = NULL;

    if (arv->raiz == NULL)
    {
        arv->raiz = novo;
    }
    else
    {
        No_abb *atual = arv->raiz;
        No_abb *pai = NULL;

        while (atual != NULL)
        {
            pai = atual;
            if (comparar_candidatos_abb(candidato, atual->candidato) < 0)
            {
                atual = atual->esq;
            }
            else if (comparar_candidatos_abb(candidato, atual->candidato) > 0)
            {
                atual = atual->dir;
            }
            else
            {
                free(novo);
                return 0;
            }
        }

        if (comparar_candidatos_abb(candidato, pai->candidato) < 0)
        {
            pai->esq = novo;
        }
        else
        {
            pai->dir = novo;
        }
    }
    return 1;
}

No_abb *abb_remover_no(No_abb *no, Candidato candidato)
{
    if (no == NULL)
    {
        return NULL;
    }

    int cmp = comparar_candidatos_abb(candidato, no->candidato);
    if (cmp < 0)
    {
        no->esq = abb_remover_no(no->esq, candidato);
    }
    else if (cmp > 0)
    {
        no->dir = abb_remover_no(no->dir, candidato);
    }
    else
    {
        if (no->esq == NULL)
        {
            No_abb *temp = no->dir;
            free(no);
            return temp;
        }
        else if (no->dir == NULL)
        {
            No_abb *temp = no->esq;
            free(no);
            return temp;
        }

        No_abb *temp = no->dir;
        while (temp->esq != NULL)
        {
            temp = temp->esq;
        }
        no->candidato = temp->candidato;
        no->dir = abb_remover_no(no->dir, temp->candidato);
    }
    return no;
}

int abb_remover(Arvore_abb *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return 0;
    }
    arv->raiz = abb_remover_no(arv->raiz, candidato);
    return 1;
}

No_abb *abb_buscar(Arvore_abb *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return NULL;
    }

    No_abb *atual = arv->raiz;
    while (atual != NULL)
    {
        if (comparar_candidatos_abb(candidato, atual->candidato) == 0)
        {
            return atual;
        }
        else if (comparar_candidatos_abb(candidato, atual->candidato) < 0)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    return NULL;
}

int abb_tamanho_no(No_abb *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return 1 + abb_tamanho_no(no->esq) + abb_tamanho_no(no->dir);
}

int abb_tamanho(Arvore_abb *arv)
{
    if (arv == NULL)
    {
        return 0;
    }
    return abb_tamanho_no(arv->raiz);
}

int abb_vazia(Arvore_abb *arv)
{
    if (arv == NULL)
    {
        return 1;
    }
    return arv->raiz == NULL;
}

void abb_imprimir_in_ordem_no(No_abb *no)
{
    if (no != NULL)
    {
        abb_imprimir_in_ordem_no(no->esq);
        imprimir_candidato_abb(no->candidato);
        abb_imprimir_in_ordem_no(no->dir);
    }
}

void abb_imprimir_in_ordem(Arvore_abb *arv)
{
    if (arv != NULL)
    {
        abb_imprimir_in_ordem_no(arv->raiz);
    }
}

void abb_imprimir_pre_ordem_no(No_abb *no)
{
    if (no != NULL)
    {
        printf("Candidato: %s - %s - %s\n", no->candidato.nome, no->candidato.cidade, no->candidato.estado);
        abb_imprimir_pre_ordem_no(no->esq);
        abb_imprimir_pre_ordem_no(no->dir);
    }
}

void abb_imprimir_pre_ordem(Arvore_abb *arv)
{
    if (arv != NULL)
    {
        abb_imprimir_pre_ordem_no(arv->raiz);
    }
}

void abb_imprimir_pos_ordem_no(No_abb *no)
{
    if (no != NULL)
    {
        abb_imprimir_pos_ordem_no(no->esq);
        abb_imprimir_pos_ordem_no(no->dir);
        printf("Candidato: %s - %s - %s\n", no->candidato.nome, no->candidato.cidade, no->candidato.estado);
    }
}

void abb_imprimir_pos_ordem(Arvore_abb *arv)
{
    if (arv != NULL)
    {
        abb_imprimir_pos_ordem_no(arv->raiz);
    }
}