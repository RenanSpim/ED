#include "stdio.h"
#include "stdlib.h"


typedef struct node {
    int val;
    int fb;
    struct node *dir;
    struct node *esq;
} Node;

Node *rotacaoEsquerda(Node *n) {
    printf("rotacao esquerda\n");
    Node *novaCabeca = n->dir;
    Node *casoPart = novaCabeca->esq;

    novaCabeca->esq = n;
    n->dir = casoPart;
    
    return novaCabeca;
}

Node *rotacaoDireita(Node *n) {
    printf("rotacao direita\n");
    Node *novaCabeca = n->esq;
    Node *casoPart = novaCabeca->dir;

    novaCabeca->dir = n;
    n->esq = casoPart;

    return novaCabeca;
}

Node *rotacaoEsquerdaDireita(Node *n) {
    printf("rotacao esquerda direita\n");
    Node *novaCabeca = n->dir->esq;
    Node *casoPart = novaCabeca->dir;
    Node *aux = n->dir;

    n->dir = novaCabeca;
    novaCabeca->dir = aux;
    aux->esq = casoPart;

    return rotacaoEsquerda(n);
}

Node *rotacaoDireitaEsquerda(Node *n) {
    printf("rotacao direita esquerda\n");
    Node *novaCabeca = n->esq->dir;
    Node *casoPart = novaCabeca->esq;
    Node *aux = n->esq;

    n->esq = novaCabeca;
    novaCabeca->esq = aux;
    aux->dir = casoPart;

    return rotacaoDireita(n);
}

int altura(Node *n) {
    int altEsq = 0, altDir = 0;
    
    if (n == NULL) return 0;
    
    altDir = altura(n->dir) + 1;
    altEsq = altura(n->esq) + 1;

    return (altDir > altEsq) ? altDir : altEsq;
}

int calcFb(Node *n) {
    return altura(n->dir) - altura(n->esq);
}

Node *balancear(Node *cabeca) {
    cabeca->fb = calcFb(cabeca);
    
    if (cabeca->fb > 1 && cabeca->dir != NULL) {
        cabeca->dir->fb = calcFb(cabeca->dir);
        if (cabeca->dir->fb != 0) {
            cabeca = (cabeca->dir->fb > 0)
                ? rotacaoEsquerda(cabeca)
                : rotacaoEsquerdaDireita(cabeca);
        }
    } else if (cabeca->fb < -1 && cabeca->esq != NULL) {
        cabeca->esq->fb = calcFb(cabeca->esq);
        if (cabeca->esq->fb != 0) {
            cabeca = (cabeca->esq->fb < 0)
                ? rotacaoDireita(cabeca)
                : rotacaoDireitaEsquerda(cabeca);
        }
    }

    return cabeca;
}

Node *inserir(Node *cabeca, int val) {
    if (cabeca == NULL) {
        cabeca = malloc(sizeof(Node));
        cabeca->val = val;
        cabeca->esq = NULL;
        cabeca->dir = NULL;
        cabeca->fb = 0;
    }

    if (val > cabeca->val) cabeca->dir = inserir(cabeca->dir, val);
    if (val < cabeca->val) cabeca->esq = inserir(cabeca->esq, val);

    cabeca = balancear(cabeca);

    return cabeca;
}

Node *remover(Node *cabeca, int val) {
    Node *aux, *prox, *atual = cabeca;
    
    if (cabeca == NULL) return NULL;

    if (val == cabeca->val) { // remove cabeca
        aux = cabeca->dir;
        atual = cabeca;

        if (cabeca->dir == NULL) { // so tem filho a esquerda
            aux = cabeca->esq;
            free(cabeca);
            return aux;
        }
        
        while (aux->esq != NULL) { // aux vira o menor valor da direita da cabeca e atual seu pai
            atual = aux;
            aux = aux->esq;
        }
        
        if (aux != cabeca->dir) {
            atual->esq = NULL;
            aux->dir = cabeca->dir;
        }
        aux->esq = cabeca->esq;
        
        aux = balancear(aux);
        return aux;
    }

    atual = cabeca;
    prox = cabeca->val > val ? cabeca->esq : cabeca->dir;

    while (prox != NULL && prox->val != val) { // prox = node a remover
        atual = prox;

        if (val > prox->val) {
            prox = prox->dir;
        } else if (val < prox->val) {
            prox = prox->esq;
        }
    }

    if (prox == NULL) return cabeca;

    if (atual->val > prox->val) { // remove atual->esq ou prox
        aux = prox->dir;
        
        if (prox->dir != NULL) { // tem direita (1 ou 2 filhos)
            atual->esq = aux;
            while (aux->esq != NULL) aux = aux->esq;
            aux->esq = prox->esq;
        } else if (prox->esq != NULL) { // tem apenas esquerda (1 filho)
            atual->esq = prox->esq;
        } else { // folha (0 filhos)
            atual->esq = NULL;
        }
    } else { // remove atual->dir
        aux = prox->esq;
        
        if (aux != NULL) { // tem esquerda (1 ou 2 filhos)
            atual->dir = aux;
            while (aux->dir != NULL) aux = aux->dir;
            aux->dir = prox->dir;
        } else if (prox->dir != NULL) { // tem apenas direita (1 filho)
            atual->dir = prox->dir;
        } else { // folha (0 filhos)
            atual->dir = NULL;
        }
    }

    free(prox);
    cabeca = balancear(cabeca);

    return cabeca;
}

void printAvlOrd(Node *cabeca) {
    if (cabeca == NULL) return;

    printAvlOrd(cabeca->esq);
    printf("%d\n", cabeca->val);
    printAvlOrd(cabeca->dir);
}

Node *buscar(Node *cabeca, int val) {
    if (cabeca == NULL) return NULL;
    
    if (val > cabeca->val) {
        return buscar(cabeca->dir, val);
    } else if (val < cabeca->val) {
        return buscar(cabeca->esq, val);
    } else {
        return cabeca;
    }

    return NULL;
}

int main() {
    Node *cabeca = NULL;
    int num;

    srand(4);

    for (int i = 0; i < 10; i++) {
        num = rand() % 1000;
        printf("inserindo: %d\n", num);
        cabeca = inserir(cabeca, num);
    }

    for (int i = 0; i < 500; i++) {
        num = rand() % 1000;
        if (buscar(cabeca, num) != NULL) printf("deletado: %d\n", num);
        cabeca = remover(cabeca, num);
    }
    
    printAvlOrd(cabeca);
}
