#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"
#include "tad_bsb_candidato.h"

// Funções de leitura e escrita de arquivos
// int lerArquivoCandidatos(char *nomeArquivo, Candidato **candidatos, int *num_candidatos);
Candidato *buscaBinariaCandidato(Candidato *vetor, int inicio, int fim, char *estado, char *cidade, char *numero);
void imprimirCandidatoCompleto(Candidato c);
void criar_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, char estado[], char cidade[], char partido[], char genero[], char cor_raca[]);
void imprimir_listagem(Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb, double tempo_abb, double tempo_avl, double tempo_bsb);
void ler_arquivo(char nome_arquivo[], Arvore_abb **abb, Arvore_avl **avl, Vetor_bsb **bsb, double *tempo_abb, double *tempo_avl, double *tempo_bsb);
int validar_entrada_em_todas(char chave, char entrada[], Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb);
int percorrer_e_comparar_abb(No_abb *no, char *valor, char chave);
int percorrer_e_comparar_avl(No_avl *no, char *valor, char chave);
int percorrer_e_comparar_bsb(Vetor_bsb *vet, char *valor, char chave);
void listagem_case(Arvore_abb *arv_abb, Arvore_avl *arv_avl, Vetor_bsb *vet_bsb);

int main()
{
    clock_t inicio, fim;
    double tempo;

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
        //strcpy(nomeArquivo, "C:\\Users\\jeans\\OneDrive\\UFU\\Algoritmos e Estruturas 2\\Trabalho Final\\TCD_AED2\\eleicoes2024.txt");
        strcpy(nomeArquivo, "F:\\Programas s2\\aed2\\TCD_AED2\\eleicoes2024.txt");

    }
    else if (opcao == 2)
    {
        //strcpy(nomeArquivo, "C:\\Users\\jeans\\OneDrive\\UFU\\Algoritmos e Estruturas 2\\Trabalho Final\\TCD_AED2\\subConjuntoEleicoes2024.txt");
        strcpy(nomeArquivo, "F:\\Programas s2\\aed2\\TCD_AED2\\subConjuntoEleicoes2024.txt");
    }
    else
    {
        printf("Opcao invalida.\n");
        return 1;
    }

    // Ler arquivo e inserir candidatos nas estruturas
    Arvore_abb *arv_abb = abb_criar();
    Arvore_avl *arv_avl = avl_criar();
    Vetor_bsb *vet_bsb = bsb_criar();
    double tempo_abb, tempo_avl, tempo_bsb;
    ler_arquivo(nomeArquivo, &arv_abb, &arv_avl, &vet_bsb, &tempo_abb, &tempo_avl, &tempo_bsb);

    // Imprimir listagem
    imprimir_listagem(arv_abb, arv_avl, vet_bsb, tempo_abb, tempo_avl, tempo_bsb);

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
            Vetor_bsb *sub_vet_bsb = filtrar_por_estado_bsb(vet_bsb, estado);
            fim = clock();
            tempo_bsb = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_bsb))
            {
                bsb_imprimir(sub_vet_bsb);
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
            sub_vet_bsb = filtrar_por_cidade_bsb(vet_bsb, cidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_bsb))
            {
                bsb_imprimir(sub_vet_bsb);
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
            sub_vet_bsb = filtrar_por_chave_bsb(vet_bsb, 'N', numero);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (!bsb_vazia(sub_vet_bsb))
            {
                bsb_imprimir(sub_vet_bsb);
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
            listagem_case(arv_abb, arv_avl, vet_bsb);
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
    bsb_liberar(vet_bsb);
    abb_liberar(arv_abb);
    avl_liberar(arv_avl);

    return 0;
}

// Função para ler o arquivo e inserir candidatos nas estruturas
void ler_arquivo(char nome_arquivo[], Arvore_abb **abb, Arvore_avl **avl, Vetor_bsb **bsb, double *tempo_abb, double *tempo_avl, double *tempo_bsb)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[512];
    Candidato candidato;
    clock_t inicio, fim;
    int contador = 0;

    // Ler e inserir na ABB
    inicio = clock();
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%2s;%99[^;];%5[^;];%19[^;];%99[^;];%99[^;];%9[^;];%19[^;];%39[^;];%9[^\n]",
               candidato.estado, candidato.cidade, candidato.numero_urna, candidato.cargo,
               candidato.nome, candidato.nome_urna, candidato.sigla_partido,
               candidato.genero, candidato.grau_instrucao, candidato.cor_raca);
        abb_inserir(*abb, candidato);
        contador++;
    }
    fim = clock();
    *tempo_abb = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Foram lidos %d candidatos na ABB.\n", contador);

    rewind(arquivo); // Voltar ao início do arquivo

    // Ler e inserir na AVL
    contador = 0;
    inicio = clock();
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%2s;%99[^;];%5[^;];%19[^;];%99[^;];%99[^;];%9[^;];%19[^;];%39[^;];%9[^\n]",
               candidato.estado, candidato.cidade, candidato.numero_urna, candidato.cargo,
               candidato.nome, candidato.nome_urna, candidato.sigla_partido,
               candidato.genero, candidato.grau_instrucao, candidato.cor_raca);
        avl_inserir(*avl, candidato);
        contador++;
    }
    fim = clock();
    *tempo_avl = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Foram lidos %d candidatos na AVL.\n", contador);

    rewind(arquivo); // Voltar ao início do arquivo

    // Ler e inserir na BSB
    contador = 0;
    inicio = clock();
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%2s;%99[^;];%5[^;];%19[^;];%99[^;];%99[^;];%9[^;];%19[^;];%39[^;];%9[^\n]",
               candidato.estado, candidato.cidade, candidato.numero_urna, candidato.cargo,
               candidato.nome, candidato.nome_urna, candidato.sigla_partido,
               candidato.genero, candidato.grau_instrucao, candidato.cor_raca);
        bsb_inserir(*bsb, candidato);
        contador++;
        // printf("Inserido %d\n", contador); //linha de teste de funcionamento
    }
    fim = clock();
    *tempo_bsb = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Foram lidos %d candidatos na BSB.\n", contador);

    fclose(arquivo);
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
        printf("\nEscolha uma opcao de listagem do resultado:\n");
        printf("1 - Listar pela ABB\n");
        printf("2 - Listar pela AVL\n");
        printf("3 - Listar pela BSB\n");
        printf("4 - Listar tempos de execucao\n");
        printf("0 - Nao listar (voltar/prosseguir)\n");
        printf("Opcao: ");
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
                printf("Opcao: ");
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
            // printf("Voltando...\n");
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

