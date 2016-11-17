//
// Created by zeph on 11/15/16.
// Just want to work on algorithm design.
//
// QuickSort(A, begin, end)
// INPUT: smart array of comparables A[i, j)   {using mathematical notation for clopen interval)
// OUTPUT: in-place sorting of this vector using quicksort
//
// PSEUDOCODE:
/*
 * QuickSort( A[i,j) ):
 *      if j <= i + 1 then return // array of size 0 or 1
 *      k = Partition( A[i,j) )
 *      QuickSort(A[i,k))
 *      QuickSort(A[k+1,j))
 *
 * // Partition will work by
 * // * Placing pivot in left-most position i
 * // LOOP INVARIANT:
 * // o   A[i] == pivot
 * // o   A[i+1,left) < pivot or is EMPTY
 * // o   A[left,right) >= pivot or is EMPTY
 * 
 * The algorithm stops when right == j. At that point the loop invariant guarantees
 * that the entire set -excluding the pivot- is partitioned. and we simply need
 * to exchange(A[i], A[left-1]).
 *
 * To obtain the loop invariant at the beginning we:
 * set: left = i+1
 *      while(A[left] < pivot) left++
 *      right = left + 1
 *      while(A[right] >= pivot) right++
 *
 * (NOTE: in the case that A[i+1] >= pivot we'll get left = i+1, and right > left)
 *
 * To maintain the loop invariant at each step:
 *      swap(A[left], A[right])
 *      while(A[right] >= pivot) right++
 *      left++
 *
 * ALTOGETHER:
 *
 * Partition( A[i,j) ):
 *      if j-i <= 1 return i (at most 1 element, so return the only relevant index)
 *
 *      pivotIdx = Random[i,j)
 *      swap(A[i], A[pivotIdx])
 *      pivot = A[i]
 *      left = i+1, right = left+1
 *      while(left < j and A[left] < pivot) left++
 *      right = left + 1
 *      while(right < j and A[right] >= pivot) right++
 *   
 *      // what if right >= j?
 *      // then either left == j in which case A[i+1,j) > pivot
 *      // or left < j in which case we're also done...
 *      if right >= j:
 *          swap(A[i], A[left-1])
 *          return left-1
 *      //NOW PROCEED WITH THE INDUCTIVE STEPS:
 *      while(true)
 *          swap(A[left], A[right])
 *          while(right < j and A[right] >= pivot) right++
 *          left++
 *          if right >= j:
 *              swap(A[i], A[left-1])
 *              return left-1
 */
#include <iostream>
#include <cassert>

template<typename T>
void prettyPrint(T* A, unsigned i, unsigned j, bool starPivot=false)
{
    std::string pivChar(starPivot ? "*" : "");
    for(unsigned it=i; it<j; ++it)
    {
        std::cout << pivChar << it << pivChar << ": " << A[it] << '\t';
        pivChar = "";
    }
    std::cout << std::endl;
}

template<typename T>
void swap(T& x, T&y)
{
    T tmp(x);
    x = y;
    y = tmp;
}

std::unique_ptr<unsigned []> makeRandomArray(size_t N)
{
    std::unique_ptr<unsigned []> result{new unsigned[N]};
    for(unsigned i=0; i<N; i++){
        result[i] = rand() % N;
    }
    return result;
}


// returns the pivotIndex
template<typename T>
unsigned partition(T* A, unsigned i, unsigned j, bool print=false)
{
    if(j-i <= 1)
        return i;

    unsigned pivotIndex = i + rand() % (j-i);
    swap(A[i], A[pivotIndex]);
    T pivot(A[i]);

    if(print)
    {
        std::cout << "Partitioning:" << std::endl;
        prettyPrint(A, i, j, true);
        std::cout << "Pivot = " << pivot << std::endl;
    }

    unsigned left = i+1, right;
    while(left<j && A[left]<pivot) ++left;
    right = left + 1;
    while(right<j && A[right]>=pivot) ++right;

    while(right < j)
    {
        swap(A[left], A[right]);
        while (right < j && A[right] >= pivot) ++right;
        left++;
    }
    swap(A[i], A[left-1]);
    if(print)
    {
        std::cout << "FINISHED PARTITIONING:" << std::endl;
        prettyPrint(A, i, j);
        std::cout << "returning left - 1 = " << left - 1 << std::endl;
    }
    return left-1;
}

template<typename T>
void QuickSort(T* A, unsigned i, unsigned j, bool print=false)
{
    if(print)
    {
        std::cout << "BEGIN QuickSorting: ";
        prettyPrint(A, i, j);
    }
    unsigned pivotIndex = partition(A, i, j, print);
    if (pivotIndex > i + 1)
        QuickSort(A, i, pivotIndex, print);
    if (pivotIndex < j - 1)
        QuickSort(A, pivotIndex+1, j, print);
    if(print)
    {
        std::cout << "FINISH QuickSorting: ";
        prettyPrint(A, i, j);
    }
}

template<typename T>
void assertIsPartitioned(T* A, unsigned pivotIndex, unsigned i, unsigned j) {
    T pivot = A[pivotIndex];
    for(; i<pivotIndex; i++)
        assert(A[i] < pivot);
    for(i=pivotIndex+1; i<j; i++)
        assert(A[i] >= pivot);
}

template<typename T>
void assertIsSorted(T* A, unsigned i, unsigned j) {
    for(; i<j-1; i++)
        //assert(A[i] <= A[i+1]);
        if(A[i] > A[i+1]){
            std::cout << "UH OH! " << std::endl;
            prettyPrint(A, i, j);
            assert(A[i] <= A[i+1]);
        }
}

void testPartition(unsigned maxSize, unsigned iterationsPerSize)
{
    std::clock_t start;
    start = std::clock();

    for(unsigned i=1; i<=maxSize; i++)
    {
        for(unsigned j=0; j<iterationsPerSize; j++)
        {
            std::unique_ptr<unsigned []> x = makeRandomArray(i);
            unsigned pivotIndex = partition(x.get(), 0, i);
            assertIsPartitioned(x.get(), pivotIndex, 0, i);
        }
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Successfully ran " << maxSize << " * " << iterationsPerSize
              << " = " << maxSize*iterationsPerSize << " PARTITION tests in "
              << duration << "seconds" << std::endl;
}


void testQuickSort(unsigned maxSize, unsigned iterationsPerSize)
{
    std::clock_t start;
    start = std::clock();

    for(unsigned i=1; i<=maxSize; i++)
    {
        for(unsigned j=0; j<iterationsPerSize; j++)
        {
            std::unique_ptr<unsigned []> x = makeRandomArray(i);
            QuickSort(x.get(), 0, i);
            assertIsSorted(x.get(), 0, i);
        }
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Successfully ran " << maxSize << " * " << iterationsPerSize
              << " = " << maxSize*iterationsPerSize << " QUICKSORT tests in "
              << duration << "seconds" << std::endl;
}
int main(){
    std::srand(std::time(0));

    int A[] = {1, 2, 3, 4};
    prettyPrint(A, 0, 4);

    swap(A[0], A[3]);
    prettyPrint(A, 0, 4);

    std::unique_ptr<unsigned []> x = makeRandomArray(13);
    partition(x.get(), 0, 13, true);

    testPartition(100, 100);

    x = makeRandomArray(20);
    QuickSort(x.get(), 0, 20, true);

    testQuickSort(100, 100);
    testQuickSort(10000, 1);
}
