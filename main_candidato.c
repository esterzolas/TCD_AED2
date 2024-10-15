#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"
#include "tad_bsb_candidato.h"

// Funções de leitura e escrita de arquivos
int lerArquivoCandidatos(char *nomeArquivo, Candidato **candidatos, int *num_candidatos);
Candidato *buscaBinariaCandidato(Candidato *vetor, int inicio, int fim, char *estado, char *cidade, char *numero);
void imprimirCandidatoCompleto(Candidato c);
void criar_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, char estado[], char cidade[], char partido[], char genero[], char cor_raca[]);
void imprimir_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, double tempo_abb, double tempo_avl, double tempo_bsb);

// Implementações
/*
Faça um programa que leia um arquivo texto com as informações dos candidatos e as
organize, considerando a ordenação baseada nos seguintes campos: estado, cidade e
número do candidato.
O processamento das informações dos candidatos deverá realizar-se de três formas
distintas:
1. Pesquisa Binária (usando vetor).
2. Árvore Binária de Busca sem balanceamento.
3. Árvore AVL.
O programa deve permitir que:
A. O usuário escolha um arquivo de texto para ser carregado nas estruturas de dados(opção de escolher entre 2 arquivos,
eleicoe2024 ou subConjuntoEleicoes2024),
considerando cada um dos 3 casos citados. Após a carga dos dados nas estruturas, deve
ser exibido o tempo para cada uma. A função de inserção deverá ser modificada para
considerar a ordenação baseada em três campos como descrito acima.
*/