// Função para validar a entrada em todas as estruturas
int validar_entrada_em_todas(char chave, char entrada[], Arvore_abb *abb, Arvore_avl *avl, Vetor_bsb *bsb)
{
    // Variáveis para indicar se o valor foi encontrado em cada estrutura
    int encontrado_abb = 0;
    int encontrado_avl = 0;
    int encontrado_bsb = 0;

    // ABB
    encontrado_abb = (percorrer_e_comparar_abb(abb->raiz, entrada, chave)) ? 1 : 0;

    // AVL
    encontrado_avl = (percorrer_e_comparar_avl(avl->raiz, entrada, chave)) ? 1 : 0;

    // BSB
    encontrado_bsb = (percorrer_e_comparar_bsb(bsb, entrada, chave)) ? 1 : 0;

    // Verificar se encontrou em todas as estruturas
    if ((encontrado_abb + encontrado_avl + encontrado_bsb) != 0)
    {
        return 3; // Encontrou em AO MENOS uma estrutura
    }

    return 0; // Não encontrou em todas as estruturas
}

int percorrer_e_comparar_abb(No_abb *no, char *valor, char chave)
{
    if (no == NULL)
    {
        return 0; // Valor não encontrado nesta subárvore
    }

    int cmp;
    if (chave == 'E')
    {
        cmp = strcmp(no->candidato.estado, valor);
    }
    else if (chave == 'C')
    {
        cmp = strcmp(no->candidato.cidade, valor);
    }
    else if (chave == 'P')
    {
        cmp = strcmp(no->candidato.sigla_partido, valor);
    }
    else if (chave == 'G')
    {
        cmp = strcmp(no->candidato.genero, valor);
    }
    else if (chave == 'R')
    {
        cmp = strcmp(no->candidato.cor_raca, valor);
    }
    else
    {
        return 0; // Chave inválida
    }

    if (cmp == 0)
    {
        return 1; // Valor encontrado!
    }

    // Continua percorrendo a árvore recursivamente
    if (cmp > 0)
    {
        return percorrer_e_comparar_abb(no->esq, valor, chave);
    }
    else
    {
        return percorrer_e_comparar_abb(no->dir, valor, chave);
    }
}

