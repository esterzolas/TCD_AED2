/* Jean Souto G. Moreira
João Vitor Feijo
Ana Alice Cordeira
Ester Freitas

- AS INFORMAÇÕES NO ARQUIVO PRECISAM ESTAR SEPARADAS POR PONTO E VÍRGULA: CEP;SIGLA;CIDADE;ENDERECO */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_ABB.h"

#define ARQUIVO "C:\\Users\\ester\\OneDrive\\facul\\5SEMESTRE\\AED2\\TCD AED2\\cep ponto e virgula.txt"
#define TAM_LINHA 200

// Função para ler os dados do arquivo e criar a ABB sabendo que estao separados por ponto e vírgula
ABB ler_arquivo(char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    ABB abb = criar_abb();
    Cidade cidade;
    char linha[TAM_LINHA];

    // Lê cada linha do arquivo
    while (fgets(linha, TAM_LINHA, arquivo) != NULL)
    {
        // Usando strtok para dividir a linha com base no ponto e vírgula
        char *token = strtok(linha, ";");
        if (token != NULL)
        {
            strncpy(cidade.cep, token, sizeof(cidade.cep) - 1);
            cidade.cep[sizeof(cidade.cep) - 1] = '\0'; // Garantir o terminador nulo
        }

        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strncpy(cidade.sigla_estado, token, sizeof(cidade.sigla_estado) - 1);
            cidade.sigla_estado[sizeof(cidade.sigla_estado) - 1] = '\0';
        }

        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strncpy(cidade.nome, token, sizeof(cidade.nome) - 1);
            cidade.nome[sizeof(cidade.nome) - 1] = '\0';
        }

        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            strncpy(cidade.endereco, token, sizeof(cidade.endereco) - 1);
            cidade.endereco[sizeof(cidade.endereco) - 1] = '\0';
        }

        // Insere a cidade na ABB
        abb = inserir(abb, cidade);
    }

    fclose(arquivo);
    return abb;
}

// Função para buscar um CEP na ABB
void buscar_cep(ABB abb)
{
    char cep[TAM_CEP];
    printf("Digite o CEP a ser pesquisado: ");
    scanf("%8s", cep);

    NoArvore *resultado = pesquisar(abb, cep);
    if (resultado != NULL)
    {
        printf("CEP: %s\nEstado: %s\nCidade: %s\nEndereco: %s\n",
               resultado->cidade.cep, resultado->cidade.sigla_estado,
               resultado->cidade.nome, resultado->cidade.endereco);
    }
    else
    {
        printf("CEP nao encontrado.\n");
    }
}

// Função para criar uma ABB com as primeiras 20 linhas do arquivo
ABB criar_abb_parcial(char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    ABB abb = criar_abb();
    Cidade cidade;
    char linha[TAM_LINHA];
    int contador = 0;

    // Lê apenas as primeiras 20 linhas do arquivo
    while (fgets(linha, TAM_LINHA, arquivo) != NULL && contador < 20)
    {
        char *token = strtok(linha, ";");
        if (token != NULL)
        {
            strncpy(cidade.cep, token, sizeof(cidade.cep) - 1);
            cidade.cep[sizeof(cidade.cep) - 1] = '\0';
        }

        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strncpy(cidade.sigla_estado, token, sizeof(cidade.sigla_estado) - 1);
            cidade.sigla_estado[sizeof(cidade.sigla_estado) - 1] = '\0';
        }

        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strncpy(cidade.nome, token, sizeof(cidade.nome) - 1);
            cidade.nome[sizeof(cidade.nome) - 1] = '\0';
        }

        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            strncpy(cidade.endereco, token, sizeof(cidade.endereco) - 1);
            cidade.endereco[sizeof(cidade.endereco) - 1] = '\0';
        }

        abb = inserir(abb, cidade);
        contador++;
    }

    fclose(arquivo);
    return abb;
}

// Função para exibir o menu e processar a escolha do usuário
void menu(ABB abb)
{
    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1 - Buscar CEP\n");
        printf("2 - Mostrar toda a arvore\n");
        printf("3 - Altura da Arvore\n");
        printf("4 - Menor e Maior CEP\n");
        printf("5 - Criar ABB Parcial e Exibir Percursos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            buscar_cep(abb);
            break;

        case 2:
            printf("\nPercurso central da ABB completa:\n");
            percorrer_central(abb);
            break;

        case 3:
            printf("Altura da arvore: %d\n", altura(abb));
            break;

        case 4:
            if (abb != NULL)
            {
                NoArvore *menor_no = menor(abb);
                NoArvore *maior_no = maior(abb);
                printf("Menor CEP: %s\n", menor_no->cidade.cep);
                printf("Maior CEP: %s\n", maior_no->cidade.cep);
            }
            else
            {
                printf("Arvore vazia.\n");
            }
            break;
        case 5:
        {
            ABB abb_parcial = criar_abb_parcial(ARQUIVO);
            printf("\nPercurso central:\n");
            percorrer_central(abb_parcial);
            printf("\nPercurso pre-fixado:\n");
            percorrer_pre_fixado(abb_parcial);
            printf("\nPercurso pos-fixado:\n");
            percorrer_pos_fixado(abb_parcial);

            // Libera a memória alocada para a ABB parcial
            liberar_abb(abb_parcial);
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main()
{
    // Lê os dados do arquivo e cria a ABB
    ABB abb = ler_arquivo(ARQUIVO);

    // Exibe o menu
    menu(abb);

    // Libera a memória alocada para a ABB
    liberar_abb(abb);

    return 0;
}
