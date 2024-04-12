typedef struct node {
    int val;
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

Node *buscar(Node *cabeca, int val);
Node *inserir(Node *cabeca, int val);
Node *remover(Node *cabeca, int val);

void printAvlOrd(Node *cabeca);
