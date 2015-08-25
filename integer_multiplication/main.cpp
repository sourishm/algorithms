#include <iostream>
#include <fstream>
#include <deque>
#include <queue>

using namespace std;

const string file1 = "file1.txt";
const string file2 = "file2.txt";

/* using reverse deque as stack */
typedef deque<int> stack;
typedef vector<queue<int>> Nqueue;

void pushStack(stack& stk, int& integer)
{
    /* push from back to use as a stack */
    stk.push_back(integer);
}

void printStack(stack& stk)
{
    /* iterate from reverse to print as a stack */
    for (auto it = stk.crbegin(); it < stk.crend(); it++) {
        cout << *it;
    }
    cout << endl;
}

bool readFile(const string& fileName, stack& stk)
{
    fstream file(fileName);
    char c;
    int integer;

    if (file.is_open()) {
        while (file.get(c) && (c != '\n')) {
            integer = static_cast<int>(c);
            integer -= 48; /* 0 is 48 */
            pushStack(stk, integer);
        }
        file.close();
        return true;
    }
    cout << "File not present" << endl;
    return false;
}

void multiply(Nqueue& Cqueue, stack& stackA, stack& stackB, stack& stackD)
{
    uint64_t i = 0, j, largestCn_size;

    /* iterate from reverse to use as a stack */
    /* create the Cn queues */
    for (auto itB = stackB.crbegin(); itB < stackB.crend(); itB++) {
        int b, carry = 0;
        b = *itB; cout << "b " << b << endl;
        queue<int>& q = Cqueue.at(i);
        uint64_t k;
        for (k = 0; k < i; k++) {
            q.push(0);
        }
        /* iterate from reverse to use as a stack */
        for (auto itA = stackA.crbegin(); itA < stackA.crend(); itA++) {
            int a, mul;
            a = *itA; cout << "a " << a << endl;
            mul = a*b;
            if (carry) {
                mul += carry;
                carry = 0;
            }
            if (mul / 10) {
                if (i < (Cqueue.size() - 1)) {
                    carry = mul / 10;
                    mul %= 10;
                }
            }
            cout << "axb " << mul << endl;
            q.push(mul);
        }
        i++;
    }
    /* add each i th digit of the Cn queues */
    largestCn_size = stackA.size() + stackB.size() - 1;
    int carry = 0;
    for (i = 0; i < largestCn_size; i++) {
        int sum = 0;
        for (j = 0; j < stackB.size(); j++) {
            queue<int>& q = Cqueue.at(j);
            if (q.size() > 0) {
                sum += q.front();
                q.pop();
            }
        }
        if (carry) {
            sum += carry;
            carry = 0;
        }
        if (sum / 10) {
            if (i < (largestCn_size - 1)) {
                carry = sum / 10;
                sum %= 10;
            }
        }
        pushStack(stackD, sum);
    }
}

int main()
{
    stack stackA, stackB, stackD;
    if (readFile(file1, stackA) && readFile(file2, stackB)) {
        printStack(stackA);
        printStack(stackB);
    }
    Nqueue Cqueue(stackB.size());
    multiply(Cqueue, stackA, stackB, stackD);
    printStack(stackD);
    return 0;
}