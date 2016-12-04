# Google Training Sessions

## IsCompleteCycle
Given an array of relative indexes, determine if the array defines a complete cycle.

### Examples
1. Input: [1, 1, 1, 1]
    * Output: true (because 0 --> 1 --> 2 --> 3 --> 0)
2. Input: [1, 2, 3]
    * Output: false (because 0 --> 2 --> 2)
3. Input: [7]
    * Output: true (because 0 --> 0)
4. Input: []
    * Output: false (because a cycle cannot be empty)

### C++ Signature
bool IsCompleteCycle(const std::vector<long>& cArray);


## Follow up from another interview:

### Iterating through two sorted lists in *O*(*m+n*)

1. Write a function that takes two vectors (or arrays), and a function object 
(and/or lambda and/or function pointer) and goes through the array
applying the function and collecting it into an output vector. Do this in
the most efficient manner.
1. Generalize this to write an iterator that does the same

### Call a `protected` member from a super-clas

### What happens when a constructor throws

### Reference variable re-assignment

## Questions that come up as I'm doing this

1. Clarify the differences between lambda's, function objects,
and function pointers.
1. Can a function accept all 3 kinds from #1 and deal correctly 
with them (possibly with a template)?
1. Figure out how to write an iterator in C++
1. What is the difference between *closure* and *capture* for C++ lambdas?
1. Do arrays have iterators in C++ 11? (there's the begin() and end())?
