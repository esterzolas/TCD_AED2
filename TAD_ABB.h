#define TAM_CEP 9
#define TAM_SIGLA 3
#define TAM_NOME 50
#define TAM_ENDERECO 100

// Definição da estrutura da cidade
typedef struct
{
    char cep[TAM_CEP];
    char sigla_estado[TAM_SIGLA];
    char nome[TAM_NOME];
    char endereco[TAM_ENDERECO];
} Cidade;

// Definição da estrutura do nó da árvore
typedef struct NoArvore
{
    Cidade cidade;             // Dados da cidade
    struct NoArvore *esquerda; // Ponteiro para o filho esquerdo
    struct NoArvore *direita;  // Ponteiro para o filho direito
} NoArvore;

// Definição do tipo de dado abstrato Árvore Binária de Busca
typedef NoArvore *ABB;

// Funções do TAD ABB

// Cria uma árvore vazia
ABB criar_abb();

// Insere um novo nó na árvore
ABB inserir(ABB raiz, Cidade cidade);

// Remove um nó da árvore
ABB remover(ABB raiz, char *cep);

// Busca um nó na árvore
NoArvore *pesquisar(ABB raiz, char *cep);

// Percursos da árvore
void percorrer_central(ABB raiz);
void percorrer_pre_fixado(ABB raiz);
void percorrer_pos_fixado(ABB raiz);

// Retorna a altura da árvore
int altura(ABB raiz);

// Encontra o nó com o menor CEP
NoArvore *menor(ABB raiz);

// Encontra o nó com o maior CEP
NoArvore *maior(ABB raiz);

// Libera a memória alocada para a árvore
void liberar_abb(ABB raiz);