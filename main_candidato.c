#include <stdio.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"

int main()
{
    Arvore_abb *abb = abb_criar();
    Arvore_avl *avl = avl_criar();

    Candidato c1 = {"SP", "Sao Paulo", "12", "prefeito", "Joao Silva", "Joao", "PSDB", 'M', "Superior", "Indigena"};
    Candidato c2 = {"SP", "Sao Paulo", "40", "prefeito", "Maria Souza", "Maria", "PT", 'F', "Ensino Medio", "Pardo"};
    Candidato c3 = {"RJ", "Rio de Janeiro", "70111", "vereador", "Pedro Santos", "Pedro", "PSD", 'M', "Fundamental", "Branco"};

    abb_inserir(abb, c1);
    abb_inserir(abb, c2);
    abb_inserir(abb, c3);

    avl_inserir(avl, c1);
    avl_inserir(avl, c2);
    avl_inserir(avl, c3);

    printf("ABB - Candidatos em ordem:\n");
    abb_imprimir_in_ordem(abb);

    printf("\nAVL - Candidatos em ordem:\n");
    avl_imprimir_in_ordem(avl);

    abb_liberar(abb);
    avl_liberar(avl);

    return 0;
}