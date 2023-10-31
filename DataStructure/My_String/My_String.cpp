#include <iostream>
using namespace std;

class My_String{
private:
    int len;
    char ch[];

public:
    My_String():
        len(0) {ch[0] = '\0';}

    My_String(char _ch[]){
        copy(_ch);
    }

    void copy(char[]);    
    bool empty();
    char get_ch(int);
    int get_len();
    int compare(My_String&);
    My_String sub_str(int, int);
    My_String concat(My_String&);
    int index(My_String&);
    int index_with_KMP(My_String& sub);
    int index_with_better_KMP(My_String& sub);
    void clear();
    void display();
} ;

void My_String_test(){
    char ch[] = "ababacb";
    My_String rm(ch);
    char ch1[] = "abababaababacb";
    My_String th(ch1);
    cout << th.index_with_better_KMP(rm) << endl;
}

int main(){
    My_String_test();
}

void My_String::copy(char _ch[]){
    for (len = 0; _ch[len]; len++)
        ch[len+1] = _ch[len];
}

bool My_String::empty(){
    return !len;
}

char My_String::get_ch(int idx){
    if (1 <= idx && idx <= len)
        return ch[idx];
    else {
        printf("Invalid index!\n");
        return 0;
    }
}

int My_String::get_len(){
    return len;
}

int My_String::compare(My_String& cmp){
    int pub_len = min(len, cmp.get_len());
    for (int i = 1; i <= pub_len; i++){
        if (get_ch(i) != cmp.get_ch(i))
            return int(get_ch(i)) - int(cmp.get_ch(i));
    }
    return len - cmp.get_len();
}

My_String My_String::sub_str(int pos, int length){
    char _ch[] = "";
    if (pos + length - 1 >= len){
        cout << "No such a substring!" << endl;
        return My_String();
    }
    for (int i = 0; i < length; i++)
        _ch[i] = get_ch(pos+i);
    _ch[length] = 0;
    return My_String(_ch);
}

My_String My_String::concat(My_String& other){
    int i;
    for (i = 1; i <= other.get_len(); i++){
        ch[i+len] = other.get_ch(i);
    }
    len += i;
}

int My_String::index(My_String& sub){
    for (int i = 1; i + sub.get_len() - 1 <= len; i++){
        bool flag = 0;
        for (int j = 1; j <= sub.get_len(); j++)
            if (get_ch(i+j-1) != sub.get_ch(j)){
                flag = 1; break;
            }
        if (!flag) 
            return i;
    }
    return -1;
}

int My_String::index_with_KMP(My_String& sub){
    int *kmp, ans = -1;
    kmp = new int(sub.get_len());
    kmp[0] = 0, kmp[1] = 0;
    for (int i = 2; i <= sub.get_len(); i++){
        int j = kmp[i-1];
        while (j > 0 && sub.get_ch(i) != sub.get_ch(j+1)) j = kmp[j];
        if (sub.get_ch(i) == sub.get_ch(j+1)) j++;
        kmp[i] = j;
    }
    for (int i = 1, j = 0; i <= len; i++){
        while (j > 0 && get_ch(i) != sub.get_ch(j+1))
            j = kmp[j];
        if (get_ch(i) == sub.get_ch(j+1))
            j++;
        if (j == sub.get_len())
            ans = i-j+1;
    }
    return ans;
}

int My_String::index_with_better_KMP(My_String& sub){
    int *next, *nextval, ans = -1;
    next = new int(sub.get_len());
    nextval = new int(sub.get_len());
    next[1] = 0; nextval[1] = 0;
    for (int i = 1, j = 0; i <= sub.get_len();){
        if (!j || sub.get_ch(i) == sub.get_ch(j)){
            i++, j++;
            next[i] = j;
        } else
            j = next[j];
    }
    for (int i = 1; i <= sub.get_len(); i++){
        nextval[i] = next[i];
        if (nextval[i] && sub.get_ch(i) == sub.get_ch(nextval[i]))
            nextval[i] = nextval[nextval[i]];
    }
    for (int i = 1, j = 1; i <= get_len() && j <= sub.get_len();){
        if (!j || get_ch(i) == sub.get_ch(j))
            i++, j++;
        else 
            j = nextval[j];
        if (j > sub.get_len())
            ans = i - j + 1;
    }
    return ans;
}

void My_String::clear(){
    for (int i = 0; i <= len; i++)
        ch[i] = '\0';
    len = 0;
}

void My_String::display(){
    for (int i = 1; i <= len; i++)   
        cout << ch[i];
    cout << endl;
}