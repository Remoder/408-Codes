#include "Stack.cpp"
#include <iostream>
using namespace std;

class Backets_Sequence{
private: 
    string str;
public:
    Backets_Sequence(string _str=""):
        str(_str) {}

    friend istream& operator >> (istream&, Backets_Sequence&);
    bool is_front_bracket(char);
    bool is_back_bracket(char);
    bool is_in_pair(char, char);
    bool is_valid();
} ;

int main(){
    Backets_Sequence str;
    while (cin >> str){
        if (str.is_valid())
            cout << "Yes" << endl;
        else 
            cout << "No" << endl;
    }
    return 0;
}

istream& operator >> (istream& input, Backets_Sequence& ans){
    input >> ans.str;
    return input;
}

bool Backets_Sequence::is_front_bracket(char ch){
    return ch == '(' || ch == '[' || ch == '{';
}

bool Backets_Sequence::is_back_bracket(char ch){
    return ch == ')' || ch == ']' || ch == '}';
}

bool Backets_Sequence::is_in_pair(char a, char b){
    return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
}

bool Backets_Sequence::is_valid(){
    Stack s;
    int len = str.size();
    for (int i = 0; i < len; i++){
        if (!is_front_bracket(str[i]) && !is_back_bracket(str[i]))
            return false;
        if (is_front_bracket(str[i]))
            s.push(int(str[i]));
        if (is_back_bracket(str[i])){
            if (s.empty() || !is_in_pair(char(s.top()), str[i])) 
                return false;
            s.pop();
        }
    }
    return s.empty();
}
