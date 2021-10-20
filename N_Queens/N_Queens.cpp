// FILE:            main.cpp
// Written by:      Lucien Maurice
// Email:           luciencmaurice@gmail.com
// 

#include <iostream>
#include "stack3.h"

using namespace std;
using namespace main_savitch_7A;

bool check(const stack<int> &s) {
    int row = static_cast<int>(s.size());
    int column = s.top();
    for (int i = 2; i <= row; i++) {
        if ((s.peek(i) == column) || (s.peek(i) == column + i - 1) || (s.peek(i) == column - i + 1))
            return false;
    }
    return true;
}

void printStack(stack<int> s) {
    int n = static_cast<int>(s.size());
    cout << "\nSolution for n = " << n << endl;
    for (int i = 1; i <= n; i++)
        cout << "\nrow " << i << " = " << s.peek(n - i + 1);
    cout << endl;
    while (!s.empty()) {
        cout << "\nrow " << s.size() << ((s.size() < 10)? " " : "") ;
        for (int i = 1; i <= n; i++)
            if (i == s.top())
                cout << " Q ";
            else
                cout << "   ";
        s.pop();
    }
    cout << "\ncol:  ";
    for (int i = 1; i <= n; i++)
        cout << ((i < 10)? " " : "") << i << " " ;
    cout << endl;
}

bool solution(int n) {
    
    bool success = false;
    stack<int> s;
    s.push(1);
    
    while (!success && !s.empty()) {
        if (!check(s)) {
            while (!s.empty() && (s.top() == n)) {
                s.top();
                s.pop();
            }
            if (!s.empty() && s.top() < n) {
                int temp = s.top();
                s.pop();
                s.push(temp + 1);
            }
        } else if (s.size() == n)
            success = true;
        else {
            s.push(1);
        }
    }
    
    if (success)
        printStack(s);
    else
        cout << "\nThere is no solution for n = " << n << endl;
    return success;
}


int main(int argc, const char * argv[]) {
    
    for (int i = 1; i <= 10; i++)
        solution(i);
    cout << endl;
    
    return 0;
}

/*
 

 Solution for n = 1

 row 1 = 1

 row 1  Q
 col:   1

 There is no solution for n = 2

 There is no solution for n = 3

 Solution for n = 4

 row 1 = 2
 row 2 = 4
 row 3 = 1
 row 4 = 3

 row 4        Q
 row 3  Q
 row 2           Q
 row 1     Q
 col:   1  2  3  4

 Solution for n = 5

 row 1 = 1
 row 2 = 3
 row 3 = 5
 row 4 = 2
 row 5 = 4

 row 5           Q
 row 4     Q
 row 3              Q
 row 2        Q
 row 1  Q
 col:   1  2  3  4  5

 Solution for n = 6

 row 1 = 2
 row 2 = 4
 row 3 = 6
 row 4 = 1
 row 5 = 3
 row 6 = 5

 row 6              Q
 row 5        Q
 row 4  Q
 row 3                 Q
 row 2           Q
 row 1     Q
 col:   1  2  3  4  5  6

 Solution for n = 7

 row 1 = 1
 row 2 = 3
 row 3 = 5
 row 4 = 7
 row 5 = 2
 row 6 = 4
 row 7 = 6

 row 7                 Q
 row 6           Q
 row 5     Q
 row 4                    Q
 row 3              Q
 row 2        Q
 row 1  Q
 col:   1  2  3  4  5  6  7

 Solution for n = 8

 row 1 = 1
 row 2 = 5
 row 3 = 8
 row 4 = 6
 row 5 = 3
 row 6 = 7
 row 7 = 2
 row 8 = 4

 row 8           Q
 row 7     Q
 row 6                    Q
 row 5        Q
 row 4                 Q
 row 3                       Q
 row 2              Q
 row 1  Q
 col:   1  2  3  4  5  6  7  8

 Solution for n = 9

 row 1 = 1
 row 2 = 3
 row 3 = 6
 row 4 = 8
 row 5 = 2
 row 6 = 4
 row 7 = 9
 row 8 = 7
 row 9 = 5

 row 9              Q
 row 8                    Q
 row 7                          Q
 row 6           Q
 row 5     Q
 row 4                       Q
 row 3                 Q
 row 2        Q
 row 1  Q
 col:   1  2  3  4  5  6  7  8  9

 Solution for n = 10

 row 1 = 1
 row 2 = 3
 row 3 = 6
 row 4 = 8
 row 5 = 10
 row 6 = 5
 row 7 = 9
 row 8 = 2
 row 9 = 4
 row 10 = 7

 row 10                   Q
 row 9           Q
 row 8     Q
 row 7                          Q
 row 6              Q
 row 5                             Q
 row 4                       Q
 row 3                 Q
 row 2        Q
 row 1  Q
 col:   1  2  3  4  5  6  7  8  9 10
 
 */
