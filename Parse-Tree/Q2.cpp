#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} node;

/// @brief Builds the parse tree
/// @param p it is the pointer variable to the node pointer
/// @param a it takes in the character to be added into data
/// @return~
char *add(node **p, char *a) //
{

    if (*a == '\0') // executed while reaching end of string
        return NULL;

    while (1)
    {
        char *q = NULL; // used later
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

/// @brief Convertion of prefix expression to parse tree
/// @param pref
/// @return It returns a node pointer
node *pref_to_ptree(char *pref)
{
    node *s = NULL;
    add(&s, pref);
    return s;
}

int main()
{
    string str;
    cout << "Enter prefix expression: " << endl;
    cin >> str;
    int len = str.size();
    const char *tmp = str.c_str();
    char inp_str[len];
    strcpy(inp_str, tmp);
    node *output = pref_to_ptree(inp_str);
    cout << "The pointer to root node of parsse tree is: " << endl;
    cout << output << endl;
}