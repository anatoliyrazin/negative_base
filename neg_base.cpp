#include <iostream>
#include <vector>
using namespace std;

class ModInt {
    public:
        ModInt(int n) : num(n) {};
        operator int() const { return num; }
        ModInt operator=(const ModInt& other);
        ModInt operator+(const ModInt& other);
        ModInt operator-(const ModInt& other);
        ModInt operator*(const ModInt& other);
        ModInt operator%(const ModInt& other);
        ModInt operator/(const ModInt& other);
        ModInt operator/=(const ModInt& other);
        friend ostream& operator<<(ostream& os, const ModInt& out);
    protected:
            int num;
};

class BaseInt {
    public:
        BaseInt(int b) : base(b) {};
        int to10(vector<int> &numB);
        int from10(vector<int> &numB, int num10);
    protected:
        int base;
};

ModInt ModInt::operator=(const ModInt& other)
{
    num = other.num;
    return *this;
}

ModInt ModInt::operator+(const ModInt& other)
{
    return ModInt(num + other.num);
}

ModInt ModInt::operator-(const ModInt& other)
{
    return ModInt(num - other.num);
}

ModInt ModInt::operator*(const ModInt& other)
{
    return ModInt(num * other.num);
}

ModInt ModInt::operator%(const ModInt& other)
{
    int n = num;
    int m = other.num;
    if(m < 0) {
        m = -m;
    }
    n %= m;
    while(n < 0) {
        n += m;
    }
    return ModInt(n);
}

ModInt ModInt::operator/(const ModInt& other)
{
    ModInt mod = *this % other;
    int n = num - mod.num;
    return ModInt(n / other.num);
}

ModInt ModInt::operator/=(const ModInt& other)
{
    *this = *this / other;
    return *this;
}

ostream& operator<<(ostream& os, const ModInt& out)
{
    os << out.num;
    return os;
}

int BaseInt::to10(vector<int> &a) {
    int n = 0;
    vector<int>::iterator i;
    for(i = a.begin(); i != a.end(); i++)
    {
        int d = *i;
        n *= base;
        n += d;
    }

    return n;
}

int BaseInt::from10(vector<int> &a, int n) {
    ModInt m(n);
    ModInt b(base);
    while(m) {
        ModInt d = m % b;
        m /= b;
        vector<int>::iterator it = a.begin();
        a.insert(it, (int)d);
    }
}
