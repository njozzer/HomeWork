#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
const char *file = "/home/njozzer/CLionProjects/untitled22/data.txt";

int max(int a, int b) {
    return a > b ? a : b;
}

int StringStartsWith(char TestArray[80], char StringToFind[80], int count) {
    for (int i = 0; i < count; i++) {
        if (TestArray[i] != StringToFind[i])
            return 0;
    }
    return 1;
}

typedef struct Node {
    char name[80];
    char version[80];
    char lisence[80];
    unsigned int has_android:1;
    unsigned int has_ios:1;
    unsigned int is_free:1;
    unsigned int is_open_source:1;
    double cost;
    char developer[80];
    char code_language[80];
    int balance;
    unsigned int height;
    struct Node *Left;
    struct Node *Right;
    struct Node *Parent;
} Node;
typedef struct AVL_Tree {
    Node *root;
} AVL_Tree;

void InitNode(Node *B,
              char name[80],
              char version[80],
              char lisence[80],
              unsigned int has_android,
              unsigned int has_ios,
              unsigned int is_free,
              unsigned int is_open_source,
              double cost,
              char developer[80],
              char code_language[80]) {

    strcpy(B->name, name);
    strcpy(B->version, version);
    strcpy(B->developer, developer);
    strcpy(B->lisence, lisence);
    strcpy(B->developer, developer);
    strcpy(B->code_language, code_language);
    B->has_android = has_android;
    B->has_ios = has_ios;
    B->is_free = is_free;
    B->is_open_source = is_open_source;
    B->cost = cost;
    B->Left = NULL;
    B->Right = NULL;
    B->Parent = NULL;
    B->height = 0;
}

void InitTree(AVL_Tree *T) {
    T->root = NULL;
}

Node *Balance(Node *p);

void FixHeight(Node *p);

void Add_R(AVL_Tree *T, Node *N, Node *Current);

int bfactor(Node *p);

Node *RotateLeft(Node *q);

Node *RotateRight(Node *p);

void Add_R(AVL_Tree *T, Node *N, Node *Current = NULL) {
    if (T == NULL) return;
    if (T->root == NULL) {
        T->root = N;
        T->root->balance = 0;
        return;
    }
    if (Current == NULL)
        Current = T->root;
    int c = strcmp(Current->name, N->name);
    if (c < 0) {
        if (Current->Left != NULL)
            Add_R(T, N, Current->Left);
        else {
            Current->Left = N;
            N->height = Current->height + 1;
            Balance(N);
        }
    }
    // Если новое имя меньше текущего, то переходим в правое поддерево
    if (c > 0) {
        if (Current->Right != NULL)
            Add_R(T, N, Current->Right);
        else {
            Current->Right = N;
            N->height = Current->height + 1;
            Balance(N);
        }
    }
    if (c == 0) {

    }
    return;
}

int bfactor(Node *p) {
    int hr = (p->Right == NULL) ? 0 : p->Right->height;
    int hl = (p->Left == NULL) ? 0 : p->Left->height;
    return hr - hl;
}

void FixHeight(Node *p) {
    int hr = (p->Right == NULL) ? 0 : p->Right->height;
    int hl = (p->Left == NULL) ? 0 : p->Left->height;
    p->height = max(hr, hl) + 1;
}

Node *RotateLeft(Node *q) {
    Node *p = q->Right;
    q->Right = p->Left;
    p->Left = q;
    FixHeight(q);
    FixHeight(p);
    return p;
}

Node *RotateRight(Node *p) {
    Node *q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
}

Node *Balance(Node *p) {
    FixHeight(p);
    if (bfactor(p) >= 2) {
        p->Right = RotateLeft(p->Right);
        return RotateLeft(p);
    }
    if (bfactor(p) <= -2) {
        p->Left = RotateLeft(p->Left);
        return RotateRight(p);
    }
    return p;
}

void Remove(AVL_Tree *T, char BookName[]) {}

Node *Find_R(AVL_Tree *T, char BookName[], Node *Current = NULL) {
    if (T == NULL) return NULL;
    if (Current == NULL) Current = T->root;
    int c = strcmp(Current->name, BookName);
    if (c == -1) {
        if (Current->Left != NULL) return Find_R(T, BookName, Current->Left);
        else return NULL;
    }
    if (c == 1) {
        if (Current->Right != NULL) return Find_R(T, BookName, Current->Right);
        else return NULL;
    }
    if (c == 0)
        return Current;
    return NULL;
}

void Load(AVL_Tree *T, const char *file) {
    if (T == NULL) return;
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("\nCouldn't open the file: %s", file);
        return;
    }
    char name[80];
    char version[80];
    char lisence[80];
    unsigned int has_android = 0;
    unsigned int has_ios = 0;
    unsigned int is_free = 0;
    unsigned int is_open_source = 0;
    double cost = 0;
    char developer[80];
    char code_language[80];

    while (fscanf(fp, "%s %s %s %d %d %d %d %lf %s %s",
                  name,
                  version,
                  lisence,
                  &has_android,
                  &has_ios,
                  &is_free,
                  &is_open_source,
                  &cost,
                  developer,
                  code_language) != EOF) {
        Node *N = (Node *) malloc(sizeof(Node));
        printf("%s %s %s", N->name, N->version, N->lisence);
        InitNode(N, name, version, lisence, has_android, has_ios, is_free, is_open_source, cost, developer,
                 code_language);
        Add_R(T, N);
    }

    fclose(fp);
}

