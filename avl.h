#define valor int

typedef struct node {
    valor val;
    int fb;
    struct node *dir;
    struct node *esq;
} Node;

Node *rotacaoEsquerda(Node *n);
Node *rotacaoDireita(Node *n);
Node *rotacaoEsquerdaDireita(Node *n);
Node *rotacaoDireitaEsquerda(Node *n);

int calcFb(Node *n);
Node *balancear(Node *cabeca);

Node *buscar(Node *cabeca, valor val);
Node *inserir(Node *cabeca, valor val);
Node *remover(Node *cabeca, valor val);

void printAvlOrd(Node *cabeca);
