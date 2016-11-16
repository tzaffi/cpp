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
#include <memory>

template<typename T>
void prettyPrint(T* A, unsigned i, unsigned j)
{
    for(unsigned it=i; it<j; ++it)
    {
        std::cout << it << ": " << A[it] << '\t';
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

template<typename T>
unsigned partition(T* A, unsigned i, unsigned j, bool print=false){
    unsigned pivotIndex = i + rand() % (j-i);
    T pivot(A[pivotIndex]);
    if(print)
    {
        std::cout << "Partitioning:" << std::endl;
        prettyPrint(A, i, j);
        std::cout << "Pivot = " << pivot << std::endl;
    }
    unsigned left = i, right = j-1;
    while(true)
    {
        while(A[left] < pivot && left < right)
            left++;
        while(A[right] > pivot && 0 < right)
            right--;
        if(left >= right)
            break;
        swap(A[left], A[right]);
        if(print)
        {
            std::cout << "left = " << left << "\t right = " << right << std::endl;
            prettyPrint(A, i, j);
        }
    }
    if(print)
    {
        std::cout << "FINISHED PARTITIONING:" << std::endl;
        prettyPrint(A, i, j);
        std::cout << "returning right = " << left << std::endl;
    }
    if(left >= right)
        return right;
}

int main(){
    std::srand(std::time(0));

    int A[] = {1, 2, 3, 4};
    prettyPrint(A, 0, 4);

    swap(A[0], A[3]);
    prettyPrint(A, 0, 4);

    std::unique_ptr<unsigned []> x = makeRandomArray(13);
    partition(x.get(), 0, 13, true);
}
