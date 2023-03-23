#include <bits/stdc++.h>
using namespace std;

/// @brief This function checks for the rule and formulates the statement and then checks if its equal to the statement
/// @param s an array that stores the statements
/// @param r an array that stores the rules
/// @param t denotes the number of lines
/// @return If the sequent is valid then returns a variable val which is a positive number and returns 0 if the sequent is invalid
int checkRule(string s[], string r[], int t)
{

    int l1, l2;
    string str;
    int val = 0;

    /// checking for the rule used using if-else if statements
    for (int i = 0; i < t; i++)
    {
        /// checking if the rule is premise and incrementing val
        if (r[i] == "P")
        {
            val++;
            continue;
        }

        /// checking if the rule is ^i (and introduction)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 2) == "^i")
        {
            l1 = stoi(r[i].substr(3, 1));
            l2 = stoi(r[i].substr(5, 1));
            str = "(" + s[l1 - 1] + "^" + s[l2 - 1] + ")";
            if (str == s[i])
            {

                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is ->e (implies elimination)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 3) == "->e")
        {
            l1 = stoi(r[i].substr(4, 1));
            l2 = stoi(r[i].substr(6, 1));
            int pos = s[l1 - 1].find("-");
            str = s[l1 - 1].substr(pos + 2);
            str = str.substr(0, str.size() - 1);
            if (str == s[i])
            {
                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is ^e1 (and elimination 1)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 3) == "^e1")
        {
            l1 = stoi(r[i].substr(4, 1));
            int pos = s[l1 - 1].find("^");
            str = s[l1 - 1].substr(0, pos);
            if (str == ("(" + s[i]))
            {
                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is ^e2 (and elimination 2)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 3) == "^e2")
        {
            l1 = stoi(r[i].substr(4, 1));
            int pos = s[l1 - 1].find("^");
            str = s[l1 - 1].substr(pos + 1);
            if (str == (s[i] + ")"))
            {
                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is Vi1 (or introduction 1)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 3) == "Vi1")
        {
            l1 = stoi(r[i].substr(4, 1));
            int pos = s[i].find("V");
            str = s[i].substr(0, pos);
            if (str == ("(" + s[l1 - 1]))
            {
                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is Vi2 (or introduction 2)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 3) == "Vi2")
        {
            l1 = stoi(r[i].substr(4, 1));
            int pos = s[l1].find("V");
            str = s[l1].substr(pos + 1);
            if (str == (s[l1 - 1] + ")"))
            {
                val++;
            }
            else
            {
                return 0;
            }
        }

        // checking if the rule is MT (Modus Tollens)
        /// If by using the rule we makeup the corresponding statement that is given before the rule then we increment val; else we return 0 and exit from the function
        else if (r[i].substr(0, 2) == "MT")
        {
            l1 = stoi(r[i].substr(3, 1));
            l2 = stoi(r[i].substr(5, 1));
            int pos = s[l1 - 1].find(">");
            str = "~" + s[l1 - 1].substr(pos + 1);
            if (str == s[l2 - 1])
            {
                string str1, str2;
                int pos = s[l1 - 1].find("-");
                str1 = "~" + s[l1 - 1].substr(0, pos);
                pos = s[i].find("/");
                str2 = s[i].substr(0, pos);
                if (str1 == str2)
                {
                    val++;
                }
                else
                {
                    return 0;
                }
            }
        }

        /// Valid prof rules are {^i, ^e1, ^e2, Vi1, Vi2, ->e, MT} along with the number of components after slashes
        /// If the proof rule doesn't match any of the valid rules mentioned above then we print Invalid Rule Entered and Exit the function
        else
        {
            // cout << "Invalid Proof Rule Entered" << endl;
            return 0;
        }
    }

    return val;
}

/// @brief Main Function
int main()
{
    /// Variable t denotes the number of input lines
    int t;
    cin >> t;
    cin.ignore();
    /// declaring arrays arr[t], state[t], rule[t] each having t no of items
    /// arr[t] - an array that stores the input lines
    /// state[t] - an array that stores the statements
    /// rule[t] - an array that stores the proof rules by parsing each input lines that is stored in arr[t]

    string arr[t], state[t], rule[t];
    /// taking each line input into arr[] array
    for (int i = 0; i < t; i++)
    {
        getline(cin, arr[i]);
    }
    string s;
    int pos;
    /// creating statements' and rules' arrays
    for (int i = 0; i < t; i++)
    {
        s = arr[i];
        pos = s.find("/");
        state[i] = s.substr(0, pos);
        rule[i] = s.substr(pos + 1);
    }

    /// passing statements, rules and no of input lines into checkRule function
    int val = checkRule(state, rule, t);

    /// Checking the value of val
    /// If val>0 - printing "Valid Proof"
    /// else - printing "Invalid Proof"
    if (val > 0)
    {
        cout << "Valid Proof";
    }
    else
    {
        cout << "Invalid Proof";
    }
    return 0;
}