int main()
{
    Candidato *candidatos;
    int num_candidatos;

    // Ler arquivo de candidatos
    char nomeArquivo[150];
    printf("Escolha um opcao de arquivo para carregar os dados:\n");
    printf("1 - eleicoes2024\n");
    printf("2 - subConjuntoEleicoes2024\n");
    printf("Opcao: ");
    // colocar 3 sub conuntos no total? um de 50, outro de 500 e outro de 5000

    int opcao;
    scanf("%d", &opcao);
    if (opcao == 1)
    {
        strcpy(nomeArquivo, "C:\\Users\\jeans\\OneDrive\\UFU\\Algoritmos e Estruturas 2\\Trabalho Final\\TCD_AED2\\eleicoes2024.txt");
    }
    else if (opcao == 2)
    {
        strcpy(nomeArquivo, "C:\\Users\\jeans\\OneDrive\\UFU\\Algoritmos e Estruturas 2\\Trabalho Final\\TCD_AED2\\subConjuntoEleicoes2024.txt");
    }
    else
    {
        printf("Opcao invalida.\n");
        return 1;
    }

    if (!lerArquivoCandidatos(nomeArquivo, &candidatos, &num_candidatos))
    {
        return 1;
    }

    clock_t inicio, fim;
    double tempo;

    // Pesquisa Binária
    inicio = clock();
    Vetor_bsb *vet_abb = bsb_criar();
    for (int i = 0; i < num_candidatos; i++)
    {
        bsb_inserir(vet_abb, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // bsb_imprimir(vet_abb);
    printf("\nForam lidos %d candidatos do arquivo %s.\n", num_candidatos, nomeArquivo);
    printf("Tempo de ordenacao por Pesquisa Binaria: %.6f segundos\n", tempo);

    // Árvore Binária de Busca
    Arvore_abb *arv_abb = abb_criar();
    inicio = clock();
    for (int i = 0; i < num_candidatos; i++)
    {
        abb_inserir(arv_abb, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de ordenacao por Arvore Binaria de Busca: %.6f segundos\n", tempo);

    // Árvore AVL
    Arvore_avl *arv_avl = avl_criar();
    inicio = clock();
    for (int i = 0; i < num_candidatos; i++)
    {
        avl_inserir(arv_avl, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de ordenacao por Arvore AVL: %.6f segundos\n", tempo);

    // Menu de opções
    /*
    O usuário escolha opções de busca de informações de candidatos:
    B1) Buscar os dados dos candidatos de um dado estado
    B2) Dado um estado, buscar os dados dos candidatos de uma dada cidade
    B3) Dado um estado e uma cidade, buscar os dados do(a) candidato(a) de um dado número
    O resultado da busca deve ser exibido para as três situações programadas, assim como o
    tempo de processamento da consulta. A função de busca deverá ser modificada para
    considerar a ordenação baseada em três campos como descrito anteriormente.
    */

    int opcao_menu = -1;
    char estado[2], cidade[100], numero[6];
    Candidato *candidato;

    do
    {
        printf("\nEscolha uma opcao de busca:\n");
        printf("1 - Dados dos candidatos de um dado estado\n");
        printf("2 - Dados dos candidatos de uma dada cidade\n");
        printf("3 - Dados do(a) candidato(a) de um dado numero\n");
        printf("4 - Criar lista com filtros\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao_menu);

        switch (opcao_menu)
        {
        case 1:
            // melhorar para aceitar só o UFs BR
            printf("\nDigite o UF: ");
            scanf("%s", estado);

            // Converte para tudo maiusculo

            // Pesquisa Binária
            double tempo_bsb = 0;
            inicio = clock();
            Vetor_bsb *sub_vet_abb = filtrar_por_estado_bsb(vet_abb, estado);
            fim = clock();
            tempo_bsb = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_abb))
            {
                bsb_imprimir(sub_vet_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado no estado %s.\n", estado);
            }

            // Árvore Binária de Busca
            double tempo_abb = 0;
            inicio = clock();
            Arvore_abb *sub_arv_abb = filtrar_por_estado_abb(arv_abb, estado);
            fim = clock();
            tempo_abb = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!abb_vazia(sub_arv_abb))
            {
                abb_imprimir_in_ordem(sub_arv_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado no estado %s.\n", estado);
            }

            // Árvore AVL
            double tempo_avl = 0;
            inicio = clock();
            Arvore_avl *sub_arv_avl = filtrar_por_estado_avl(arv_avl, estado);
            fim = clock();
            tempo_avl = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!avl_vazia(sub_arv_avl))
            {
                avl_imprimir_in_ordem(sub_arv_avl);
            }
            else
            {
                printf("Nenhum candidato encontrado no estado %s.\n", estado);
            }
            printf("Tempo de busca por Pesquisa Binaria: %.6f segundos\n", tempo_bsb);
            printf("Tempo de busca por Arvore Binaria de Busca: %.6f segundos\n", tempo_abb);
            printf("Tempo de busca por Arvore AVL: %.6f segundos\n", tempo_avl);
            opcao_menu = -1;
            break;

        case 2:
            // mesma coisa aqui
            printf("\nDigite o UF: ");
            scanf("%s", estado);

            printf("Digite a cidade: ");
            scanf(" %[^\n]", cidade);
            // Converte para tudo maiusculo

            // Pesquisa Binária
            inicio = clock();
            sub_vet_abb = filtrar_por_cidade_bsb(vet_abb, cidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_abb))
            {
                bsb_imprimir(sub_vet_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s.\n", cidade, estado);
            }
            printf("Tempo de busca por Pesquisa Binaria: %.6f segundos\n", tempo);

            // Árvore Binária de Busca
            inicio = clock();
            sub_arv_abb = filtrar_por_cidade_abb(arv_abb, cidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!abb_vazia(sub_arv_abb))
            {
                abb_imprimir_in_ordem(sub_arv_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s.\n", cidade, estado);
            }
            printf("Tempo de busca por Arvore Binaria de Busca: %.6f segundos\n", tempo);

            // Árvore AVL
            inicio = clock();
            sub_arv_avl = filtrar_por_cidade_avl(arv_avl, cidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!avl_vazia(sub_arv_avl))
            {
                avl_imprimir_in_ordem(sub_arv_avl);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s.\n", cidade, estado);
            }
            printf("Tempo de busca por Arvore AVL: %.6f segundos\n", tempo);
            opcao_menu = -1;
            break;

        case 3:
            // mesma coisa aqui
            printf("\nDigite o UF: ");
            scanf("%s", estado);

            printf("Digite a cidade: ");
            scanf(" %[^\n]", cidade);
            // Converte para tudo maiusculo

            printf("Digite o numero: ");
            scanf("%s", numero);

            // Pesquisa Binária
            inicio = clock();
            sub_vet_abb = filtrar_por_chave_bsb(vet_abb, 'N', numero);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_abb))
            {
                bsb_imprimir(sub_vet_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s, com o numero %s.\n", cidade, estado, numero);
            }
            printf("Tempo de busca por Pesquisa Binaria: %.6f segundos\n", tempo);

            // Árvore Binária de Busca
            inicio = clock();
            sub_arv_abb = filtrar_por_chave_abb(arv_abb, 'N', numero);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!abb_vazia(sub_arv_abb))
            {
                abb_imprimir_in_ordem(sub_arv_abb);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s, com o numero %s.\n", cidade, estado, numero);
            }

            // Árvore AVL
            inicio = clock();
            sub_arv_avl = filtrar_por_chave_avl(arv_avl, 'N', numero);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!avl_vazia(sub_arv_avl))
            {
                avl_imprimir_in_ordem(sub_arv_avl);
            }
            else
            {
                printf("Nenhum candidato encontrado na cidade %s, estado %s, com o numero %s.\n", cidade, estado, numero);
            }
            printf("Tempo de busca por Arvore AVL: %.6f segundos\n", tempo);
            opcao_menu = -1;
            break;

        case 4:;
            opcao_menu = -1;
            char estado[MAX_TAM_ESTADO];
            char cidade[MAX_TAM_CIDADE];
            char partido[MAX_TAM_SIGLA_PARTIDO];
            char genero[MAX_TAM_GENERO];
            char cor_raca[MAX_TAM_COR_RACA];

            //melhor: aceita somente maiusculos atualmente e nao faz nenhuma validação

            printf("Filtros de Listagem (digite NA para ignorar o filtro):\n");
            printf("Estado: ");
            setbuf(stdin, NULL);
            scanf("%s", estado);

            printf("Cidade: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", cidade);

            printf("Partido: ");
            setbuf(stdin, NULL);
            scanf("%s", partido);

            printf("Genero (Masculino ou Feminino): ");
            setbuf(stdin, NULL);
            scanf("%s", genero);

            printf("Cor/Raca: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", cor_raca);

            criar_listagem(arv_abb, arv_avl, vet_abb, estado, cidade, partido, genero, cor_raca);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao_menu != 0);

    // Liberar memória
    bsb_liberar(vet_abb);
    abb_liberar(arv_abb);
    avl_liberar(arv_avl);
    free(candidatos);

    return 0;
}

// Funções de leitura e escrita de arquivos
// ESTADO;CIDADE;NR_CANDIDATO;CARGO;NM_CANDIDATO;NM_URNA_CANDIDATO;SG_PARTIDO;GENERO;GRAU_INSTRUCAO;COR_RACA
int lerArquivoCandidatos(char *nomeArquivo, Candidato **candidatos, int *num_candidatos)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s!\n", nomeArquivo);
        return 0;
    }

    *candidatos = (Candidato *)malloc(MAX_CANDIDATOS * sizeof(Candidato));
    if (*candidatos == NULL)
    {
        printf("Erro ao alocar memória para os candidatos!\n");
        fclose(arquivo);
        return 0;
    }

    *num_candidatos = 0;
    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%2s;%99[^;];%5[^;];%19[^;];%99[^;];%99[^;];%9[^;];%19[^;];%39[^;];%9[^\n]",
               (*candidatos)[*num_candidatos].estado, (*candidatos)[*num_candidatos].cidade,
               (*candidatos)[*num_candidatos].numero_urna, (*candidatos)[*num_candidatos].cargo,
               (*candidatos)[*num_candidatos].nome, (*candidatos)[*num_candidatos].nome_urna,
               (*candidatos)[*num_candidatos].sigla_partido, (*candidatos)[*num_candidatos].genero,
               (*candidatos)[*num_candidatos].grau_instrucao, (*candidatos)[*num_candidatos].cor_raca);
        (*num_candidatos)++;
    }

    fclose(arquivo);
    return 1;
}

