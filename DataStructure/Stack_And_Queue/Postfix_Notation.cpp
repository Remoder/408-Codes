#include "Stack.cpp"
#include <iostream>
#include <cstring>
using namespace std;

class Expression{
protected: 
    string str;
public:
    Expression(string _str=""):
        str(_str) {}

    friend istream& operator >> (istream&, Expression&);
    void display();
} ;

class Postfix_Notation: public Expression{
public:
    Postfix_Notation(string _str=""):
        Expression(_str) {}
    int calc();
} ;

class Infix_Notation: public Expression{
public:
    Infix_Notation(string _str=""):
        Expression(_str) {}
    Postfix_Notation trans_to_postfix_notation();
    int calc();
} ;

int trans_to_number(string);
bool is_digit(char);
bool higher_level_sgn(char, char);

int main(){
    
    return 0;
}

int trans_to_number(string str){
    int res = 0, len = str.size();
    for (int i = 0; i < len; i++)
        res = res * 10 + str[i] - '0';
    return res;
}

bool is_digit(char ch){
    return '0' <= ch && ch <= '9';
}

bool higher_level_sgn(char a, char b){
    return (a == '*' || a == '/') || 
           ((a == '+' || a == '-') && (b != '*' && b != '/')) ||
           ((a == '(') && (b == '(' || b == ')')) || (b == ')');
}

istream& operator >> (istream& input, Expression& ans){
    input >> ans.str;
    return input;
}

void Expression::display(){
    int len = str.size();
    for (int i = str[0] == '0' ? 1 : 0; i < len; i++)
        cout << str[i];
    cout << endl;
} 

Postfix_Notation Infix_Notation::trans_to_postfix_notation(){
    Stack sgn; 
    string ans = "", tmp = "";
    if (!is_digit(str[0]))
        ans += "0 ";
    int len = str.size();
    for (int i = 0; i < len; i++){
        if (is_digit(str[i])){
            tmp += str[i];
        } else {
            if (tmp[0]){
                tmp += " ";
                ans += tmp;
            }
            if (str[i] == '(' || sgn.empty() || higher_level_sgn(str[i], char(sgn.top()))){
                sgn.push(int(str[i]));
            } else {
                if (str[i] != ')'){
                    ans += str[i], ans += ' ';
                }
                while (!sgn.empty() && higher_level_sgn(char(sgn.top()), str[i])){
                    if (char(sgn.top()) != '(')
                        ans += char(sgn.top()), ans += ' ';
                    sgn.pop();
                }
            }
            tmp = "";
        }
    }
    if (tmp[0]){
        tmp += " ";
        ans += tmp;
    }
    while (!sgn.empty()){
        ans += char(sgn.top()), ans += ' ';
        sgn.pop();
    }
    return Postfix_Notation(ans);
} 
