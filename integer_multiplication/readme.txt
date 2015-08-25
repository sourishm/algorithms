Problem statement -

Given 2 very large numbers, A and B, output the result of A x B.


Solution -

First let us see how number multiplication works in its simplest form.

Example :-

A = 12
B = 13

A x B

 12
x13
-----
 36
120
------
156

We multiply each digit of B with each digit of A and finally do a column wise addition of the digits to achieve the result.


Definition of approach -

Input numbers = A and B, A has m digits and B has n digits

    A = a(m)a(m-1)a(m-2)....a(0)
    B = b(n)b(n-1)b(n-2)....b(0)

Number A can be seen as comprised of m digits, ranging from 0 to m.
Number B can be seen as comprised of n digits, ranging from 0 to n.

If A = 123, then a(0) = 3(units digit), a(1) = 2(tenths digit), a(2) = 1(hundredth digit) and so on.









A x B =

    a(m)a(m-1)....a(0)
    b(n)b(n-1)......b(0)
    ----------------------
    a(m)xb(0) a(m-1)xb(0) ....a(1)xb(0) a(0)xb(0)
    a(m)xb(1) a(m-1)xb(1)....a(0)xb(0)  0
    a(m)xb(2)..........a(0)xb(0) 0      0

Let each such row of resultant numbers be C, such that

C(0) = a(m)xb(0) a(m-1)xb(0) ... a(1)xb(0) a(0)xb(0)

So, we are multiplying a digit of B with each digit of A to get the number C.
Thus, there will be n such C numbers, since B has n digits.

C(0), C(1), ..., c(n)

Let C(n)[i] be the i th digit of the C(n) number.
For every C(j), j ranging from 0 to n, the units digit in C(j), which is C(j)[0] is shifted j times.
Thus the C(0) is shifted 0 times, C(1) is shifted 1 times, ..., C(n) is shifted (n-1) times.

Let D be the result of the multiplication of A x B.
Then each digit of D, i.e 
D[i] = C(0)[i] + C(1)[i] + C(2)[i] + ...+ C(n)[i] = summation of n {C(n)[i]}


High level algorithm and data structures

Step 1. Since the input numbers are stored in a file. Read the input one character at a time and start storing it in a stack.
Stack is a LIFO data structure. Thus the units location will be stored on the top of the stack. The multiplication operation is started from the units location and then moves forward.
Read the input numbers into two stacks A and B.

Step 2. Now each digit of B needs to be multiplied will all the digits of A. The result is stored in C(n). C can be a queue. Queue is FIFO data structure. Since the lower order digits are applied to the multiplication operation first and then again the lower order digits are going to be used for the subsequent addition, FIFO is used.
The implementation of shifting of zeros for each queue is left out of the high level algorithm.
The implementation of carry forward the tenths term for each a x b multiplication is left out the high level algorithm.
The code will contain the details.

for (i = 0 to n)
{
    b = B.pop();
    queue q = C[i];
    q.push(0), i times;
    for (j = 0 to m)
    {
        a = A.pop();
        q.push(b x a);
    }
}

Step 3. Add each i th digit of each C[n] queues. Store the result of the sum in a stack D. The highest order digit will be on top of the stack. Each queue has at least m digits. The largest queue will have (m+n-1) digits, since the largest queue will be shifted by (n-1) zeros.

for (i = 0 to (m+n-1))
{
    for (j = i to n)
    {
        queue q = C[j];
        if (q.size() > 0)
        {
            sum += q.pop();
        }
    }
    D.push(sum);
}

Step 4. Print the stack D.