int percorrer_e_comparar_avl(No_avl *no, char *valor, char chave)
{
    if (no == NULL)
    {
        return 0; // Valor não encontrado nesta subárvore
    }

    int cmp;
    if (chave == 'E')
    {
        cmp = strcmp(no->candidato.estado, valor);
    }
    else if (chave == 'C')
    {
        cmp = strcmp(no->candidato.cidade, valor);
    }
    else if (chave == 'P')
    {
        cmp = strcmp(no->candidato.sigla_partido, valor);
    }
    else if (chave == 'G')
    {
        cmp = strcmp(no->candidato.genero, valor);
    }
    else if (chave == 'R')
    {
        cmp = strcmp(no->candidato.cor_raca, valor);
    }
    else
    {
        return 0; // Chave inválida
    }

    if (cmp == 0)
    {
        return 1; // Valor encontrado!
    }

    // Continua percorrendo a árvore recursivamente
    if (cmp > 0)
    {
        return percorrer_e_comparar_avl(no->esq, valor, chave);
    }
    else
    {
        return percorrer_e_comparar_avl(no->dir, valor, chave);
    }
}

int percorrer_e_comparar_bsb(Vetor_bsb *vet, char *valor, char chave)
{
    for (int i = 0; i < vet->tamanho; i++)
    {
        int cmp;
        if (chave == 'E')
        {
            cmp = strcmp(vet->candidatos[i].estado, valor);
        }
        else if (chave == 'C')
        {
            cmp = strcmp(vet->candidatos[i].cidade, valor);
        }
        else if (chave == 'P')
        {
            cmp = strcmp(vet->candidatos[i].sigla_partido, valor);
        }
        else if (chave == 'G')
        {
            cmp = strcmp(vet->candidatos[i].genero, valor);
        }
        else if (chave == 'R')
        {
            cmp = strcmp(vet->candidatos[i].cor_raca, valor);
        }
        else
        {
            return 0; // Chave inválida
        }

        if (cmp == 0)
        {
            return 1; // Valor encontrado!
        }
    }
    return 0; // Valor não encontrado no vetor
}

