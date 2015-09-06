#include <iostream>
#include <vector>
using namespace std;

/*
 * class ModInt
 * Extention of integers to support division and modulo operations for negative integers
 */
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

/*
 * class BaseInt
 * Convert from decimal to other base and vice versa. Works for negative base.
 */
class BaseInt {
    public:
        BaseInt(int b) : base(b) {};
        int to10(vector<int> &numB);
        int from10(vector<int> &numB, int num10);
    protected:
        int base;
};

// standard assignment oprator
ModInt ModInt::operator=(const ModInt& other)
{
    num = other.num;
    return *this;
}

// support for integer +
ModInt ModInt::operator+(const ModInt& other)
{
    return ModInt(num + other.num);
}

// support for integer - (binary)
ModInt ModInt::operator-(const ModInt& other)
{
    return ModInt(num - other.num);
}

// support for integer *
ModInt ModInt::operator*(const ModInt& other)
{
    return ModInt(num * other.num);
}

// support for integer modulo operator, works for negative
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

// support for integer division operator, works for negative
ModInt ModInt::operator/(const ModInt& other)
{
    ModInt mod = *this % other;
    int n = num - mod.num;
    return ModInt(n / other.num);
}

// support for integer /= operator, works for negative
ModInt ModInt::operator/=(const ModInt& other)
{
    *this = *this / other;
    return *this;
}

// stream output for ModInt objects
ostream& operator<<(ostream& os, const ModInt& out)
{
    os << out.num;
    return os;
}

// convert to decimal, works for both positive and negative radix
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

// convert from decimal, works for both positive and negative radix
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

// demo for ModInt class and its differences from standard integers
int demoModInt(int a, int b) {
    cout << "Demo for pair (" << a << "," << b << "):" << endl;
    int c = a / b;
    int d = a % b;

    ModInt ma(a);
    ModInt mb(b);
    ModInt mc = ma / mb;
    ModInt md = ma % mb;

    cout << "Standard integer division: " << a << " / " << b << " = " << c << endl;
    cout << "Fixed integer division: " << ma << " / " << mb << " = " << mc << endl;
    cout << "Standard integer modulo: " << a << " % " << b << " = " << d << endl;
    cout << "Fixed integer modulo: " << ma << " mod " << mb << " = " << md << endl << endl;
}

int main() {

    demoModInt(17, 5);
    demoModInt(17, -5);
    demoModInt(-17, 5);
    demoModInt(-17, -5);
    
    return 0;
}
