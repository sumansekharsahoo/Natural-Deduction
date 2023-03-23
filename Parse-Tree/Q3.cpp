#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} node;

/// @brief converts parse tree to infix expression
/// @param p takes in node pointer as parameter
void ptree_to_inf(node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        if (p->left != NULL || p->right != NULL)
        {
            printf("(");
        }
        ptree_to_inf(p->left);
        printf("%c ", p->data);
        ptree_to_inf(p->right);
        if (p->left != NULL || p->right != NULL)
        {
            printf(")");
        }
    }
}

char *add(node **p, char *a)
{

    if (*a == '\0')
        return NULL;

    while (1)
    {
        char *q = NULL;
        if (*p == NULL)
        {

            node *nn = (node *)malloc(sizeof(node));
            nn->data = *a;
            nn->left = NULL;
            nn->right = NULL;
            *p = nn;
        }
        else
        {

            if (*a >= 'a' && *a <= 'z')
            {
                return a;
            }

            if (*a == '~')
            {
                (*p)->left = NULL;
                q = add(&(*p)->right, a + 1);
            }
            else
            {
                q = add(&(*p)->left, a + 1);

                q = add(&(*p)->right, q + 1);
            }
            return q;
        }
    }
}

node *pref_to_ptree(char *pref)
{
    node *s = NULL;
    add(&s, pref);
    return s;
}

int main()
{
    string str;
    cout << "Enter the prefix expression: " << endl;
    cin >> str;
    cout << "We will make a parse tree out of the prefix expression and return the infix expression by in-order traversal of the parse tree " << endl;
    cout << "The infix expression is: " << endl;
    int len = str.size();
    const char *tmp = str.c_str();
    char inp_str[len];
    strcpy(inp_str, tmp);
    node *output = pref_to_ptree(inp_str);
    ptree_to_inf(output);
}