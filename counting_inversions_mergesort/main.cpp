#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const string fileName = "IntegerArray.txt";

/* T is numeric, int, float, long, etc */
template <typename T>
bool readFile(vector<T>& vec)
{
    T number;
    fstream file(fileName);

    if (file.is_open()) {
        while (file >> number) {
            vec.push_back(number);
        }
        file.close();
        return true;
    } else {
        cout << "File not present" << endl;
        return false;
    }
}

template <typename T>
void print_vector(vector<T>& vec)
{
    cout << "Printing the vector ..." << endl;
    for (auto& x : vec) {
        cout << x << endl;
    }
}

template <typename T>
uint64_t mergeCountInv(vector<T>& vec, uint64_t left, uint64_t mid, uint64_t right)
{
    uint64_t inversions = 0;
    uint64_t size_v1, size_v2;
    size_v1 = (mid - left) + 1;
    size_v2 = right - mid;
    /* create temporary vectors */
    vector<T> vector1(size_v1), vector2(size_v2);

    /* copy data into temporary vectors */
    copy_n((vec.cbegin()+left), size_v1, vector1.begin());
    copy_n((vec.cbegin()+mid+1), size_v2, vector2.begin());

    /* merge the temporary vectors back into the original vector */
    uint64_t i = 0, j = 0, k = left;
    while ((i < vector1.size()) && (j < vector2.size())) {
        if (vector1.at(i) <= vector2.at(j)) {
            vec.at(k) = vector1.at(i);
            i++;
        } else {
            inversions += vector1.size() - i;
            vec.at(k) = vector2.at(j);
            j++;
        }
        k++;
    }
    /* copy the remaining elements */
    if (i < vector1.size()) {
        copy_n((vector1.cbegin() + i),
               (vector1.size() - i),
               (vec.begin() + k));
    }
    if (j < vector2.size()) {
        copy_n((vector2.cbegin() + j),
               (vector2.size() - j),
               (vec.begin() + k));
    }
    return inversions;
}

template <typename T>
uint64_t mergeSortCountInv(vector<T>& vec, uint64_t left, uint64_t right)
{
    uint64_t inversions = 0;
    if (left < right) {
        /* find the middle point */
        uint64_t mid = (left + right) / 2;
        /* recursively sort the left */
        inversions = mergeSortCountInv(vec, left, mid);
        /* recursively sort the right */
        inversions += mergeSortCountInv(vec, (mid+1), right);
        /* merge the sorted vectors */
        inversions += mergeCountInv(vec, left, mid, right);
    }
    return inversions;
}

int main()
{
    vector<int> vec;

    if (readFile(vec)) {
        //cout << "Input vector ..." << endl;
        //print_vector(vec);
        cout << "Number of inversions = " << mergeSortCountInv(vec, 0, (vec.size() - 1)) << endl;
        //cout << "After merge sort ..." << endl;
        //print_vector(vec);
    }

    return 0;
}