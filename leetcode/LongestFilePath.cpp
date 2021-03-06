//
// Created by zeph on 11/28/16.
//

/*
Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2
 containing a file file.ext.

The string
 "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
The directory dir contains two sub-directories subdir1 and subdir2.
 subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1.
 subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute
 path to a file within our file system. For example, in the second example
 above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its
 length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the
 longest absolute path to file in the abstracted file system. If there is
 no file in the system, return 0.

Note:
The name of a file contains at least a . and an extension.
>>>>The name of a directory or sub-directory will not contain a . <<<< .
Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path
 aaaaaaaaaaaaaaaaaaaaa/sth.png.

 */

#include <iostream>


using namespace std;

class Solution {
public:
    int lengthLongestPath(string input, int level=0) {
        string splitter = "\n";
        for(int i=0; i<level; i++){ splitter += '\t'; }
        int tree1end = input.find(splitter);
        while(tree1end != string::npos){
            if(input[tree1end+level+1] != '\t'){ break; }
            tree1end = input.find(splitter, tree1end+level+1);
        }
        int res;
        if(tree1end == string::npos){
            res = lengthLongestPathInTree(input, level);
//            cout << "\nlongest in forest " << input << " is " << res;
            return res;
        }
        res = max(lengthLongestPathInTree(input.substr(0,tree1end), level),
                   lengthLongestPath(input.substr(tree1end+1), level));
//        cout << "\nlongest in forest " << input << " is " << res;
        return res;
    }

private:
    int lengthLongestPathInTree (string tree, int level) {
        int rootEnd = tree.find('\n');
        if (rootEnd == string::npos){
            //if not a file, return 0!
            return tree.find('.') != string::npos ? tree.size() - level : 0;
        }
        int subCase = lengthLongestPath(tree.substr(rootEnd+1),level+1);
        return subCase ? rootEnd - level + 1 + subCase : subCase;
    }
};

int main(){
    cout << "Longest Absolute File Path\n\n";

    Solution s;
    string pathString = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
    cout << "\n\nThe longest path in \n" << pathString << "\n is\n " << s.lengthLongestPath(pathString);

    pathString = "a";
    cout << "\n\nThe longest path in \n" << pathString << "\n is\n " << s.lengthLongestPath(pathString);

    pathString ="a\n\tb\n\t\tc";
    cout << "\n\nThe longest path in \n" << pathString << "\n is\n " << s.lengthLongestPath(pathString);
    return 0;
}