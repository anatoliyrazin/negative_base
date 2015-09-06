#include <iostream>
#include <vector>
using namespace std;

// replacement for integer modulo operator, works for negative
int mod(int m, int n)
{
    if(n < 0) {
        n = -n;
    }
    m %= n;
    while(m < 0) {
        m += n;
    }

    return m;
}

// replacement for integer division operator, works for negatives
int div(int m, int n)
{
    int r = mod(m, n);
    m -= r;

    return m / n;
}

// convert to decimal, works for both positive and negative radix
int to10(int base, vector<int> &a) {
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
int from10(int base, vector<int> &a, int n) {
    while(n) {
        int d = mod(n, base);
        n = div(n, base);
        vector<int>::iterator it = a.begin();
        a.insert(it, (int)d);
    }
}

// demo for ModInt class and its differences from standard integers
int demoMod(int a, int b) {
    cout << "Demo for pair (" << a << "," << b << "):" << endl;
    int c = a / b;
    int d = a % b;

    int mc = div(a, b);
    int md = mod(a, b);

    cout << "Standard integer division: " << a << " / " << b << " = " << c << endl;
    cout << "Fixed integer division: " << a << " / " << b << " = " << mc << endl;
    cout << "Standard integer modulo: " << a << " % " << b << " = " << d << endl;
    cout << "Fixed integer modulo: " << a << " mod " << b << " = " << md << endl << endl;
}

// BaseInt demo: convert decimal value to base n
int demoBase(int a, int n) {
    cout << "Decimal " << a << " in base " << n << " is ";

    vector<int> v;

    from10(n, v, a);

    vector<int>::iterator i;
    for(i = v.begin(); i != v.end(); i++)
    {
        cout << *i;
    }
    cout << endl << endl;
}

// BaseInt demo: convert base n value to decimal, n must be between -10 and 10
int demoBase(const char s[], int n) {
    vector<int> v;
    const char *p = s;
    while(*p) {
        int d = *p - '0';
        v.push_back(d);
        p++;
    }

    cout << "Convert " << s << " in base " << n << " to decimal: " << to10(n, v) << endl << endl;
}

int main() {

    // some demos for ModInt
    demoMod(17, 5);
    demoMod(17, -5);
    demoMod(-17, 5);
    demoMod(-17, -5);

    // some demos for BaseInt
    demoBase(1000, 3);
    demoBase(1000, -3);
    // demoBase(-1000, 3); /* this should fail */
    demoBase(-1000, -3);

    demoBase("1101001", 3);
    demoBase("2212001", -3);
    demoBase("12101012", -3);

    return 0;
}
