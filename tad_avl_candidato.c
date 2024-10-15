#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_avl_candidato.h"

// Funções auxiliares
int comparar_candidatos_avl(Candidato c1, Candidato c2)
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

void imprimir_candidato_completo_avl(Candidato c)
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

void imprimir_candidato_simples_avl(Candidato c)
{
    printf("Nome na urna: %s; Numero: %s; Estado: %s; Cidade: %s; Cargo: %s\n", c.nome_urna, c.numero_urna, c.estado, c.cidade, c.cargo);
}

int altura_no(No_avl *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return no->altura;
}

int fator_balanceamento(No_avl *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return altura_no(no->esq) - altura_no(no->dir);
}

No_avl *no_maximo(No_avl *no)
{
    No_avl *atual = no;
    while (atual->dir != NULL)
    {
        atual = atual->dir;
    }
    return atual;
}

No_avl *rotacao_direita(No_avl *y)
{
    No_avl *x = y->esq;
    No_avl *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + (altura_no(y->esq) > altura_no(y->dir) ? altura_no(y->esq) : altura_no(y->dir));
    x->altura = 1 + (altura_no(x->esq) > altura_no(x->dir) ? altura_no(x->esq) : altura_no(x->dir));

    return x;
}

No_avl *rotacao_esquerda(No_avl *x)
{
    No_avl *y = x->dir;
    No_avl *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + (altura_no(x->esq) > altura_no(x->dir) ? altura_no(x->esq) : altura_no(x->dir));
    y->altura = 1 + (altura_no(y->esq) > altura_no(y->dir) ? altura_no(y->esq) : altura_no(y->dir));

    return y;
}

// Funções da AVL

Arvore_avl *avl_criar()
{
    Arvore_avl *arv = (Arvore_avl *)malloc(sizeof(Arvore_avl));
    if (arv != NULL)
    {
        arv->raiz = NULL;
    }
    return arv;
}

void avl_liberar_no(No_avl *no)
{
    if (no != NULL)
    {
        avl_liberar_no(no->esq);
        avl_liberar_no(no->dir);
        free(no);
    }
}

void avl_liberar(Arvore_avl *arv)
{
    if (arv != NULL)
    {
        avl_liberar_no(arv->raiz);
        free(arv);
    }
}

No_avl *avl_inserir_no(No_avl *no, Candidato candidato)
{
    if (no == NULL)
    {
        No_avl *novo = (No_avl *)malloc(sizeof(No_avl));
        if (novo == NULL)
        {
            return NULL;
        }
        novo->candidato = candidato;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    int cmp = comparar_candidatos_avl(candidato, no->candidato);
    if (cmp < 0)
    {
        no->esq = avl_inserir_no(no->esq, candidato);
    }
    else if (cmp > 0)
    {
        no->dir = avl_inserir_no(no->dir, candidato);
    }
    else
    {
        return no;
    }

    no->altura = 1 + (altura_no(no->esq) > altura_no(no->dir) ? altura_no(no->esq) : altura_no(no->dir));

    int balanceamento = fator_balanceamento(no);

    if (balanceamento > 1 && comparar_candidatos_avl(candidato, no->esq->candidato) < 0)
    {
        return rotacao_direita(no);
    }

    if (balanceamento < -1 && comparar_candidatos_avl(candidato, no->dir->candidato) > 0)
    {
        return rotacao_esquerda(no);
    }

    if (balanceamento > 1 && comparar_candidatos_avl(candidato, no->esq->candidato) > 0)
    {
        no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }

    if (balanceamento < -1 && comparar_candidatos_avl(candidato, no->dir->candidato) < 0)
    {
        no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }

    return no;
}

int avl_inserir(Arvore_avl *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return 0;
    }
    arv->raiz = avl_inserir_no(arv->raiz, candidato);
    return 1;
}