void imprimirCandidatoCompleto(Candidato c)
{
    printf("Nome: %s\n", c.nome);
    printf("Nome na urna: %s\n", c.nome_urna);
    printf("Numero: %d\n", c.numero_urna);
    printf("Estado: %s\n", c.estado);
    printf("Cidade: %s\n", c.cidade);
    printf("Cargo: %s\n", c.cargo);
    printf("Partido: %s\n", c.sigla_partido);
    printf("Genero: %s\n", c.genero);
    printf("Grau de instrucao: %s\n", c.grau_instrucao);
    printf("Cor/Raca: %s\n", c.cor_raca);
    printf("--------------------\n");
}

void imprimir_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, double tempo_abb, double tempo_avl, double tempo_bsb)
{
    int opcao_menu = -1;
    do
    {
        printf("\nEscolha uma opcao de listagem do resultado da filtragem:\n");
        printf("1 - Listar pela ABB\n");
        printf("2 - Listar pela AVL\n");
        printf("3 - Listar pela BSB\n");
        printf("4 - Listar tempos de execucao\n");
        printf("0 - Nao listar (sair)\n");
        scanf("%d", &opcao_menu);

        switch (opcao_menu)
        {
        case 1:
            opcao_menu = -1;
            do
            {
                printf("\nEscolha uma opcao de listagem da ABB:\n");
                printf("1 - In-ordem\n");
                printf("2 - Pre-ordem\n");
                printf("3 - Pos-ordem\n");
                printf("0 - Voltar\n");
                scanf("%d", &opcao_menu);

                switch (opcao_menu)
                {
                case 1:
                    printf("---- Listagem ABB in ordem ----\n");
                    abb_imprimir_in_ordem(abb);
                    break;
                case 2:
                    printf("---- Listagem ABB pre ordem ----\n");
                    abb_imprimir_pre_ordem(abb);
                    break;
                case 3:
                    printf("---- Listagem ABB pos ordem ----\n");
                    abb_imprimir_pos_ordem(abb);
                    break;
                case 0:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
                }
            } while (opcao_menu != 0);
            opcao_menu = -1;
            break;
        case 2:
            opcao_menu = -1;
            do
            {
                printf("\nEscolha uma opcao de listagem da AVL:\n");
                printf("1 - In-ordem\n");
                printf("2 - Pre-ordem\n");
                printf("3 - Pos-ordem\n");
                printf("0 - Voltar\n");
                scanf("%d", &opcao_menu);

                switch (opcao_menu)
                {
                case 1:
                    printf("---- Listagem AVL in ordem ----\n");
                    avl_imprimir_in_ordem(avl);
                    break;
                case 2:
                    printf("---- Listagem AVL pre ordem ----\n");
                    avl_imprimir_pre_ordem(avl);
                    break;
                case 3:
                    printf("---- Listagem AVL pos ordem ----\n");
                    avl_imprimir_pos_ordem(avl);
                    break;
                case 0:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
                }
            } while (opcao_menu != 0);
            opcao_menu = -1;
            break;
        case 3:
            opcao_menu = -1;
            printf("---- Listagem BSB ----\n");
            bsb_imprimir(bsb);
            break;

        case 4:
            opcao_menu = -1;
            printf("Tempo de execucao da ABB: %.6f segundos\n", tempo_abb);
            printf("Tempo de execucao da AVL: %.6f segundos\n", tempo_avl);
            printf("Tempo de execucao da BSB: %.6f segundos\n", tempo_bsb);
            break;

        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao_menu != 0);
}

void criar_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, char estado[], char cidade[], char partido[], char genero[], char cor_raca[])
{
    clock_t inicio, fim;

    // Aplicar filtros para ABB e guardar tempo usado
    double tempo_abb = 0;
    inicio = clock();
    Arvore_abb *resultado_abb = abb; // Começa com a árvore completa
    if (strcmp(estado, "NA") != 0)
    {
        resultado_abb = filtrar_por_estado_abb(resultado_abb, estado);
    }
    if (strcmp(cidade, "NA") != 0)
    {
        resultado_abb = filtrar_por_cidade_abb(resultado_abb, cidade);
    }
    if (strcmp(partido, "NA") != 0)
    {
        resultado_abb = filtrar_por_chave_abb(resultado_abb, 'P', partido);
    }
    if (strcmp(genero, "NA") != 0)
    {
        resultado_abb = filtrar_por_chave_abb(resultado_abb, 'G', genero);
    }
    if (strcmp(cor_raca, "NA") != 0)
    {
        resultado_abb = filtrar_por_chave_abb(resultado_abb, 'R', cor_raca);
    }
    fim = clock();
    tempo_abb = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Aplicar filtros para AVL e guardar tempo usado
    double tempo_avl = 0;
    inicio = clock();
    Arvore_avl *resultado_avl = avl; // Começa com a árvore completa
    if (strcmp(estado, "NA") != 0)
    {
        resultado_avl = filtrar_por_estado_avl(resultado_avl, estado);
    }
    if (strcmp(cidade, "NA") != 0)
    {
        resultado_avl = filtrar_por_cidade_avl(resultado_avl, cidade);
    }
    if (strcmp(partido, "NA") != 0)
    {
        resultado_avl = filtrar_por_chave_avl(resultado_avl, 'P', partido);
    }
    if (strcmp(genero, "NA") != 0)
    {
        resultado_avl = filtrar_por_chave_avl(resultado_avl, 'G', genero);
    }
    if (strcmp(cor_raca, "NA") != 0)
    {
        resultado_avl = filtrar_por_chave_avl(resultado_avl, 'R', cor_raca);
    }
    fim = clock();
    tempo_avl = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Aplicar filtros para BSB e guardar tempo usado
    double tempo_bsb = 0;
    inicio = clock();
    Vetor_bsb *resultado_bsb = bsb; // Começa com o vetor completo
    if (strcmp(estado, "NA") != 0)
    {
        resultado_bsb = filtrar_por_estado_bsb(resultado_bsb, estado);
    }
    if (strcmp(cidade, "NA") != 0)
    {
        resultado_bsb = filtrar_por_cidade_bsb(resultado_bsb, cidade);
    }
    if (strcmp(partido, "NA") != 0)
    {
        resultado_bsb = filtrar_por_chave_bsb(resultado_bsb, 'P', partido);
    }
    if (strcmp(genero, "NA") != 0)
    {
        resultado_bsb = filtrar_por_chave_bsb(resultado_bsb, 'G', genero);
    }
    if (strcmp(cor_raca, "NA") != 0)
    {
        resultado_bsb = filtrar_por_chave_bsb(resultado_bsb, 'R', cor_raca);
    }
    fim = clock();
    tempo_bsb = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (abb_vazia(resultado_abb) && avl_vazia(resultado_avl) && bsb_vazia(resultado_bsb))
    {
        printf("\nNenhum candidato encontrado com os filtros especificados.\n");
        return;
    }
    else
    {
        printf("\nForam encontrados %d candidatos com os filtros especificados.\n", abb_tamanho(resultado_abb));
        imprimir_listagem(resultado_abb, resultado_avl, resultado_bsb, tempo_abb, tempo_avl, tempo_bsb);
    }

    // Liberar memória das estruturas temporárias se forem diferentes das originais
    if (resultado_abb != abb)
    {
        abb_liberar(resultado_abb);
    }

    if (resultado_avl != avl)
    {
        avl_liberar(resultado_avl);
    }

    if (resultado_bsb != bsb)
    {
        bsb_liberar(resultado_bsb);
    }
}