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

void postfix_notation_test(){
    Infix_Notation str;
    while (cin >> str){
        cout << "The infix notation is ";
        str.display();
        cout << "The result is ";
        cout << str.calc() << endl;
        Postfix_Notation x = str.trans_to_postfix_notation();
        cout << "The postfix notation is ";
        x.display();
        cout << "The result is ";
        cout << x.calc() << endl;
    }
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
    return (a == '*' || a == '/') || (b != '*' && b != '/');
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

int Postfix_Notation::calc(){
    Stack num;
    string tmp = "";
    int len = str.size();
    for (int i = 0; i < len; i++){
        if (str[i] != ' ')
            tmp += str[i];
        else {
            if (is_digit(tmp[0]))
                num.push(trans_to_number(tmp));
            else {
                int res = 0;
                int b = num.top(); num.pop();
                int a = num.top(); num.pop();
                switch (tmp[0]){
                    case '+':
                        res = a + b;
                        num.push(res);
                        break;
                    case '-':
                        res = a - b;
                        num.push(res);
                        break;
                    case '*':
                        res = a * b;
                        num.push(res);
                        break;
                    case '/':
                        if (b == 0){
                            printf("Cannot divided by 0.\n");
                            break;
                        }
                        res = a / b;
                        num.push(res);
                        break;
                }
            }
            tmp = "";
        }
    }
    if (num.get_len() == 1)
        return num.top();
    return -1;
}

Postfix_Notation Infix_Notation::trans_to_postfix_notation(){
    Stack sgn;
    string ans = "", tmp = "";
    if (str[0] == '-')
        ans += "0 ";
    int len = str.size();
    for (int i = 0; i < len; i++){
        if (is_digit(str[i])){
            tmp += str[i];
        } else {
            if (is_digit(tmp[0])){
                ans += tmp + ' ';
            }
            if (str[i] == '(')
                sgn.push(int(str[i]));
            else if (str[i] == ')'){
                while (!sgn.empty()){
                    if (char(sgn.top() == '('))
                        sgn.pop();
                    else{
                        ans += char(sgn.top()), ans += ' ';
                        sgn.pop();
                    }
                }
            } else {
                while (!sgn.empty() && higher_level_sgn(char(sgn.top()), str[i])){
                    if (char(sgn.top()) != '('){
                        ans += char(sgn.top()), ans += ' ';
                        sgn.pop();
                    } else {
                        sgn.pop();
                        break;
                    }
                } 
                sgn.push(int(str[i]));
            }
            tmp = "";
        }
    }
    if (tmp[0])
        tmp += " ", ans += tmp;
    while (!sgn.empty()){
        ans += char(sgn.top()), ans += ' ';
        sgn.pop();
    }
    return Postfix_Notation(ans);
} 

int Infix_Notation::calc(){
    return trans_to_postfix_notation().calc();
}