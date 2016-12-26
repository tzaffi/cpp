# Coding Exercise: Custom Sort A Large File

## Summary:

Write a command line program named “sortme” (with an appropriate executable file extension if
any) that will take in two parameters: an input filename and an output filename.
i.e. Running 

```
sortme FileA FileB
```
 
will result in reading in `FileA` and output to `FileB`.

The input file specified by the input filename will be a large text file having many lines of
text. Each line of the file is unique. The program will output the sorted lines to the new file
specified by the output filename.

The sort algorithm should be based off the number of occurrences of the letter “s” on the line in
ascending order. (That is, the line with the most number of “s” occurrences should appear at the
end of the output file.)

Assume the input file is of 100x the amount of working memory available to your program.
(That is, if the maximum amount of memory available to the process is 1GB, the file is 100GB in
size. Simply put, assume you will not be able to store the entire contents of the file in memory.)
Please submit the code in either Java, C, C++, C# or Python. Please keep external library usage
to a minimum. Feel free to create temporary files to assist in your efforts.
Code will be judged based on conciseness, readability, novelty and performance (both memory
and speed).

## Full Disclosure
The source code is mostly my own (especially the logic), 
except for various Stack-Overflow answer
snippets that related to proper STL and stream operator usage.

## My Approach
I was at first tempted to use the fact that the ordering criterion is very
simple -just count the number of S's. This lead to a possible hybrid bucket
sort approach where I would bucket sort upto a certain cutoff in the number of s's,
and use a different approach to sort the rest.

However, the overhead of this approach were overly complex so that I was not
confident that I could pull it off in the time alotted. So I opted for a simpler,
if less efficient, but more generic approach: external merge sort.

### Sorting
Memory is the big problem here. A production solution requires investigating
whether std::sort on a vector, `multi_set` (whose memory overhead is predictable) or a 
custom memory-capped sorting approach (such as quicksort) are best to use.
If there were sufficient time, I would use quicksort.

* Note on **uniqueness of lines**: the fact that each line was unique,
did not allow us to use `set` instead of `multi_set` because
of the custom comparator whose implied equality would only care of the S content.

### Assumptions
The scenario outlined the assumption that the textfile was around 100x the
working memory available. Ideally, the working memory should be provided
as a compile time variable. To simplify the coding, I created a constant
`MAX_MEMORY` (set to 1GB) which will need to be modified as needed before
compiling. The program is designed to handle any text file size as we make 
sure to only read one line at a time. However, this leads to as assumption:

* There is no line in the file that whose size is greater than 1/4 of the 
amount of working memory. Unfortunately, the existence of such a line
would crash the program.

### USAGE
```
sortme pathToInputFile.txt pathToOutputFile.txt

# EG:
sortme veryLarge.txt veryLargeButSorted.txt
```
There is also an optional 3rd parameter for specifying working memory:
```
sortme pathToInputFile.txt pathToOutputFile.txt MAX_WORKING_MEMORY

# EG (for 1GB working memory = 1024^3 bytes):
sortme veryLarge.txt veryLargeButSorted.txt 1073741824
```