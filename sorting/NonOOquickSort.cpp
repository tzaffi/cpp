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
 * // * Any item between i+1 and left is in the left partition (strictly less than pivot)
 * // * Any item between left and right is in the right partition (greater or equal to pivot)
 * // (NOTE: A[left] is unknown, this is just a place-holder)
 * // At each step increment right and re-commit to  LOOP INVARIANT by:
 * //    * If A[right-1] >= pivot ... there's nothing to do and we're done
 * //    * ELSE: swap A[left] <---> A[right] and increment left <--- left+1 thus reinsuring loop invariant
 * // Since everything to the left
 * Partition( A[i,j) ):
 *      pivotIdx = Random[i,j)
 *      pivot = A[pivotIdx]
 *      swap(A[i], A[pivotIdx])
 *      left = i
 *      for right = i+1 to j:
 *          //enter with LOOP INVARIANT IN PLACE
 *          if (A[right] < pivot)
 *              swap(A[left], A[right])
 *              left = left+1
 *          while(A[left] < pivot and left < right)
 *              left = left + 1
 *          while(A[right] >= pivot and left < right)
 *              right = right -1
 *          if(left >= right) break
 *          swap(A[left], A[right]
 *      return left
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