void listagem_case(Arvore_abb *arv_abb, Arvore_avl *arv_avl, Vetor_bsb *vet_bsb)
{
    char estado[MAX_TAM_ESTADO];
    char cidade[MAX_TAM_CIDADE];
    char partido[MAX_TAM_SIGLA_PARTIDO];
    char genero[MAX_TAM_GENERO];
    char cor_raca[MAX_TAM_COR_RACA];

    // melhor: aceita somente maiusculos atualmente e nao faz nenhuma validação

    printf("\nFiltros de Listagem (digite NA para ignorar o filtro):\n");
    printf("Estado: ");
    setbuf(stdin, NULL);
    scanf("%s", estado);

    for (int i = 0; i < strlen(estado); i++)
    {
        estado[i] = toupper(estado[i]);
    }

    if (strcmp(estado, "NA") != 0)
    {
        int valido = validar_entrada_em_todas('E', estado, arv_abb, arv_avl, vet_bsb);
        if (valido == 3)
        {
            printf("Estado encontrado e valido.\n");
        }
        else
        {
            printf("Estado nao encontrado ou invalido. Campo ESTADO sera desconsiderado na filtragem.\n");
            strcpy(estado, "NA");
        }
    }

    printf("\nCidade: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", cidade);

    for (int i = 0; i < strlen(cidade); i++)
    {
        cidade[i] = toupper(cidade[i]);
    }

    if (strcmp(cidade, "NA") != 0)
    {
        int valido = validar_entrada_em_todas('C', cidade, arv_abb, arv_avl, vet_bsb);
        if (valido == 3)
        {
            printf("Cidade encontrada e valida.\n");
        }
        else
        {
            printf("Cidade nao encontrada ou invalida. Campo CIDADE sera desconsiderado na filtragem.\n");
            strcpy(cidade, "NA");
        }
    }

    printf("\nPartido: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", partido);

    for (int i = 0; i < strlen(partido); i++)
    {
        partido[i] = toupper(partido[i]);
    }

    if (strcmp(partido, "NA") != 0)
    {
        int valido = validar_entrada_em_todas('P', partido, arv_abb, arv_avl, vet_bsb); 
        if (valido == 3)
        {
            printf("Partido encontrado e valido.\n");
        }
        else
        {
            printf("Partido nao encontrado ou invalido. Campo PARTIDO sera desconsiderado na filtragem.\n");
            strcpy(partido, "NA");
        }
    }

    printf("\nGenero (Masculino ou Feminino): ");
    setbuf(stdin, NULL);
    scanf("%s", genero);

    for (int i = 0; i < strlen(genero); i++)
    {
        genero[i] = toupper(genero[i]);
    }

    if (strcmp(genero, "NA") != 0)
    {
        int valido = validar_entrada_em_todas('G', genero, arv_abb, arv_avl, vet_bsb);
        if (valido == 3)
        {
            printf("Genero encontrado e valido.\n");
        }
        else
        {
            printf("Genero nao encontrado ou invalido. Campo GENERO sera desconsiderado na filtragem.\n");
            strcpy(genero, "NA");
        }
    }

    printf("\nCor/Raca: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", cor_raca);

    for (int i = 0; i < strlen(cor_raca); i++)
    {
        cor_raca[i] = toupper(cor_raca[i]);
    }

    if (strcmp(cor_raca, "NA") != 0)
    {
        int valido = validar_entrada_em_todas('R', cor_raca, arv_abb, arv_avl, vet_bsb);
        if (valido == 3)
        {
            printf("Cor/Raca encontrada e valida.\n");
        }
        else
        {
            printf("Cor/Raca nao encontrada ou invalida. Campo COR/RACA será desconsiderado na filtragem.\n");
            strcpy(cor_raca, "NA");
        }
    }

    criar_listagem(arv_abb, arv_avl, vet_bsb, estado, cidade, partido, genero, cor_raca);
}

//parte da esterzolas sobre a leitura do arquivo que mudei um pouco. aguardando feedback para poder excluir tudo abaixo ou não.

// Funções de leitura e escrita de arquivos
// ESTADO;CIDADE;NR_CANDIDATO;CARGO;NM_CANDIDATO;NM_URNA_CANDIDATO;SG_PARTIDO;GENERO;GRAU_INSTRUCAO;COR_RACA
/*int lerArquivoCandidatos(char *nomeArquivo, Candidato **candidatos, int *num_candidatos)
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
}*/

/*if (!lerArquivoCandidatos(nomeArquivo, &candidatos, &num_candidatos))
    {
        return 1;
    }

    clock_t inicio, fim;
    double tempo;

    // Pesquisa Binária
    inicio = clock();
    Vetor_bsb *vet_bsb = bsb_criar();
    for (int i = 0; i < num_candidatos; i++)
    {
        bsb_inserir(vet_bsb, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // bsb_imprimir(vet_bsb);
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
    printf("Tempo de ordenacao por Arvore AVL: %.6f segundos\n", tempo);*/