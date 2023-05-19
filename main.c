#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* word;
    struct Node* left;
    struct Node* right;
} Node;
Node *tree=NULL;
Node* newNode(char *c)
{
    Node* n=malloc(sizeof(Node));
    n->word=malloc(strlen(c)+1);
    strcpy(n->word,c);
    n->left=n->right=NULL;
}
Node* insert(Node* n,char* c)
{
    if(n==NULL)
        return newNode(c);
    if(strcasecmp(n->word,c)<0)
        n->left= insert(n->left,c);
    else
        n->right= insert(n->right,c);
    return n;
}
int count(Node* n)
{
    if(!n)
        return 0;
    else
        return 1+count(n->left)+count(n->right);
}
int max(int x, int y)
{
    return x>y? x:y;
}
int height(Node *n)
{
    if(!n)
        return -1;
    else
        return 1+max(height(n->left),height(n->right));
}
void readFile()
{
    char string[50];
    FILE *f1=fopen("EN-US-Dictionary.txt","r");
    while(!feof(f1))
    {
        fscanf(f1,"%s\n",string);
        tree=insert(tree,string);
    }
    fclose(f1);
    printf("\tDictionary loaded successfully!\n");
    printf("\t...............................\n");
}
int found(Node* n,char *c)
{
    if(n==NULL)
        return 0;
    if(strcasecmp(n->word,c)==0)
        return 1;
    else if(strcasecmp(n->word,c)<0)
        return found(n->left,c);
    else
        return found(n->right,c);
}
Node* Findleaf(Node *n,char *c)
{
    if(n==NULL)
        return NULL;
    else if(strcasecmp(n->word,c)<0){
        Node *temp=Findleaf(n->left,c);
        if(temp==NULL)
        {
            return n;
        }
    }
    else{
        Node *temp=Findleaf(n->right,c);
        if(temp==NULL)
        {
            return n;
        }
    }
}
void findSuccessor(Node* root, Node**succ, char*word)
{
    if (root == NULL)
        *succ = NULL;
    if (strcasecmp(word, root->word ) < 0 )
    {
        *succ = root;
        findSuccessor(root->left,succ, word);
    }
    else if (strcasecmp(word, root->word ) > 0 )
        findSuccessor(root->right,succ, word);
}
void findPredecessor(Node* root, Node**pred, char*word)
{
   if (root == NULL)
        *pred = NULL;
    if (strcasecmp(word, root->word ) < 0 )
    {
        findPredecessor(root->left,pred, word);
    }
    else if (strcasecmp(word, root->word ) > 0 )
    {
        *pred = root;
        findPredecessor(root->right,pred, word);
    }

}
void checker(char *line)
{
    char* token=strtok(line," ");
    while(token){
        int x= found(tree,token);
        Node *temp = Findleaf(tree,token);
        if(x==1)
            printf("%s - CORRECT\n",token);
        else{
            Findleaf(tree,token);

            Node* temp=Findleaf(tree,token);

            printf("%s - Incorrect, Suggestions: %s \n",token,temp->word);
        }
        token=strtok(NULL," ");
    }

}
int main()
{
    readFile();
    printf("Size: %d\n",count(tree));
    printf("..................................................\n");
    printf("height: %d\n",height(tree));
    printf("..................................................\n");
    printf("Enter a sentence: \n");
    char x[500];
    gets(x);
    checker(x);
    return 0;
}