void Add(AVL_Tree *T, Node *N) {
    if (T == NULL) return;
    if (T->root == NULL) {
        T->root = N;
        return;
    }
    Node *Current = T->root;
    while (Current != NULL) {
        int c = strcmp(Current->name, N->name);
        if (c < 0) {
            if (Current->Left != NULL) {
                Current = Current->Left;
                continue;
            }
            Current->Left = N;
            break;
        }
        if (c > 0) {
            if (Current->Right != NULL) {
                Current = Current->Right;
                continue;
            }
            Current->Right = N;
            break;
        }
        if (c == 0) {
            //нашли совпадение имён
        }
    }
}

void SaveNode(Node *node, FILE *fp) {
    if (fp == NULL)
        return;
    if (node != NULL) {
        fprintf(fp, "%s %s %s %d %d %d %d %lf %s %s\n",
                node->name,
                node->version,
                node->lisence,
                node->has_android,
                node->has_ios,
                node->is_free,
                node->is_open_source,
                node->cost,
                node->developer,
                node->code_language);
        if (node->Left != NULL)
            SaveNode(node->Left, fp);
        if (node->Right != NULL)
            SaveNode(node->Right, fp);
    }
}

void Save(AVL_Tree *T, const char *file) {
    if (T == NULL) return;
    FILE *ptr;
    ptr = fopen(file, "w");
    if (ptr == NULL) {
        printf("\nCouldn't open the file: %s", file);
        return;
    }
    SaveNode(T->root, ptr);
    fclose(ptr);
}

void PreOrder(Node *node, void (*f)(Node *)) {
    if (node != NULL)
        f(node);
    if (node->Left != NULL)
        PreOrder(node->Left, f);
    if (node->Right != NULL)
        PreOrder(node->Right, f);
}

void InOrder(Node *node, void (*f)(Node *)) {
    if (node->Left != NULL)
        InOrder(node->Left, f);
    if (node != NULL)
        f(node);
    if (node->Right != NULL)
        InOrder(node->Right, f);
}

void PostOrder(Node *node, void (*f)(Node *)) {
    if (node->Left != NULL)
        PostOrder(node->Left, f);
    if (node->Right != NULL)
        PostOrder(node->Right, f);
    if (node != NULL)
        f(node);
}

void print(Node *B) {
    if (B != NULL)
        printf("\nName: %s\nDeveloper: %s \nVersion: %s\nIs_Free : %d\n*****",
               B->name,
               B->developer,
               B->version,
               B->is_free);
}

Node *find(AVL_Tree *tree, char name[80]) {
    Node *curr = tree->root;
    int cmp = strcmp(name, curr->name);
    while (cmp != 0) {
        if (cmp == -1) {
            curr = curr->Left;
            if (curr == NULL)
                return curr;
        } else if (cmp == 1) {
            curr = curr->Right;
            if (curr == NULL)
                return curr;
        }
        cmp = strcmp(name, curr->name);

    }
    return curr;

}

Node *copy(Node *target) {
    Node *node = (Node *) malloc(sizeof(Node));
    InitNode(node,
             target->name,
             target->version,
             target->lisence,
             target->has_android,
             target->has_ios,
             target->is_free,
             target->is_open_source,
             target->cost,
             target->developer,
             target->code_language);
    return node;
}

/**
 *  param
 *  1 = free
 *  0 = not free
 * */
void *filter(Node *curr, AVL_Tree *ftree, int is_free) {
    if (is_free == curr->is_free) {
        Add_R(ftree, copy(curr));
    }
    if (is_free == curr->is_free) {
        Add_R(ftree, curr);
    }
    if (curr->Left != NULL) {
        filter(curr->Left, ftree, is_free);
    }
    if (curr->Right != NULL) {
        filter(curr->Left, ftree, is_free);
    }
}

int main() {
    AVL_Tree tree;
    InitTree(&tree);
    Node *node1 = (Node *) malloc(sizeof(Node));
    Node *node2 = (Node *) malloc(sizeof(Node));
    Node *node3 = (Node *) malloc(sizeof(Node));
    Node *node4 = (Node *) malloc(sizeof(Node));
    InitNode(node1, "Name1", "1.0", "lisence1", 1, 1, 0, 1, 390.0, "developer1", "Java");
    InitNode(node2, "Name2", "0.7s", "lisence2", 0, 0, 1, 0, 540.0, "developer2", "C/C++");
    InitNode(node3, "Name3", "3.4b", "lisence3", 1, 1, 0, 1, 564.0, "developer3", "C#");
    InitNode(node4, "Name4", "0.1a", "lisence4", 1, 1, 0, 1, 490.0, "developer4", "Python3");
    Add_R(&tree, node1);
    Add_R(&tree, node2);
    Add_R(&tree, node3);
    Add_R(&tree, node4);
    void (*f_ptr)(Node *);
    f_ptr = print;
    printf("*****");
    Save(&tree, file);
    AVL_Tree ftree;
    InitTree(&ftree);
    filter(tree.root, &ftree, 0);
    PreOrder(ftree.root, f_ptr);

    return 0;
}
