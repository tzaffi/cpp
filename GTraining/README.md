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

* [SortedArrayIterator](./SortedArrayIterator.cpp)
* [Merge Sort](./MergeSort.cpp)

1. Write a function that takes two vectors (or arrays), and a function object 
(and/or lambda and/or function pointer) and goes through the array
applying the function and collecting it into an output vector. Do this in
the most efficient manner.
1. Generalize this to write an iterator that does the same
1. Use this to implement merge sort
1. **EC**: Generalize using variadic templates to multiple array merge.

### Call a `protected` member from a super-class

```$C++
struct protectedHi {
protected:
    void hi() { cout << "Hello from <protectedHi>\n"; }
}
```

### What happens when a constructor throws?
E.g.
```C++
struct A{
    A(){
       cout << "Hello from A\n";
       throw 1;
    }
    ~A(){ cout << "Goodbye from A\n"; }
}
struct B{
    B(){ cout << "Hellow from B\n"; }
    ~B(){ cout << "Goodbye from B\n"; }
}
struct C{
    C() a = A(), b = B(){ cout << "Hellow from C\n"; }
    ~C(){ cout << "Goodbye from C\n"; }
private:
    A a;
    B b;
}
```

### Reference variable re-assignment
What happens here:
```C++
int x = 1, y = 2;
int& r = x; //there's supposed to be an ampersand after `int`... no sure why we don't see it
r = 3;
cout << x << y << r; 
```

### Review the *Big Six* functions that automatically get created for every class
Which functions get created, what keywords do you use? (`default` ?`delete`?)

```C++
obj()
obj(const obj&)
obj(obj&&)
obj& operator= (const obj&)
obj& operator= (obj&&)
~obj()
```
Yes, use **delete** and **default**

### Review how to get a uniformly distributed double
Is it something like:

~~double leftBound = -1.0, rightBound = 1.0;~~
~~double r = rand(leftBound, rightBound);~~


And how do you provide a good random seed?

ANSWER:
```C++
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_real_distribution<double> distribution(0.0, total);
double rndNumber = distribution(generator);
```
In other words:

1. Create a seed using a semi random process such as the current time or `random_device`
1. Use it to seed a random generator engine
1. Define a distribution (*independent of the generator*)
1. Provide the generator as the distribution's argument

* Write a program that is given a vector of weights, and a function
`isReady()` which tells you whether a particular weight should be used,
randomly chooses a weight in proportion to its size (if it's *ready*)

A: cf. `pickRandomElementFromSubset.cpp`


## Questions that come up as I'm doing this

1. Clarify the differences between lambda's, function objects,
and function pointers.
1. Can a function accept all 3 kinds from #1 and deal correctly 
with them (possibly with a template)?
1. Figure out how to write an iterator in C++
1. What is the difference between *closure* and *capture* for C++ lambdas?
1. Do arrays have iterators in C++ 11? (there's the begin() and end())?
1. Clarify how protected members get visibility in sub-classes.
1. Clarify if `struct` subclasses act any differently from `class` sub-clasess.
