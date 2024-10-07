#ifndef _TAD_ABB_CANDIDATO_H_
#define _TAD_ABB_CANDIDATO_H_

#define MAX_TAM_ESTADO 3
#define MAX_TAM_CIDADE 50
#define MAX_TAM_NOME 50
#define MAX_TAM_NOME_URNA 20
#define MAX_TAM_SIGLA_PARTIDO 10
#define MAX_TAM_COR_RACA 10
#define MAX_TAM_GRAU_INSTRUCAO 40
#define MAX_TAM_GENERO 20
#define MAX_TAM_CARGO 20

// Estrutura do candidato
typedef struct Candidato
{
    char estado[MAX_TAM_ESTADO];
    char cidade[MAX_TAM_CIDADE];
    char numero_urna[6];
    char cargo[MAX_TAM_CARGO];
    char nome[MAX_TAM_NOME];
    char nome_urna[MAX_TAM_NOME_URNA];
    char sigla_partido[MAX_TAM_SIGLA_PARTIDO];
    char genero[MAX_TAM_GENERO];
    char grau_instrucao[MAX_TAM_GRAU_INSTRUCAO];
    char cor_raca[MAX_TAM_COR_RACA];

} Candidato;

// Estrutura do nó da ABB
typedef struct No_abb
{
    Candidato candidato;
    struct No_abb *esq;
    struct No_abb *dir;
} No_abb;

// Estrutura da ABB
typedef struct Arvore_abb
{
    No_abb *raiz;
} Arvore_abb;

// Funções de manipulação da ABB
Arvore_abb *abb_criar();
void abb_liberar(Arvore_abb *arv);
int abb_inserir(Arvore_abb *arv, Candidato candidato);
int abb_remover(Arvore_abb *arv, Candidato candidato);
No_abb *abb_buscar(Arvore_abb *arv, Candidato candidato);
int abb_tamanho(Arvore_abb *arv);
int abb_vazia(Arvore_abb *arv);
void abb_imprimir_in_ordem(Arvore_abb *arv);
void abb_imprimir_pre_ordem(Arvore_abb *arv);
void abb_imprimir_pos_ordem(Arvore_abb *arv);

#endif // _TAD_ABB_CANDIDATO_H_