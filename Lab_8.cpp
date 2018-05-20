#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <cstdio>
#include <stdlib.h>

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

struct BookNode {
    char name[80];
    char author[80];

    int balance;
    int height;

    BookNode *Left;
    BookNode *Right;
    BookNode *Parent;
};

void InitNode(BookNode *B) {
    B->Left = NULL;
    B->Right = NULL;
    B->Parent = NULL;

    B->height = 0;
}

void print(BookNode *B) {
    if (B != NULL)
        printf("\nName: %s\nAuthor: %s", B->name, B->author);
}

struct BookTree {
    BookNode *Root;
};

void InitTree(BookTree *T) {
    T->Root = NULL;
}

BookNode *Balance(BookNode *p);

void FixHeight(BookNode *p);

void Add_R(BookTree *T, BookNode *N, BookNode *Current);

int bfactor(BookNode *p);

BookNode *RotateLeft(BookNode *q);

BookNode *RotateRight(BookNode *p);

void Add_R(BookTree *T, BookNode *N, BookNode *Current = NULL) {
    if (T == NULL) return;
    if (T->Root == NULL) {
        T->Root = N;
        T->Root->balance = 0;
        return;
    }
    if (Current == NULL)
        Current = T->Root;
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

int bfactor(BookNode *p) {
    int hr = (p->Right == NULL) ? 0 : p->Right->height;
    int hl = (p->Left == NULL) ? 0 : p->Left->height;
    return hr - hl;
}

void FixHeight(BookNode *p) {
    int hr = (p->Right == NULL) ? 0 : p->Right->height;
    int hl = (p->Left == NULL) ? 0 : p->Left->height;
    p->height = max(hr, hl) + 1;
}

BookNode *RotateLeft(BookNode *q) {
    BookNode *p = q->Right;
    q->Right = p->Left;
    p->Left = q;
    FixHeight(q);
    FixHeight(p);
    return p;
}

BookNode *RotateRight(BookNode *p) {
    BookNode *q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
}

BookNode *Balance(BookNode *p) {
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


void Remove(BookTree *T, char BookName[]) {}

BookNode *Find_R(BookTree *T, char BookName[], BookNode *Current = NULL) {
    if (T == NULL) return NULL;
    if (Current == NULL) Current = T->Root;
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


void MakeAction(BookNode *Node, void (*f)(BookNode *)) {
    if (Node != NULL)
        f(Node);
    if (Node->Left != NULL)
        MakeAction(Node->Left, f);
    if (Node->Right != NULL)
        MakeAction(Node->Right, f);
}

void Load(BookTree *T, char FileName[]) {
    if (T == NULL) return;
    FILE *fp;
    fp = fopen(FileName, "r");
    if (fp == NULL) {
        printf("\nCouldn't open the file: %s", FileName);
        return;
    }
    char Name[80];
    char Author[80];
    while (1) {
        //fscanf(fp, "%s%s", Name, Author);
        fgets(Name, 80, fp);
        fgets(Author, 80, fp);
        //if(strcmp(Name, "NULL")!=0 && strcmp(Author, "NULL")!=0)
        if (!StringStartsWith(Name, "NULL", 4) && !StringStartsWith(Author, "NULL", 4)) {
            BookNode *N = (BookNode *) malloc(sizeof(BookNode));
            InitNode(N);
            strcpy(N->author, Author);
            strcpy(N->name, Name);
            Add_R(T, N);
        } else
            break;
    }
    fclose(fp);
}

void Add(BookTree *T, BookNode *N) {
    if (T == NULL) return;
    if (T->Root == NULL) {
        T->Root = N;
        return;
    }
    BookNode *Current = T->Root;
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

void SaveNode(BookNode *Node, FILE *fp) {
    if (fp == NULL)
        return;
    if (Node != NULL) {
        //fprintf(fp, "%s%s", Node->name, Node->author);
        fputs(Node->name, fp);
        fputs("\n", fp);
        fputs(Node->author, fp);
        fputs("\n", fp);
        if (Node->Left != NULL)
            SaveNode(Node->Left, fp);
        if (Node->Right != NULL)
            SaveNode(Node->Right, fp);
    }
}

void Save(BookTree *T, char FileName[]) {
    if (T == NULL) return;
    FILE *ptr;
    ptr = fopen(FileName, "w");
    if (ptr == NULL) {
        printf("\nCouldn't open the file: %s", FileName);
        return;
    }

    SaveNode(T->Root, ptr);
    fputs("NULL\n", ptr);
    fputs("NULL", ptr);
    fclose(ptr);
}

void PreOrder(BookNode *Node, void (*f)(BookNode *)) {
    if (Node != NULL)
        f(Node);
    if (Node->Left != NULL)
        PreOrder(Node->Left, f);
    if (Node->Right != NULL)
        PreOrder(Node->Right, f);
}

void InOrder(BookNode *Node, void (*f)(BookNode *)) {
    if (Node->Left != NULL)
        InOrder(Node->Left, f);
    if (Node != NULL)
        f(Node);
    if (Node->Right != NULL)
        InOrder(Node->Right, f);
}

void PostOrder(BookNode *Node, void (*f)(BookNode *)) {
    if (Node->Left != NULL)
        PostOrder(Node->Left, f);
    if (Node->Right != NULL)
        PostOrder(Node->Right, f);
    if (Node != NULL)
        f(Node);
}

int main() {
    BookTree Tree;
    InitTree(&Tree);
    BookTree *ptr = &Tree;
    BookNode *London = (BookNode *) malloc(sizeof(BookNode));
    InitNode(London);
    strcpy(London->author, "J.London");
    strcpy(London->name, "Little Lady of the big house");
    BookNode *T = (BookNode *) malloc(sizeof(BookNode));
    InitNode(T);
    strcpy(T->author, "L.Tolstoy");
    strcpy(T->name, "War and Peace");
    BookNode *S = (BookNode *) malloc(sizeof(BookNode));
    InitNode(S);
    strcpy(S->author, "M.Sholohov");
    strcpy(S->name, "Calm Don");
    BookNode *Scott = (BookNode *) malloc(sizeof(BookNode));
    InitNode(Scott);
    strcpy(Scott->author, "W.Scott");
    strcpy(Scott->name, "Weverly");
    BookNode *Dryzer = (BookNode *) malloc(sizeof(BookNode));
    InitNode(Dryzer);
    strcpy(Dryzer->author, "Dryzer");
    strcpy(Dryzer->name, "American Tragedy");
    Add_R(ptr, Scott);
    Add_R(ptr, T);
    Add_R(ptr, London);
    Add_R(ptr, S);
    Add_R(ptr, Dryzer);

    printf("%d", bfactor(ptr->Root));
    printf("\n-----\nPreorder:");
    void (*f_ptr)(BookNode *);
    f_ptr = print;
    PreOrder(Tree.Root, f_ptr);
    printf("\n-----\nInorder:");
    InOrder(Tree.Root, f_ptr);
    printf("\n-----\nPostorder:");
    PostOrder(Tree.Root, f_ptr);

    return 0;
}

