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