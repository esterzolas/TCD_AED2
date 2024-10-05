#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_ABB.h"

// Cria uma árvore vazia
ABB criar_abb()
{
    return NULL;
}

// Insere um novo nó na árvore
ABB inserir(ABB raiz, Cidade cidade)
{
    if (raiz == NULL)
    {
        NoArvore *novo_no = (NoArvore *)malloc(sizeof(NoArvore));
        novo_no->cidade = cidade;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        return novo_no;
    }
    else
    {
        // Compara os CEPs para decidir a inserção
        if (strcmp(cidade.cep, raiz->cidade.cep) < 0)
        {
            raiz->esquerda = inserir(raiz->esquerda, cidade);
        }
        else
        {
            raiz->direita = inserir(raiz->direita, cidade);
        }
        return raiz;
    }
}

// Remove um nó da árvore
ABB remover(ABB raiz, char *cep)
{
    if (raiz == NULL)
    {
        return raiz;
    }

    // Compara os CEPs para encontrar o nó a ser removido
    if (strcmp(cep, raiz->cidade.cep) < 0)
    {
        raiz->esquerda = remover(raiz->esquerda, cep);
    }
    else if (strcmp(cep, raiz->cidade.cep) > 0)
    {
        raiz->direita = remover(raiz->direita, cep);
    }
    else
    {
        // Nó com um ou nenhum filho
        if (raiz->esquerda == NULL)
        {
            NoArvore *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            NoArvore *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Nó com dois filhos
        NoArvore *temp = menor(raiz->direita);
        raiz->cidade = temp->cidade;
        raiz->direita = remover(raiz->direita, temp->cidade.cep);
    }
    return raiz;
}

// Busca um nó na árvore
NoArvore *pesquisar(ABB raiz, char *cep)
{
    if (raiz == NULL || strcmp(raiz->cidade.cep, cep) == 0)
    {
        return raiz;
    }
    if (strcmp(cep, raiz->cidade.cep) < 0)
    {
        return pesquisar(raiz->esquerda, cep);
    }
    else
    {
        return pesquisar(raiz->direita, cep);
    }
}

// Percursos da árvore
void percorrer_central(ABB raiz)
{
    if (raiz != NULL)
    {
        percorrer_central(raiz->esquerda);
        printf("CEP: %s, Estado: %s, Cidade: %s, Endereco: %s\n",
               raiz->cidade.cep, raiz->cidade.sigla_estado,
               raiz->cidade.nome, raiz->cidade.endereco);
        percorrer_central(raiz->direita);
    }
}

void percorrer_pre_fixado(ABB raiz)
{
    if (raiz != NULL)
    {
        printf("CEP: %s, Estado: %s, Cidade: %s, Endereco: %s\n",
               raiz->cidade.cep, raiz->cidade.sigla_estado,
               raiz->cidade.nome, raiz->cidade.endereco);
        percorrer_pre_fixado(raiz->esquerda);
        percorrer_pre_fixado(raiz->direita);
    }
}

void percorrer_pos_fixado(ABB raiz)
{
    if (raiz != NULL)
    {
        percorrer_pos_fixado(raiz->esquerda);
        percorrer_pos_fixado(raiz->direita);
        printf("CEP: %s, Estado: %s, Cidade: %s, Endereco: %s\n",
               raiz->cidade.cep, raiz->cidade.sigla_estado,
               raiz->cidade.nome, raiz->cidade.endereco);
    }
}

// Retorna a altura da árvore
int altura(ABB raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        int altura_esquerda = altura(raiz->esquerda);
        int altura_direita = altura(raiz->direita);
        if (altura_esquerda > altura_direita)
        {
            return altura_esquerda + 1;
        }
        else
        {
            return altura_direita + 1;
        }
    }
}

// Encontra o nó com o menor CEP
NoArvore *menor(ABB raiz)
{
    NoArvore *atual = raiz;
    while (atual != NULL && atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual;
}

// Encontra o nó com o maior CEP
NoArvore *maior(ABB raiz)
{
    NoArvore *atual = raiz;
    while (atual != NULL && atual->direita != NULL)
    {
        atual = atual->direita;
    }
    return atual;
}

// Libera a memória da árvore
void liberar_abb(ABB raiz)
{
    if (raiz != NULL)
    {
        liberar_abb(raiz->esquerda);
        liberar_abb(raiz->direita);
        free(raiz);
    }
}