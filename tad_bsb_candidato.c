#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_bsb_candidato.h"

// Funções auxiliares

int comparar_candidatos_bsb(Candidato c1, Candidato c2)
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

// Função auxiliar para redimensionar o vetor
int bsb_redimensionar(Vetor_bsb *vet, int nova_capacidade)
{
    Candidato *novo_vetor = (Candidato *)realloc(vet->candidatos, nova_capacidade * sizeof(Candidato));
    if (novo_vetor == NULL)
    {
        return 0; // Falha na realocação de memória
    }
    vet->candidatos = novo_vetor;
    vet->capacidade = nova_capacidade;
    return 1;
}

// Funções da Busca Binária em Vetor

Vetor_bsb *bsb_criar()
{
    Vetor_bsb *vet = (Vetor_bsb *)malloc(sizeof(Vetor_bsb));
    if (vet != NULL)
    {
        vet->tamanho = 0;
        vet->capacidade = 10; // Define uma capacidade inicial
        vet->candidatos = (Candidato *)malloc(vet->capacidade * sizeof(Candidato));
        if (vet->candidatos == NULL)
        {
            free(vet);
            return NULL; // Falha na alocação de memória
        }
    }
    return vet;
}

void bsb_liberar(Vetor_bsb *vet)
{
    if (vet != NULL)
    {
        free(vet->candidatos);
        free(vet);
    }
}

int bsb_inserir(Vetor_bsb *vet, Candidato candidato)
{
    // Verifica se é necessário redimensionar o vetor
    if (vet->tamanho == vet->capacidade)
    {
        if (!bsb_redimensionar(vet, 2 * vet->capacidade))
        {
            return 0; // Falha na realocação de memória
        }
    }

    // Encontra a posição correta para inserir o candidato
    int i = vet->tamanho;
    while (i > 0 && comparar_candidatos_bsb(candidato, vet->candidatos[i - 1]) < 0)
    {
        vet->candidatos[i] = vet->candidatos[i - 1];
        i--;
    }

    // Insere o candidato na posição encontrada
    vet->candidatos[i] = candidato;
    vet->tamanho++;
    return 1;
}

int bsb_remover(Vetor_bsb *vet, Candidato candidato)
{
    int indice = bsb_buscar(vet, candidato);
    if (indice == -1)
    {
        return 0; // Candidato não encontrado
    }

    // Desloca os elementos para a esquerda a partir do índice
    for (int i = indice; i < vet->tamanho - 1; i++)
    {
        vet->candidatos[i] = vet->candidatos[i + 1];
    }

    vet->tamanho--;

    // Realoca o vetor para liberar memória (opcional - veja observações)
    if (vet->tamanho < vet->capacidade / 2 && vet->capacidade > 10)
    {
        // Se o tamanho for menor que a metade da capacidade,
        // reduz a capacidade pela metade, mas mantém um mínimo de 10.
        if (!bsb_redimensionar(vet, vet->capacidade / 2))
        {
            // A realocação falhou, mas a remoção lógica foi feita.
            // Pode-se retornar 1 ou tratar o erro de outra forma.
            return 1;
        }
    }

    return 1;
}

int bsb_buscar(Vetor_bsb *vet, Candidato candidato)
{
    int inicio = 0;
    int fim = vet->tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int cmp = comparar_candidatos_bsb(candidato, vet->candidatos[meio]);

        if (cmp == 0)
        {
            return meio; // Posição do candidato no vetor
        }
        else if (cmp < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    return -1; // Candidato não encontrado
}

int bsb_tamanho(Vetor_bsb *vet)
{
    return vet->tamanho;
}

int bsb_vazia(Vetor_bsb *vet)
{
    return vet->tamanho == 0;
}

void bsb_imprimir(Vetor_bsb *vet)
{
    if (bsb_vazia(vet))
    {
        printf("Vetor vazio!\n");
        return;
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        imprimir_candidato_simples_bsb(vet->candidatos[i]);
    }
}

void imprimir_candidato_completo_bsb(Candidato c)
{
    printf("Nome: %s\n", c.nome);
    printf("Nome na urna: %s\n", c.nome_urna);
    printf("Numero: %s\n", c.numero_urna);
    printf("Estado: %s\n", c.estado);
    printf("Cidade: %s\n", c.cidade);
    printf("Cargo: %s\n", c.cargo);
    printf("Partido: %s\n", c.sigla_partido);
    printf("Genero: %c\n", c.genero);
    printf("Grau de instrucao: %c\n", c.grau_instrucao);
    printf("Cor/Raca: %c\n", c.cor_raca);
    printf("--------------------\n");
}

void imprimir_candidato_simples_bsb(Candidato c)
{
    printf("Nome na urna: %s; Numero: %s; Estado: %s; Cidade: %s; Cargo: %s\n", c.nome_urna, c.numero_urna, c.estado, c.cidade, c.cargo);
}