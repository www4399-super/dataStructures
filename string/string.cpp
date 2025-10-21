#include <iostream>
#include <vector>
using namespace std;
class MyString
{
private:
    char *data;
    int length;

public:
    size_t my_strlen(const char *str) const
    {
        size_t len = 0;
        while (str[len] != '\0')
        {
            len++;
        }
        return len;
    }

    void my_strcpy(char *dest, const char *src) const
    {
        size_t i = 0;
        while ((dest[i] = src[i]) != '\0')
        {
            i++;
        }
    }

    MyString()
    {
        data = new char[1]{'\0'};
        length = 0;
    }

    MyString(const char *str)
    {
        length = my_strlen(str);
        data = new char[length + 1];
        my_strcpy(data, str);
    }
    MyString(const MyString &s)
    {
        length = s.length;
        data=new char[length+1];
         my_strcpy(data,s.data);
    }
    ~MyString()
    {
        delete[] data;
    }

    MyString& operator=(const MyString&s){//解决浅拷贝的问题
        if(this == &s){
            return *this;
        }
        delete[] data;
        length = s.length;
        data = new char[length+1];
        my_strcpy(data,s.data);
        return *this;
    }

    char operator[](int index) const{
        return data[index];
    }

    vector<int> getNext(const MyString &pattern)
    {
        if (pattern.length < 2)
        {
            return {0};
        }
        vector<int> next(pattern.length);
        next[0] = 0;
        next[1] = 0;
        int comp = 0;
        int cur = 2;
        while (cur < pattern.length)
        {
            if (pattern[cur - 1] == pattern[comp])
            {
                next[cur] = comp + 1;
                cur++;
                comp++;
            }
            else
            {
                if (comp > 0)
                {
                    comp = next[comp];
                }
                else
                {
                    next[cur++] = 0;
                }
            }
        }
        return next;
    }

    int kmp(const MyString& str,const MyString& pattern)
    { // kmp算法返回匹配到的第一个字符串下标
        vector<int> next = getNext(pattern);
        int scur = 0;
        int pcur = 0;
        while (scur < str.length && pcur < pattern.length)
        {
            if (str[scur] == pattern[pcur])
            {
                scur++;
                pcur++;
            }
            else
            {
                if (pcur > 0)
                {
                    pcur = next[pcur];
                }
                else
                {
                    scur++;
                }
            }
        }
        return pcur == pattern.length ? scur - pattern.length : -1;
    }

    friend ostream &operator<<(ostream &cout, const MyString &s);
};
ostream &operator<<(ostream &cout, const MyString &s)
{
    for (size_t i = 0; i < s.length; i++)
    {
        cout << s.data[i];
    }
    return cout;
}

int main()
{
    MyString str("abcdabc");
    MyString pattern("bc");
    int a = str.kmp(str,pattern);
    cout << a;
    
}