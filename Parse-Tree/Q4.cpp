#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} node;

#define MAX 1000

class Stack
{
    int top;

public:
    char a[MAX];

    Stack() { top = -1; }
    bool push(char x);
    char pop();
    char peek();
    bool isEmpty();
};

bool Stack::push(char x)
{
    if (top >= (MAX - 1))
    {
        cout << "Stack Overflow";
        return false;
    }
    else
    {
        a[++top] = x;
        return true;
    }
}

char Stack::pop()
{
    if (top < 0)
    {
        cout << "Stack Underflow";
        return 0;
    }
    else
    {
        char x = a[top--];
        return x;
    }
}
char Stack::peek()
{
    if (top < 0)
    {
        cout << "Stack is Empty";
        return 0;
    }
    else
    {
        char x = a[top];
        return x;
    }
}

bool Stack::isEmpty()
{
    return (top < 0);
}

string rev(string str)
{
    string rstr;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        rstr.push_back(str[i]);
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (rstr[i] == '(')
        {
            rstr[i] = ')';
        }
        else if (rstr[i] == ')')
        {
            rstr[i] = '(';
        }
    }
    return rstr;
}

int precedence(char c)
{
    if (c == '~')
    {
        return 3;
    }
    else if (c == '*')
    {
        return 2;
    }
    else if (c == '+')
    {
        return 1;
    }
    else if (c == '>')
    {
        return 0;
    }
    return -1;
}

bool isOperand(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
        return true;
    }
    return false;
}

string inf_to_post(string s)
{
    class Stack st;
    string postFix;

    for (int i = 0; i < s.length(); i++)
    {
        if (isOperand(s[i]))
        {
            postFix += s[i];
        }
        else if (s[i] == '(')
        {
            st.push('(');
        }
        else if (s[i] == ')')
        {
            while (st.peek() != '(')
            {
                postFix += st.peek();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.isEmpty() && precedence(s[i]) <= precedence(st.peek()))
            {
                postFix += st.peek();
                st.pop();
            }
            st.push(s[i]);
        }
    }

    while (!st.isEmpty())
    {
        postFix += st.peek();
        st.pop();
    }

    return postFix;
}

string inf_to_pref(string inp)
{
    string revinp = rev(inp);
    string postf = inf_to_post(revinp);
    string pref = rev(postf);
    return pref;
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

/// @brief calculates the height of the parse tree
/// @param root takes  in the root node as parameter
/// @return int value of the height
int height(node *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(height(root->left), height(root->right));
}

int main()
{
    string inp;
    cout << "Input infix expression of the parse tree whose height is to be computed: " << endl;
    cin >> inp;
    string str = inf_to_pref(inp);
    int len = str.size();
    const char *tmp = str.c_str();
    char inp_str[len];
    strcpy(inp_str, tmp);
    node *output = pref_to_ptree(inp_str);
    int ht = height(output);
    cout << "The height of tree is : " << endl;
    cout << ht;
}