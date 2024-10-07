#include <stdio.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"
#include "tad_bsb_candidato.h"

int main()
{
    // Criação das estruturas
    Arvore_abb *abb = abb_criar();
    Arvore_avl *avl = avl_criar();
    Vetor_bsb *vetor_bsb = bsb_criar();

    // Criação de candidatos
    Candidato c1 = {"SP", "Sao Paulo", "12", "prefeito", "Joao Silva", "Joao", "PSDB", "Masculino", "Superior", "Indigena"};
    Candidato c2 = {"SP", "Ribeirao Preto", "40", "prefeito", "Maria Souza", "Maria", "PT", "Feminino", "Ensino Medio", "Pardo"};
    Candidato c3 = {"RJ", "Rio de Janeiro", "70111", "vereador", "Pedro Santos", "Pedro", "PSD", "Masculino", "Fundamental", "Branco"};
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