No_avl *avl_remover_no(No_avl *raiz, Candidato candidato)
{
    if (raiz == NULL)
    {
        return raiz;
    }

    int cmp = comparar_candidatos_avl(candidato, raiz->candidato);
    if (cmp < 0)
    {
        raiz->esq = avl_remover_no(raiz->esq, candidato);
    }
    else if (cmp > 0)
    {
        raiz->dir = avl_remover_no(raiz->dir, candidato);
    }
    else
    {
        if ((raiz->esq == NULL) || (raiz->dir == NULL))
        {
            No_avl *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }
            free(temp);
        }
        else
        {
            No_avl *temp = no_maximo(raiz->esq);
            raiz->candidato = temp->candidato;
            raiz->esq = avl_remover_no(raiz->esq, temp->candidato);
        }
    }

    if (raiz == NULL)
    {
        return raiz;
    }

    raiz->altura = 1 + (altura_no(raiz->esq) > altura_no(raiz->dir) ? altura_no(raiz->esq) : altura_no(raiz->dir));

    int balanceamento = fator_balanceamento(raiz);

    if (balanceamento > 1 && fator_balanceamento(raiz->esq) >= 0)
    {
        return rotacao_direita(raiz);
    }

    if (balanceamento > 1 && fator_balanceamento(raiz->esq) < 0)
    {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->dir) <= 0)
    {
        return rotacao_esquerda(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->dir) > 0)
    {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

int avl_remover(Arvore_avl *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return 0;
    }
    arv->raiz = avl_remover_no(arv->raiz, candidato);
    return 1;
}

No_avl *avl_buscar(Arvore_avl *arv, Candidato candidato)
{
    if (arv == NULL)
    {
        return NULL;
    }

    No_avl *atual = arv->raiz;
    while (atual != NULL)
    {
        if (comparar_candidatos_avl(candidato, atual->candidato) == 0)
        {
            return atual;
        }
        else if (comparar_candidatos_avl(candidato, atual->candidato) < 0)
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

int avl_tamanho_no(No_avl *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return 1 + avl_tamanho_no(no->esq) + avl_tamanho_no(no->dir);
}

int avl_tamanho(Arvore_avl *arv)
{
    if (arv == NULL)
    {
        return 0;
    }
    return avl_tamanho_no(arv->raiz);
}

int avl_vazia(Arvore_avl *arv)
{
    if (arv == NULL)
    {
        return 1;
    }
    return arv->raiz == NULL;
}

void avl_imprimir_in_ordem_no(No_avl *no)
{
    if (no != NULL)
    {
        avl_imprimir_in_ordem_no(no->esq);
        imprimir_candidato_simples_avl(no->candidato);
        avl_imprimir_in_ordem_no(no->dir);
    }
}

void avl_imprimir_in_ordem(Arvore_avl *arv)
{
    if (arv != NULL)
    {
        avl_imprimir_in_ordem_no(arv->raiz);
    }
}

void avl_imprimir_pre_ordem_no(No_avl *no)
{
    if (no != NULL)
    {
        printf("Candidato: %s - %s - %s\n", no->candidato.nome, no->candidato.cidade, no->candidato.estado);
        avl_imprimir_pre_ordem_no(no->esq);
        avl_imprimir_pre_ordem_no(no->dir);
    }
}

void avl_imprimir_pre_ordem(Arvore_avl *arv)
{
    if (arv != NULL)
    {
        avl_imprimir_pre_ordem_no(arv->raiz);
    }
}

void avl_imprimir_pos_ordem_no(No_avl *no)
{
    if (no != NULL)
    {
        avl_imprimir_pos_ordem_no(no->esq);
        avl_imprimir_pos_ordem_no(no->dir);
        printf("Candidato: %s - %s - %s\n", no->candidato.nome, no->candidato.cidade, no->candidato.estado);
    }
}

void avl_imprimir_pos_ordem(Arvore_avl *arv)
{
    if (arv != NULL)
    {
        avl_imprimir_pos_ordem_no(arv->raiz);
    }
}

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

    /*if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }*/

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

    /*if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado na cidade.\n");
    }*/

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
    if (comparar_chave_avl(atual->candidato, chave, argumento))
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

    /*if (avl_vazia(sub_arv))
    {
        printf("Nenhum candidato encontrado no estado.\n");
    }*/

    return sub_arv;
}

void copiar_subarvore_chave_avl(No_avl *no, Arvore_avl *sub_arv, char chave, char argumento[])
{
    if (no == NULL)
    {
        return;
    }
    if (comparar_chave_avl(no->candidato, chave, argumento))
    {
        avl_inserir(sub_arv, no->candidato);
    }
    copiar_subarvore_chave_avl(no->esq, sub_arv, chave, argumento);
    copiar_subarvore_chave_avl(no->dir, sub_arv, chave, argumento);
}

int comparar_chave_avl(Candidato candidato, char chave, char argumento[])
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