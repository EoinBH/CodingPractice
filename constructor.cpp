#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Multiplier {
public:
    int a;
    int b;
    int c;
    Multiplier(int& num1, int& num2) {
        a = num1;
        b = num2;
        c = a*b;
    }
    
    int getAnswer() {
        return c;
    }
    
    friend ostream& operator<<(ostream& str, Multiplier &m);
    
};

ostream& operator<<(ostream& str, Multiplier &m) {
    str << m.c;
    return str;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int num1;
    int num2;
    std::cout << "Insert first number: " << std::endl;
    std::cin >> num1;
    std::cout << "Insert second number: " << std::endl;
    std::cin >> num2;
    Multiplier multiplier(num1, num2);
    //int answer = multiplier.getAnswer();
    std::cout << "Product of numbers: " << multiplier << std::endl;
    std::cout << "100";
    return 0;
}

/*
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Multiplier {
public:
    int a;
    int b;
    int c;
    Multiplier(int& num1, int& num2) {
        a = num1;
        b = num2;
        c = a*b;
    }
    
    int getAnswer() {
        return c;
    }
    
    friend ostream& operator<<(ostream& str, Multiplier &m);
    
};

ostream& operator<<(ostream& str, Multiplier &m) {
    str << m.c;
    return str;
}


int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT
    int num1;
    int num2;
    std::cout << "Insert first number: " << std::endl;
    std::cin >> num1;
    std::cout << "Insert second number: " << std::endl;
    std::cin >> num2;
    Multiplier multiplier(num1, num2);
    //int answer = multiplier.getAnswer();
    std::cout << "Product of numbers: " << multiplier << std::endl;
    std::cout << "100";
    return 0;
}
*/