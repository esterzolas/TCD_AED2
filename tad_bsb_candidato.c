#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_bsb_candidato.h"

// Funções auxiliares
void imprimir_candidato_completo_bsb(Candidato c)
{
    printf("\nNome: %s\n", c.nome);
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
    printf("\nNome na urna: %s\n", c.nome_urna);
    printf("Numero: %s\n", c.numero_urna);
    printf("Estado: %s\n", c.estado);
    printf("Cidade: %s\n", c.cidade);
    printf("Cargo: %s\n", c.cargo);
    printf("Partido: %s\n", c.sigla_partido);
    printf("--------------------\n");
}

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
        vet->capacidade = 100; // Define uma capacidade inicial
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
        if (!bsb_redimensionar(vet, 100 + vet->capacidade))
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
    if (vet->capacidade - 100 > vet->tamanho)
    {
        // Verifica se é possível reduzir o vetor
        if (!bsb_redimensionar(vet, vet->capacidade - 100))
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

Vetor_bsb *filtrar_por_estado_bsb(Vetor_bsb *vet, char estado[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet; // Retorna um vetor vazio se o original for nulo ou vazio
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (strcmp(vet->candidatos[i].estado, estado) == 0)
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}

Vetor_bsb *filtrar_por_cidade_bsb(Vetor_bsb *vet, char cidade[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet;
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (strcmp(vet->candidatos[i].cidade, cidade) == 0)
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}

Vetor_bsb *filtrar_por_chave_bsb(Vetor_bsb *vet, char chave, char argumento[])
{
    Vetor_bsb *sub_vet = bsb_criar();
    if (vet == NULL || bsb_vazia(vet))
    {
        return sub_vet;
    }

    for (int i = 0; i < vet->tamanho; i++)
    {
        if (comparar_chave_bsb(vet->candidatos[i], chave, argumento))
        {
            bsb_inserir(sub_vet, vet->candidatos[i]);
        }
    }
    return sub_vet;
}

int comparar_chave_bsb(Candidato candidato, char chave, char argumento[])
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