#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tad_abb_candidato.h"
#include "tad_avl_candidato.h"
#include "tad_bsb_candidato.h"

// Funções de leitura e escrita de arquivos
int lerArquivoCandidatos(char *nomeArquivo, Candidato **candidatos, int *num_candidatos);
int compararCandidatos(const void *a, const void *b);
Candidato *buscaBinariaCandidato(Candidato *vetor, int inicio, int fim, char *estado, char *cidade, char *numero);
void cadastrarCandidato(Candidato *candidatos, int *num_candidatos);
void atualizarArquivoCandidatos(Candidato *candidatos, int num_candidatos);
void imprimirCandidatoCompleto(Candidato c);

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
    char nomeArquivo[100];
    printf("Escolha um opcao de arquivo para carregar os dados:\n");
    printf("1 - eleicoes2024\n");
    printf("2 - subConjuntoEleicoes2024\n");

    int opcao;
    scanf("%d", &opcao);
    if (opcao == 1)
    {
        strcpy(nomeArquivo, "C:\\Users\\ester\\OneDrive\\facul\\5SEMESTRE\\AED2\\TCD_AED2\\eleicoes2024.txt");
    }
    else if (opcao == 2)
    {
        strcpy(nomeArquivo, "C:\\Users\\ester\\OneDrive\\facul\\5SEMESTRE\\AED2\\TCD_AED2\\subConjuntoEleicoes2024.txt");
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
    // ?
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação por Pesquisa Binária: %.6f segundos\n", tempo);

    // Árvore Binária de Busca
    Arvore_abb *arv_abb = abb_criar();
    inicio = clock();
    for (int i = 0; i < num_candidatos; i++)
    {
        abb_inserir(arv_abb, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação por Árvore Binária de Busca: %.6f segundos\n", tempo);

    // Árvore AVL
    Arvore_avl *arv_avl = avl_criar();
    inicio = clock();
    for (int i = 0; i < num_candidatos; i++)
    {
        avl_inserir(arv_avl, candidatos[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação por Árvore AVL: %.6f segundos\n", tempo);

    free(candidatos);
    abb_liberar(arv_abb);
    avl_liberar(arv_avl);

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
    while (fscanf(arquivo, "%2s;%99[^;];%5[^;];%19[^;];%99[^;];%99[^;];%9[^;];%19[^;];%39[^;];%9[^\n]\n",
                   (*candidatos)[*num_candidatos].estado, (*candidatos)[*num_candidatos].cidade,
                   (*candidatos)[*num_candidatos].numero_urna, (*candidatos)[*num_candidatos].cargo,
                   (*candidatos)[*num_candidatos].nome, (*candidatos)[*num_candidatos].nome_urna,
                   (*candidatos)[*num_candidatos].sigla_partido, (*candidatos)[*num_candidatos].genero,
                   (*candidatos)[*num_candidatos].grau_instrucao, (*candidatos)[*num_candidatos].cor_raca) == 10)
    {
        (*num_candidatos)++;
        if (*num_candidatos == MAX_CANDIDATOS)
        {
            break;
        }
    }

    fclose(arquivo);
    return 1;
}

int compararCandidatos(const void *a, const void *b)
{
    Candidato *c1 = (Candidato *)a;
    Candidato *c2 = (Candidato *)b;

    int cmpEstado = strcmp(c1->estado, c2->estado);
    if (cmpEstado != 0)
        return cmpEstado;

    int cmpCidade = strcmp(c1->cidade, c2->cidade);
    if (cmpCidade != 0)
        return cmpCidade;

    return c1->numero_urna - c2->numero_urna;
}

Candidato *buscaBinariaCandidato(Candidato *vetor, int inicio, int fim, char *estado, char *cidade, char *numero)
{
    if (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        // Comparar estado primeiro (usando strcmp para strings)
        int cmpEstado = strcmp(vetor[meio].estado, estado);
        if (cmpEstado == 0)
        {
            // Comparar cidade (usando strcmp para strings)
            int cmpCidade = strcmp(vetor[meio].cidade, cidade);
            if (cmpCidade == 0)
            {
                // Comparar numero_urna com numero (usando strcmp, pois ambos são char[])
                int cmpNumero = strcmp(vetor[meio].numero_urna, numero);
                if (cmpNumero == 0)
                {
                    return &vetor[meio]; // Encontrado
                }
                else if (cmpNumero < 0)
                {
                    return buscaBinariaCandidato(vetor, meio + 1, fim, estado, cidade, numero); // Buscar na metade direita
                }
                else
                {
                    return buscaBinariaCandidato(vetor, inicio, meio - 1, estado, cidade, numero); // Buscar na metade esquerda
                }
            }
            else if (cmpCidade < 0)
            {
                return buscaBinariaCandidato(vetor, meio + 1, fim, estado, cidade, numero); // Buscar na metade direita (cidade maior)
            }
            else
            {
                return buscaBinariaCandidato(vetor, inicio, meio - 1, estado, cidade, numero); // Buscar na metade esquerda (cidade menor)
            }
        }
        else if (cmpEstado < 0)
        {
            return buscaBinariaCandidato(vetor, meio + 1, fim, estado, cidade, numero); // Buscar na metade direita (estado maior)
        }
        else
        {
            return buscaBinariaCandidato(vetor, inicio, meio - 1, estado, cidade, numero); // Buscar na metade esquerda (estado menor)
        }
    }

    return NULL; // Não encontrado
}

void cadastrarCandidato(Candidato *candidatos, int *num_candidatos)
{
    printf("Digite o estado: ");
    scanf("%2s", candidatos[*num_candidatos].estado);

    printf("Digite a cidade: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].cidade);

    printf("Digite o numero: ");
    scanf("%d", &candidatos[*num_candidatos].numero_urna);

    printf("Digite o cargo: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].cargo);

    printf("Digite o nome completo: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].nome);

    printf("Digite o nome de urna: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].nome_urna);

    printf("Digite o partido: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].sigla_partido);

    printf("Digite o genero: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].genero);

    printf("Digite o grau de instrucao: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].grau_instrucao);

    printf("Digite a cor/raca: ");
    scanf(" %[^\n]", candidatos[*num_candidatos].cor_raca);

    (*num_candidatos)++;
    printf("Candidato cadastrado com sucesso!\n");
}

void atualizarArquivoCandidatos(Candidato *candidatos, int num_candidatos)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para atualizacao!\n");
        return;
    }

    for (int i = 0; i < num_candidatos; i++)
    {
        fprintf(arquivo, "%s  %s  %d  %s  %s  %s  %s  %s  %s  %s\n",
                candidatos[i].estado, candidatos[i].cidade, candidatos[i].numero_urna,
                candidatos[i].cargo, candidatos[i].nome, candidatos[i].nome_urna,
                candidatos[i].sigla_partido, candidatos[i].genero, candidatos[i].grau_instrucao,
                candidatos[i].cor_raca);
    }

    fclose(arquivo);
    printf("Arquivo atualizado com sucesso!\n");
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
