//
// Created by zeph on 12/4/16.
//

#include <vector>

/**
 * Given two sorted Vectors, use the merge sort iteration method to iterate through the arrays
 * and reduce from the union by applying the choice() function. For example, if:
 *   o choice = insertLeft() - always pick the left param (useful for union)
 *   o choice = insertLeftIfEqual() - pick the left param if both are equal (useful for intersection)
 *   o choice = insertLeftUnique() - always pick the left param if it is different from the previous insertion
 * @tparam T - a comparable type
 * @param a - an array of T's sorted in ascending order
 * @param b - an array of T's sorted in ascending order
 * @param insertChoice - a function that given T-values left and right and an aggregator vector to insert the
 * choice into, provides logic for picking a choice and then inserts that choice into the aggreagator.
 * Returns true iff a choice was inserted (false in the case when nothing was inserted)
 * @param finishEarly - optional parameter defaulting to false. Set true if you want to finish early such
 * as in the case of intersection.
 * @return the aggregator vector from the reduction operator that was applied to a and b
 */
template <typename T>
inline std::vector<T> iterateAndReduce(const std::vector<T>& a,
                                       const std::vector<T>& b,
                                       bool insertChoice(const T& left, const T& right, std::vector<T>& aggregator),
                                       bool finishEarly = false){
    std::vector<T> aggregator;
    auto i = a.cbegin(), j = b.cbegin();
    while(i != a.cend() && j != b.cend()){
        while(i != a.cend() && j != b.cend() && *i == *j){
            insertChoice(*i, *j, aggregator);
            ++i, ++j;
        }
        while(i != a.cend() && j != b.cend() && *i < *j){
            insertChoice(*i, *j, aggregator);
            ++i;
        }
        while(i != a.cend() && j != b.cend() && *j < *i){
            insertChoice(*j, *i, aggregator);
            ++j;
        }
    }
    if(!finishEarly){
        while(i != a.cend()){
            insertChoice(*i, *a.cbegin(), aggregator);
            ++i;
        }
        while(j != b.cend()){
            insertChoice(*j, *b.cbegin(), aggregator);
            ++j;
        }
    }
    return aggregator;
}

namespace Choosers{
    template <typename T>
    bool insertLeftIfEqual(const T& left, const T& right, std::vector<T>& aggregator){
        if(left == right){
            aggregator.push_back(left);
            return true;
        }
        return false;
    }
}