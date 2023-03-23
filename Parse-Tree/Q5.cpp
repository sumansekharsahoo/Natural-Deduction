#include <iostream>
#include <string.h>
#define max 1000
using namespace std;
///@param top indicates the index of topmost element of the stack
///@param stck is used to inplement stack
///@warning every input needs to be enclosed inside round brackets and round brackets only
int top = -1;
int stck[max] = {0};
///@param i is used as a index to traverse converted prefix expression from the given infix expression from the  user
///@param a is used to store the converted prefix expression from the given infix expression from the  user
int i = 0;
char a[max] = {0};
struct node
{

    char op;

    struct node *l;

    struct node *r;
};

void reverse(char *p, int n);
void print(char *p, int n);
void infixToPostfix(char *p, char *q);
int prde(char opter);
void push(char ch);
void pop();
char topf();
bool empty();
void infixtoprefix(char infix[]);
struct node *tree(struct node *q);
bool evaluate(struct node *ptr);

/// push implements push fuction of stack stl
///@param ch is the character to be stored inside the stack
void push(char ch)
{
    stck[top + 1] = ch;
    top++;
}
/// pop removes the top element of stack
void pop()
{
    stck[top] = 0;
    top--;
}
///@returns the topmost element of stack
char topf()
{
    return (stck[top]);
}
///@returns if the stack is empty or not
bool empty()
{
    if (top == (-1))
        return true;
    else
        return false;
}
///@param opter is the variable in which current operator is stored
///@returns precedence of the operators that are passed
int prde(char opter)
{
    char ch = opter;
    int l;
    switch (ch)
    {
    case '(':
        l = 0;
        break;
    case '~':
        l = 4;
        break;
    case '*':
        l = 3;
        break;
    case '+':
        l = 2;
        break;
    case '>':
        l = 1;
        break;
    }
    return l;
}
/// infixToPostfix converts reversed infix expression to postfix expression
///@param p is the pointer pointing to reversed infix char array
///@param q is the pointer pointing to postfix char array
void infixToPostfix(char *p, char *q)
{
    int i = 0;
    int j = 0;
    char ch;
    while ((ch = *(p + (i++))) != '\0')
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
        {
            *(q + (j++)) = ch;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (topf() != '(')
            {
                *(q + (j++)) = topf();
                pop();
            }
            pop();
        }
        else
        {
            while ((!empty()) && (prde(ch) <= prde(topf())))
            {
                *(q + (j++)) = topf();
                pop();
            }
            push(ch);
        }
    }
    while (!empty())
    {
        *(q + (j++)) = topf();
        pop();
    }
}
/// reverse method reverses the input char array
///@param p is the pointer pointing to char array which needs to be reversed
///@param n is the number of characters that need to be reversed
void reverse(char *p, int n)
{
    char rev;
    for (int i = 0; i < n / 2; i++)
    {
        rev = *(p + i);
        *(p + i) = *(p + (n - 1 - i));
        *(p + (n - 1 - i)) = rev;
    }
    for (int i = 0; i < n; i++)
    {
        if (*(p + i) == '(')
        {
            *(p + i) = ')';
        }
        else if (*(p + i) == ')')
        {
            *(p + i) = '(';
        }
    }
}
/// copy method copies the input array to array a of characters which store the converted prefix expression
///@param p is the pointer pointing to char array which needs to be copied
///@param n is the number of characters that need to be copied
void copyarr(char *p, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        a[i] = p[i];
    }
}
/// infixToprefix converts given infix expression(from the user) to prefix expression
///@param infix is the pointer pointing to given infix char array
///@param n1 is the size of the given infix expression
///@param n2 is the size of the postfix expression
void infixtoprefix(char *infix)
{

    char postfix[max] = {0};

    int n1 = strlen(infix);
    reverse(infix, n1);
    infixToPostfix(infix, postfix);
    int n2 = strlen(postfix);
    reverse(postfix, n2);
    copyarr(postfix, n2);
}
/// recursive method that creates the binary parse tree
///@param q is a pointer pointing to the most recent node that was created
///@returns pointer pointing to the most recent node that was created
struct node *tree(struct node *q)
{
    char ch = (*(a + i++));
    if (ch == '\0')
    {
        return nullptr;
    }
    struct node *s = (struct node *)malloc(sizeof(struct node));
    if (isalnum(ch))
    {
        s->l = nullptr;
        s->r = nullptr;
        cout << "enter the truth value of" << endl
             << ch << endl;
        char newch;
        cin >> newch;
        s->op = newch;
        return s;
    }
    else if (ch == '~')
    {
        s->op = ch;
        s->r = tree(s);
        return s;
    }
    else
    {
        s->op = ch;
        s->l = tree(s);
        s->r = tree(s);
        return s;
    }
}
/// @brief evaluate is a recursive function to evaluate the converted prefix expression from the given infix expression
/// @param ptr is the pointer pointing to the most recent node that was evaluated
/// @return bool value of most recent node based on the operator it has and the recursive values it has got from other calls
bool evaluate(struct node *ptr)
{

    char ch = ptr->op;

    if (isalnum(ch))
    {
        if (ch == 'T')
        {

            return 1;
        }

        else if (ch == 'F')
        {

            return 0;
        }
    }

    else if (ch == '~')
    {
        bool p = evaluate(ptr->r);
        return (!p);
    }

    else
    {
        if (ch == '+')
        {
            bool v1 = evaluate(ptr->l);
            bool v2 = evaluate(ptr->r);
            return (v1 || v2);
        }

        else if (ch == '*')
        {
            bool v1 = evaluate(ptr->l);
            bool v2 = evaluate(ptr->r);
            return (v1 && v2);
        }

        else if (ch == '>')
        {
            bool v1 = evaluate(ptr->l);
            bool v2 = evaluate(ptr->r);
            return ((!v1) || v2);
        }
    }
}

int main()
{
    char infix[max] = {0};
    cout << "Enter the Infix Expression: ";
    cin >> infix;
    infixtoprefix(infix);
    struct node *start = nullptr;
    start = tree(nullptr);
    bool ans = evaluate(start);
    if (ans)
    {
        cout << "the truth value of the expression is T" << endl;
    }
    else
    {
        cout << "the truth value of the expression is F" << endl;
    }
    return 0;
}