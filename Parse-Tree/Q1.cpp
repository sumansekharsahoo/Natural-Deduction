/// Converting INFIX expression to PREFIX expression
///
/// Task 1

#include <iostream>
using namespace std;

#define MAX 1000

class Stack
{
    /// Stack Class implementation
    ///
    /// Since we cannot use Predefined Stack, we are implementing our own stack
    ///@param top indicates the index of topmost element of the stack
    int top;

public:
    ///@param MAX Maximum size of Stack
    char a[MAX];

    /// Constructor for initiating top = -1 whenever we create a Stack object
    Stack() { top = -1; }

    /// push function takes in a character and places it on top of the stack and returns true if operation was successful and false if Stack is getting Overflowed

    bool push(char x) // push() function defination
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

    /// pop function returns the character present at the top of the Stack or returns 0 if Stack is Empty
    char pop() // pop() function defination
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

    /// peek function returns the character present at top of the Stack and returns 0 if Stack is empty
    char peek() // peek() function defination
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

    /// isEmpty function returns true if the  Stack is Empty and false if the Stack is not Empty*/
    bool isEmpty() // isEmpty() function defination
    {
        return (top < 0);
    }
};

/// rev fuction reverses string. It also takes care of inverting the parantheses brackets '(' -> ')' and ')' -> '('.  Eg: (a+b*c)>d   ->  d>(c*b+a)
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

/// @brief Precedence order: '~' > '*' > '+' > '>'
/// @param c takes in the operator
/// @return it returns the operator preference
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

int main()
{
    cout << "Enter the Infix expression: ";
    string input;
    cin >> input;
    string out = inf_to_pref(input);
    cout << "The Prefix Expression is: ";
    cout << out << endl;
    return 0;
}